// Copyright 2024 HackStone-HAL9000 (@Jason)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// clang-format off

#undef ___
#define ___ NO_LED

led_config_t g_led_config = {
    {
        {NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED},
        {NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED},
        {NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED},
        {NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED},
        {NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED}
    }, {
        {0,0},{15,0},{30,0},
        {224,64},{209,64},{194,64}
}, {
    4,4,4,4,4,4
}};


/* 只会调用一次 */

void keyboard_post_init_kb(void) {
    // 同时初始化无线EECONFIG
    wls_port_eeconfig_init();

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

    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(0, 255, 255, 255);
        rgb_matrix_set_color(1, 255, 255, 255);
        rgb_matrix_set_color(2, 255, 255, 255);
        rgb_matrix_set_color(3, 255, 255, 255);
        rgb_matrix_set_color(4, 255, 255, 255);
        rgb_matrix_set_color(5, 255, 255, 255);
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
    return true;
}
