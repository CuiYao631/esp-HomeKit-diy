/*
 * @Author: CuiYao 
 * @Date: 2022-11-18 10:08:51 
 * @Last Modified by: CuiYao
 * @Last Modified time: 2022-11-18 12:17:35
 */


#include <Arduino.h>
#include <arduino_homekit_server.h>
#include <EasyButton.h>
#include "wifi_info.h"

#define LOG_D(fmt, ...) printf_P(PSTR(fmt "\n"), ##__VA_ARGS__);

#define PIN_BUTTON 0            //Button PIN
int duration = 2000;            //长按触发时间 ms
EasyButton button(PIN_BUTTON);  //声明按钮

int active = 0;  //激活



void setup() {
  Serial.begin(115200);
  wifi_connect();
  //初始化按键
  button.begin();
  //定义按键单按事件回调
  button.onPressed(onPressed);
  //定义按键长按事件回调
  button.onPressedFor(duration, onPressedForDuration);

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

extern "C" homekit_characteristic_t cha_faucet_active;

static uint32_t next_heap_millis = 0;


// called when the lock-mechanism target-set is changed by iOS Home APP
void set_lock(const homekit_value_t value) {

  uint8_t state = value.int_value;
  cha_faucet_active.value.int_value = state;

  if (state == 0) {
    // lock-mechanism was unsecured by iOS Home APP
    open_lock();
  }
  if (state == 1) {
    // lock-mechanism was secured by iOS Home APP
    close_lock();
  }

  //report the lock-mechanism current-sate to HomeKit
  homekit_characteristic_notify(&cha_faucet_active, cha_faucet_active.value);
}

void my_homekit_setup() {

  cha_faucet_active.setter = set_lock;
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



/* use this functions to let your lock mechanism do whatever yoi want */
void open_lock() {
  Serial.println("unsecure");
  // add your code here eg switch a relay or whatever
}

void close_lock() {
  Serial.println("secure");
  // add your code here eg switch a relay or whatever
}


// 单按事件函数
void onPressed() {

  if (active == 0) {
    cha_faucet_active.value.int_value = 1;
    active = 1;
  } else if (active == 1) {
    cha_faucet_active.value.int_value = 0;
    active = 0;
  }

  //report the lock-mechanism current-sate to HomeKit
  homekit_characteristic_notify(&cha_faucet_active, cha_faucet_active.value);
}
// 长按事件函数
void onPressedForDuration() {
  // if (inuse == 0) {
  //   cha_in_use.value.int_value = 1;
  //   inuse = 1;
  // } else if (active == 1) {
  //   cha_in_use.value.int_value = 0;
  //   inuse = 0;
  // }
  // //report the lock-mechanism current-sate to HomeKit
  // homekit_characteristic_notify(&cha_in_use, cha_in_use.value);
}