// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: STM32F407

#include "ui.h"
#include "ui_helpers.h"
#include "lv_font.h"
#include "math.h"
#include "main.h"
//#include "dac.h"
//#include "dma.h"
#define MY_ICON_RILI "\xEE\x98\x83"

#define PI 3.1415926



///////////////////// VARIABLES ////////////////////






lv_obj_t * ui_Screen1;
lv_obj_t * list_1;
lv_obj_t * lable_thd;
lv_obj_t * lable_chthd;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
#error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
#error "#error LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void list_1_event_cb(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    uint8_t obj_num=lv_dropdown_get_selected(obj);
    if(code == LV_EVENT_VALUE_CHANGED){
        char buf[32];
        lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
        switch (obj_num) {
            /*
             * PH5---->Switch1  1
             * PA3---->Switch2  2
             * PA4---->Switch3  3
             * PH4---->Switch4  4
             * */
            case 0:

                HAL_GPIO_WritePin(Switch_1_GPIO_Port,Switch_1_Pin,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(Switch_2_GPIO_Port,Switch_2_Pin,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(Switch_3_GPIO_Port,Switch_3_Pin,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(Switch_4_GPIO_Port,Switch_4_Pin,GPIO_PIN_RESET);
                break;
            case 1:
                HAL_GPIO_WritePin(Switch_1_GPIO_Port,Switch_1_Pin,GPIO_PIN_SET);
                HAL_GPIO_WritePin(Switch_2_GPIO_Port,Switch_2_Pin,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(Switch_3_GPIO_Port,Switch_3_Pin,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(Switch_4_GPIO_Port,Switch_4_Pin,GPIO_PIN_RESET);
                break;
            case 2:
                HAL_GPIO_WritePin(Switch_1_GPIO_Port,Switch_1_Pin,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(Switch_2_GPIO_Port,Switch_2_Pin,GPIO_PIN_SET);
                HAL_GPIO_WritePin(Switch_3_GPIO_Port,Switch_3_Pin,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(Switch_4_GPIO_Port,Switch_4_Pin,GPIO_PIN_RESET);
                break;
            case 3:
                HAL_GPIO_WritePin(Switch_1_GPIO_Port,Switch_1_Pin,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(Switch_2_GPIO_Port,Switch_2_Pin,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(Switch_3_GPIO_Port,Switch_3_Pin,GPIO_PIN_SET);
                HAL_GPIO_WritePin(Switch_4_GPIO_Port,Switch_4_Pin,GPIO_PIN_RESET);
                break;
            case 4:
                HAL_GPIO_WritePin(Switch_1_GPIO_Port,Switch_1_Pin,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(Switch_2_GPIO_Port,Switch_2_Pin,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(Switch_3_GPIO_Port,Switch_3_Pin,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(Switch_4_GPIO_Port,Switch_4_Pin,GPIO_PIN_SET);
                break;
            default:;

        }
    }

}

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(void)
{
    //STYLE

    static lv_style_t btn_style;
    lv_style_init(&btn_style);
    lv_style_set_bg_color(&btn_style,lv_color_white());
    lv_style_set_text_color(&btn_style, lv_palette_darken(LV_PALETTE_BLUE_GREY,3));

    static lv_style_t btn_style_pressed;
    lv_style_init(&btn_style_pressed);
    lv_style_set_bg_color(&btn_style_pressed, lv_color_hex(0x14a73c));
    lv_style_set_radius(&btn_style_pressed,5);

    static lv_style_t line_style;
    lv_style_init(&line_style);
    lv_style_set_line_width(&line_style,2);
    lv_style_set_line_color(&line_style, lv_palette_main(LV_PALETTE_BLUE));

    // ui_Screen1

    ui_Screen1 = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);


}




void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    lv_disp_load_scr(ui_Screen1);

    lv_obj_t * label;
    label= lv_label_create(ui_Screen1);
    lv_label_set_text(label,"Wave Change");
    lv_obj_set_style_text_font(label,&lv_font_MiSans_Normal_17,LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_align(label,LV_ALIGN_CENTER,-145,-85);

    list_1 = lv_dropdown_create(ui_Screen1);
    lv_obj_set_pos(list_1, 292, 235);
    lv_obj_set_width(list_1, 160);
    lv_dropdown_set_options(list_1, "正常波形\n底部失真\n顶部失真\n双边失真\n交越失真");
    lv_obj_t  * list_option= lv_dropdown_get_list(list_1);
    lv_obj_set_style_text_font(list_1,&lv_font_MiSans_Normal_15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(list_option,&lv_font_MiSans_Normal_15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_event_cb(list_1, list_1_event_cb, LV_EVENT_READY, NULL);

    lable_thd= lv_label_create(ui_Screen1);
    lv_label_set_text(lable_thd,"THD:");
    lv_obj_set_style_text_font(lable_thd,&lv_font_MiSans_Normal_17,LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_align(lable_thd,LV_ALIGN_CENTER,30,-45);

    lable_chthd=lv_label_create(ui_Screen1);
    lv_label_set_text(lable_chthd,"0%");
    lv_obj_set_style_text_font(lable_chthd,&lv_font_MiSans_Normal_17,LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_align(lable_chthd,LV_ALIGN_CENTER,80,-45);


}

