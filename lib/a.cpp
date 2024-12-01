//计数程序 使用了触摸屏
#include <lvgl.h>
#include <TFT_eSPI.h>

#include "FT6336U.h"
// #include<src/demos/lv_demos.h>
// #include<examples/lv_examples.h>
//#include "demos/lv_demos.h"
#define I2C_SDA 21
#define I2C_SCL 22
#define RST_N_PIN 33
#define INT_N_PIN 39
FT6336U ft6336u(I2C_SDA, I2C_SCL, RST_N_PIN, INT_N_PIN);
//#include<ui.h>
#define Red_Pin 5
#define White_Pin 18
static lv_indev_t * indev_key;
/*Change to your screen resolution*/
static const uint16_t screenWidth  = 480;
static const uint16_t screenHeight = 320;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */
FT6336U_TouchPointType tp; 

static lv_group_t *groupRect; //全局变量
int cnt = 0;
/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp_drv );
    Serial.print( "Data y " );
}
void pinInit(void)
{
   
    pinMode(White_Pin,INPUT_PULLUP);
    Serial.println("pinInit");
    

}
static void my_key_read(lv_indev_drv_t * indev_driver,lv_indev_data_t * data )
{
    
    data->state = LV_INDEV_STATE_REL;
    int pinY= digitalRead(White_Pin);
    if( pinY== 0){
          
        data->state = LV_INDEV_STATE_PR;
    }else{
               
        data->state = LV_INDEV_STATE_REL;
    }
    static bool last_state;

   

    
    // Serial.print("selectedMenuItem:");
     //Serial.println(data->state);
     
}

/*Read the touchpad*/
//这个函数读取x y坐标点没有用
// static void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
// {
//     uint16_t touchX, touchY;
    
//     int  val = digitalRead(INT_N_PIN) ;
    
//     if(val = -1 )
//     {
//         data->state = LV_INDEV_STATE_REL;
//         // Serial.print( data->point.x );
//     }
//     else
//     {
//         data->state = LV_INDEV_STATE_PR;

//         /*Set the coordinates*/
//         data->point.x = ft6336u.read_touch1_x();
//         data->point.y = ft6336u.read_touch1_y();
//         data->point.x = 480 - data->point.y;
//         data->point.y = data->point.x;

//         Serial.print( "Data x " );
//         Serial.println( data->point.x );

//         Serial.print( "Data y " );
//         Serial.println( data->point.y );
//     }
//      Serial.print( data->point.x );

// }
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
    uint16_t touchX, touchY;

    //bool touched = tft.getTouch( &touchX, &touchY, 600 );
    tp = ft6336u.scan(); 
    int touched = tp.touch_count;

    if( !touched )
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        int x = tp.tp[0].x;
        int y = tp.tp[0].y;
        if(x >= 0 && x < screenWidth && y >= 0 && y < screenHeight)
        {
            data->state = LV_INDEV_STATE_PR;
            data->point.x = 480-tp.tp[0].y;
            data->point.y = tp.tp[0].x;
        }
        //Serial.print( data->point.x );
    }
    Serial.print( data->point.x );
    Serial.print( ";");
    Serial.println( data->point.y );
}
static void increment_on_click(lv_event_t * e)
{
    lv_obj_t * btn = lv_event_get_target(e);
    lv_obj_t * label = lv_obj_get_child(btn, 0);
    lv_event_code_t code = lv_event_get_code(e);
    //int index = (int)lv_event_get_user_data(e);
   
    if ( code == LV_EVENT_PRESSED){
        lv_label_set_text_fmt(label, "%"LV_PRIu32, cnt);
        cnt++;
    }
    if ( code == LV_EVENT_CLICKED){
        lv_label_set_text_fmt(label, "%"LV_PRIu32, cnt);
        cnt++;
    }
    //Serial.println(code);
    
    
}



void setup()
{
    pinInit();
    Serial.begin( 115200 ); /* prepare for possible serial debug */

    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println( LVGL_Arduino );
    Serial.println( "I am LVGL_Arduino" );

    lv_init();
    


    tft.begin();          /* TFT init */
    tft.setRotation( 3 ); /* Landscape orientation, flipped */

    ft6336u.begin();


    
    //初始化显示器
    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 10 );
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    //初始化触摸设备
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    // indev_drv.type = LV_INDEV_TYPE_ENCODER;
    // indev_drv.read_cb = my_key_read;

    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_key = lv_indev_drv_register( &indev_drv );
    indev_drv.read_cb = my_touchpad_read;
    
    
    
  
    
    
    
    // lv_obj_t * obj1;
    // obj1 = lv_obj_create(lv_scr_act());
    // lv_obj_set_size(obj1, 300, 70);
    // lv_obj_align(obj1, LV_ALIGN_CENTER, 0, 0);

    // lv_obj_t * obj1;
    // obj1 = lv_obj_create(lv_scr_act());
    // lv_obj_set_size(obj1, 150, 100);
    // //lv_obj_add_event_cb(obj1, increment_on_click, LV_EVENT_PRESSED, NULL);

    // lv_obj_t * label1 = lv_label_create(obj1);
    // lv_label_set_text(label1, "Drag me");
    // lv_obj_center(label1);
    

    lv_obj_t * obj2;
    obj2 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj2, 150, 100);
    lv_obj_set_align(obj2,LV_ALIGN_CENTER);
    
    lv_obj_add_event_cb(obj2, increment_on_click, LV_EVENT_CLICKED, NULL);

    lv_obj_t * label2 = lv_label_create(obj2);
    lv_label_set_text(label2, "me");
    lv_obj_center(label2);

    

    // lv_obj_t * label3 = lv_label_create(obj1);
    // lv_label_set_text(label3, "Click me!");
    // lv_obj_center(label3);
    // Serial.println( "Setup done" );

    // groupRect = lv_group_create();
    // lv_group_set_default(groupRect);    
    // lv_indev_set_group(indev_key, groupRect);
    //lv_group_add_obj(groupRect, obj1);

     //lv_group_add_obj(groupRect, obj2);
    
    
}

void loop()
{
    
    lv_timer_handler(); /* let the GUI do its work */
    delay( 5 );
}

