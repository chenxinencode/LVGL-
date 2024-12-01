#include"init.h"


//触摸驱动
#define I2C_SDA 21
#define I2C_SCL 22
#define RST_N_PIN 33
#define INT_N_PIN 32
FT6336U ft6336u(I2C_SDA, I2C_SCL, RST_N_PIN, INT_N_PIN);
#define blk 5
//外接设备
#define Red_Pin 5
#define White_Pin 1

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */
FT6336U_TouchPointType tp; 
lv_indev_t * indev_key;//设备

void pinInit(void)//背光控制
{
   
    pinMode(blk,OUTPUT);
    // Serial.println("pinInit");
    analogWrite(blk,255);

}
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
    // Serial.print( "my_disp_flush " );
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
     
}

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
        int x = tp.tp[1].x;
        int y = tp.tp[1].y;
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


void initDisp(void)
{
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

    

}

void initIndev(void)
{
    //初始化触摸设备
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_key = lv_indev_drv_register( &indev_drv );
    indev_drv.read_cb = my_touchpad_read;
}



void initFunction(void)//初始化函数
{
    //1.初始化外部设备
    pinInit();
    //2.串口输出初始化
    Serial.begin( 115200 ); 
    // humtem_setup();
    // humtem_loop();
    
    //3.初始化lvgl
    lv_init();
    //4.初始化TFT 
    tft.begin();          
    tft.setRotation( 3 ); 
    //4.初始化触摸屏
    ft6336u.begin();
    //5.初始化显示器
    initDisp();
    //6.初始化输入设备
    initIndev();
}
