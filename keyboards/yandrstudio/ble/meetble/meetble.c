// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "meetble.h"

#ifdef BIU_BLE5_ENABLE
#    include "biu_ble_common.h"
#endif

#if defined(RGBLIGHT_ENABLE) && defined(BIU_BLE5_ENABLE)

const rgblight_segment_t PROGMEM bt_conn1[] = RGBLIGHT_LAYER_SEGMENTS( {2, 1, HSV_GREEN} );                    // 0
const rgblight_segment_t PROGMEM bt_conn2[] = RGBLIGHT_LAYER_SEGMENTS( {3, 1, HSV_GREEN} );                    // 1
const rgblight_segment_t PROGMEM bt_conn3[] = RGBLIGHT_LAYER_SEGMENTS( {1, 1, HSV_GREEN} );                    // 2
const rgblight_segment_t PROGMEM bt_conn4[] = RGBLIGHT_LAYER_SEGMENTS( {4, 1, HSV_GREEN} );                    // 3
const rgblight_segment_t PROGMEM bt_pair1[] = RGBLIGHT_LAYER_SEGMENTS( {2, 1, HSV_BLUE} );                     // 4
const rgblight_segment_t PROGMEM bt_pair2[] = RGBLIGHT_LAYER_SEGMENTS( {3, 1, HSV_BLUE} );                     // 5
const rgblight_segment_t PROGMEM bt_pair3[] = RGBLIGHT_LAYER_SEGMENTS( {1, 1, HSV_BLUE} );                     // 6
const rgblight_segment_t PROGMEM bt_pair4[] = RGBLIGHT_LAYER_SEGMENTS( {4, 1, HSV_BLUE} );                     // 7
const rgblight_segment_t PROGMEM usb_pair[] = RGBLIGHT_LAYER_SEGMENTS( {0, 1, HSV_BLUE}, {5, 1, HSV_BLUE} );   // 8
const rgblight_segment_t PROGMEM usb_conn[] = RGBLIGHT_LAYER_SEGMENTS( {0, 1, HSV_WHITE}, {5, 1, HSV_WHITE} ); // 9
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_RED});               // 10
const rgblight_segment_t PROGMEM bat_10_layer[] = RGBLIGHT_LAYER_SEGMENTS({2, 1, HSV_RED});                    // 11
const rgblight_segment_t PROGMEM bat_30_layer[] = RGBLIGHT_LAYER_SEGMENTS({2, 2, HSV_GREEN});                  // 12
const rgblight_segment_t PROGMEM bat_50_layer[] = RGBLIGHT_LAYER_SEGMENTS({1, 3, HSV_GREEN});                  // 13
const rgblight_segment_t PROGMEM bat_70_layer[] = RGBLIGHT_LAYER_SEGMENTS({1, 4, HSV_GREEN});                  // 14
const rgblight_segment_t PROGMEM bat_80_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 5, HSV_GREEN});                  // 15
const rgblight_segment_t PROGMEM bat_90_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_GREEN});                  // 16

const rgblight_segment_t* const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST(bt_conn1, bt_conn2, bt_conn3, bt_conn4,
                                                                             bt_pair1, bt_pair2, bt_pair3, bt_pair4,
                                                                             usb_pair, usb_conn,
                                                                             my_capslock_layer,
                                                                             bat_10_layer, bat_30_layer, bat_50_layer,
                                                                             bat_70_layer, bat_80_layer, bat_90_layer);

void rgb_adv_unblink_all_layer(void) {
    for (uint8_t i = 0; i < 17; i++) {
        rgblight_unblink_layer(i);
    }
}

bool ble_led_update_kb(uint8_t channle, uint8_t state) {
    /*
    _ble_channle:
        BLE: 0-7
        USB: 0xa
        2G4: 0xb
    _ble_state:
        NRF_WORKING：1
        NRF_ADVING_NO_WL：8
        NRF_ADVING_WITH_WL：7

        USB_ACTIVE: 0xA0
        USB_DISCONNECTION：0xA1
    */
    rgb_adv_unblink_all_layer();
    if (channle == 0xa) {
        if (state != 0xa0) {
            rgblight_blink_layer_repeat(8, 500, 8);
        } else {
            rgblight_blink_layer_repeat(9, 3000, 1);
        }
    } else if (channle <= 7) {
        if (state == 7) {
            rgblight_blink_layer_repeat(channle%4, 500, 8);
        } else if (state == 8) {
            rgblight_blink_layer_repeat(channle%4+4, 200, 20);
        } else if (state == 1) {
            rgblight_blink_layer_repeat(channle%4, 3000, 1);
        }
    }
    return true;
}

bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        rgblight_set_layer_state(10, led_state.caps_lock);
    }
    return true;
}

void keyboard_post_init_kb(void) {
    rgblight_reload_from_eeprom();
    rgblight_layers = _rgb_layers;
    keyboard_post_init_user();
}
#endif


#ifndef BIU_BLE5_ENABLE
void keyboard_pre_init_kb(void) {
    palSetLineMode(RGB_BLE_SW, PAL_MODE_OUTPUT_PUSHPULL);
    writePin(RGB_BLE_SW, 0);
}
#endif
