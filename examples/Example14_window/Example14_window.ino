/*
 * @Author: CuiYao 
 * @Date: 2022-11-20 15:37:58 
 * @Last Modified by: CuiYao
 * @Last Modified time: 2022-11-20 16:27:32
 */


#include <Arduino.h>
#include <arduino_homekit_server.h>
#include "wifi_info.h"
#include <EasyButton.h>

//Button PIN
#define BUTTON_PIN 0
//长按触发时间
int duration = 2000;
//声明按钮
EasyButton button(BUTTON_PIN);
int inputValue = 0;
int postion = 0;

#define LOG_D(fmt, ...) printf_P(PSTR(fmt "\n"), ##__VA_ARGS__);

void setup() {
  Serial.begin(115200);
  //初始化按键
  button.begin();

  //定义按键单按事件回调
  button.onPressed(onPressed);
  //定义按键长按事件回调
  button.onPressedFor(duration, onPressedForDuration);
  //连接WIFI
  wifi_connect();
  // 在首次运行此新的HomeKit示例时删除以前的HomeKit配对存储
  homekit_storage_reset();
  my_homekit_setup();
}

void loop() {
  // 持续更新按钮状态。
  button.read();
  // 持续更新homekit状态
  my_homekit_loop();
  delay(10);
}




//==============================
// HomeKit setup and loop
//==============================

// access your HomeKit characteristics defined in my_accessory.c
extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_current_status;
extern "C" homekit_characteristic_t cha_target_status;
extern "C" homekit_characteristic_t cha_position_status;
extern "C" homekit_characteristic_t cha_hold_postion;
extern "C" homekit_characteristic_t cha_obstruction_detected;

static uint32_t next_heap_millis = 0;

#define PIN_SWITCH 2

//Called when the switch value is changed by iOS Home APP
void cha_target_status_setter(const homekit_value_t value) {
  uint8_t active = value.uint8_value;
  Serial.println("target");
  Serial.println(active);

  // if (active==0){
  //   cha_position_status.value.int_value=0;
  //   homekit_characteristic_notify(&cha_position_status, cha_position_status.value);
  // }
  // if (active=100){
  //   cha_position_status.value.int_value=1;
  //   homekit_characteristic_notify(&cha_position_status, cha_position_status.value);
  // }
  cha_target_status.value.int_value = active;
  homekit_characteristic_notify(&cha_target_status, cha_target_status.value);
  cha_current_status.value.int_value = active;
  homekit_characteristic_notify(&cha_current_status, cha_current_status.value);
}


// 单按事件函数
void onPressed() {
  Serial.println("Button has been pressed!");
  if (inputValue == 0) {
    inputValue = 1;
    // cha_obstruction_detected.value.bool_value = true;
    // homekit_characteristic_notify(&cha_obstruction_detected, cha_obstruction_detected.value);
    cha_target_status.value.int_value = 0;
    homekit_characteristic_notify(&cha_target_status, cha_target_status.value);
    cha_current_status.value.int_value = 0;
    homekit_characteristic_notify(&cha_current_status, cha_current_status.value);
    Serial.println("YES");
  } else {
    inputValue = 0;
    // cha_obstruction_detected.value.bool_value = false;
    // homekit_characteristic_notify(&cha_obstruction_detected, cha_obstruction_detected.value);
    cha_target_status.value.int_value = 100;
    homekit_characteristic_notify(&cha_target_status, cha_target_status.value);
    cha_current_status.value.int_value = 100;
    homekit_characteristic_notify(&cha_current_status, cha_current_status.value);
    Serial.println("NO");
  }
}
// 长按事件函数
void onPressedForDuration() {
  Serial.println("Button has been pressed for the given duration!");
  if (postion == 0) {
    postion = 1;
    cha_hold_postion.value.bool_value = true;
    homekit_characteristic_notify(&cha_hold_postion, cha_hold_postion.value);
    cha_position_status.value.int_value = 2;
    homekit_characteristic_notify(&cha_position_status, cha_position_status.value);
    Serial.println("YES");
  } else {
    postion = 0;
    cha_hold_postion.value.bool_value = false;
    homekit_characteristic_notify(&cha_hold_postion, cha_hold_postion.value);
    Serial.println("NO");
  }
}

void my_homekit_setup() {
  pinMode(PIN_SWITCH, OUTPUT);
  digitalWrite(PIN_SWITCH, HIGH);

  cha_target_status.setter = cha_target_status_setter;

  arduino_homekit_setup(&config);
}

void my_homekit_loop() {
  arduino_homekit_loop();
  const uint32_t t = millis();
  if (t > next_heap_millis) {
    // show heap info every 5 seconds
    next_heap_millis = t + 5 * 1000;
    LOG_D("Free heap: %d, HomeKit clients: %d",
          ESP.getFreeHeap(), arduino_homekit_connected_clients_count());
  }
}
