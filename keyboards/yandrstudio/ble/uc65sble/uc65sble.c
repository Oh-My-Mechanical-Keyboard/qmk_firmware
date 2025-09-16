// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "uc65sble.h"

#ifdef BIU_BLE5_ENABLE
#    include "biu_ble_common.h"
#endif

#ifdef RGB_MATRIX_ENABLE

#    include "rgb_matrix_layer.h"


led_config_t g_led_config = {{{0, 1, 2, 3, 4, 6, 8, 10, 11, 13, 15, 17, 18, 19, 20}, {21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35}, {36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, NO_LED, 48, NO_LED}, {51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, NO_LED, 62, 63, NO_LED}, {64, 65, 66, 67, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, 68, 69, NO_LED, 70, 71, 72}},
                             {{0, 0},   {16, 0},  {32, 0},  {48, 0},  {64, 0},   {80, 0},   {80, 0},   {96, 0},   {96, 0},   {112, 0},  {112, 0}, {128, 0}, {144, 0}, {144, 0}, {160, 0}, {160, 0}, {176, 0}, {176, 0},  {192, 0},  {208, 0},  {224, 0},  {0, 16},   {16, 16},  {32, 16}, {48, 16}, {64, 16}, {80, 16}, {96, 16},  {112, 16}, {128, 16}, {144, 16}, {160, 16}, {176, 16}, {192, 16}, {208, 16}, {224, 16}, {0, 32}, {16, 32}, {32, 32},
                              {48, 32}, {64, 32}, {80, 32}, {96, 32}, {112, 32}, {128, 32}, {144, 32}, {160, 32}, {176, 32}, {208, 32}, {0, 48},  {16, 48}, {32, 48}, {48, 48}, {64, 48}, {80, 48}, {96, 48}, {112, 48}, {128, 48}, {144, 48}, {160, 48}, {192, 48}, {208, 48}, {0, 64},  {16, 64}, {32, 64}, {48, 64}, {144, 64}, {160, 64}, {192, 64}, {208, 64}, {224, 64}, {224, 48}, {224, 32}, {224, 16}, {0, 16},   {0, 32}, {0, 48}
                             },
                             {// LED Index to Flag
                              4, 4, 4, 4, 4, 2, 4, 2, 4, 2, 4, 4, 2, 4, 2, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2}};

// globol
kb_cstm_config_t kb_cstm_config;

// rgb matrix layer
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn1_layer[] = RGB_MATRIX_LAYER_SEGMENTS({22, 1, HSV_GREEN});                                                                                                   // 0
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn2_layer[] = RGB_MATRIX_LAYER_SEGMENTS({23, 1, HSV_GREEN});                                                                                                   // 1
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn3_layer[] = RGB_MATRIX_LAYER_SEGMENTS({24, 1, HSV_GREEN});                                                                                                   // 2
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn4_layer[] = RGB_MATRIX_LAYER_SEGMENTS({25, 1, HSV_GREEN});                                                                                                   // 3
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair1_layer[] = RGB_MATRIX_LAYER_SEGMENTS({22, 1, HSV_BLUE});                                                                                                    // 4
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair2_layer[] = RGB_MATRIX_LAYER_SEGMENTS({23, 1, HSV_BLUE});                                                                                                    // 5
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair3_layer[] = RGB_MATRIX_LAYER_SEGMENTS({24, 1, HSV_BLUE});                                                                                                    // 6
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair4_layer[] = RGB_MATRIX_LAYER_SEGMENTS({25, 1, HSV_BLUE});                                                                                                    // 7
const rgb_matrix_adv_layer_segment_t PROGMEM usb_pair_layer[] = RGB_MATRIX_LAYER_SEGMENTS({38, 1, HSV_BLUE});                                                                                                    // 8
const rgb_matrix_adv_layer_segment_t PROGMEM usb_conn_layer[] = RGB_MATRIX_LAYER_SEGMENTS({38, 1, HSV_GREEN});                                                                                                   // 9
const rgb_matrix_adv_layer_segment_t PROGMEM capslock_layer[] = RGB_MATRIX_LAYER_SEGMENTS({49, 1, HSV_RED});                                                                                                     // 10
const rgb_matrix_adv_layer_segment_t PROGMEM bat_10_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({50, 1, HSV_RED});                                                                                                     // 11
const rgb_matrix_adv_layer_segment_t PROGMEM bat_20_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 2, HSV_GREEN});                                                                                                    // 12
const rgb_matrix_adv_layer_segment_t PROGMEM bat_30_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 3, HSV_GREEN});                                                                                                    // 13
const rgb_matrix_adv_layer_segment_t PROGMEM bat_40_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 4, HSV_GREEN});                                                                                                    // 14
const rgb_matrix_adv_layer_segment_t PROGMEM bat_50_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 4, HSV_GREEN}, {6, 1, HSV_GREEN});                                                                                 // 15
const rgb_matrix_adv_layer_segment_t PROGMEM bat_60_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 4, HSV_GREEN}, {6, 1, HSV_GREEN}, {8, 1, HSV_GREEN});                                                              // 16
const rgb_matrix_adv_layer_segment_t PROGMEM bat_70_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 4, HSV_GREEN}, {6, 1, HSV_GREEN}, {8, 1, HSV_GREEN}, {10, 1, HSV_GREEN});                                          // 17
const rgb_matrix_adv_layer_segment_t PROGMEM bat_80_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 4, HSV_GREEN}, {6, 1, HSV_GREEN}, {8, 1, HSV_GREEN}, {10, 2, HSV_GREEN});                                          // 18
const rgb_matrix_adv_layer_segment_t PROGMEM bat_90_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 4, HSV_GREEN}, {6, 1, HSV_GREEN}, {8, 1, HSV_GREEN}, {10, 2, HSV_GREEN}, {13, 1, HSV_GREEN});                      // 19
const rgb_matrix_adv_layer_segment_t PROGMEM bat_100_layer[]  = RGB_MATRIX_LAYER_SEGMENTS({1, 4, HSV_GREEN}, {6, 1, HSV_GREEN}, {8, 1, HSV_GREEN}, {10, 2, HSV_GREEN}, {13, 1, HSV_GREEN}, {15, 1, HSV_GREEN});  // 20

const rgb_matrix_adv_layer_segment_t* const PROGMEM my_rgb_matrix_layers[] = RGB_MATRIX_LAYERS_LIST(bt_conn1_layer, bt_conn2_layer, bt_conn3_layer, bt_conn4_layer, bt_pair1_layer, bt_pair2_layer, bt_pair3_layer, bt_pair4_layer, usb_pair_layer, usb_conn_layer, capslock_layer, bat_10_layer, bat_20_layer, bat_30_layer, bat_40_layer, bat_50_layer, bat_60_layer, bat_70_layer, bat_80_layer, bat_90_layer, bat_100_layer);

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

extern rgb_task_states              rgb_task_state;
extern rgb_matrix_adv_layers_mask_t rgb_matrix_adv_enabled_layer_mask;
extern rgb_matrix_adv_layers_mask_t _blinking_layer_mask;

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    rgb_matrix_set_color(49, 0, 0, 0);
    rgb_matrix_set_color(50, 0, 0, 0);
    if (rgb_matrix_is_enabled()) {
        if (kb_cstm_config.underground_rgb_sw == 1) {
            for (uint8_t i = led_min; i < led_max; ++i) {
                if ((g_led_config.flags[i] == 4)) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
        } else if (kb_cstm_config.underground_rgb_sw == 2) {
            for (uint8_t i = led_min; i < led_max; ++i) {
                if ((g_led_config.flags[i] == 2)) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
        }
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
    if (channle == 0xa) {
        if (state != 0xa0) {
            rgb_matrix_adv_unblink_all_but_caps_bat_layer();
            rgb_matrix_adv_blink_layer_repeat(8, 500, 8);
        } else {
            rgb_matrix_adv_unblink_all_but_caps_bat_layer();
            rgb_matrix_adv_blink_layer_repeat(9, 1000, 1);
        }
    } else if (channle <= 7) {
        if (state == 7) {
            rgb_matrix_adv_unblink_all_but_layer(channle % 4);
            rgb_matrix_adv_blink_layer_repeat(channle % 4, 500, 8);
        } else if (state == 8) {
            rgb_matrix_adv_unblink_all_but_layer(channle % 4 + 4);
            rgb_matrix_adv_blink_layer_repeat(channle % 4 + 4, 200, 20);
        } else if (state == 1) {
            rgb_matrix_adv_unblink_all_but_layer(channle % 4);
            rgb_matrix_adv_blink_layer_repeat(channle % 4, 3000, 1);
        } else {
            rgb_matrix_adv_unblink_all_but_caps_bat_layer();
        }
    }
    if (!rgb_matrix_is_enabled()) {
        rgb_task_state = FLUSHING;
    }
    return true;
}

void eeconfig_init_kb(void) {
    kb_cstm_config.raw = 0;
    eeconfig_update_kb(kb_cstm_config.raw);
}

void keyboard_post_init_kb(void) {
    kb_cstm_config.underground_rgb_sw = eeconfig_read_kb();
    rgb_matrix_reload_from_eeprom();
    rgb_matrix_layers = my_rgb_matrix_layers;
}
#endif

#ifndef BIU_BLE5_ENABLE
void keyboard_pre_init_kb(void) {
    palSetLineMode(RGB_BLE_SW, PAL_MODE_OUTPUT_PUSHPULL);
    writePin(RGB_BLE_SW, 0);
}
#endif
