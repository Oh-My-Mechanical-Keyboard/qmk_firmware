// Copyright 2024 HackStone-HAL9000 (@Jason)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "module.h"
#include "logo_rgb.h"
#include "wireless.h"
// clang-format off

kb_cstm_config_t kb_cstm_config;
bool hs_factory_test = false;
uint32_t rgb_t_itv = 1000;
uint32_t rgb_t_timer = 0;
uint8_t rgb_t_pos = 0;
uint8_t rgb_t_v = 10;

#undef ___
#define ___ NO_LED

led_config_t g_led_config = {
    {
        {NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED},
        {NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED},
        {NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED},
        {NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED},
        {NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED},
        {NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED,  NO_LED}
    }, {
        {100, 38},{120, 38},{140, 38},{160, 38},{180, 38},{200, 38},
        {224, 0},{224, 15},{224, 30},{224, 45},{224, 60},
        {180,64},{170,64},{160,64},{150,64},{140,64},  {130,64},{120,64},{110,64},{100,64},{90,64}, {80,64},{70,64},{60,64},{50,64},{40,64}, {30,64},{20,64},{10,64},{0,64},
        {0, 60},{0, 45},{0, 30},{0, 15},{0, 0}
    }, {
        4,4,4,4,4, 4,4,4,4,4,
        4,4,4,4,4, 4,4,4,4,4,
        4,4,4,4,4, 4,4,4,4,4,
        4,4,4,4,4
}};


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
    corner_rgb_matrix_task();

    if (kb_cstm_config.key_rgb_sw == 0) {
        for (uint8_t i = 0; i < 6; ++i) {
            rgb_matrix_set_color(i, 0, 0, 0);
        }
    }

    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = 0; i < 6; i++) {
            rgb_matrix_set_color(i, 200, 200, 200);
        }
    }

    // 无线模式提示
    wls_port_rgb_indicators_task();

    if (hs_factory_test) {
        if (rgb_t_timer == 0) rgb_t_timer = timer_read32();
        if (timer_elapsed32(rgb_t_timer) > rgb_t_itv) {
            rgb_t_timer = timer_read32();
            rgb_t_pos = (rgb_t_pos + 1) % 3;
        }
        switch (rgb_t_pos) {
            case 0:
                rgb_matrix_set_color_all(rgb_t_v, 0, 0);
                break;
            case 1:
                rgb_matrix_set_color_all(0, rgb_t_v, 0);
                break;
            case 2:
                rgb_matrix_set_color_all(0, 0, rgb_t_v);
            default:
                break;

        }
    }

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

    if (hs_factory_test) {
        switch(keycode) {
            case MO(1): {
                if (record->event.pressed) {
                    tap_code_delay(KC_APP, 30);
                }
                return false;
            }
            case KC_SPC: {
                if (record->event.pressed) {
                    if (wireless_get_current_devs() != DEVS_2G4) {
                        wireless_devs_change(wireless_get_current_devs(), DEVS_2G4, false);
                    } else {
                        tap_code_delay(KC_SPC, 30);
                    }
                }
                return false;
            }
        }
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
        case KRGB_TOG:
        case RGB_TOG:
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
    uint8_t *command_data = &(data[1]);
    if (command_id == 0x03 && command_data[0] == 0x96) {
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

    uint8_t value_id   = data[2];
    uint8_t value_data = data[3];
    dprintf("VCMD: %d, %d, %d, %d\n", command_id, channel_id, value_id, value_data);
    if (command_id == id_custom_set_value && channel_id == id_qmk_rgb_matrix_channel && value_id == id_qmk_rgb_matrix_effect) {
        if (value_data == 0) {
            kb_cstm_config.key_rgb_sw = 0;
            eeprom_update_block(&kb_cstm_config, BOX_LED_EECONFIG_ADDR, sizeof(kb_cstm_config));
            raw_hid_send(data, length);
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
