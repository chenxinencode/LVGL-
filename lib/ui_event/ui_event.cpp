#include "ui_event.h"

#include "Wire.h"
#include "AHT20.h"
float temperature;
float humidity;
AHT20 humiditySensor;
const int SCLPin = 3;
const int SDAPin = 1;
extern lv_indev_t *indev_key;
// 定义线条的起始和结束位置
#define LINE_X1 60
#define LINE_X2 60
#define LINE_Y1 45
#define LINE_Y2 115
static lv_obj_t *btn1;
static lv_obj_t *btn2;
static lv_obj_t *btn3;

static lv_obj_t *bat_label;

static lv_obj_t *ui_Screen1;
static lv_obj_t *ui_Label1;
static lv_obj_t *ui_Image1;
static lv_obj_t *ui_Screen2;
static lv_obj_t *ui_Image2;
static lv_obj_t *label1;
static lv_obj_t *label2;
static lv_obj_t *label3;
static lv_obj_t *label4;
static lv_obj_t *chart5;
static lv_obj_t *panel;
static lv_obj_t *btn;
static lv_obj_t *label;
static lv_obj_t *voltmeter_chart5;
static lv_obj_t *volt_chart;
static lv_obj_t *cur_chart;
static lv_obj_t *screen_1;
static int32_t touch_start_x;
static int32_t touch_start_y;


lv_obj_t *poweron_label;
lv_obj_t *fre;
lv_obj_t *duty;
lv_obj_t *fre_keyboard;
lv_obj_t *duty_keyboard;

static lv_group_t *group;
// lv_obj_t *i2c_extarea;
// lv_obj_t *i2con;
// lv_obj_t *uart_extarea;
// lv_obj_t *wireless_uart_extarea;
lv_obj_t *pwm_btn;
// lv_obj_t *uart_btn;
// lv_obj_t *uart_list;
// lv_obj_t *wireless_uart_list;
// lv_obj_t *wireless_uart_btn;

lv_timer_t *updatelabel_timer1;
lv_timer_t *updatelabel_timer2;
lv_timer_t *updatelabel_timer3;

lv_timer_t *adddata_timer;
lv_timer_t *adddata_timer2;

lv_timer_t *slider_update_timer;

// lv_timer_t *FRE_label_update_timer;
static lv_obj_t *slider;
// 创建样式对象
static lv_style_t style_rect;





void update_slider_timer(lv_timer_t *timer)
{
    if (lv_obj_has_state(btn1, LV_STATE_FOCUSED))
    {
        lv_slider_set_value(slider, 3, LV_ANIM_OFF);
    }
    if (lv_obj_has_state(btn2, LV_STATE_FOCUSED))
    {
        lv_slider_set_value(slider, 2, LV_ANIM_OFF);
    }
    if (lv_obj_has_state(btn3, LV_STATE_FOCUSED))
    {
        lv_slider_set_value(slider, 1, LV_ANIM_OFF);
    }
    
    // float volt = analogRead(2);
    // float bat = volt / 4095 * 6.6;
    // if (bat >= 3.95)
    // {
    //     lv_obj_set_pos(bat_label, 260, 196);
    //     lv_label_set_text(bat_label, LV_SYMBOL_CHARGE);
    // }
    // if (bat < 3.95 && bat >= 3.7)
    // {
    //     lv_obj_set_pos(bat_label, 251, 196);
    //     lv_label_set_text(bat_label, LV_SYMBOL_BATTERY_FULL);
    // }
    // if (bat < 3.7 && bat >= 3.4)
    // {
    //     lv_obj_set_pos(bat_label, 251, 196);
    //     lv_label_set_text(bat_label, LV_SYMBOL_BATTERY_3);
    // }
    // if (bat < 3.4 && bat >= 3)
    // {
    //     lv_obj_set_pos(bat_label, 251, 196);
    //     lv_label_set_text(bat_label, LV_SYMBOL_BATTERY_2);
    // }
    // if (bat < 3 && bat >= 2.7)
    // {
    //     lv_obj_set_pos(bat_label, 251, 196);
    //     lv_label_set_text(bat_label, LV_SYMBOL_BATTERY_1);
    // }
    // if (bat < 2.6)
    // {
    //     lv_obj_set_pos(bat_label, 251, 196);
    //     lv_label_set_text(bat_label, LV_SYMBOL_BATTERY_EMPTY);
    // }
}

void ui_Screen1_screen_init(void) // 创建主界面
{
    int unarea = 0;//左侧不能触摸宽度
    screen_1 = lv_scr_act();//null页面无显示
    lv_obj_clear_flag(screen_1, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_width(screen_1, 320);
    lv_obj_set_height(screen_1, 320);
    lv_obj_set_pos(screen_1,160,0);
    lv_obj_set_style_border_width(screen_1, 0, LV_PART_MAIN);

    lv_obj_clean(screen_1);
    lv_obj_set_style_bg_color(screen_1, lv_color_hex(0x000000), 0);

    panel = lv_obj_create(screen_1);
    lv_obj_set_size(panel, 230, 240);
    lv_obj_set_pos(panel, 10, 0);
    lv_obj_set_style_bg_color(panel, lv_color_hex(0x000000), 0);//设置背景颜色 黑色
    lv_obj_set_style_border_width(panel, 0, 0);
    lv_obj_remove_style(panel, 0, LV_PART_SCROLLBAR);
    lv_obj_set_flex_flow(panel, LV_FLEX_FLOW_COLUMN); // 垂直排列子对象
    lv_obj_set_scroll_dir(panel, LV_DIR_VER);

    lv_style_init(&style_rect);
    // 设置边框的颜色和粗细
    lv_style_set_border_color(&style_rect, lv_color_hex(0xFF0000)); // 红色边框
    lv_style_set_border_width(&style_rect, 3);                      // 5 像素粗细
    lv_style_set_bg_color(&style_rect, lv_color_hex(0x000000));     // 白色背景
    lv_style_set_radius(&style_rect, 20);                           // 圆角半径

    // 设置聚焦状态的边框
    static lv_style_t focused_style;
    lv_style_init(&focused_style);
    lv_style_set_border_color(&focused_style, lv_color_hex(0xFFD700));//淡黄色
    lv_style_set_border_width(&focused_style, 5);

    btn1 = lv_btn_create(panel);
    lv_obj_set_size(btn1, 215, 80);
    lv_obj_align(btn1, LV_ALIGN_OUT_RIGHT_TOP, 0, 0);
    lv_obj_add_style(btn1, &style_rect, 0); // 将样式应用到矩形上
    lv_obj_add_style(btn1, &focused_style, LV_STATE_FOCUSED);
    lv_obj_add_event_cb(btn1, btn1_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *btn1_label = lv_label_create(btn1);
    lv_obj_align(btn1_label, LV_ALIGN_OUT_RIGHT_MID, 0, 18);
    lv_label_set_text(btn1_label, "Pin Map");
    lv_obj_set_style_text_font(btn1_label, &lv_font_montserrat_20, 0);
    lv_obj_t *img1 = lv_img_create(btn1);
    lv_img_set_src(img1, &pinmap_png);                       // Replace with your image variable or path
    lv_obj_set_size(img1, LV_SIZE_CONTENT, LV_SIZE_CONTENT); // Set image size
    lv_obj_align(img1, LV_ALIGN_OUT_RIGHT_MID, 126, 0);      // Center the image within the button

    btn2 = lv_btn_create(panel);
    lv_obj_set_size(btn2, 215, 80);
    lv_obj_align(btn2, LV_ALIGN_OUT_RIGHT_TOP, 0, 0);
    lv_obj_add_style(btn2, &style_rect, 0); // 将样式应用到矩形上
    lv_obj_add_style(btn2, &focused_style, LV_STATE_FOCUSED);
    lv_obj_add_event_cb(btn2, btn2_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *btn2_label = lv_label_create(btn2);
    lv_obj_align(btn2_label, LV_ALIGN_OUT_RIGHT_MID, 0, 18);
    lv_label_set_text(btn2_label, "DC POWER");
    lv_obj_set_style_text_font(btn2_label, &lv_font_montserrat_20, 0);
    lv_obj_t *img2 = lv_img_create(btn2);
    lv_img_set_src(img2, &power_png);                        // Replace with your image variable or path
    lv_obj_set_size(img2, LV_SIZE_CONTENT, LV_SIZE_CONTENT); // Set image size
    lv_obj_align(img2, LV_ALIGN_OUT_RIGHT_MID, 126, 0);      // Center the image within the button

    btn3 = lv_btn_create(panel);
    lv_obj_set_size(btn3, 215, 80);
    lv_obj_align(btn3, LV_ALIGN_OUT_RIGHT_TOP, 0, 0);
    lv_obj_add_style(btn3, &style_rect, 0); // 将样式应用到矩形上
    lv_obj_add_event_cb(btn3, btn3_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_style(btn3, &focused_style, LV_STATE_FOCUSED);
    lv_obj_t *btn3_label = lv_label_create(btn3);
    lv_obj_align(btn3_label, LV_ALIGN_OUT_RIGHT_MID, 0, 18);
    lv_label_set_text(btn3_label, "PWM OUT");
    lv_obj_set_style_text_font(btn3_label, &lv_font_montserrat_20, 0);
    lv_obj_t *img3 = lv_img_create(btn3);
    lv_img_set_src(img3, &pwm_png);                          // Replace with your image variable or path
    lv_obj_set_size(img3, LV_SIZE_CONTENT, LV_SIZE_CONTENT); // Set image size
    lv_obj_align(img3, LV_ALIGN_OUT_RIGHT_MID, 126, 0);      // Center the image within the button

    

    lv_style_init(&style_rect);
    // 设置边框的颜色和粗细
    lv_style_set_border_color(&style_rect, lv_color_hex(0xFF0000)); // 红色边框
    lv_style_set_border_width(&style_rect, 3);                      // 5 像素粗细
    lv_style_set_bg_color(&style_rect, lv_color_hex(0x000000));     // 白色背景
    lv_style_set_radius(&style_rect, 20);                           // 圆角半径

    slider = lv_slider_create(screen_1);
    lv_obj_set_size(slider, 15, 90);
    lv_obj_set_pos(slider, 260, 30);
    lv_slider_set_range(slider, 1, 10);
    lv_slider_set_value(slider, 10, LV_ANIM_OFF);
    lv_obj_set_style_bg_opa(slider, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(slider, lv_color_hex(0xFF0000), LV_PART_KNOB);
    lv_obj_set_style_bg_color(slider, lv_color_hex(0x333333), LV_PART_MAIN);
    lv_obj_set_style_bg_color(slider, lv_color_hex(0x333333), LV_PART_INDICATOR);
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_ALL, NULL);//聚焦在对应的按钮上
    slider_update_timer = lv_timer_create(update_slider_timer, 300, NULL);//更新按钮是否聚焦  每隔0.3s会触发这个update_slider_timer函数
    lv_obj_update_snap(panel, LV_ANIM_OFF);

    //电池状态
    bat_label = lv_label_create(screen_1);
    lv_label_set_text(bat_label, " ");
    lv_obj_set_pos(bat_label, 251, 196);
    lv_obj_set_style_text_color(bat_label, lv_color_hex(0x32CD32), 0);//淡绿色
    lv_obj_set_style_text_font(bat_label, &lv_font_montserrat_26, 0);

    // group = lv_group_create();
    // lv_indev_set_group(indev_key, group);
    // lv_group_add_obj(group, btn1);
    // lv_group_add_obj(group, btn2);
    // lv_group_add_obj(group, btn3);

}


void humtem_setup()
{
  Wire1.begin(SDAPin,SCLPin); //有触控设备的时候必须得用Wire1,并在AHT20库里将所有的Wire替换成Wire1

  if (humiditySensor.begin() == false)
  {
      Serial.println("AHT20 not detected. Please check wiring. Freezing.");
      while (1);
  }
  Serial.println("AHT20 acknowledged.");
}

void humtem_loop()
{
  
  temperature = humiditySensor.getTemperature();
  humidity = humiditySensor.getHumidity();
    
}

void add_data(lv_timer_t *timer)
{
    humtem_setup();
    humtem_loop();
    lv_chart_set_next_value(volt_chart, (lv_chart_series_t *)timer->user_data, temperature);
    // lv_label_set_text(label1, voltageStr);
}

void add_data2(lv_timer_t *timer)
{

    lv_chart_set_next_value(cur_chart, (lv_chart_series_t *)timer->user_data, humidity);
    // lv_label_set_text(label1, voltageStr);
}


void update_label_timer1(lv_timer_t *timer)
{
    lv_obj_t *voltmeter_label1 = (lv_obj_t *)timer->user_data;
    lv_label_set_text(voltmeter_label1, voltageStr);
}

void update_label_timer2(lv_timer_t *timer)
{
    lv_obj_t *voltmeter_label2 = (lv_obj_t *)timer->user_data;
    lv_label_set_text(voltmeter_label2, currentStr);
}
void update_label_timer3(lv_timer_t *timer)
{
    lv_obj_t *voltmeter_label3 = (lv_obj_t *)timer->user_data;
    lv_label_set_text(voltmeter_label3, powerStr);
}

void btn1_event_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        if (slider_update_timer)
        {
            lv_timer_del(slider_update_timer); // 删除定时器1
            slider_update_timer = NULL;        // 清空指针以避免悬空指针
        }
        pinmap_init();
    }
}
void btn2_event_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (event_code == LV_EVENT_CLICKED)
    {   
        lv_obj_clean(lv_scr_act());
        if (slider_update_timer)
        {
            lv_timer_del(slider_update_timer); // 删除定时器1
            slider_update_timer = NULL;        // 清空指针以避免悬空指针
        }
        power_init();
    }
}

void btn3_event_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if (slider_update_timer)
    {
        lv_timer_del(slider_update_timer); // 删除定时器1
        slider_update_timer = NULL;        // 清空指针以避免悬空指针
    }
    if (event_code == LV_EVENT_CLICKED)
    {
        pwm_init();
    }
}



// 滑动条的事件回调
void slider_event_cb(lv_event_t *e)
{
    int value = lv_slider_get_value(slider); // 获取滑动条的值
    switch (4 - value)
    {
    case 1:
        lv_group_focus_obj(btn1);
        break;
    case 2:
        lv_group_focus_obj(btn2);
        break;
    case 3:
        lv_group_focus_obj(btn3);
        break;
    
    default:
        break;
    }
}
void anim_cb1(lv_obj_t *var, int32_t v)
{
    // 更新文本对象的位置
    lv_obj_set_x(var, v);
}

void anim_cb2(lv_obj_t *var, int32_t v)
{
    // 更新文本对象的位置
    lv_obj_set_y(var, v);
}

void anim_end_callback()
{

    ui_Screen1_screen_init();
}
void create_boot_animation(void)
{
    int unarea = 0;//左侧不能触摸宽度
    lv_obj_t *screen_1 = lv_scr_act();//null页面无显示
    lv_obj_clear_flag(screen_1, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_width(screen_1, 320);
    lv_obj_set_height(screen_1, 320);
    lv_obj_set_pos(screen_1,170,0);
    lv_obj_set_style_border_width(screen_1, 0, LV_PART_MAIN);
    //第一部分动画
    lv_obj_set_style_bg_color(screen_1, lv_color_hex(0x000000), 0);
    ui_Image1 = lv_img_create(screen_1);
    lv_img_set_src(ui_Image1, &ui_img_game3_png);
    lv_obj_set_width(ui_Image1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image1, LV_SIZE_CONTENT);
    lv_obj_set_pos(ui_Image1, 65, 50);
    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);
    // 初始化动画 横向移动的头像
    lv_anim_t anim1;
    lv_anim_init(&anim1);                                // 初始化动画结构体
    lv_anim_set_exec_cb(&anim1, (lv_anim_exec_xcb_t)anim_cb1);               // 设置动画回调函数
    lv_anim_set_var(&anim1, ui_Image1);                  // 设置动画作用的对象
    lv_anim_set_time(&anim1, 450);                       // 设置动画时间
    lv_anim_set_values(&anim1, 35, 80);                  // 设置运动轨迹
    lv_anim_set_path_cb(&anim1, lv_anim_path_overshoot); // 使用“overshoot”路径效果，使动画更加生动

    //第二部分动画 线条
    lv_obj_t *line = lv_line_create(screen_1);
    // 设置线条的起始和结束点
    static lv_point_t points[] = {{LINE_X1, LINE_Y1}, {LINE_X2, LINE_Y2}};
    lv_line_set_points(line, points, 2);

    // 设置线条的样式
    lv_obj_set_style_line_width(line, 10, 0);
    lv_obj_set_style_line_color(line, lv_color_hex(0xFF0000), 0); // 红色
    lv_obj_set_style_line_rounded(line, true, LV_PART_MAIN);
    lv_anim_t anim2;
    lv_anim_init(&anim2);                                      // 初始化动画结构体
    lv_anim_set_var(&anim2, line);                             // 设置动画作用的对象
    lv_anim_set_exec_cb(&anim2, (lv_anim_exec_xcb_t)anim_cb2); // 设置动画回调函数
    lv_anim_set_values(&anim2, -100, 15);                      // 设置运动轨迹
    lv_anim_set_time(&anim2, 450);                             // 设置动画时间
    lv_anim_set_path_cb(&anim2, lv_anim_path_overshoot);       // 动画路径线性
    //第三部分动画 exlink tool
    ui_Image2 = lv_img_create(screen_1);
    lv_img_set_src(ui_Image2, &Exlink_png);
    lv_obj_set_width(ui_Image2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Image2, LV_SIZE_CONTENT);
    lv_obj_set_pos(ui_Image2, 55, 150);
    lv_obj_add_flag(ui_Image2, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(ui_Image2, LV_OBJ_FLAG_SCROLLABLE);
    lv_anim_t anim3;
    lv_anim_init(&anim3);                                      // 初始化动画结构体
    lv_anim_set_var(&anim3, ui_Image2);                        // 设置动画作用的对象
    lv_anim_set_exec_cb(&anim3, (lv_anim_exec_xcb_t)anim_cb2); // 设置动画回调函数
    lv_anim_set_values(&anim3, 240, 150);                      // 设置运动轨迹
    lv_anim_set_time(&anim3, 450);                             // 动画时间
    lv_anim_set_path_cb(&anim3, lv_anim_path_overshoot);       // 动画路径线性
    //第四部分动画 回到主页
    lv_obj_t *label = lv_label_create(screen_1); /* 创建标签 */
    lv_label_set_text(label, "");                    /* 设置文本内容 */
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 0);    /* 设置位置 */
    lv_anim_t anim4;
    lv_anim_init(&anim4);           // 初始化动画结构体
    lv_anim_set_var(&anim4, label); // 设置动画作用的对象
    lv_anim_set_ready_cb(&anim4, (lv_anim_ready_cb_t)anim_end_callback);//回到主页
    lv_anim_set_exec_cb(&anim4, (lv_anim_exec_xcb_t)anim_cb2); // 设置动画回调函数
    lv_anim_set_values(&anim4, 30, 30);                        // 设置动画轨迹
    lv_anim_set_time(&anim4, 2000);                            // 设置动画时间为 2000 毫秒
    lv_anim_set_path_cb(&anim4, lv_anim_path_overshoot);       // 动画路径线性
    // lv_anim_start(&anim2); // 启动动画

    // 设置动画时间线
    lv_anim_timeline_t *anim_timeline = lv_anim_timeline_create();
    lv_anim_timeline_add(anim_timeline, 0, &anim1);
    lv_anim_timeline_add(anim_timeline, 150, &anim2);
    lv_anim_timeline_add(anim_timeline, 200, &anim3);
    lv_anim_timeline_add(anim_timeline, 200, &anim4);
    // 启动动画时间线
    lv_anim_timeline_start(anim_timeline);
}

void ui1_init(void)//初始化动画
{
    // 设置显示主题
    lv_theme_default_init(NULL, lv_color_hex(0x000000), lv_color_hex(0xFF0000), LV_THEME_DEFAULT_DARK, NULL);
    create_boot_animation();
}

// //按钮返回功能
// static void back_event_handler2(lv_event_t *e)
// {
//   lv_obj_t *obj = lv_event_get_target(e);
//   lv_obj_t *menu = (lv_obj_t *)lv_event_get_user_data(e);

//   if (lv_menu_back_btn_is_root(menu, obj))
//   {
//     // lv_obj_t *mbox1 = lv_msgbox_create(NULL, "Hello", "Root back btn click.", NULL, true);
//     // lv_obj_center(mbox1);
//     lv_scr_load_anim(screen_1, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, false);
//   }
// }
//触控返回功能
void event_handler_back(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_indev_t *indev = lv_indev_get_act(); // 获取当前激活的输入设备
    if (indev)
    {
        lv_point_t touch_point;
        lv_indev_get_point(indev, &touch_point); // 获取触摸点
        if (code == LV_EVENT_PRESSED)
        {
            touch_start_x = touch_point.x;
        }
        else if (code == LV_EVENT_RELEASED)
        {
            int32_t delta_x = touch_point.x - touch_start_x; // 检测向左滑动
            if (abs(delta_x) > SWIPE_THRESHOLD && delta_x > 0)
            {
               
                if (slider_update_timer)
                {
                    lv_timer_del(slider_update_timer); // 删除定时器1
                    slider_update_timer = NULL;        // 清空指针以避免悬空指针
                }
                if (updatelabel_timer1)
                {
                    lv_timer_del(updatelabel_timer1); // 删除定时器1
                    updatelabel_timer1 = NULL;        // 清空指针以避免悬空指针
                }
                if (updatelabel_timer2)
                {
                    lv_timer_del(updatelabel_timer2); // 删除定时器1
                    updatelabel_timer2 = NULL;        // 清空指针以避免悬空指针
                }
                if (updatelabel_timer3)
                {
                    lv_timer_del(updatelabel_timer3); // 删除定时器1
                    updatelabel_timer3 = NULL;        // 清空指针以避免悬空指针
                }
                if (adddata_timer)
                {
                    lv_timer_del(adddata_timer); // 删除定时器2
                    adddata_timer = NULL;        // 清空指针以避免悬空指针
                }
                // if (adddata_timer2)
                // {
                //     lv_timer_del(adddata_timer2); // 删除定时器2
                //     adddata_timer2 = NULL;        // 清空指针以避免悬空指针
                // }

                ui_Screen1_screen_init();
            }
        }
    }
}

void pwm_init(void)
{

    lv_obj_clean(lv_scr_act());
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000000), 0);
    lv_obj_add_event_cb(lv_scr_act(), event_handler_back, LV_EVENT_ALL, NULL);
    // lv_obj_add_event_cb(lv_scr_act(), longpress_event_handler_back, LV_EVENT_LONG_PRESSED, NULL);

    lv_obj_t *pwm = lv_img_create(lv_scr_act());
    lv_img_set_src(pwm, &pwmint_png);                       // Replace with your image variable or path
    lv_obj_set_size(pwm, LV_SIZE_CONTENT, LV_SIZE_CONTENT); // Set image size
    lv_obj_set_pos(pwm, 60, 110);

    lv_obj_t *rounded_rect1 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect1, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect1, 50, 35);
    lv_obj_set_pos(rounded_rect1, 26, 205);
    lv_obj_set_style_radius(rounded_rect1, 5, LV_PART_MAIN);                        // 圆角半径20
    lv_obj_set_style_bg_color(rounded_rect1, lv_color_hex(0x696969), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect1_label1 = lv_label_create(rounded_rect1);                // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect1_label1, "1");                                   // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect1_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect1_label1, LV_ALIGN_TOP_MID, 0, 2);      // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect1_label2 = lv_label_create(rounded_rect1); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect1_label2, "GND");                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect1_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect1_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形
    lv_obj_add_event_cb(lv_scr_act(), event_handler_back, LV_EVENT_ALL, NULL);

    lv_obj_t *rounded_rect2 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect2, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect2, 50, 35);
    lv_obj_set_pos(rounded_rect2, 76, 205);
    lv_obj_set_style_radius(rounded_rect2, 5, LV_PART_MAIN);                        // 圆角半径20
    lv_obj_set_style_bg_color(rounded_rect2, lv_color_hex(0x8B0000), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect2_label1 = lv_label_create(rounded_rect2);                // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect2_label1, "6");                                   // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect2_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect2_label1, LV_ALIGN_TOP_MID, 0, 2);      // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect2_label2 = lv_label_create(rounded_rect2); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect2_label2, "PWM");                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect2_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect2_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形
    lv_obj_add_event_cb(lv_scr_act(), event_handler_back, LV_EVENT_ALL, NULL);

    lv_obj_t *volt_label1 = lv_label_create(lv_scr_act()); // 将文本标签添加到圆角矩形上
    lv_label_set_text(volt_label1, "#FFD700 ROW1#");       // 设置文本内容
    lv_obj_set_style_text_font(volt_label1, &lv_font_montserrat_20, 0);
    lv_obj_set_pos(volt_label1, 200, 210);
    lv_label_set_recolor(volt_label1, true);

    fre = lv_textarea_create(lv_scr_act()); /* 创建文本框 */
    lv_textarea_set_placeholder_text(fre, "0-100K");
    lv_obj_set_style_text_font(fre, &lv_font_montserrat_20, LV_PART_MAIN); /* 设置字体 */
    lv_textarea_set_one_line(fre, true);                                   /* 设置单行模式 */
    lv_obj_set_size(fre, 100, 45);
    lv_obj_set_pos(fre, 92, 10);

    duty = lv_textarea_create(lv_scr_act()); /* 创建文本框 */
    lv_textarea_set_placeholder_text(duty, "0-100");
    lv_obj_set_style_text_font(duty, &lv_font_montserrat_20, LV_PART_MAIN); /* 设置字体 */
    lv_textarea_set_one_line(duty, true);                                   /* 设置单行模式 */
    lv_obj_set_size(duty, 100, 45);
    lv_obj_set_pos(duty, 92, 60);

    lv_obj_t *fre_label1 = lv_label_create(lv_scr_act()); // 将文本标签添加到圆角矩形上
    lv_label_set_text(fre_label1, "#FFD700 FRE#");        // 设置文本内容
    lv_obj_set_style_text_font(fre_label1, &lv_font_montserrat_20, 0);
    lv_obj_set_pos(fre_label1, 30, 20);
    lv_label_set_recolor(fre_label1, true);

    lv_obj_t *duty_label1 = lv_label_create(lv_scr_act()); // 将文本标签添加到圆角矩形上
    lv_label_set_text(duty_label1, "#87CEFA DUTY#");       // 设置文本内容
    lv_obj_set_style_text_font(duty_label1, &lv_font_montserrat_20, 0);
    lv_obj_set_pos(duty_label1, 30, 70);
    lv_label_set_recolor(duty_label1, true);

    lv_obj_t *fre_label2 = lv_label_create(lv_scr_act()); // 将文本标签添加到圆角矩形上
    lv_label_set_text(fre_label2, "#FFD700 Hz#");         // 设置文本内容
    lv_obj_set_style_text_font(fre_label2, &lv_font_montserrat_20, 0);
    lv_obj_set_pos(fre_label2, 200, 20);
    lv_label_set_recolor(fre_label2, true);

    lv_obj_t *duty_label2 = lv_label_create(lv_scr_act()); // 将文本标签添加到圆角矩形上
    lv_label_set_text(duty_label2, "#87CEFA %#");          // 设置文本内容
    lv_obj_set_style_text_font(duty_label2, &lv_font_montserrat_20, 0);
    lv_obj_set_pos(duty_label2, 200, 65);
    lv_label_set_recolor(duty_label2, true);

    fre_keyboard = lv_keyboard_create(lv_scr_act());
    duty_keyboard = lv_keyboard_create(lv_scr_act());
    lv_keyboard_set_mode(fre_keyboard, LV_KEYBOARD_MODE_NUMBER);
    lv_keyboard_set_mode(duty_keyboard, LV_KEYBOARD_MODE_NUMBER);
    lv_keyboard_set_textarea(fre_keyboard, fre);
    lv_keyboard_set_textarea(duty_keyboard, duty);
    lv_obj_add_flag(fre_keyboard, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(duty_keyboard, LV_OBJ_FLAG_HIDDEN);

    // lv_obj_add_event_cb(fre, fretext_event_handler, LV_EVENT_CLICKED, NULL);
    // lv_obj_add_event_cb(duty, dutytext_event_handler, LV_EVENT_CLICKED, NULL);
    // lv_obj_add_event_cb(fre_keyboard, clear_keyboard_event_handler, LV_EVENT_VALUE_CHANGED, NULL);  /* 设置键盘事件回调 */
    // lv_obj_add_event_cb(duty_keyboard, clear_keyboard_event_handler, LV_EVENT_VALUE_CHANGED, NULL); /* 设置键盘事件回调 */

    static lv_style_t pwm_style;
    lv_style_init(&pwm_style);
    lv_style_set_bg_color(&pwm_style, lv_color_hex(0xFF0000));
    lv_style_set_border_color(&pwm_style, lv_color_hex(0x000000));
    lv_style_set_border_width(&pwm_style, 2);

    pwm_btn = lv_btn_create(lv_scr_act());
    lv_obj_add_style(pwm_btn, &pwm_style, 0); // 将样式应用到矩形上
    lv_obj_set_size(pwm_btn, 69, 50);
    lv_obj_set_pos(pwm_btn, 230, 30);
    // lv_obj_add_event_cb(pwm_btn, pwm_btn_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *pwm_btn_label = lv_label_create(pwm_btn);
    lv_obj_set_style_text_color(pwm_btn_label, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(pwm_btn_label, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(pwm_btn_label, "OPEN");
    lv_obj_set_style_text_font(pwm_btn_label, &lv_font_montserrat_20, 0);
}

void power_init(void)
{
    lv_obj_clean(lv_scr_act());
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000000), 0);
    lv_obj_add_event_cb(lv_scr_act(), event_handler_back, LV_EVENT_ALL, NULL);
    // lv_obj_add_event_cb(lv_scr_act(), longpress_event_handler_back, LV_EVENT_LONG_PRESSED, NULL);
    // lv_obj_add_event_cb(lv_scr_act(), back_event_handler2, LV_EVENT_CLICKED, menu);//根目录返回按键 

    //  创建电流电压电功率标签
    lv_obj_t *volt = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_color(volt, lv_color_hex(0xFF0000), 0);
    lv_obj_set_style_text_font(volt, &lv_font_montserrat_28, 0);
    lv_obj_set_pos(volt, 40, 10);

    lv_obj_t *cur = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_color(cur, lv_color_hex(0x00FF7F), 0);
    lv_obj_set_style_text_font(cur, &lv_font_montserrat_28, 0);
    lv_obj_set_pos(cur, 40, 35);

    lv_obj_t *watt = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_color(watt, lv_color_hex(0x00FFFF), 0);
    lv_obj_set_style_text_font(watt, &lv_font_montserrat_28, 0);
    lv_obj_set_pos(watt, 40, 60);

    //定时给标签更新数据电流电压电功率
    updatelabel_timer1 = lv_timer_create(update_label_timer1, 100, volt);
    updatelabel_timer2 = lv_timer_create(update_label_timer2, 100, cur);
    updatelabel_timer3 = lv_timer_create(update_label_timer3, 100, watt);
    //创建单位标签 V A W伏安瓦
    lv_obj_t *V = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_font(V, &lv_font_montserrat_28, 0);
    lv_obj_set_pos(V, 126, 10);
    lv_label_set_text(V, "#FF0000 V#"); // 设置文本内容
    lv_label_set_recolor(V, true);

    lv_obj_t *A = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_font(A, &lv_font_montserrat_28, 0);
    lv_obj_set_pos(A, 126, 35);
    lv_label_set_text(A, "#00FF7F A#"); // 设置文本内容
    lv_label_set_recolor(A, true);

    lv_obj_t *W = lv_label_create(lv_scr_act());
    lv_obj_set_style_text_font(W, &lv_font_montserrat_28, 0);
    lv_obj_set_pos(W, 121, 60);
    lv_label_set_text(W, "#00FFFF W#"); // 设置文本内容
    lv_label_set_recolor(W, true);
    //电压电路表格
    volt_chart = lv_chart_create(lv_scr_act());
    lv_obj_set_style_bg_color(volt_chart, lv_color_hex(0x303030), LV_PART_MAIN);
    lv_obj_set_style_line_color(volt_chart, lv_color_hex(0x696969), LV_PART_MAIN);
    lv_obj_set_size(volt_chart, 260, 50);
    lv_obj_set_pos(volt_chart, 30, 100);
    lv_chart_set_point_count(volt_chart, 15);
    lv_chart_set_axis_tick(volt_chart, LV_CHART_AXIS_PRIMARY_Y, 4, 2, 3, 2, false, 30);
    lv_chart_set_range(volt_chart, LV_CHART_AXIS_PRIMARY_Y, 10, 40);
    lv_obj_set_style_width(volt_chart, 0, LV_PART_INDICATOR);
    lv_obj_set_style_height(volt_chart, 0, LV_PART_INDICATOR);
    lv_chart_set_update_mode(volt_chart, LV_CHART_UPDATE_MODE_SHIFT);
    lv_chart_series_t *ser1 = lv_chart_add_series(volt_chart, lv_color_hex(0xFF0000), LV_CHART_AXIS_PRIMARY_Y);
    adddata_timer = lv_timer_create(add_data, 1000, ser1);
    lv_chart_refresh(volt_chart);

    cur_chart = lv_chart_create(lv_scr_act());
    lv_obj_set_style_bg_color(cur_chart, lv_color_hex(0x303030), LV_PART_MAIN);
    lv_obj_set_style_line_color(cur_chart, lv_color_hex(0x696969), LV_PART_MAIN);
    lv_obj_set_size(cur_chart, 260, 50);
    lv_obj_set_pos(cur_chart, 30, 153);
    lv_chart_set_point_count(cur_chart, 15);
    lv_chart_set_axis_tick(cur_chart, LV_CHART_AXIS_PRIMARY_Y, 4, 2, 3, 2, false, 30);
    lv_chart_set_range(cur_chart, LV_CHART_AXIS_PRIMARY_Y, 50, 55);
    lv_obj_set_style_width(cur_chart, 0, LV_PART_INDICATOR);
    lv_obj_set_style_height(cur_chart, 0, LV_PART_INDICATOR);
    lv_chart_set_update_mode(cur_chart, LV_CHART_UPDATE_MODE_SHIFT);
    lv_chart_series_t *ser2 = lv_chart_add_series(cur_chart, lv_color_hex(0x00FF7F), LV_CHART_AXIS_PRIMARY_Y);
    adddata_timer2 = lv_timer_create(add_data2, 1000, ser2);//添加图标数据
    lv_chart_refresh(cur_chart);

    // 设置聚焦状态的边框
    static lv_style_t focused_style;
    lv_style_init(&focused_style);
    lv_style_set_border_color(&focused_style, lv_color_hex(0xFFD700));
    lv_style_set_border_width(&focused_style, 3);

    static lv_style_t powerbtn_style;
    lv_style_init(&powerbtn_style);
    lv_style_set_bg_color(&powerbtn_style, lv_color_hex(0x000000));
    lv_style_set_border_color(&powerbtn_style, lv_color_hex(0x808080));
    lv_style_set_border_width(&powerbtn_style, 2);
    //电源符号
    lv_obj_t *poweron = lv_btn_create(lv_scr_act());
    lv_obj_set_size(poweron, 41, 83);
    lv_obj_set_pos(poweron, 249, 10);
    lv_obj_add_style(poweron, &powerbtn_style, 0); // 将样式应用到矩形上
    lv_obj_add_style(poweron, &focused_style, LV_STATE_FOCUSED);
    // lv_obj_add_event_cb(poweron, poweronbtn_event_cb, LV_EVENT_CLICKED, NULL);
    poweron_label = lv_label_create(poweron);
    lv_obj_set_style_text_color(poweron_label, lv_color_hex(0xFF0000), 0);
    lv_obj_align(poweron_label, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(poweron_label, LV_SYMBOL_POWER);
    lv_obj_set_style_text_font(poweron_label, &lv_font_montserrat_28, 0);

    //加号
    lv_obj_t *VUP = lv_btn_create(lv_scr_act());
    lv_obj_set_size(VUP, 40, 40);
    lv_obj_set_pos(VUP, 203, 10);
    lv_obj_add_style(VUP, &powerbtn_style, 0); // 将样式应用到矩形上
    lv_obj_add_style(VUP, &focused_style, LV_STATE_FOCUSED);
    // lv_obj_add_event_cb(VUP, VUPbtn_event_cb, LV_EVENT_CLICKED, NULL);

    // lv_obj_add_style(poweron, &focused_style, LV_STATE_FOCUSED);
    // lv_obj_add_event_cb(poweron, btn1_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *VUP_label = lv_label_create(VUP);
    lv_obj_set_style_text_color(VUP_label, lv_color_hex(0x87CEEB), 0);
    lv_obj_align(VUP_label, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(VUP_label, LV_SYMBOL_PLUS);
    lv_obj_set_style_text_font(VUP_label, &lv_font_montserrat_24, 0);

    //减号
    lv_obj_t *VDOWN = lv_btn_create(lv_scr_act());
    lv_obj_set_size(VDOWN, 40, 40);
    lv_obj_set_pos(VDOWN, 203, 51);
    lv_obj_add_style(VDOWN, &powerbtn_style, 0); // 将样式应用到矩形上
    lv_obj_add_style(VDOWN, &focused_style, LV_STATE_FOCUSED);
    // lv_obj_add_event_cb(VDOWN, VDOWNbtn_event_cb, LV_EVENT_CLICKED, NULL);

    // lv_obj_add_style(poweron, &focused_style, LV_STATE_FOCUSED);
    // lv_obj_add_event_cb(poweron, btn1_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *VDOWN_label = lv_label_create(VDOWN);
    lv_obj_set_style_text_color(VDOWN_label, lv_color_hex(0x87CEEB), 0);
    lv_obj_align(VDOWN_label, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(VDOWN_label, LV_SYMBOL_MINUS);
    lv_obj_set_style_text_font(VDOWN_label, &lv_font_montserrat_24, 0);

    //11v
    lv_obj_t *V11 = lv_btn_create(lv_scr_act());
    lv_obj_set_size(V11, 42, 26);
    lv_obj_set_pos(V11, 155, 10);
    lv_obj_add_style(V11, &powerbtn_style, 0); // 将样式应用到矩形上
    lv_obj_add_style(V11, &focused_style, LV_STATE_FOCUSED);
    // lv_obj_add_event_cb(V11, V11btn_event_cb, LV_EVENT_CLICKED, NULL);

    // lv_obj_add_style(poweron, &focused_style, LV_STATE_FOCUSED);
    // lv_obj_add_event_cb(poweron, btn1_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *V11_label = lv_label_create(V11);
    lv_obj_set_style_text_color(V11_label, lv_color_hex(0xFFD700), 0);
    lv_obj_align(V11_label, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(V11_label, "11V");
    lv_obj_set_style_text_font(V11_label, &lv_font_montserrat_20, 0);

    //5v
    lv_obj_t *V5 = lv_btn_create(lv_scr_act());
    lv_obj_set_size(V5, 42, 26);
    lv_obj_set_pos(V5, 155, 37);
    lv_obj_add_style(V5, &powerbtn_style, 0); // 将样式应用到矩形上
    lv_obj_add_style(V5, &focused_style, LV_STATE_FOCUSED);
    // lv_obj_add_event_cb(V5, V5btn_event_cb, LV_EVENT_CLICKED, NULL);

    // lv_obj_add_style(poweron, &focused_style, LV_STATE_FOCUSED);
    // lv_obj_add_event_cb(poweron, btn1_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *V5_label = lv_label_create(V5);
    lv_obj_set_style_text_color(V5_label, lv_color_hex(0xFFD700), 0);
    lv_obj_align(V5_label, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(V5_label, "5V");
    lv_obj_set_style_text_font(V5_label, &lv_font_montserrat_20, 0);

    //3v
    lv_obj_t *V3 = lv_btn_create(lv_scr_act());
    lv_obj_set_size(V3, 42, 26);
    lv_obj_set_pos(V3, 155, 64);
    lv_obj_add_style(V3, &powerbtn_style, 0); // 将样式应用到矩形上
    lv_obj_add_style(V3, &focused_style, LV_STATE_FOCUSED);
    // lv_obj_add_event_cb(V3, V3btn_event_cb, LV_EVENT_CLICKED, NULL);

    // lv_obj_add_style(poweron, &focused_style, LV_STATE_FOCUSED);
    // lv_obj_add_event_cb(poweron, btn1_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t *V3_label = lv_label_create(V3);
    lv_obj_set_style_text_color(V3_label, lv_color_hex(0xFFD700), 0);
    lv_obj_align(V3_label, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(V3_label, "3V3");
    lv_obj_set_style_text_font(V3_label, &lv_font_montserrat_18, 0);

    // group = lv_group_create();
    // lv_indev_set_group(indev_keypad, group);
    // lv_group_add_obj(group, poweron);
    // lv_group_add_obj(group, VUP);
    // lv_group_add_obj(group, VDOWN);
    // lv_group_add_obj(group, V11);
    // lv_group_add_obj(group, V5);
    // lv_group_add_obj(group, V3);
    //底下gnd1
    lv_obj_t *rounded_rect1 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect1, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect1, 50, 35);
    lv_obj_set_pos(rounded_rect1, 26, 205);
    lv_obj_set_style_radius(rounded_rect1, 5, LV_PART_MAIN);                        // 圆角半径20
    lv_obj_set_style_bg_color(rounded_rect1, lv_color_hex(0x696969), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect1_label1 = lv_label_create(rounded_rect1);                // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect1_label1, "1");                                   // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect1_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect1_label1, LV_ALIGN_TOP_MID, 0, 2);      // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect1_label2 = lv_label_create(rounded_rect1); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect1_label2, "GND");                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect1_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect1_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形
    lv_obj_add_event_cb(lv_scr_act(), event_handler_back, LV_EVENT_ALL, NULL);
    //底下out2
    lv_obj_t *rounded_rect2 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect2, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect2, 50, 35);
    lv_obj_set_pos(rounded_rect2, 76, 205);
    lv_obj_set_style_radius(rounded_rect2, 5, LV_PART_MAIN);                        // 圆角半径20
    lv_obj_set_style_bg_color(rounded_rect2, lv_color_hex(0x8B0000), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect2_label1 = lv_label_create(rounded_rect2);                // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect2_label1, "2");                                   // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect2_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect2_label1, LV_ALIGN_TOP_MID, 0, 2);      // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect2_label2 = lv_label_create(rounded_rect2); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect2_label2, "OUT");                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect2_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect2_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形
    lv_obj_add_event_cb(lv_scr_act(), event_handler_back, LV_EVENT_ALL, NULL);

    lv_obj_t *volt_label1 = lv_label_create(lv_scr_act()); // 将文本标签添加到圆角矩形上
    lv_label_set_text(volt_label1, "#FFD700 ROW1#");       // 设置文本内容
    lv_obj_set_style_text_font(volt_label1, &lv_font_montserrat_20, 0);
    lv_obj_set_pos(volt_label1, 200, 210);
    lv_label_set_recolor(volt_label1, true);
}

void pinmap_init(void)
{

    lv_obj_clean(lv_scr_act());
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000000), 0);
    lv_obj_add_event_cb(lv_scr_act(), event_handler_back, LV_EVENT_ALL, NULL);
    // lv_obj_add_event_cb(lv_scr_act(), longpress_event_handler_back, LV_EVENT_LONG_PRESSED, NULL);

    lv_obj_t *name_label1 = lv_label_create(lv_scr_act());         // 将文本标签添加到圆角矩形上
    lv_label_set_text(name_label1, "#FFD700 ROW1:MCU and power#"); // 设置文本内容
    lv_obj_set_style_text_font(name_label1, &lv_font_montserrat_20, 0);
    lv_obj_set_pos(name_label1, 30, 26);
    lv_label_set_recolor(name_label1, true);

    lv_obj_t *name_label2 = lv_label_create(lv_scr_act());           // 将文本标签添加到圆角矩形上
    lv_label_set_text(name_label2, "#00FFFF ROW2:DLA and DAPlink#"); // 设置文本内容
    lv_obj_set_style_text_font(name_label2, &lv_font_montserrat_20, 0);
    lv_obj_set_pos(name_label2, 30, 60);
    lv_label_set_recolor(name_label2, true);

    lv_obj_t *rounded_rect1 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect1, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect1, 21, 65);
    lv_obj_set_pos(rounded_rect1, 26, 110);
    lv_obj_set_style_radius(rounded_rect1, 5, LV_PART_MAIN);                        // 圆角半径20
    lv_obj_set_style_bg_color(rounded_rect1, lv_color_hex(0x696969), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect1_label1 = lv_label_create(rounded_rect1);                // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect1_label1, "GD");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect1_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect1_label1, LV_ALIGN_TOP_MID, 0, 0);      // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect1_label2 = lv_label_create(rounded_rect1); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect1_label2, "1");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect1_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect1_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect2 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect2, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect2, 21, 65);
    lv_obj_set_pos(rounded_rect2, 47, 110);
    lv_obj_set_style_radius(rounded_rect2, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect2, lv_color_hex(0xA52A2A), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect2_label1 = lv_label_create(rounded_rect2);                // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect2_label1, "IO");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect2_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect2_label1, LV_ALIGN_TOP_MID, 0, 0);      // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect2_label2 = lv_label_create(rounded_rect2); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect2_label2, "2");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect2_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect2_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect3 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect3, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect3, 21, 65);
    lv_obj_set_pos(rounded_rect3, 68, 110);
    lv_obj_set_style_radius(rounded_rect3, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect3, lv_color_hex(0xFF0000), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect3_label1 = lv_label_create(rounded_rect3);                // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect3_label1, "3V");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect3_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect3_label1, LV_ALIGN_TOP_MID, 0, 0);      // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect3_label2 = lv_label_create(rounded_rect3); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect3_label2, "3");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect3_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect3_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect4 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect4, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect4, 21, 65);
    lv_obj_set_pos(rounded_rect4, 89, 110);
    lv_obj_set_style_radius(rounded_rect4, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect4, lv_color_hex(0xFF0000), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect4_label1 = lv_label_create(rounded_rect4);                // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect4_label1, "5V");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect4_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect4_label1, LV_ALIGN_TOP_MID, 0, 0);      // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect4_label2 = lv_label_create(rounded_rect4); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect4_label2, "4");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect4_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect4_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect5 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect5, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect5, 21, 65);
    lv_obj_set_pos(rounded_rect5, 110, 110);
    lv_obj_set_style_radius(rounded_rect5, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect5, lv_color_hex(0x008000), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect5_label1 = lv_label_create(rounded_rect5);                // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect5_label1, "CO");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect5_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect5_label1, LV_ALIGN_TOP_MID, 0, 0);      // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect5_label2 = lv_label_create(rounded_rect5); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect5_label2, "5");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect5_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect5_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect6 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect6, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect6, 21, 65);
    lv_obj_set_pos(rounded_rect6, 131, 110);
    lv_obj_set_style_radius(rounded_rect6, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect6, lv_color_hex(0x008000), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect6_label1 = lv_label_create(rounded_rect6);                // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect6_label1, "PW");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect6_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect6_label1, LV_ALIGN_TOP_MID, 0, 0);      // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect6_label2 = lv_label_create(rounded_rect6); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect6_label2, "6");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect6_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect6_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect7 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect7, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect7, 21, 65);
    lv_obj_set_pos(rounded_rect7, 152, 110);
    lv_obj_set_style_radius(rounded_rect7, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect7, lv_color_hex(0x0000FF), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect7_label1 = lv_label_create(rounded_rect7);                // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect7_label1, "SL");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect7_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect7_label1, LV_ALIGN_TOP_MID, 0, 0);      // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect7_label2 = lv_label_create(rounded_rect7); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect7_label2, "7");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect7_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect7_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect8 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect8, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect8, 21, 65);
    lv_obj_set_pos(rounded_rect8, 173, 110);
    lv_obj_set_style_radius(rounded_rect8, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect8, lv_color_hex(0x0000FF), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect8_label1 = lv_label_create(rounded_rect8);                // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect8_label1, "SA");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect8_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect8_label1, LV_ALIGN_TOP_MID, 0, 0);      // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect8_label2 = lv_label_create(rounded_rect8); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect8_label2, "8");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect8_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect8_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect9 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect9, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect9, 21, 65);
    lv_obj_set_pos(rounded_rect9, 194, 110);
    lv_obj_set_style_radius(rounded_rect9, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect9, lv_color_hex(0xC71585), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect9_label1 = lv_label_create(rounded_rect9);                // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect9_label1, "DI");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect9_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect9_label1, LV_ALIGN_TOP_MID, 0, 0);      // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect9_label2 = lv_label_create(rounded_rect9); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect9_label2, "9");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect9_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect9_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect10 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect10, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect10, 21, 65);
    lv_obj_set_pos(rounded_rect10, 215, 110);
    lv_obj_set_style_radius(rounded_rect10, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect10, lv_color_hex(0xC71585), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect10_label1 = lv_label_create(rounded_rect10);               // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect10_label1, "CL");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect10_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect10_label1, LV_ALIGN_TOP_MID, 0, 0);       // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect10_label2 = lv_label_create(rounded_rect10); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect10_label2, "10");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect10_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect10_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect11 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect11, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect11, 21, 65);
    lv_obj_set_pos(rounded_rect11, 236, 110);
    lv_obj_set_style_radius(rounded_rect11, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect11, lv_color_hex(0xC71585), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect11_label1 = lv_label_create(rounded_rect11);               // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect11_label1, "RS");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect11_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect11_label1, LV_ALIGN_TOP_MID, 0, 0);       // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect11_label2 = lv_label_create(rounded_rect11); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect11_label2, "11");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect11_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect11_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect12 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect12, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect12, 21, 65);
    lv_obj_set_pos(rounded_rect12, 257, 110);
    lv_obj_set_style_radius(rounded_rect12, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect12, lv_color_hex(0xFF8C00), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect12_label1 = lv_label_create(rounded_rect12);               // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect12_label1, "RX");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect12_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect12_label1, LV_ALIGN_TOP_MID, 0, 0);       // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect12_label2 = lv_label_create(rounded_rect12); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect12_label2, "12");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect12_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect12_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect13 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect13, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect13, 21, 65);
    lv_obj_set_pos(rounded_rect13, 278, 110);
    lv_obj_set_style_radius(rounded_rect13, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect13, lv_color_hex(0xFF8C00), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect13_label1 = lv_label_create(rounded_rect13);               // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect13_label1, "TX");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect13_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect13_label1, LV_ALIGN_TOP_MID, 0, 0);       // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect13_label2 = lv_label_create(rounded_rect13); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect13_label2, "13");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect13_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect13_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect14 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect14, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect14, 21, 65);
    lv_obj_set_pos(rounded_rect14, 26, 175);
    lv_obj_set_style_radius(rounded_rect14, 5, LV_PART_MAIN);                        // 圆角半径20
    lv_obj_set_style_bg_color(rounded_rect14, lv_color_hex(0x696969), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect14_label1 = lv_label_create(rounded_rect14);               // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect14_label1, "GD");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect14_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect14_label1, LV_ALIGN_TOP_MID, 0, 0);       // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect14_label2 = lv_label_create(rounded_rect14); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect14_label2, "14");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect14_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect14_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect15 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect15, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect15, 21, 65);
    lv_obj_set_pos(rounded_rect15, 47, 175);
    lv_obj_set_style_radius(rounded_rect15, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect15, lv_color_hex(0x20B2AA), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect15_label1 = lv_label_create(rounded_rect15);               // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect15_label1, "C0");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect15_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect15_label1, LV_ALIGN_TOP_MID, 0, 0);       // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect15_label2 = lv_label_create(rounded_rect15); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect15_label2, "15");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect15_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect15_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect16 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect16, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect16, 21, 65);
    lv_obj_set_pos(rounded_rect16, 68, 175);
    lv_obj_set_style_radius(rounded_rect16, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect16, lv_color_hex(0x20B2AA), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect16_label1 = lv_label_create(rounded_rect16);               // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect16_label1, "C1");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect16_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect16_label1, LV_ALIGN_TOP_MID, 0, 0);       // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect16_label2 = lv_label_create(rounded_rect16); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect16_label2, "16");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect16_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect16_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect17 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect17, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect17, 21, 65);
    lv_obj_set_pos(rounded_rect17, 89, 175);
    lv_obj_set_style_radius(rounded_rect17, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect17, lv_color_hex(0x20B2AA), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect17_label1 = lv_label_create(rounded_rect17);               // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect17_label1, "C2");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect17_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect17_label1, LV_ALIGN_TOP_MID, 0, 0);       // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect17_label2 = lv_label_create(rounded_rect17); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect17_label2, "17");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect17_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect17_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect18 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect18, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect18, 21, 65);
    lv_obj_set_pos(rounded_rect18, 110, 175);
    lv_obj_set_style_radius(rounded_rect18, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect18, lv_color_hex(0x20B2AA), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect18_label1 = lv_label_create(rounded_rect18);               // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect18_label1, "C3");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect18_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect18_label1, LV_ALIGN_TOP_MID, 0, 0);       // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect18_label2 = lv_label_create(rounded_rect18); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect18_label2, "18");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect18_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect18_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect19 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect19, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect19, 21, 65);
    lv_obj_set_pos(rounded_rect19, 131, 175);
    lv_obj_set_style_radius(rounded_rect19, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect19, lv_color_hex(0x20B2AA), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect19_label1 = lv_label_create(rounded_rect19);               // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect19_label1, "C4");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect19_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect19_label1, LV_ALIGN_TOP_MID, 0, 0);       // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect19_label2 = lv_label_create(rounded_rect19); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect19_label2, "19");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect19_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect19_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect20 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect20, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect20, 21, 65);
    lv_obj_set_pos(rounded_rect20, 152, 175);
    lv_obj_set_style_radius(rounded_rect20, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect20, lv_color_hex(0x20B2AA), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect20_label1 = lv_label_create(rounded_rect20);               // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect20_label1, "C5");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect20_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect20_label1, LV_ALIGN_TOP_MID, 0, 0);       // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect20_label2 = lv_label_create(rounded_rect20); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect20_label2, "20");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect20_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect20_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect21 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect21, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect21, 21, 65);
    lv_obj_set_pos(rounded_rect21, 173, 175);
    lv_obj_set_style_radius(rounded_rect21, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect21, lv_color_hex(0x20B2AA), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect21_label1 = lv_label_create(rounded_rect21);               // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect21_label1, "C6");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect21_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect21_label1, LV_ALIGN_TOP_MID, 0, 0);       // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect21_label2 = lv_label_create(rounded_rect21); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect21_label2, "21");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect21_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect21_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect22 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect22, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect22, 21, 65);
    lv_obj_set_pos(rounded_rect22, 194, 175);
    lv_obj_set_style_radius(rounded_rect22, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect22, lv_color_hex(0x20B2AA), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect22_label1 = lv_label_create(rounded_rect22);               // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect22_label1, "C7");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect22_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect22_label1, LV_ALIGN_TOP_MID, 0, 0);       // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect22_label2 = lv_label_create(rounded_rect22); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect22_label2, "22");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect22_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect22_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect23 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect23, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect23, 21, 65);
    lv_obj_set_pos(rounded_rect23, 215, 175);
    lv_obj_set_style_radius(rounded_rect23, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect23, lv_color_hex(0x006400), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect23_label1 = lv_label_create(rounded_rect23);               // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect23_label1, "DI");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect23_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect23_label1, LV_ALIGN_TOP_MID, 0, 0);       // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect23_label2 = lv_label_create(rounded_rect23); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect23_label2, "23");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect23_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect23_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect24 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect24, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect24, 21, 65);
    lv_obj_set_pos(rounded_rect24, 236, 175);
    lv_obj_set_style_radius(rounded_rect24, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect24, lv_color_hex(0x006400), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect24_label1 = lv_label_create(rounded_rect24);               // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect24_label1, "CL");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect24_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect24_label1, LV_ALIGN_TOP_MID, 0, 0);       // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect24_label2 = lv_label_create(rounded_rect24); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect24_label2, "24");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect24_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect24_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect25 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect25, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect25, 21, 65);
    lv_obj_set_pos(rounded_rect25, 257, 175);
    lv_obj_set_style_radius(rounded_rect25, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect25, lv_color_hex(0xFF1493), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect25_label1 = lv_label_create(rounded_rect25);               // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect25_label1, "RX");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect25_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect25_label1, LV_ALIGN_TOP_MID, 0, 0);       // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect25_label2 = lv_label_create(rounded_rect25); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect25_label2, "25");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect25_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect25_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形

    lv_obj_t *rounded_rect26 = lv_obj_create(lv_scr_act());
    lv_obj_remove_style(rounded_rect26, 0, LV_PART_SCROLLBAR);
    lv_obj_set_size(rounded_rect26, 21, 65);
    lv_obj_set_pos(rounded_rect26, 278, 175);
    lv_obj_set_style_radius(rounded_rect26, 5, LV_PART_MAIN);
    lv_obj_set_style_bg_color(rounded_rect26, lv_color_hex(0xFF1493), LV_PART_MAIN); // 背景色为绿色
    lv_obj_t *rounded_rect26_label1 = lv_label_create(rounded_rect26);               // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect26_label1, "TX");                                  // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect26_label1, &lv_font_montserrat_12, 0);
    lv_obj_align(rounded_rect26_label1, LV_ALIGN_TOP_MID, 0, 0);       // 将文本居中对齐到圆角矩形
    lv_obj_t *rounded_rect26_label2 = lv_label_create(rounded_rect26); // 将文本标签添加到圆角矩形上
    lv_label_set_text(rounded_rect26_label2, "26");                    // 设置文本内容
    lv_obj_set_style_text_font(rounded_rect26_label2, &lv_font_montserrat_16, 0);
    lv_obj_align(rounded_rect26_label2, LV_ALIGN_BOTTOM_MID, 0, 0); // 将文本居中对齐到圆角矩形
}
