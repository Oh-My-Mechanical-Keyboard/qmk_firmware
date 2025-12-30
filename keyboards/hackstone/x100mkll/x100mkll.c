// Copyright 2024 HackStone-HAL9000 (@Jason)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "debug.h"
#include "logo_rgb.h"

// clang-format off

#undef ___
#define ___ NO_LED

led_config_t g_led_config = {
    {
        {17,   NO_LED,  16,  15,  14,  13,  12,  11,  10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0}, 
        {18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36}, 
        {55, 54,  53,  52,  51,  50,  49,  48,  47,  46,  45,  44,  43,  42,  41,  40,  39,  38,   NO_LED}, 
        {56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,   67, NO_LED,  68,  69,  70,  71,  72, 37}, 
        {92,   NO_LED,  91,  90,  89,  88,  87,  86,  85,  84,  83,  82,  81,  80,   NO_LED,  75,  74,  73,   NO_LED}, 
        {93,  94,  95,   NO_LED,   NO_LED,   NO_LED,  96,   NO_LED,   NO_LED,   NO_LED,  97,  98,  99,  100,  101,   NO_LED,  102,  103,  104}
    }, {
        {224,0},{212,0},{199,0},{187,0},{174,0},{162,0},{149,0},{137,0},{124,0},{112,0},{100,0},{87,0},{75,0},{62,0},{50,0},{37,0},{25,0},       {0,0},
        {0,13},{12,13},{25,13},{37,13},{50,13},{62,13},{75,13},{87,13},{100,13},{112,13},{124,13},{137,13},{149,13},{162,13},{174,13},{187,13},{199,13},{212,13},{224,13},
            {212,26},{199,26},{187,26},{174,26},{162,26},{149,26},{137,26},{124,26},{112,26},{100,26},{87,26},{75,26},{62,26},{50,26},{37,26},{25,26},{12,26},{0,26},
        {0,38},{12,38},{25,38},{37,38},{50,38},{62,38},{75,38},{87,38},{100,38},{112,38},{124,38},{137,38},       {162,38},{174,38},{187,38},{199,38},{212,38},{224,38},
            {212,51},{199,51},{187,51},
            {180,51}, {175,51}, {170,51}, {166,51},
            {162,51},{149,51},{137,51},{124,51},{112,51},{100,51},{87,51},{75,51},{62,51},{50,51},{37,51},{25,51},       {0,51},
        {0,64},{12,64},{25,64},                     {75,64},                     {124,64},{137,64},{149,64},{162,64},{174,64},       {199,64},{212,64},{224,64}
}, {
    4,4,4,4,4, 4,4,4,4,4,
    4,4,4,4,4, 4,4,4,4,4,
    4,4,4,4,4, 4,4,4,4,4,

    4,4,4,4,4, 4,4,4,4,4,
    4,4,4,4,4, 4,4,4,4,4,
    4,4,4,4,4, 4,4,4,4,4,

    4,4,4,4,4, 4,4,4,4,4,
    4,4,4,4,4, 4,4,4,4,4,
    4,4,4,4,4, 4,4,4,4,4,

    4,4,4,4,4, 4,4,4,4,4,
    4,4,4,4,4
}};


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
            if (i == 76 || i == 77 || i == 78 || i == 79) {
                continue;
            }
            rgb_matrix_set_color(i, 0, 0, 0);
        }
    }

    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(56, 255, 255, 255);
    }

    if (host_keyboard_led_state().num_lock) {
        rgb_matrix_set_color(33, 255, 255, 255);
    }

    if (keymap_config.no_gui) {
        rgb_matrix_set_color(94, 255, 255, 255);
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
        case LRGB_VAL:
            if (record->event.pressed) {
                rgb_box_val_step(false);
            }
            return false;
        case LRGB_SPD:
            if (record->event.pressed) {
                rgb_box_speed_step(false);
            }
            return false;
        case LRGB_COL:
            if (record->event.pressed) {
                rgb_box_color_step(false);
            }
            return false;
        case RGB_TOG:
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



bool via_command_kb(uint8_t *data, uint8_t length) {
    uint8_t command_id = data[0];
    uint8_t channel_id = data[1];
    uint8_t value_id   = data[2];
    uint8_t value_data = data[3];
    dprintf("VCMD: %d, %d, %d, %d\n", command_id, channel_id, value_id, value_data);
    if (command_id == id_custom_set_value && channel_id == id_qmk_rgb_matrix_channel && value_id == id_qmk_rgb_matrix_effect) {
        if (value_data == 0) {
            kb_cstm_config.key_rgb_sw = 0;
            eeprom_update_block(&kb_cstm_config, BOX_LED_EECONFIG_ADDR, sizeof(kb_cstm_config));
            replaced_hid_send(data, length);
            return true; // 接管
        } else {
            kb_cstm_config.key_rgb_sw = 1;
            eeprom_update_block(&kb_cstm_config, BOX_LED_EECONFIG_ADDR, sizeof(kb_cstm_config));
            return false; // 不接管
        }
    }
    return false;
}


enum via_corner_rgb_value {
    via_crgb_brightness = 1,
    via_crgb_speed = 2,
    via_crgb_effect = 3,
    via_crgb_colored = 4,
    via_crgb_rgb = 5
};

void via_config_set_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch ( *value_id )
    {
        case via_crgb_brightness:
            rgb_box_val_set(value_data[0]);
            break;
        case via_crgb_speed:
            rgb_box_speed_set(value_data[0]);
            break;
        case via_crgb_effect:
            rgb_box_mode_set(value_data[0]);
            break;
        case via_crgb_colored:
            rgb_box_colored_set(value_data[0]);
            break;
        case via_crgb_rgb: {
            HSV hsv = (HSV){HSV_BLACK};
            hsv.h = value_data[0];
            hsv.s = value_data[1];
            hsv.v = 255;
            rgb_box_color_set(hsv_to_rgb(hsv));
        } break;
    }
}
void via_config_get_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch ( *value_id )
    {
        case via_crgb_brightness:
            value_data[0] = rgb_box_val_get();
            break;
        case via_crgb_speed:
            value_data[0] = rgb_box_speed_get();
            break;
        case via_crgb_effect:
            value_data[0] = rgb_box_mode_get();
            break;
        case via_crgb_colored:
            value_data[0] = rgb_box_colored_get();
            break;
        case via_crgb_rgb: {
            HSV hsv = rgb_to_hsv(rgb_box_color_get());
            value_data[0] = hsv.h;
            value_data[1] = hsv.s;
        } break;
    }
}
void via_config_save_value(void) {
    eeprom_update_block(&kb_cstm_config, BOX_LED_EECONFIG_ADDR, sizeof(kb_cstm_config));
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value: {
                via_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value: {
                via_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save: {
                via_config_save_value();
                break;
            }
            default: {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }

    // Return the unhandled state
    *command_id = id_unhandled;
}
