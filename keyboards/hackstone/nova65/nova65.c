// Copyright 2024 HackStone-HAL9000 (@Jason)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "module.h"
#include "wireless.h"

// clang-format off

kb_cstm_config_t kb_cstm_config;
bool hs_factory_test = false;
uint32_t rgb_t_itv = 1000;
uint32_t rgb_t_timer = 0;
uint8_t rgb_t_pos = 0;
uint8_t rgb_t_v = 10;

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
        replaced_hid_send(data, length);
        return true;
    }

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
        case WIN_LOCK:
            if (record->event.pressed) {
                keymap_config.raw = eeconfig_read_keymap();
                if (keymap_config.no_gui) {
                    keymap_config.no_gui = false;
                } else {
                    keymap_config.no_gui = true;
                }
                    eeconfig_update_keymap(keymap_config.raw);
            }
            return false;
        default:
            return true;
    }
    return true;
}

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

kb_cstm_config_t kb_cstm_config;

/* 只会调用一次 */
void eeconfig_init_kb_datablock(void) {

    kb_cstm_config.flag = 1;
    kb_cstm_config.key_rgb_sw = 1;

    eeprom_update_block(&kb_cstm_config, BOX_LED_EECONFIG_ADDR, sizeof(kb_cstm_config));
}

/* 只会调用一次 */
void keyboard_post_init_kb(void) {

    eeprom_read_block(&kb_cstm_config, (void *)BOX_LED_EECONFIG_ADDR, sizeof(kb_cstm_config));
    if (kb_cstm_config.flag == 0) {
        eeconfig_init_kb_datablock();
    }

    // 同时初始化无线EECONFIG
    wls_port_eeconfig_init();

    // 无线PRE
    wls_port_init_pre();

    keyboard_post_init_user();

#ifdef CONSOLE_ENABLE
    debug_enable=true;
#endif
    // 无线POST
    wls_port_init_post();
}


bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {

    if (kb_cstm_config.key_rgb_sw == 0) { // 最高优先级
        rgb_matrix_set_color_all(0, 0, 0);
    }

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

