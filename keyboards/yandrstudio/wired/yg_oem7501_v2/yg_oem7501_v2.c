// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "yg_oem7501_v2.h"

#include "raw_hid.h"
bool yr_factory_test = false;
uint32_t rgb_t_itv = 1000;
uint32_t rgb_t_timer = 0;
uint8_t rgb_t_pos = 0;
uint8_t rgb_t_v = 10;

#ifdef RGBLIGHT_ENABLE

void keyboard_post_init_kb(void) {
    rgblight_reload_from_eeprom();
}
#endif


void housekeeping_task_kb(void) {
    if (yr_factory_test) {
        if (rgblight_get_mode() != RGBLIGHT_MODE_STATIC_LIGHT) {
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        } else {
            if (rgb_t_timer == 0) rgb_t_timer = timer_read32();
            if (timer_elapsed32(rgb_t_timer) > rgb_t_itv) {
                rgb_t_timer = timer_read32();
                rgb_t_pos = (rgb_t_pos + 1) % 3;
            }
            switch (rgb_t_pos) {
                case 0:
                    rgblight_setrgb(rgb_t_v, 0, 0);
                    break;
                case 1:
                    rgblight_setrgb(0, rgb_t_v, 0);
                    break;
                case 2:
                    rgblight_setrgb(0, 0, rgb_t_v);
                default:
                    break;

            }
        }
    }
}

bool via_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id = &(data[0]);
    uint8_t *command_data = &(data[1]);
    if (*command_id == 0x03 && command_data[0] == 0x96) {
        dprintf(">>Recv a pkg with cmd_data1: [%d]!!\n", command_data[1]);
        if (command_data[1] == 0x96) { // Factory test
            if (!yr_factory_test) {
                yr_factory_test = true;
            }
            raw_hid_send(data, length);
        }
        return true;
    }
    return false;
}
