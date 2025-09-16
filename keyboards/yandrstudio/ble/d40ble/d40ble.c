// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "d40ble.h"

#if defined(RGBLIGHT_ENABLE) && defined(BIU_BLE5_ENABLE) && !defined(FACTORY_TEST)

const rgblight_segment_t PROGMEM bt_conn1[] = RGBLIGHT_LAYER_SEGMENTS( {0, 1, HSV_GREEN} );      // 0
const rgblight_segment_t PROGMEM bt_conn2[] = RGBLIGHT_LAYER_SEGMENTS( {1, 1, HSV_GREEN} );      // 1
const rgblight_segment_t PROGMEM bt_conn3[] = RGBLIGHT_LAYER_SEGMENTS( {2, 1, HSV_GREEN} );      // 2
const rgblight_segment_t PROGMEM bt_pair1[] = RGBLIGHT_LAYER_SEGMENTS( {0, 1, HSV_BLUE} );       // 3
const rgblight_segment_t PROGMEM bt_pair2[] = RGBLIGHT_LAYER_SEGMENTS( {1, 1, HSV_BLUE} );       // 4
const rgblight_segment_t PROGMEM bt_pair3[] = RGBLIGHT_LAYER_SEGMENTS( {2, 1, HSV_BLUE} );       // 5
const rgblight_segment_t PROGMEM usb_pair[] = RGBLIGHT_LAYER_SEGMENTS( {3, 1, HSV_BLUE});        // 6
const rgblight_segment_t PROGMEM usb_conn[] = RGBLIGHT_LAYER_SEGMENTS( {3, 1, HSV_GREEN});       // 7
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 4, HSV_RED}); // 8
const rgblight_segment_t PROGMEM bat_10_layer[] = RGBLIGHT_LAYER_SEGMENTS({23, 1, HSV_RED});      // 9
const rgblight_segment_t PROGMEM bat_30_layer[] = RGBLIGHT_LAYER_SEGMENTS({19, 5, HSV_CYAN});     // 10
const rgblight_segment_t PROGMEM bat_50_layer[] = RGBLIGHT_LAYER_SEGMENTS({14, 10, HSV_CYAN});     // 11
const rgblight_segment_t PROGMEM bat_70_layer[] = RGBLIGHT_LAYER_SEGMENTS({9, 15, HSV_CYAN});     // 12
const rgblight_segment_t PROGMEM bat_100_layer[] = RGBLIGHT_LAYER_SEGMENTS({4, 20, HSV_CYAN});    // 13

const rgblight_segment_t* const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST(bt_conn1, bt_conn2, bt_conn3,
                                                                             bt_pair1, bt_pair2, bt_pair3,
                                                                             usb_pair, usb_conn,
                                                                             my_capslock_layer,
                                                                             bat_10_layer, bat_30_layer, bat_50_layer,
                                                                             bat_70_layer, bat_100_layer);

void rgb_adv_unblink_all_layer(void) {
    for (uint8_t i = 0; i < 14; i++) {
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
            rgblight_blink_layer_repeat(6, 500, 8);
        } else {
            rgblight_blink_layer_repeat(7, 3000, 1);
        }
    } else if (channle <= 7) {
        if (state == 7) {
            rgblight_blink_layer_repeat(channle%3, 500, 8);
        } else if (state == 8) {
            rgblight_blink_layer_repeat(channle%3+3, 200, 20);
        } else if (state == 1) {
            rgblight_blink_layer_repeat(channle%3, 3000, 1);
        }
    }
    return true;
}

bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        rgblight_set_layer_state(8, led_state.caps_lock);
    }
    return true;
}

#endif
