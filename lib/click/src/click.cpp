#include<click.h>
int cnt;
static void increment_on_click(lv_event_t * e)
{
    lv_obj_t * btn = lv_event_get_target(e);
    lv_obj_t * label = lv_obj_get_child(btn, 0);
    lv_event_code_t code = lv_event_get_code(e);
    //int index = (int)lv_event_get_user_data(e);
   
    if ( code == LV_EVENT_PRESSED){
        lv_label_set_text_fmt(label,"%"LV_PRIu32, cnt);
        cnt++;
    }
    if ( code == LV_EVENT_CLICKED){
        lv_label_set_text_fmt(label, "%"LV_PRIu32, cnt);
        cnt++;
    }
    //Serial.println(code);
    
    
}

void click_example_1(void)
{
    lv_obj_t * obj2;
    obj2 = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj2, 150, 100);
    lv_obj_set_align(obj2,LV_ALIGN_CENTER);

    lv_obj_add_event_cb(obj2, increment_on_click, LV_EVENT_CLICKED, NULL);

    lv_obj_t * label2 = lv_label_create(obj2);
    lv_label_set_text(label2, "me");
    lv_obj_center(label2);
}
