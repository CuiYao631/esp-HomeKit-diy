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



// door
homekit_characteristic_t cha_current_status = HOMEKIT_CHARACTERISTIC_(CURRENT_POSITION, (uint8_t)1);
homekit_characteristic_t cha_target_status = HOMEKIT_CHARACTERISTIC_(TARGET_POSITION, (uint8_t)1);
homekit_characteristic_t cha_position_status = HOMEKIT_CHARACTERISTIC_(POSITION_STATE, (uint8_t)1);
// door operation
homekit_characteristic_t cha_name = HOMEKIT_CHARACTERISTIC_(NAME, "window");
homekit_characteristic_t cha_hold_postion = HOMEKIT_CHARACTERISTIC_(HOLD_POSITION, false);
homekit_characteristic_t cha_obstruction_detected = HOMEKIT_CHARACTERISTIC_(OBSTRUCTION_DETECTED, false);


homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_window, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "window"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "XCuiTech-HomeKit"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "2022.717"),
            HOMEKIT_CHARACTERISTIC(MODEL, "ESP8266"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
            NULL
        }),
		HOMEKIT_SERVICE(WINDOW, .primary=true, .characteristics=(homekit_characteristic_t*[]){
        &cha_name,
		    &cha_current_status,
        &cha_target_status,
        &cha_position_status,
        &cha_hold_postion,
        &cha_obstruction_detected,
			NULL
		}),
        NULL
    }),
    NULL
};

homekit_server_config_t config = {
		.accessories = accessories,
		.password = "123-45-678"
};
