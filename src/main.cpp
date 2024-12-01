//在触摸屏上用LVGL显示wifi选择的菜单界面

// // #include"menu.h"
//  //#include"click.h"

// #include"wifi_scan.h"
// #include<Arduino.h>

#include"init.h"//初始化库
#include"ui_event.h"
extern float temperature;
extern float humidity;
char voltageStr[20], currentStr[20], powerStr[20], mAHStr[20]; // 存储ina226测量数据

void humtem_task();

void setup()
{
    //初始化函数
    initFunction();//初始化库
    


    

    
  
//代码放这
    
    
    //下面2行是wifi连接的lvgl代码
    // home();
    // lv_example_menu_5();
    
    
    
    
   
    ui1_init(); 


    
}

void loop()
{
    
    lv_timer_handler(); /* let the GUI do its work */
    
    humtem_task();

    delay( 5 );
    //下面1行是wifi连接的lvgl代码
    // wifi_scan_loop();//wifi_scan部分
}

void humtem_task() // 温度监测任务
{
    
   

    sprintf(voltageStr, "%0.2f", temperature);//温度
    sprintf(currentStr, "%0.2f", humidity);//湿度
    sprintf(powerStr, "%0.2f", humidity);

}