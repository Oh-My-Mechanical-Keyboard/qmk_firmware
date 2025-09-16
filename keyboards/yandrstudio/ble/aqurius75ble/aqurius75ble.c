// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "aqurius75ble.h"

#ifdef BIU_BLE5_ENABLE
#    include "biu_ble_common.h"
#endif

#ifdef RGB_MATRIX_ENABLE

#include "rgb_matrix_layer.h"

led_config_t g_led_config = {{
                                {81,   NO_LED,  80,  79,  78,  77,  76,  75,  74,  73,  72,  71,  70,  69,  68},
                                {53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67},
                                {52,  51,  50,  49,  48,  47,  46,  45,  44,  43,  42,  41,  40,  39,  38},
                                {24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,   NO_LED,  37},
                                {23,  22,  21,  20,  19,  18,  17,  16,  15,  14,  13,   NO_LED,  12,  11,  10},
                                {0,  1,  2,   NO_LED,   NO_LED,  3,   NO_LED,   NO_LED,   NO_LED,  4,  5,  6,  7,  8,  9}
                            },
                            {
                                {0,64},{16,64},{32,64},              {80,64},                     {144,64},{160,64},{176,64},{192,64},{208,64},{224,64},
                                {224,51},{208,51},{192,51},       {160,51},{144,51},{128,51},{112,51},{96,51},{80,51},{64,51},{48,51},{32,51},{16,51},{0,51},
                                {0,38},{16,38},{32,38},{48,38},{64,38},{80,38},{96,38},{112,38},{128,38},{144,38},{160,38},{176,38},{192,38},       {224,38},
                                {224,26},{208,26},{192,26},{176,26},{160,26},{144,26},{128,26},{112,26},{96,26},{80,26},{64,26},{48,26},{32,26},{16,26},{0,26},
                                {0,13},{16,13},{32,13},{48,13},{64,13},{80,13},{96,13},{112,13},{128,13},{144,13},{160,13},{176,13},{192,13},{208,13},{224,13},
                                {224,0},{208,0},{192,0},{176,0},{160,0},{144,0},{128,0},{112,0},{96,0},{80,0},{64,0},{48,0},{32,0},       {0,0}
                            },
                            {
                              // LED Index to Flag
                              4,4,4,4,4, 4,4,4,4,4,
                              4,4,4,4,4, 4,4,4,4,4,
                              4,4,4,4,4, 4,4,4,4,4,
                              4,4,4,4,4, 4,4,4,4,4,
                              4,4,4,4,4, 4,4,4,4,4,
                              4,4,4,4,4, 4,4,4,4,4,
                              4,4,4,4,4, 4,4,4,4,4,
                              4,4,4,4,4, 4,4,4,4,4,
                              4,4
                            }};

// rgb matrix layer

const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn1_layer[] = RGB_MATRIX_LAYER_SEGMENTS({51, 1, HSV_GREEN});  // 0
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn2_layer[] = RGB_MATRIX_LAYER_SEGMENTS({50, 1, HSV_GREEN});  // 1
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn3_layer[] = RGB_MATRIX_LAYER_SEGMENTS({49, 1, HSV_GREEN});  // 2
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn4_layer[] = RGB_MATRIX_LAYER_SEGMENTS({48, 1, HSV_GREEN});  // 3
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair1_layer[] = RGB_MATRIX_LAYER_SEGMENTS({51, 1, HSV_BLUE});   // 4
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair2_layer[] = RGB_MATRIX_LAYER_SEGMENTS({50, 1, HSV_BLUE});   // 5
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair3_layer[] = RGB_MATRIX_LAYER_SEGMENTS({49, 1, HSV_BLUE});   // 6
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair4_layer[] = RGB_MATRIX_LAYER_SEGMENTS({48, 1, HSV_BLUE});   // 7
const rgb_matrix_adv_layer_segment_t PROGMEM usb_pair_layer[] = RGB_MATRIX_LAYER_SEGMENTS({48, 1, HSV_BLUE});   // 8
const rgb_matrix_adv_layer_segment_t PROGMEM usb_conn_layer[] = RGB_MATRIX_LAYER_SEGMENTS({48, 1, HSV_GREEN});  // 9
const rgb_matrix_adv_layer_segment_t PROGMEM capslock_layer[] = RGB_MATRIX_LAYER_SEGMENTS({24, 1, HSV_RED});    // 10
const rgb_matrix_adv_layer_segment_t PROGMEM bat_10_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({54, 1, HSV_RED});     // 11
const rgb_matrix_adv_layer_segment_t PROGMEM bat_20_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({54, 2, HSV_GREEN});   // 12
const rgb_matrix_adv_layer_segment_t PROGMEM bat_30_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({54, 3, HSV_GREEN});   // 13
const rgb_matrix_adv_layer_segment_t PROGMEM bat_40_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({54, 4, HSV_GREEN});   // 14
const rgb_matrix_adv_layer_segment_t PROGMEM bat_50_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({54, 5, HSV_GREEN});   // 15
const rgb_matrix_adv_layer_segment_t PROGMEM bat_60_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({54, 6, HSV_GREEN});   // 16
const rgb_matrix_adv_layer_segment_t PROGMEM bat_70_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({54, 7, HSV_GREEN});   // 17
const rgb_matrix_adv_layer_segment_t PROGMEM bat_80_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({54, 8, HSV_GREEN});   // 18
const rgb_matrix_adv_layer_segment_t PROGMEM bat_90_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({54, 9, HSV_GREEN});   // 19
const rgb_matrix_adv_layer_segment_t PROGMEM bat_100_layer[]  = RGB_MATRIX_LAYER_SEGMENTS({54, 10, HSV_GREEN});  // 20

const rgb_matrix_adv_layer_segment_t* const PROGMEM my_rgb_matrix_layers[] =
                                                    RGB_MATRIX_LAYERS_LIST(bt_conn1_layer, bt_conn2_layer, bt_conn3_layer, bt_conn4_layer,
                                                                           bt_pair1_layer, bt_pair2_layer, bt_pair3_layer, bt_pair4_layer,
                                                                           usb_pair_layer, usb_conn_layer,
                                                                           capslock_layer,
                                                                           bat_10_layer, bat_20_layer, bat_30_layer, bat_40_layer, bat_50_layer,
                                                                           bat_60_layer, bat_70_layer, bat_80_layer, bat_90_layer, bat_100_layer);


void rgb_matrix_adv_unblink_all_but_caps_bat_layer(void) {
    for (uint8_t i = 0; i < 10; i++) {
        rgb_matrix_adv_unblink_layer(i);
    }
}

void rgb_matrix_adv_unblink_all_batlayer_but_one_layer(uint8_t l) {
    for (uint8_t i = 11; i < 21; i++) {
        if (l == i) continue;
        rgb_matrix_adv_unblink_layer(i);
    }
}

void rgb_matrix_adv_unblink_all_but_layer(uint8_t l) {
    for (uint8_t i = 0; i < 21; i++) {
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
    rgb_matrix_adv_set_layer_state(10, host_keyboard_led_state().caps_lock);
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
            rgb_matrix_adv_blink_layer_repeat(8, 500, 8);
        } else {
            rgb_matrix_adv_blink_layer_repeat(9, 1000, 1);
        }
    } else if (channle <= 7) {
        if (state == 7) {
            rgb_matrix_adv_blink_layer_repeat(channle%4, 500, 8);
        } else if (state == 8) {
            rgb_matrix_adv_blink_layer_repeat(channle%4+4, 200, 20);
        } else if (state == 1) {
            rgb_matrix_adv_blink_layer_repeat(channle%4, 3000, 1);
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
