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
homekit_characteristic_t cha_fan_on = HOMEKIT_CHARACTERISTIC_(ON, 0);
//optional
homekit_characteristic_t cha_name = HOMEKIT_CHARACTERISTIC_(NAME, "fan");
homekit_characteristic_t cha_rotation_speed = HOMEKIT_CHARACTERISTIC_(ROTATION_SPEED,50);
homekit_characteristic_t cha_swing_mode = HOMEKIT_CHARACTERISTIC_(SWING_MODE,0);
homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_fan, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "fan"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "fan"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "12345678"),
            HOMEKIT_CHARACTERISTIC(MODEL, "speaker"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
            NULL
        }),
    HOMEKIT_SERVICE(FAN, .primary=true, .characteristics=(homekit_characteristic_t*[]){
      &cha_fan_on,
      &cha_name,
      &cha_rotation_speed,
      &cha_swing_mode,
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
