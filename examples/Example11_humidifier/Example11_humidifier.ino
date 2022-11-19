/*
 * @Author: CuiYao 
 * @Date: 2022-11-18 10:08:51 
 * @Last Modified by: CuiYao
 * @Last Modified time: 2022-11-19 21:57:30
 */


#include <Arduino.h>
#include <arduino_homekit_server.h>
#include <EasyButton.h>
#include "wifi_info.h"
#include "ESPRotary.h"

#define PIN_BUTTON 13  //Button PIN

//LOG
#define LOG_D(fmt, ...) printf_P(PSTR(fmt "\n"), ##__VA_ARGS__);

int duration = 2000;  //长按触发时间 ms
int active = 0;       //激活
float sped = 0;       //速度
int inuse = 0;
EasyButton button(PIN_BUTTON);  //声明按钮


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

extern "C" homekit_characteristic_t cha_active;
extern "C" homekit_characteristic_t cha_speed;
extern "C" homekit_characteristic_t cha_swing_mode;
extern "C" homekit_characteristic_t cha_current_status;
extern "C" homekit_characteristic_t cha_target_status;
extern "C" homekit_characteristic_t cha_thresholding;
extern "C" homekit_characteristic_t cha_thresholding01;
extern "C" homekit_characteristic_t cha_humidity;
static uint32_t next_heap_millis = 0;


// called when the lock-mechanism target-set is changed by iOS Home APP
void fan_active(const homekit_value_t value) {

  uint8_t state = value.int_value;

  cha_humidity.value.float_value=30.0;
  homekit_characteristic_notify(&cha_humidity, cha_humidity.value);
  cha_active.value.int_value = state;
  active = state;
  if (state == 0) {
    OFF();
    cha_active.value.int_value = 0;
    homekit_characteristic_notify(&cha_active, cha_active.value);
  }
  if (state == 1) {
      ON();
      Serial.println("Idle");
      cha_active.value.int_value = 1;
      homekit_characteristic_notify(&cha_active, cha_active.value);
      cha_target_status.value.int_value = 0;
      homekit_characteristic_notify(&cha_target_status, cha_target_status.value);
      cha_current_status.value.int_value = 1;
      homekit_characteristic_notify(&cha_current_status, cha_current_status.value);
      cha_thresholding.value.float_value=50.0,
      homekit_characteristic_notify(&cha_thresholding, cha_thresholding.value);
  }
}

void target_status(const homekit_value_t value) {
  uint8_t state = value.int_value;
  Serial.println(state);

  cha_humidity.value.float_value=30.0;
  homekit_characteristic_notify(&cha_humidity, cha_humidity.value);
  switch (state) {
    case 0:
      Serial.println("Idle");
      cha_active.value.int_value = 1;
      homekit_characteristic_notify(&cha_active, cha_active.value);
      cha_target_status.value.int_value = 0;
      homekit_characteristic_notify(&cha_target_status, cha_target_status.value);
      cha_current_status.value.int_value = 1;
      homekit_characteristic_notify(&cha_current_status, cha_current_status.value);
      cha_thresholding.value.float_value=50.0,
      homekit_characteristic_notify(&cha_thresholding, cha_thresholding.value);
      break;
    case 1:
      Serial.println("Humidifying");
      cha_active.value.int_value = 1;
      homekit_characteristic_notify(&cha_active, cha_active.value);
      cha_target_status.value.int_value = 1;
      homekit_characteristic_notify(&cha_target_status, cha_target_status.value);
      cha_current_status.value.int_value = 2;
      homekit_characteristic_notify(&cha_current_status, cha_current_status.value);
      cha_thresholding.value.float_value=90.0,
      homekit_characteristic_notify(&cha_thresholding, cha_thresholding.value);
      break;
    case 2:
      Serial.println("Dehumidifying");
      cha_active.value.int_value = 1;
      homekit_characteristic_notify(&cha_active, cha_active.value);
      cha_target_status.value.int_value = 2;
      homekit_characteristic_notify(&cha_target_status, cha_target_status.value);
      cha_current_status.value.int_value = 3;
      homekit_characteristic_notify(&cha_current_status, cha_current_status.value);
      cha_thresholding01.value.float_value=80.0,
      homekit_characteristic_notify(&cha_thresholding01, cha_thresholding01.value);
      break;
  }
}

void my_homekit_setup() {

  cha_active.setter = fan_active;
  cha_target_status.setter = target_status;
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
void ON() {
  Serial.println("ON");
}

void OFF() {
  Serial.println("OFF");
}

// 单按事件函数
void onPressed() {

  if (active == 0) {
    cha_active.value.int_value = 1;
    ON();

    active = 1;
  } else if (active == 1) {
    cha_active.value.int_value = 0;
    OFF();
    active = 0;
  }

  //report the lock-mechanism current-sate to HomeKit
  homekit_characteristic_notify(&cha_active, cha_active.value);
}
// 长按事件函数
void onPressedForDuration() {
  if (inuse == 0) {
    cha_swing_mode.value.int_value = 1;
    inuse = 1;
  } else if (active == 1) {
    cha_swing_mode.value.int_value = 0;

    inuse = 0;
  }
  //report the lock-mechanism current-sate to HomeKit
  homekit_characteristic_notify(&cha_swing_mode, cha_swing_mode.value);
}