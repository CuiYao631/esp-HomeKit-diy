/*
 * @Author: CuiYao 
 * @Date: 2022-11-18 10:08:51 
 * @Last Modified by: CuiYao
 * @Last Modified time: 2022-11-18 13:00:13
 */


#include <Arduino.h>
#include <arduino_homekit_server.h>
#include <EasyButton.h>
#include "wifi_info.h"
#include "ESPRotary.h"

#define ROTARY_PIN1 14
#define ROTARY_PIN2 12
#define PIN_BUTTON  13            //Button PIN          

//编码器
#define CLICKS_PER_STEP 4   //单步次数
#define MIN_POS         0   //最小位置
#define MAX_POS         100 //最大位置
#define START_POS       5   //起始位置
#define INCREMENT       2   //增量
//LOG
#define LOG_D(fmt, ...) printf_P(PSTR(fmt "\n"), ##__VA_ARGS__);

int duration = 2000;            //长按触发时间 ms
int active = 0;                 //激活
float sped=0;                     //速度
int inuse = 0;
EasyButton button(PIN_BUTTON);  //声明按钮
ESPRotary r;                    //编码器声明


void setup() {
  Serial.begin(115200);
  wifi_connect();
  //初始化按键
  button.begin();
  //定义按键单按事件回调
  button.onPressed(onPressed);
  //定义按键长按事件回调
  button.onPressedFor(duration, onPressedForDuration);

  //初始化编码器
  r.begin(ROTARY_PIN1, ROTARY_PIN2, CLICKS_PER_STEP, MIN_POS, MAX_POS, START_POS, INCREMENT);
  r.setChangedHandler(rotate);
  // r.setLeftRotationHandler(showDirection);
  // r.setRightRotationHandler(showDirection);

  //homekit_storage_reset();
  my_homekit_setup();
}

void loop() {
  my_homekit_loop();
  button.read();
  r.loop();
  delay(10);  
}

//==============================
// HomeKit setup and loop
//==============================

// access lock-mechanism HomeKit characteristics defined in my_accessory.c
extern "C" homekit_server_config_t config;

extern "C" homekit_characteristic_t cha_fan_on;
extern "C" homekit_characteristic_t cha_rotation_speed;
extern "C" homekit_characteristic_t cha_swing_mode;



static uint32_t next_heap_millis = 0;


// called when the lock-mechanism target-set is changed by iOS Home APP
void fan_active(const homekit_value_t value) {

  uint8_t state = value.int_value;
  cha_fan_on.value.int_value = state;
  active=state;
  if (state == 0) {
    ON();
  }
  if (state == 1) {
    
    OFF();
  }

  //report the lock-mechanism current-sate to HomeKit
  homekit_characteristic_notify(&cha_fan_on, cha_fan_on.value);
}

void speed(const homekit_value_t value){

  sped=value.float_value;
  r.resetPosition(int(sped));
  UpdataSpeed(sped);
}
void rotate(ESPRotary& r) {
  sped=r.getPosition();
  UpdataSpeed(float(sped));
}


void my_homekit_setup() {

  cha_fan_on.setter = fan_active;
  cha_rotation_speed.setter = speed;
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
void UpdataSpeed(float value){

  
  Serial.println(value);
  cha_rotation_speed.value.float_value = value;
  homekit_characteristic_notify(&cha_rotation_speed, cha_rotation_speed.value);
}

// 单按事件函数
void onPressed() {

  if (active == 0) {
    cha_fan_on.value.int_value = 1;
    ON();
    
    active = 1;
  } else if (active == 1) {
    cha_fan_on.value.int_value = 0;
    OFF();
    active = 0;
  }

  //report the lock-mechanism current-sate to HomeKit
  homekit_characteristic_notify(&cha_fan_on, cha_fan_on.value);
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