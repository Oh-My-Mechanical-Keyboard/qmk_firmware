// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ckw87ble.h"

#ifdef BIU_BLE5_ENABLE
#    include "biu_ble_common.h"
#endif

#if defined(RGBLIGHT_ENABLE) && defined(BIU_BLE5_ENABLE)

const rgblight_segment_t PROGMEM bt_conn[] = RGBLIGHT_LAYER_SEGMENTS( {10, 1, HSV_GREEN} );                    // 0
const rgblight_segment_t PROGMEM bt_pair[] = RGBLIGHT_LAYER_SEGMENTS( {10, 1, HSV_BLUE} );                     // 1
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 3, HSV_WHITE}, {10, 1, HSV_WHITE}); // 2
const rgblight_segment_t PROGMEM bat_10_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 3, HSV_RED});                    // 3
const rgblight_segment_t PROGMEM bat_30_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 3, HSV_GREEN});                  // 4
const rgblight_segment_t PROGMEM bat_50_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 5, HSV_GREEN});                  // 5
const rgblight_segment_t PROGMEM bat_70_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 7, HSV_GREEN});                  // 6
const rgblight_segment_t PROGMEM bat_90_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 9, HSV_GREEN});                  // 7
const rgblight_segment_t PROGMEM bat_100_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 10, HSV_GREEN});                // 8

const rgblight_segment_t* const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST(bt_conn, bt_pair,
                                                                             my_capslock_layer,
                                                                             bat_10_layer, bat_30_layer, bat_50_layer,
                                                                             bat_70_layer, bat_90_layer, bat_100_layer);

void rgb_adv_unblink_all_layer(void) {
    for (uint8_t i = 0; i < 9; i++) {
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
    if (channle <= 7) {
        if (state == 7) {
            rgblight_blink_layer_repeat(0, 500, 8);
        } else if (state == 8) {
            rgblight_blink_layer_repeat(1, 200, 20);
        } else if (state == 1) {
            rgblight_blink_layer_repeat(0, 3000, 1);
        }
    }
    return true;
}

bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        rgblight_set_layer_state(2, led_state.caps_lock);
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
    writePin(RGB_BLE_SW, RGB_EN_STATE);
}
#endif
