/*
 * my_accessory.c
 * Define the accessory in C language using the Macro in characteristics.h
 *
 *  Created on: 2021-02-05
 *      Author: cooper @ makesmart.net
 *      Thank you for this great library!
 *      
 */

#include <homekit/homekit.h>
#include <homekit/characteristics.h>

void my_accessory_identify(homekit_value_t _value) {
  printf("accessory identify\n");
}


// characteristics of the lock-mechanism
// format: uint8_t // 0 is unsecured // 1 is secured
homekit_characteristic_t cha_active = HOMEKIT_CHARACTERISTIC_(ACTIVE, 1);
homekit_characteristic_t cha_current_status = HOMEKIT_CHARACTERISTIC_(CURRENT_HUMIDIFIER_DEHUMIDIFIER_STATE, 0);
homekit_characteristic_t cha_target_status = HOMEKIT_CHARACTERISTIC_(TARGET_HUMIDIFIER_DEHUMIDIFIER_STATE, 0);
homekit_characteristic_t cha_humidity = HOMEKIT_CHARACTERISTIC_(CURRENT_RELATIVE_HUMIDITY, 0);
//optional
homekit_characteristic_t cha_name = HOMEKIT_CHARACTERISTIC_(NAME, "humidifier");
homekit_characteristic_t cha_speed = HOMEKIT_CHARACTERISTIC_(ROTATION_SPEED,50);
homekit_characteristic_t cha_swing_mode = HOMEKIT_CHARACTERISTIC_(SWING_MODE,0);
homekit_characteristic_t cha_thresholding = HOMEKIT_CHARACTERISTIC_(RELATIVE_HUMIDITY_HUMIDIFIER_THRESHOLD,0);
homekit_characteristic_t cha_thresholding01 = HOMEKIT_CHARACTERISTIC_(RELATIVE_HUMIDITY_DEHUMIDIFIER_THRESHOLD,0);

homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_humidifier, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "humidifier"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "humidifier"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "12345678"),
            HOMEKIT_CHARACTERISTIC(MODEL, "humidifier"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
            NULL
        }),
    HOMEKIT_SERVICE(HUMIDIFIER_DEHUMIDIFIER, .primary=true, .characteristics=(homekit_characteristic_t*[]){
      &cha_active,
      &cha_current_status,
      &cha_target_status,
      &cha_name,
      &cha_speed,
      &cha_swing_mode,
      &cha_thresholding,
      &cha_thresholding01,
      &cha_humidity,
      NULL
    }),
        NULL
    }),
  //   HOMEKIT_ACCESSORY(.id=3, .category=homekit_accessory_category_sensor, .services=(homekit_service_t*[]) {
  //   	HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
	// 		HOMEKIT_CHARACTERISTIC(NAME, "Humidity Sensor"),
	// 		HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
	// 		NULL
	// 	}),
  //   	HOMEKIT_SERVICE(HUMIDITY_SENSOR, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
	// 		HOMEKIT_CHARACTERISTIC(NAME, "Humidity"),
	// 		&cha_humidity,
	// 		NULL
	// 	}),
	// 	NULL
	// }),
    NULL
};

homekit_server_config_t config = {
    .accessories = accessories,
    .password = "123-45-678"
};
