/*
 * switch.ino
 *
 *  Created on: 2020-05-15
 *      Author: Mixiaoxiao (Wang Bin)
 *
 * HAP section 8.38 Switch
 * An accessory contains a switch.
 *
 * This example shows how to:
 * 1. define a switch accessory and its characteristics (in my_accessory.c).
 * 2. get the switch-event sent from iOS Home APP.
 * 3. report the switch value to HomeKit.
 *
 * You should:
 * 1. read and use the Example01_TemperatureSensor with detailed comments
 *    to know the basic concept and usage of this library before other examples。
 * 2. erase the full flash or call homekit_storage_reset() in setup()
 *    to remove the previous HomeKit pairing storage and
 *    enable the pairing with the new accessory of this new HomeKit example.
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

#define LOG_D(fmt, ...)   printf_P(PSTR(fmt "\n") , ##__VA_ARGS__);

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
extern "C" homekit_characteristic_t cha_current_door_status;
extern "C" homekit_characteristic_t cha_target_door_status;
extern "C" homekit_characteristic_t cha_obstruction_detected;

static uint32_t next_heap_millis = 0;

#define PIN_SWITCH 2

//Called when the switch value is changed by iOS Home APP
void cha_target_door_status_setter(const homekit_value_t value) {
    uint8_t active = value.uint8_value;  
    cha_target_door_status.value.uint8_value=active;
    if (active==1){
        Serial.println("CLOSED");
     cha_current_door_status.value.uint8_value=1;
     homekit_characteristic_notify(&cha_current_door_status,  cha_current_door_status.value);
    }else{
        Serial.println("OPEN");

     cha_current_door_status.value.uint8_value=0;
     homekit_characteristic_notify(&cha_current_door_status,  cha_current_door_status.value);
    }
	// bool on = value.bool_value;
	// cha_switch_on.value.bool_value = on;	//sync the value
	// LOG_D("Switch: %s", on ? "ON" : "OFF");
	// digitalWrite(PIN_SWITCH, on ? LOW : HIGH);
}

// 单按事件函数
void onPressed() {
  Serial.println("Button has been pressed!");
  if (inputValue==0){
    inputValue=1;
     cha_obstruction_detected.value.bool_value=true;
     homekit_characteristic_notify(&cha_obstruction_detected, cha_obstruction_detected.value);
     Serial.println("YES");
  }else{
    inputValue=0;
    cha_obstruction_detected.value.bool_value=false;
     homekit_characteristic_notify(&cha_obstruction_detected, cha_obstruction_detected.value);
     Serial.println("NO");
  }
  //inputValue = digitalRead(PIN_SWITCH);
//  
//  if (inputValue==LOW){
//    Serial.println("OFF");
//    cha_switch_on.value.bool_value=false;
//     homekit_characteristic_notify(&cha_switch_on, cha_switch_on.value);
//     digitalWrite(PIN_SWITCH, HIGH);
//  }else{
//    Serial.println("ON");
//    cha_switch_on.value.bool_value=true;
//     homekit_characteristic_notify(&cha_switch_on, cha_switch_on.value);
//     digitalWrite(PIN_SWITCH, LOW);
//  }
}
// 长按事件函数
void onPressedForDuration() {
    Serial.println("Button has been pressed for the given duration!");
    homekit_storage_reset(); 
    system_restart();
}

void my_homekit_setup() {
	pinMode(PIN_SWITCH, OUTPUT);
	digitalWrite(PIN_SWITCH, HIGH);

	cha_target_door_status.setter = cha_target_door_status_setter;
  
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
