#ifndef wifi_scan_H
#define wifi_scan_H

#include <Arduino.h>
#include"lvgl.h"
#include <vector>
#include <WiFi.h>



enum
{
  LV_MENU_ITEM_BUILDER_VARIANT_1,
  LV_MENU_ITEM_BUILDER_VARIANT_2
};
typedef uint8_t lv_menu_builder_variant_t;

static lv_obj_t *menu_screen;
static lv_obj_t *menu;
static lv_obj_t *screen;
static lv_obj_t *bar1;
static lv_obj_t *bar2;
static lv_obj_t *bar3;
static lv_obj_t *bar4;
static lv_obj_t *label1;
static lv_obj_t *label2;
static lv_obj_t *label3;
static lv_obj_t *label4;
static lv_timer_t *timer;
static lv_obj_t *wfList;
static lv_obj_t *root_page;
static lv_obj_t *listWiFisection;
static lv_obj_t *txtArea;
static lv_obj_t *kb;
static lv_obj_t *container;
static lv_obj_t *mbox1;
static lv_obj_t *msg;




static void ta_event_cb(lv_event_t *e);
static void setting_button(lv_event_t *e);
static void switch_handler_wifi(lv_event_t *e);
static void list_event_handler(lv_event_t *e);
static void back_event_handler(lv_event_t *e);
static void switch_handler(lv_event_t *e);
static void pass_input(lv_event_t *e);
static void showingFoundWiFiList();
static void networkScanner();
static void timerForNetwork(lv_timer_t *timer);
static lv_obj_t *create_text(lv_obj_t *parent, const char *icon, const char *txt, lv_menu_builder_variant_t builder_variant);
static lv_obj_t *create_slider(lv_obj_t *parent, const char *icon, const char *txt, int32_t min, int32_t max, int32_t val);
static lv_obj_t *create_switch(lv_obj_t *parent, const char *icon, const char *txt, bool chk);
static void scanWIFITask(void *pvParameters);
static void beginWIFITask(void *pvParameters);

void wifi_scan_loop(void);

void home(void);
void lv_example_menu_5(void);
#endif