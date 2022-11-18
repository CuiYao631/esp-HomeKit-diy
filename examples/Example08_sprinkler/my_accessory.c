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
homekit_characteristic_t cha_sprinkler_active = HOMEKIT_CHARACTERISTIC_(ACTIVE, 1);
homekit_characteristic_t cha_sprinkler_program = HOMEKIT_CHARACTERISTIC_(PROGRAM_MODE, 0);
homekit_characteristic_t cha_in_use = HOMEKIT_CHARACTERISTIC_(IN_USE,1);
//optional
homekit_characteristic_t cha_name = HOMEKIT_CHARACTERISTIC_(NAME, "speaker");

homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_sprinkler, .services=(homekit_service_t*[]) {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "speaker"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "speaker"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "12345678"),
            HOMEKIT_CHARACTERISTIC(MODEL, "speaker"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
            NULL
        }),
    HOMEKIT_SERVICE(IRRIGATION_SYSTEM, .primary=true, .characteristics=(homekit_characteristic_t*[]){
      &cha_sprinkler_active,
      &cha_sprinkler_program,
      &cha_in_use,
      &cha_name,
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
