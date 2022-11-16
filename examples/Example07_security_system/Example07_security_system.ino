/*
 * security_system.ino
 * @Author: CuiYao 
 * @Date: 2022-11-16 17:01:54 
 * @Last Modified by: CuiYao
 * @Last Modified time: 2022-11-16 17:20:41
 * 安全系统为四个状态、atHome (在家)、goOut (外出)、atNight (夜间)、close (关闭)、alarm (触发警报)
 */


#include <Arduino.h>
#include <arduino_homekit_server.h>
#include <EasyButton.h>
#include "wifi_info.h"

#define PIN_BUTTON 0  //Button PIN

#define LOG_D(fmt, ...)   printf_P(PSTR(fmt "\n") , ##__VA_ARGS__);

EasyButton button(PIN_BUTTON);  //声明按钮

void setup() {
  Serial.begin(115200);
  wifi_connect();
  //初始化按键
  button.begin();
  //定义按键单按事件回调
  button.onPressed(onPressed);

  homekit_storage_reset();
  my_homekit_setup();
}

void loop() {
  my_homekit_loop();
  button.read();
  delay(10);
}

//==============================
// HomeKit setup and loop
//==============================

// access lock-mechanism HomeKit characteristics defined in my_accessory.c
extern "C" homekit_server_config_t config;

extern "C" homekit_characteristic_t cha_system_current_state;
extern "C" homekit_characteristic_t cha_system_target_state;

static uint32_t next_heap_millis = 0;


// called when the lock-mechanism target-set is changed by iOS Home APP
void set_lock(const homekit_value_t value) {
  
  uint8_t state = value.int_value;
  cha_system_current_state.value.int_value = state;
  
  if(state == 0){
    atHome();
  }
  if(state == 1){
    goOut();
  }
  if(state == 2){
    atNight();
  }
  if(state == 3){
    goOut();
  }
  
  //report the lock-mechanism current-sate to HomeKit
  homekit_characteristic_notify(&cha_system_current_state, cha_system_current_state.value);
  
}

void my_homekit_setup() {
  
  cha_system_target_state.setter = set_lock;
  arduino_homekit_setup(&config);

  
}


void my_homekit_loop() {
  arduino_homekit_loop();
  const uint32_t t = millis();
  if (t > next_heap_millis) {
    // show heap info every 30 seconds
    next_heap_millis = t + 30 * 1000;
    LOG_D("Free heap: %d, HomeKit clients: %d",
        ESP.getFreeHeap(), arduino_homekit_connected_clients_count());

  }
}



void atHome(){
  Serial.println("atHome"); 
}
void goOut(){
  Serial.println("goOut");  
}
void atNight(){
  Serial.println("atNight");  
}
void close(){
  Serial.println("close");  
}
void alarm(){
  Serial.println("alarm");  
}

void onPressed() {
    cha_system_current_state.value.int_value = 4;

     homekit_characteristic_notify(&cha_system_current_state, cha_system_current_state.value);

}