// Copyright 2024 HackStone-HAL9000 (@Jason)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "module.h"
#include "debug.h"
#include "logo_rgb.h"
// clang-format off

#undef ___
#define ___ NO_LED

led_config_t g_led_config = {
    {
        {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  11,  12,  13,  14,  15},
        {31,  30,  29,  28,  27,  26,  25,  24,  23,  22,  21,  20,  19,  18,  17,  16},
        {32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47},
        {63,  62,  61, 60,  59,  58,  57,  56,  55,  54,  53,  52,   NO_LED,  51,   NO_LED,   NO_LED},
        {64,   NO_LED,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,   NO_LED,  75,  76,   NO_LED},
        {89,  88,  87,   NO_LED,  86,   NO_LED,  85,  84,   NO_LED,  83,  82,  81,  80,  79,  78,  77},
    }, {
        {0,0},{15,0},{30,0},{45,0},{60,0},{75,0},{90,0},{105,0},{119,0},{134,0},{149,0},{164,0},{179,0},{194,0},{209,0},{224,0},
        {224,13},{209,13},{194,13},{179,13},{164,13},{149,13},{134,13},{119,13},{105,13},{90,13},{75,13},{60,13},{45,13},{30,13},{15,13},{0,13},
        {0,26},{15,26},{30,26},{45,26},{60,26},{75,26},{90,26},{105,26},{119,26},{134,26},{149,26},{164,26},{179,26},{194,26},{209,26},{224,26},
        {224,38}, {222,38}, {220,38},    {194,38},       {164,38},{149,38},{134,38},{119,38},{105,38},{90,38},{75,38},{60,38},{45,38},{30,38},{15,38},{0,38},
        {0,51},       {30,51},{45,51},{60,51},{75,51},{90,51},{105,51},{119,51},{134,51},{149,51},{164,51},       {194,51},{209,51},
        {224,64},{209,64},{194,64},{179,64},{164,64},{149,64},{134,64},       {105,64},{90,64},       {60,64},       {30,64},{15,64},{0,64}
}, {
    4,4,4,4,4, 4,4,4,4,4,
    4,4,4,4,4, 4,4,4,4,4,
    4,4,4,4,4, 4,4,4,4,4,

    4,4,4,4,4, 4,4,4,4,4,
    4,4,4,4,4, 4,4,4,4,4,
    4,4,4,4,4, 4,4,4,4,4,

    4,4,4,4,4, 4,4,4,4,4,
    4,4,4,4,4, 4,4,4,4,4,
    4,4,4,4,4, 4,4,4,4,4
}};

// rgb matrix layer
/*

rgb_matrix_adv_layer_segment_t wl_bt1_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({30, 1,  HSV_GREEN});  // 0
rgb_matrix_adv_layer_segment_t wl_bt2_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({29, 1,  HSV_GREEN});  // 1
rgb_matrix_adv_layer_segment_t wl_bt3_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({28, 1,  HSV_GREEN});  // 2
rgb_matrix_adv_layer_segment_t wl_24g_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({27, 1,  HSV_GREEN});  // 3
rgb_matrix_adv_layer_segment_t usb_layer[]      = RGB_MATRIX_LAYER_SEGMENTS({26, 1,  HSV_BLUE});   // 4
rgb_matrix_adv_layer_segment_t capslock_layer[] = RGB_MATRIX_LAYER_SEGMENTS({63, 1,  HSV_RED});    // 5
rgb_matrix_adv_layer_segment_t winlock_layer[]  = RGB_MATRIX_LAYER_SEGMENTS({88, 1,  HSV_RED});    // 6
rgb_matrix_adv_layer_segment_t bat_10_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({30, 1,  HSV_RED});    // 7
rgb_matrix_adv_layer_segment_t bat_20_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({29, 2,  HSV_RED});    // 8
rgb_matrix_adv_layer_segment_t bat_30_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({28, 3,  HSV_RED});    // 9
rgb_matrix_adv_layer_segment_t bat_40_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({27, 4,  HSV_YELLOW}); // 10
rgb_matrix_adv_layer_segment_t bat_50_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({26, 5,  HSV_YELLOW}); // 11
rgb_matrix_adv_layer_segment_t bat_60_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({25, 6,  HSV_YELLOW}); // 12
rgb_matrix_adv_layer_segment_t bat_70_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({24, 7,  HSV_YELLOW}); // 13
rgb_matrix_adv_layer_segment_t bat_80_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({23, 8,  HSV_GREEN});  // 14
rgb_matrix_adv_layer_segment_t bat_90_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({22, 9,  HSV_GREEN});  // 15
rgb_matrix_adv_layer_segment_t bat_100_layer[]  = RGB_MATRIX_LAYER_SEGMENTS({21, 10, HSV_GREEN});  // 16

*/

kb_cstm_config_t kb_cstm_config;

/* 只会调用一次 */
void eeconfig_init_kb_datablock(void) {

    kb_cstm_config.flage = 1;

    kb_cstm_config.key_rgb_sw = 1;
    kb_cstm_config.box_rgb_mode = 2;
    kb_cstm_config.box_rgb_colored  = 1;
    kb_cstm_config.box_rgb_val = BOX_LED_MAX_V;

    kb_cstm_config.box_rgb_speed = 2*BOX_LED_SPEED_STEP;
    kb_cstm_config.box_rgb_r = 0x7A;
    kb_cstm_config.box_rgb_g = 0;
    kb_cstm_config.box_rgb_b = 0xFF;
    eeprom_update_block(&kb_cstm_config, BOX_LED_EECONFIG_ADDR, sizeof(kb_cstm_config));

    wls_port_eeconfig_init();
}

void keyboard_post_init_kb(void) {
    eeprom_read_block(&kb_cstm_config, (void *)BOX_LED_EECONFIG_ADDR, sizeof(kb_cstm_config));
    // 无线PRE
    wls_port_init_pre();

    keyboard_post_init_user();

    debug_enable = true;

    // 无线POST
    wls_port_init_post();
}


bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {

    if (rgb_matrix_indicators_advanced_user(led_min, led_max) != true) {
        return false;
    }

    // 统一渲染
    logo_rgb_matrix_task();

    if (kb_cstm_config.key_rgb_sw == 0) {
        for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; ++i) {
            if (i == 48 || i == 49 || i == 50) {
                continue;
            }
            rgb_matrix_set_color(i, 0, 0, 0);
        }
    }

    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(63, 255, 255, 255);
    }

    if (keymap_config.no_gui) {
        rgb_matrix_set_color(88, 255, 255, 255);
    }

    // 无线模式提示
    wls_port_rgb_indicators_task();

    return true;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

    if (process_record_user(keycode, record) != true) {
        return false;
    }

    // 无线模式长短按
    if (process_record_wls(keycode, record) != true) {
        return false;
    }

    switch (keycode) {
        case KRGB_TOG:
            if (record->event.pressed) {
                if (kb_cstm_config.key_rgb_sw) {
                    kb_cstm_config.key_rgb_sw = 0;
                } else {
                    kb_cstm_config.key_rgb_sw = 1;
                }
                eeprom_update_block(&kb_cstm_config, BOX_LED_EECONFIG_ADDR, sizeof(kb_cstm_config));
            }
            return false;
        case LRGB_TOG:
            if (record->event.pressed) {
                rgb_box_mode_step(false);
            }
            return false;
        default:
            return true;
    }

    return false;
}

bool hs_factory_test = false;
bool via_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id = &(data[0]);
    uint8_t *command_data = &(data[1]);
    if (*command_id == 0x03 && command_data[0] == 0x96) {
        if (command_data[1] == 0x96) { // Factory test
            if (!hs_factory_test) {
                hs_factory_test = true;
            }
        }
        // length = 3;
        if (command_data[2] == 0x96) { // Factory test
            uint8_t check_data = md_get_version();
            dprintf("check_data %d\n", check_data);
            if (check_data < 51) {
                command_data[2] = 0x44;
            }
        }
        raw_hid_send(data, length);
        return true;
    }
    return false;
}
