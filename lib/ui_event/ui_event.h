#ifndef _ui_H
#define _ui_H


#include"lvgl.h"










#define SWIPE_THRESHOLD 30 // 最小滑动距离阈值
#define SAMPLE_COUNT 256




extern char voltageStr[20], currentStr[20], powerStr[20], mAHStr[20];
void power_init(void);
// void ui_event_Screen1(lv_event_t *e);

// void ui_event_Image1(lv_event_t *e);

// void ui_event_Screen2(lv_event_t *e);

// void ui_event_Image2(lv_event_t *e);
void pinmap_init(void);
void pwm_init(void);
void power_init(void);

void anim_cb1(lv_obj_t *obj, int32_t v);
void anim_cb2(lv_obj_t *obj, int32_t v);
void anim_end_callback();

void btn1_event_cb(lv_event_t *e);
void btn2_event_cb(lv_event_t *e);
void btn3_event_cb(lv_event_t *e);




// void keyboard_event_handler(lv_event_t *e);
// void fretext_event_handler(lv_event_t *e);
// void dutytext_event_handler(lv_event_t *e);
// void clear_keyboard_event_handler(lv_event_t *e);

void slider_event_cb(lv_event_t *e);




// char batStr[20];








LV_IMG_DECLARE(ui_img_game3_png);
LV_IMG_DECLARE(Exlink_png);
LV_IMG_DECLARE(pinmap_png);
LV_IMG_DECLARE(power_png);
LV_IMG_DECLARE(pwm_png);
LV_IMG_DECLARE(usarthelper_png);
LV_IMG_DECLARE(i2c_png);
LV_IMG_DECLARE(voltmeter_png);
LV_IMG_DECLARE(DSO_png);
LV_IMG_DECLARE(wireless_png);
LV_IMG_DECLARE(readme_png);
LV_IMG_DECLARE(pwmint_png);
LV_IMG_DECLARE(FREcounter_png);
LV_IMG_DECLARE(kobe_png);

void create_boot_animation(void);
void ui1_init(void);
void ui_Screen1_screen_init(void);

// void pinmap_init(void);
// void power_init(void);
// void pwm_init(void);



#endif