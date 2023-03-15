/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "dma2d.h"
#include "ltdc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "ui.h"
#include "arm_math.h"
#include "arm_const_structs.h"



/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define ADC1_BUFFER_SIZE 1024	//ADC1用了4通道, 存32组, 方便做平均
#define sqrt2 1.4142135623730950488
//32字节对齐(地址+大小)
//adc1_data指定到 AXI SRAM 的0x24000000
//adc3_data指定到 SRAM4 的0x38000000
ALIGN_32BYTES (uint16_t adc1_data[ADC1_BUFFER_SIZE]) __attribute__((section(".ARM.__at_0x24000000")));

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t ADC_STOP=0;
uint32_t fft_max_index;
float32_t maxValue;
float32_t fft_input[ADC1_BUFFER_SIZE*2];
float32_t fft_output[ADC1_BUFFER_SIZE];

float32_t THD;
char thd_text[30]={0};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void GetTHD();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_FMC_Init();
  MX_USART1_UART_Init();
  MX_DMA2D_Init();
  MX_LTDC_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
    SDRAM_InitSequence();
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    ui_init();
    HAL_TIM_Base_Start(&htim3);
//    HAL_TIM_Base_Start_IT(&htim3);

    if(HAL_ADCEx_Calibration_Start(&hadc1,ADC_CALIB_OFFSET,ADC_SINGLE_ENDED)!=HAL_OK)
    {
        printf("hadc1 error with HAL_ADCEx_Calibration_Start\r\n");
        Error_Handler();
    }
    if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc1_data, ADC1_BUFFER_SIZE) != HAL_OK)
    {
        printf("hadc1 error with HAL_ADC_Start_DMA\r\n");
        Error_Handler();
    }

//    arm_status status;
//    status = ARM_MATH_SUCCESS;


    printf("start\r\n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      lv_task_handler();

      for (int i = 0; i < ADC1_BUFFER_SIZE; i++) {
          fft_input[i * 2] = (adc1_data[i] * 2.0 / 65535.0-1.0) * 3.3;
          fft_input[2 * i + 1] = 0;
      }
      for(int i=0;i<1024;i++) {
          printf("%f,%d\n",fft_input[i*2],i);
      }

//      lv_task_handler();
      arm_cfft_f32(&arm_cfft_sR_f32_len1024,fft_input,0,1);
      arm_cmplx_mag_f32(fft_input,fft_output,ADC1_BUFFER_SIZE);
      arm_max_f32(fft_output,ADC1_BUFFER_SIZE,&maxValue,&fft_max_index);
      lv_task_handler();

      for(int i=0;i<512;i++) {
          if (i) {
              fft_output[i] = fft_output[i] / 512.0;
//                  printf("%lf,%d\n",fft_output[i],i);
          } else fft_output[i] = fft_output[i] / 1024.0;
      }

      GetTHD();
      sprintf(thd_text,"%.3f %%",THD);
      lv_label_set_text(lable_chthd,thd_text);
//      HAL_ADCEx_Calibration_Start(&hadc1,ADC_CALIB_OFFSET,ADC_SINGLE_ENDED);
      HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc1_data, ADC1_BUFFER_SIZE);
      lv_task_handler();


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSE);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */



void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
{
    /* Invalidate Data Cache to get the updated content of the SRAM on the first half of the ADC converted data buffer */
    if(hadc->Instance == ADC1) {
//        SCB_InvalidateDCache_by_Addr((uint32_t *) &adc1_data[0], ADC1_BUFFER_SIZE);
    }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{

    /* Invalidate Data Cache to get the updated content of the SRAM on the second half of the ADC converted data buffer */
    if(hadc->Instance == ADC1) {
//        ADC_STOP=1;
        HAL_ADC_Stop_DMA(&hadc1);

//        lv_task_handler();
//        SCB_InvalidateDCache_by_Addr((uint32_t *) &adc1_data[ADC1_BUFFER_SIZE/2], ADC1_BUFFER_SIZE);
    }
}

void GetTHD(){
    //计算第8个点，第16个点，第32个点，第64个点，第128个点
    THD=sqrt((fft_output[16]/sqrt2)*(fft_output[16]/sqrt2)+(fft_output[32]/sqrt2)*(fft_output[32]/sqrt2)+(fft_output[64]/sqrt2)*(fft_output[64]/sqrt2)+(fft_output[128]/sqrt2)*(fft_output[128]/sqrt2)+(fft_output[256]/sqrt2)*(fft_output[256]/sqrt2))/((fft_output[8]/sqrt2)*(fft_output[8]/sqrt2));
}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
