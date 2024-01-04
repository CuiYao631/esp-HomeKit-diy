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
//homekit_characteristic_t cha_faucet_active = HOMEKIT_CHARACTERISTIC_(ACTIVE, 0);

homekit_characteristic_t cha_faucet_active = HOMEKIT_CHARACTERISTIC_(PROGRAMMABLE_SWITCH_EVENT, 0);

//optional
homekit_characteristic_t cha_name = HOMEKIT_CHARACTERISTIC_(NAME, "shower_head");

homekit_accessory_t *accessories[] = {
    HOMEKIT_ACCESSORY(.id=1,
                      .category=homekit_accessory_category_video_door_bell, 
                      .config_number=4,
                      .services=(homekit_service_t*[]) 
    {
        HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, "door_bell"),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, "door_bell"),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, "12345678"),
            HOMEKIT_CHARACTERISTIC(MODEL, "door_bell"),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, "1.0"),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
            NULL
        }),
       HOMEKIT_SERVICE(CAMERA_RTP_STREAM_MANAGEMENT, .primary=true, .characteristics=(homekit_characteristic_t*[]){
            HOMEKIT_CHARACTERISTIC(
                SUPPORTED_VIDEO_STREAM_CONFIGURATION,
              //  .value=HOMEKIT_TLV_(&supported_video_config)
            ),
            HOMEKIT_CHARACTERISTIC(
                SUPPORTED_AUDIO_STREAM_CONFIGURATION,
              //  .value=HOMEKIT_TLV_(&supported_audio_config)
            ),
            HOMEKIT_CHARACTERISTIC(
                SUPPORTED_RTP_CONFIGURATION,
             //   .value=HOMEKIT_TLV_(&supported_rtp_config)
            ),
            HOMEKIT_CHARACTERISTIC(
                STREAMING_STATUS, 
                //.getter=camera_streaming_status_get
            ),
            HOMEKIT_CHARACTERISTIC(
                SETUP_ENDPOINTS,
              //  .getter=camera_setup_endpoints_get,
              //  .setter=camera_setup_endpoints_set
            ),
            HOMEKIT_CHARACTERISTIC(
                SELECTED_RTP_STREAM_CONFIGURATION,
              //  .getter=camera_selected_rtp_configuration_get,
              //  .setter=camera_selected_rtp_configuration_set
            ),
           NULL
       }),
        HOMEKIT_SERVICE(DOORBELL, .characteristics=(homekit_characteristic_t*[]){
            HOMEKIT_CHARACTERISTIC(NAME,"门铃"),
            //HOMEKIT_CHARACTERISTIC(PROGRAMMABLE_SWITCH_EVENT, 0),
            &cha_faucet_active,
            HOMEKIT_CHARACTERISTIC(VOLUME, 70),
            HOMEKIT_CHARACTERISTIC(BRIGHTNESS, 0),
            NULL
        }),
        HOMEKIT_SERVICE(MICROPHONE, .characteristics=(homekit_characteristic_t*[]){
            HOMEKIT_CHARACTERISTIC(NAME,"麦克风"),
            HOMEKIT_CHARACTERISTIC(VOLUME,70),
            HOMEKIT_CHARACTERISTIC(MUTE, true),
            NULL
        }),
        HOMEKIT_SERVICE(SPEAKER, .characteristics=(homekit_characteristic_t*[]){
            HOMEKIT_CHARACTERISTIC(NAME,"扬声器"),
            HOMEKIT_CHARACTERISTIC(VOLUME,70),
            HOMEKIT_CHARACTERISTIC(MUTE, true),
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
