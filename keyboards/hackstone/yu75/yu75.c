// Copyright 2024 HackStone-HAL9000 (@Jason)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include "module.h"

/* 只会调用一次 */

void keyboard_post_init_kb(void) {
    // 同时初始化无线EECONFIG
    wls_port_eeconfig_init();

    // 无线PRE
    wls_port_init_pre();

    keyboard_post_init_user();

    // 无线POST
    wls_port_init_post();
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
        replaced_hid_send(data, length);
        return true;
    }
    return false;
}
