/*
 * my_accessory.c
 * Define the accessory in C language using the Macro in characteristics.h
 *
 *  Created on: 2020-05-15
 *      Author: Mixiaoxiao (Wang Bin)
 */

#include <homekit/homekit.h>
#include <homekit/characteristics.h>

void my_accessory_identify(homekit_value_t _value) {
	printf("accessory identify\n");
}

// Garage (HAP section 8.38)
//  Required Characteristics:
//  - CURRENT_DOOR_STATE
//  - TARGET_DOOR_STATE
//  - OBSTRUCTION_DETECTED
 
//  Optional Characteristics:
//  - NAME
//  - LOCK_CURRENT_STATE
//  - LOCK_TARGET_STATE

// format: uint8;; HAP section 9.70; write the .setter function to get the switch-event sent from iOS Home APP.
homekit_characteristic_t cha_current_door_status = HOMEKIT_CHARACTERISTIC_(CURRENT_DOOR_STATE, (uint8_t)1);

homekit_characteristic_t cha_target_door_status = HOMEKIT_CHARACTERISTIC_(TARGET_DOOR_STATE, (uint8_t)1);

homekit_characteristic_t cha_obstruction_detected = HOMEKIT_CHARACTERISTIC_(OBSTRUCTION_DETECTED, false);

// format: string; HAP section 9.62; max length 64
homekit_characteristic_t cha_name = HOMEKIT_CHARACTERISTIC_(NAME, "Car_Door");

homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_garage, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "Car_Door"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "XCuiTech-HomeKit"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "2022.717"),
            HOMEKIT_CHARACTERISTIC(MODEL, "ESP8266"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
            NULL
        }),
		HOMEKIT_SERVICE(GARAGE_DOOR_OPENER, .primary=true, .characteristics=(homekit_characteristic_t*[]){
			&cha_current_door_status,
      &cha_target_door_status,
      &cha_obstruction_detected,
			&cha_name,
			NULL
		}),
        NULL
    }),
    NULL
};

homekit_server_config_t config = {
		.accessories = accessories,
		.password = "111-11-111"
};
