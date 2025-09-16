// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "dpadble.h"

#ifdef RGB_MATRIX_ENABLE

#include "rgb_matrix_layer.h"

// globol
kb_cstm_config_t kb_cstm_config;

led_config_t g_led_config = {
    {
        {6, 7, 8, NO_LED},
        {11, 10, 9, NO_LED},
        {12, 13, 14, NO_LED}
    },
    {
      // LED Index to Physical Position
        {0,0},{224,32},{0,64},{224,64},{0,32},{224,0},
        {0,0},{112,0},{224,0},
        {224,32},{112,32},{0,32},
        {0,64},{112,64},{224,64}
    },
    {
      // LED Index to Flag
      2,2,2, 2,2,2,
      4,4,4, 4,4,4, 4,4,4

    }
};

// rgb matrix layer

const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn1_layer[] = RGB_MATRIX_LAYER_SEGMENTS({11, 1, HSV_GREEN});                     // 0
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn2_layer[] = RGB_MATRIX_LAYER_SEGMENTS({10, 1, HSV_GREEN});                     // 1
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair1_layer[] = RGB_MATRIX_LAYER_SEGMENTS({11, 1, HSV_BLUE});                      // 2
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair2_layer[] = RGB_MATRIX_LAYER_SEGMENTS({10, 1, HSV_BLUE});                      // 3
const rgb_matrix_adv_layer_segment_t PROGMEM usb_pair_layer[] = RGB_MATRIX_LAYER_SEGMENTS({9, 1, HSV_BLUE});                     // 4
const rgb_matrix_adv_layer_segment_t PROGMEM usb_conn_layer[] = RGB_MATRIX_LAYER_SEGMENTS({9, 1, HSV_GREEN});                    // 5
const rgb_matrix_adv_layer_segment_t PROGMEM bat_10_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({0, 1, HSV_RED});                      // 6
const rgb_matrix_adv_layer_segment_t PROGMEM bat_30_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({0, 1, HSV_GREEN}, {5, 1, HSV_GREEN});                    // 7
const rgb_matrix_adv_layer_segment_t PROGMEM bat_50_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({0, 2, HSV_GREEN}, {5, 1, HSV_GREEN});                    // 8
const rgb_matrix_adv_layer_segment_t PROGMEM bat_70_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({0, 2, HSV_GREEN}, {4, 2, HSV_GREEN}); // 9
const rgb_matrix_adv_layer_segment_t PROGMEM bat_90_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({0, 3, HSV_GREEN}, {4, 2, HSV_GREEN}); // 10
const rgb_matrix_adv_layer_segment_t PROGMEM bat_100_layer[]  = RGB_MATRIX_LAYER_SEGMENTS({0, 6, HSV_GREEN}); // 11

const rgb_matrix_adv_layer_segment_t* const PROGMEM my_rgb_matrix_layers[] =
                                                    RGB_MATRIX_LAYERS_LIST(bt_conn1_layer, bt_conn2_layer,
                                                                           bt_pair1_layer, bt_pair2_layer,
                                                                           usb_pair_layer, usb_conn_layer,
                                                                           bat_10_layer, bat_30_layer, bat_50_layer,
                                                                           bat_70_layer, bat_90_layer, bat_100_layer);


void rgb_matrix_adv_unblink_all_but_caps_bat_layer(void) {
    for (uint8_t i = 0; i < 6; i++) {
        rgb_matrix_adv_unblink_layer(i);
    }
}

void rgb_matrix_adv_unblink_all_batlayer_but_one_layer(uint8_t l) {
    for (uint8_t i = 6; i < 12; i++) {
        if (l == i) continue;
        rgb_matrix_adv_unblink_layer(i);
    }
}

void rgb_matrix_adv_unblink_all_but_layer(uint8_t l) {
    for (uint8_t i = 0; i < 12; i++) {
        if (l == i) continue;
        rgb_matrix_adv_unblink_layer(i);
    }
}

extern rgb_task_states rgb_task_state;

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }

    if (rgb_matrix_is_enabled()) {
        if (kb_cstm_config.top_rgb_sw == 1) {
            for (uint8_t i = led_min; i < led_max; ++i) {
                if ((g_led_config.flags[i] == 4)) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
        } else if (kb_cstm_config.top_rgb_sw == 2) {
            for (uint8_t i = led_min; i < led_max; ++i) {
                if ((g_led_config.flags[i] == 2)) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
        }
    }

    rgb_matrix_adv_blink_layer_repeat_helper();
    // If not enabled, then nothing else will actually set the LEDs...
    if (!rgb_matrix_is_enabled()) {
        rgb_task_state = FLUSHING;
    }
    return true;
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
    rgb_matrix_adv_unblink_all_but_caps_bat_layer();
    if (channle == 0xa) {
        if (state != 0xa0) {
            rgb_matrix_adv_blink_layer_repeat(4, 500, 8);
        } else {
            rgb_matrix_adv_blink_layer_repeat(5, 1000, 1);
        }
    } else if (channle <= 7) {
        if (state == 7) {
            rgb_matrix_adv_blink_layer_repeat(channle%2, 500, 8);
        } else if (state == 8) {
            rgb_matrix_adv_blink_layer_repeat(channle%2+2, 200, 20);
        } else if (state == 1) {
            rgb_matrix_adv_blink_layer_repeat(channle%2, 3000, 1);
        }
    }
    if (!rgb_matrix_is_enabled()) {
        rgb_task_state = FLUSHING;
    }
    return true;
}

void eeconfig_init_kb_datablock(void) {
    kb_cstm_config.top_rgb_sw = 0;
    eeconfig_update_kb_datablock(&kb_cstm_config);
}

extern const rgb_matrix_driver_t rgb_matrix_driver;
void keyboard_post_init_kb(void) {
    eeconfig_read_kb_datablock(&kb_cstm_config);
    rgb_matrix_reload_from_eeprom();
    rgb_matrix_driver.flush();
    rgb_matrix_layers = my_rgb_matrix_layers;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case TOP_RGB_TOG:
            if (rgb_matrix_config.enable && record->event.pressed) {
                kb_cstm_config.top_rgb_sw += 1;
                kb_cstm_config.top_rgb_sw %= 3;
                eeconfig_update_kb_datablock(&kb_cstm_config);
            }
            return false;
        default:
            return process_record_user(keycode, record);
    }
    return process_record_user(keycode, record);
}

#endif

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_kb(void) {
    rgblight_reload_from_eeprom();
}
#endif

#ifndef BIU_BLE5_ENABLE
void keyboard_pre_init_kb(void) {
    palSetLineMode(RGB_BLE_SW, PAL_MODE_OUTPUT_PUSHPULL);
    writePin(RGB_BLE_SW, 0);
}
#endif
