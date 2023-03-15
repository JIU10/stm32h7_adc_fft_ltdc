#include "ctiic.h"


uint16_t fac_us=400;						    //不论是否使用OS,fac_us都需要使用
void delay_us(u32 nus)
{
    u32 ticks;
    u32 told,tnow,tcnt=0;
    u32 reload=SysTick->LOAD;				//LOAD的值
    ticks=nus*fac_us; 						//需要的节拍数
    told=SysTick->VAL;        				//刚进入时的计数器值
    while(1)
    {
        tnow=SysTick->VAL;
        if(tnow!=told)
        {
            if(tnow<told)tcnt+=told-tnow;	//这里注意一下SYSTICK是一个递减的计数器就可以了.
            else tcnt+=reload-tnow+told;
            told=tnow;
            if(tcnt>=ticks)break;			//时间超过/等于要延迟的时间,则退出.
        }
    };
}




//控制I2C速度的延时
void CT_Delay(void)
{
    delay_us(150);
//    HAL_Delay(1);
}


//电容触摸芯片IIC接口初始化
void CT_IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOH_CLK_ENABLE();			//开启GPIOH时钟
    __HAL_RCC_GPIOI_CLK_ENABLE();			//开启GPIOI时钟

    GPIO_Initure.Pin = GPIO_PIN_6;          //PH6
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_OD; //开漏输出
    GPIO_Initure.Pull = GPIO_PULLUP;        //上拉
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;   //高速
    HAL_GPIO_Init(GPIOH, &GPIO_Initure);    //初始化

    GPIO_Initure.Pin = GPIO_PIN_3;          //PI3
    HAL_GPIO_Init(GPIOI, &GPIO_Initure);    //初始化
}

//产生IIC起始信号
void CT_IIC_Start(void)
{
    CT_IIC_SDA(1);
    CT_IIC_SCL(1);
    CT_Delay();
    CT_IIC_SDA(0);//START:when CLK is high,DATA change form high to low
    CT_Delay();
    CT_IIC_SCL(0);//钳住I2C总线，准备发送或接收数据
    CT_Delay();
}

//产生IIC停止信号
void CT_IIC_Stop(void)
{
    CT_IIC_SDA(0);
    CT_Delay();
    CT_IIC_SCL(1);
    CT_Delay();
    CT_IIC_SDA(1);//STOP:when CLK is high DATA change form low to high
    CT_Delay();
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 CT_IIC_Wait_Ack(void)
{
    u8 ucErrTime = 0;
    u8 rack = 0;

    CT_IIC_SDA(1);
    CT_Delay();
    CT_IIC_SCL(1);
    CT_Delay();

    while (CT_READ_SDA)
    {
        ucErrTime++;

        if (ucErrTime > 250)
        {
            CT_IIC_Stop();
            rack = 1;
            break;
        }

        CT_Delay();
    }

    CT_IIC_SCL(0);//时钟输出0
    CT_Delay();
    return rack;
}

//产生ACK应答
void CT_IIC_Ack(void)
{
    CT_IIC_SDA(0);
    CT_Delay();
    CT_IIC_SCL(1);
    CT_Delay();
    CT_IIC_SCL(0);
    CT_Delay();
    CT_IIC_SDA(1);
    CT_Delay();
}
//不产生ACK应答
void CT_IIC_NAck(void)
{
    CT_IIC_SDA(1);
    CT_Delay();
    CT_IIC_SCL(1);
    CT_Delay();
    CT_IIC_SCL(0);
    CT_Delay();
}
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答
void CT_IIC_Send_Byte(u8 txd)
{
    u8 t;

    for (t = 0; t < 8; t++)
    {
        CT_IIC_SDA((txd & 0x80) >> 7);
        CT_Delay();
        CT_IIC_SCL(1);
        CT_Delay();
        CT_IIC_SCL(0);
        txd <<= 1;
    }

    CT_IIC_SDA(1);
}
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK
u8 CT_IIC_Read_Byte(unsigned char ack)
{
    u8 i, receive = 0;

    for (i = 0; i < 8; i++ )
    {
        receive <<= 1;
        CT_IIC_SCL(1);
        CT_Delay();

        if (CT_READ_SDA)receive++;

        CT_IIC_SCL(0);
        CT_Delay();

    }

    if (!ack)
        CT_IIC_NAck();//发送nACK
    else
        CT_IIC_Ack(); //发送ACK

    return receive;
}




























