#ifndef _init_H
#define _init_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>

#include <lvgl.h>
#include <TFT_eSPI.h>



/*Change to your screen resolution*/
static const uint16_t screenWidth  = 480;
static const uint16_t screenHeight = 328;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];




static lv_group_t *groupRect; //组



void initIndev(void);
void initDisp(void);
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data );
static void my_key_read(lv_indev_drv_t * indev_driver,lv_indev_data_t * data );
void my_disp_flush( lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p );
void initFunction(void);//初始化函数

#endif