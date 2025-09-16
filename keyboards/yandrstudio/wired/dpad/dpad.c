// Copyright 2024 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "dpad.h"

#include "raw_hid.h"
bool yr_factory_test = false;
uint32_t rgb_t_itv = 1000;
uint32_t rgb_t_timer = 0;
uint8_t rgb_t_pos = 0;
uint8_t rgb_t_v = 10;

#ifdef RGB_MATRIX_ENABLE

// globol
kb_cstm_config_t kb_cstm_config;

led_config_t g_led_config = {
    {
        {6, 7, 8, NO_LED},
        {11, 10, 9, NO_LED},
        {12, 13, 14, NO_LED}
    },
    {
      // LED Index to Physical Position
        {0,0},{224,32},{0,64},{224,64},{0,32},{224,0},
        {0,0},{112,0},{224,0},
        {224,32},{112,32},{0,32},
        {0,64},{112,64},{224,64}
    },
    {
      // LED Index to Flag
      2,2,2, 2,2,2,
      4,4,4, 4,4,4, 4,4,4

    }
};

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }

    if (rgb_matrix_is_enabled()) {
        if (kb_cstm_config.top_rgb_sw == 1) {
            for (uint8_t i = led_min; i < led_max; ++i) {
                if ((g_led_config.flags[i] == 4)) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
        } else if (kb_cstm_config.top_rgb_sw == 2) {
            for (uint8_t i = led_min; i < led_max; ++i) {
                if ((g_led_config.flags[i] == 2)) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
        }
    }

    if (yr_factory_test) {
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

void eeconfig_init_kb_datablock(void) {
    kb_cstm_config.top_rgb_sw = 0;
    eeconfig_update_kb_datablock(&kb_cstm_config);
}

extern const rgb_matrix_driver_t rgb_matrix_driver;
void keyboard_post_init_kb(void) {
    eeconfig_read_kb_datablock(&kb_cstm_config);
    rgb_matrix_reload_from_eeprom();
    rgb_matrix_driver.flush();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case TOP_RGB_TOG:
            if (rgb_matrix_config.enable && record->event.pressed) {
                kb_cstm_config.top_rgb_sw += 1;
                kb_cstm_config.top_rgb_sw %= 3;
                eeconfig_update_kb_datablock(&kb_cstm_config);
            }
            return false;
        default:
            return process_record_user(keycode, record);
    }
    return process_record_user(keycode, record);
}

#endif

void keyboard_pre_init_kb(void) {
    palSetLineMode(A15, PAL_MODE_OUTPUT_PUSHPULL);
    writePin(A15, 0);
}


bool via_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id = &(data[0]);
    uint8_t *command_data = &(data[1]);
    if (*command_id == 0x03 && command_data[0] == 0x96) {
        dprintf(">>Recv a pkg with cmd_data1: [%d] cmd_data1: [%d]!!\n", command_data[1], command_data[2]);
        if (command_data[1] == 0x96) { // Factory test
            if (!yr_factory_test) {
                yr_factory_test = true;
            }
        }
        raw_hid_send(data, length);
        return true;
    }
    return false;
}

void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_TIM3_REMAP_PARTIALREMAP;
}
