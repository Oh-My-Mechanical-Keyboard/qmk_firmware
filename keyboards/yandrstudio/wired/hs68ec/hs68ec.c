// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "hs68ec.h"

void keyboard_post_init_kb() {
    keyboard_post_init_user();
    debug_enable = true;
}

bool via_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id = &(data[0]);
    uint8_t *command_data = &(data[1]);
    if (*command_id == 0x96 && command_data[0] == 0x96) {
        if (command_data[1] == 0x96) {
            eeconfig_disable();
            wait_ms(100);
        }
        if (command_data[2] == 0x96) {
            bootloader_jump();
        } else if (command_data[2] == 0x97) {
            NVIC_SystemReset();
        } else if (command_data[2] == 0x98) {
            bootloader_jump();
        }
        return true;
    }
    return false;
}