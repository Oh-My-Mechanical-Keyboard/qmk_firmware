// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rsalice_ble.h"

#ifdef BIU_BLE5_ENABLE
#    include "biu_ble_common.h"
#endif

#ifdef RGB_MATRIX_ENABLE

#include "rgb_matrix_layer.h"

led_config_t g_led_config = {{
                                {41,     42,     43,     44,     45,     46,     NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
                                {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, 0,      1,      2,      3,      4,      5,      6},
                                {40,     39,     38,     37,     36,     35,     NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
                                {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, 12,     11,     10,     9,      8,      NO_LED, 7},
                                {29,     30,     31,     32,     33,     34,     NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
                                {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, 13,     14,     15,     16,     17,     18,     19},
                                {28,     27,     NO_LED, 26,     25,     NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
                                {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, 24,     23,     NO_LED, 22,     21,     20}
                            },
                            {
                                {122,9},{142,9},{162,9},{183,9},{203,9},{224,9},{244,9},
                                {244,27},{203,27},{183,27},{162,27},{142,27},{122,27},
                                {122,45},{142,45},{162,45},{183,45},{203,45},{224,45},{244,45},
                                {244,64},{224,64},{203,64},{162,64},{142,64},{81,64},{61,64},{20,64},{0,64},
                                {0,36},{20,36},{40,36},{61,36},{81,36},{101,36},
                                {101,18},{81,18},{61,18},{40,18},{20,18},{0,18},
                                {0,0},{20,0},{40,0},{61,0},{81,0},{101,0}
                            },
                            {
                              // LED Index to Flag
                              4,4,4,4,4, 4,4,4,4,4,
                              4,4,4,4,4, 4,4,4,4,4,
                              4,4,4,4,4, 4,4,4,4,4,
                              4,4,4,4,4, 4,4,4,4,4,
                              4,4,4,4,4, 4,4
                            }};

// rgb matrix layer

const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn1_layer[] = RGB_MATRIX_LAYER_SEGMENTS({39, 1, HSV_GREEN});  // 0
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn2_layer[] = RGB_MATRIX_LAYER_SEGMENTS({38, 1, HSV_GREEN});  // 1
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn3_layer[] = RGB_MATRIX_LAYER_SEGMENTS({37, 1, HSV_GREEN});  // 2
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair1_layer[] = RGB_MATRIX_LAYER_SEGMENTS({39, 1, HSV_BLUE});   // 3
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair2_layer[] = RGB_MATRIX_LAYER_SEGMENTS({38, 1, HSV_BLUE});   // 4
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair3_layer[] = RGB_MATRIX_LAYER_SEGMENTS({37, 1, HSV_BLUE});   // 5
const rgb_matrix_adv_layer_segment_t PROGMEM usb_pair_layer[] = RGB_MATRIX_LAYER_SEGMENTS({36, 1, HSV_BLUE});   // 6
const rgb_matrix_adv_layer_segment_t PROGMEM usb_conn_layer[] = RGB_MATRIX_LAYER_SEGMENTS({36, 1, HSV_GREEN});  // 7
const rgb_matrix_adv_layer_segment_t PROGMEM capslock_layer[] = RGB_MATRIX_LAYER_SEGMENTS({40, 1, HSV_RED});    // 8
const rgb_matrix_adv_layer_segment_t PROGMEM bat_10_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({42, 1, HSV_RED});     // 9
const rgb_matrix_adv_layer_segment_t PROGMEM bat_20_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({42, 2, HSV_GREEN});   // 10
const rgb_matrix_adv_layer_segment_t PROGMEM bat_30_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({42, 3, HSV_GREEN});   // 11
const rgb_matrix_adv_layer_segment_t PROGMEM bat_40_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({42, 4, HSV_GREEN});   // 12
const rgb_matrix_adv_layer_segment_t PROGMEM bat_50_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({42, 5, HSV_GREEN});   // 13
const rgb_matrix_adv_layer_segment_t PROGMEM bat_60_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({42, 5, HSV_GREEN}, {0, 1, HSV_GREEN});   // 14
const rgb_matrix_adv_layer_segment_t PROGMEM bat_70_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({42, 5, HSV_GREEN}, {0, 2, HSV_GREEN});   // 15
const rgb_matrix_adv_layer_segment_t PROGMEM bat_80_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({42, 5, HSV_GREEN}, {0, 3, HSV_GREEN});   // 16
const rgb_matrix_adv_layer_segment_t PROGMEM bat_90_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({42, 5, HSV_GREEN}, {0, 4, HSV_GREEN});   // 17
const rgb_matrix_adv_layer_segment_t PROGMEM bat_100_layer[]  = RGB_MATRIX_LAYER_SEGMENTS({42, 5, HSV_GREEN}, {0, 5, HSV_GREEN});  // 18

const rgb_matrix_adv_layer_segment_t* const PROGMEM my_rgb_matrix_layers[] =
                                                    RGB_MATRIX_LAYERS_LIST(bt_conn1_layer, bt_conn2_layer, bt_conn3_layer,
                                                                           bt_pair1_layer, bt_pair2_layer, bt_pair3_layer,
                                                                           usb_pair_layer, usb_conn_layer,
                                                                           capslock_layer,
                                                                           bat_10_layer, bat_20_layer, bat_30_layer, bat_40_layer, bat_50_layer,
                                                                           bat_60_layer, bat_70_layer, bat_80_layer, bat_90_layer, bat_100_layer);


void rgb_matrix_adv_unblink_all_but_caps_bat_layer(void) {
    for (uint8_t i = 0; i < 8; i++) {
        rgb_matrix_adv_unblink_layer(i);
    }
}

void rgb_matrix_adv_unblink_all_batlayer_but_one_layer(uint8_t l) {
    for (uint8_t i = 9; i < 19; i++) {
        if (l == i) continue;
        rgb_matrix_adv_unblink_layer(i);
    }
}

void rgb_matrix_adv_unblink_all_but_layer(uint8_t l) {
    for (uint8_t i = 0; i < 19; i++) {
        if (l == i) continue;
        rgb_matrix_adv_unblink_layer(i);
    }
}

extern rgb_task_states rgb_task_state;

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }

    rgb_matrix_adv_blink_layer_repeat_helper();
    rgb_matrix_adv_set_layer_state(8, host_keyboard_led_state().caps_lock);
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
            rgb_matrix_adv_blink_layer_repeat(6, 500, 8);
        } else {
            rgb_matrix_adv_blink_layer_repeat(7, 1000, 1);
        }
    } else if (channle <= 7) {
        if (state == 7) {
            rgb_matrix_adv_blink_layer_repeat(channle%3, 500, 8);
        } else if (state == 8) {
            rgb_matrix_adv_blink_layer_repeat(channle%3+3, 200, 20);
        } else if (state == 1) {
            rgb_matrix_adv_blink_layer_repeat(channle%3, 3000, 1);
        }
    }
    if (!rgb_matrix_is_enabled()) {
        rgb_task_state = FLUSHING;
    }
    return true;
}

void keyboard_post_init_kb(void) {
    rgb_matrix_reload_from_eeprom();
    rgb_matrix_layers = my_rgb_matrix_layers;
    // debug_enable = true;
}

#endif


#ifndef BIU_BLE5_ENABLE
void keyboard_pre_init_kb(void) {
    palSetLineMode(RGB_BLE_SW, PAL_MODE_OUTPUT_PUSHPULL);
    writePin(RGB_BLE_SW, 0);
}
#endif
