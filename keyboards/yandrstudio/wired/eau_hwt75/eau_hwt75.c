// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "eau_hwt75.h"
#include "raw_hid.h"
bool yr_factory_test = false;
uint32_t rgb_t_itv = 1000;
uint32_t rgb_t_timer = 0;
uint8_t rgb_t_pos = 0;
uint8_t rgb_t_v = 5;

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {
    {
        {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  11,  12,  13,  14}, 
        {29,  28,  27,  26,  25,  24,  23,  22,  21,  20,  19,  18,  17,  16,  15}, 
        {30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44}, 
        {58,  57,  56,  55,  54,  53,  52,  51,  50,  49,  48,  47,   NO_LED,  46,  45}, 
        {59,   NO_LED,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72}, 
        {83,  82,  81,   NO_LED,   NO_LED,  NO_LED,  79,  NO_LED,   NO_LED,   NO_LED,  77,  76,  75,  74,  73}
    },
    {
        // LED Index to Physical Position
        {0,0},{16,0},{32,0},{48,0},{64,0},{80,0},{96,0},{112,0},{128,0},{144,0},{160,0},{176,0},{192,0},{208,0},{224,0},
        {224,13},{208,13},{192,13},{176,13},{160,13},{144,13},{128,13},{112,13},{96,13},{80,13},{64,13},{48,13},{32,13},{16,13},{0,13},
        {0,26},{16,26},{32,26},{48,26},{64,26},{80,26},{96,26},{112,26},{128,26},{144,26},{160,26},{176,26},{192,26},{208,26},{224,26},
        {224,38},{208,38},       {176,38},{160,38},{144,38},{128,38},{112,38},{96,38},{80,38},{64,38},{48,38},{32,38},{16,38},{0,38},
        {0,51},       {32,51},{48,51},{64,51},{80,51},{96,51},{112,51},{128,51},{144,51},{160,51},{176,51},{192,51},{208,51},{224,51},
        {224,64},{208,64},{192,64},{176,64},{160,64},              {112,64},{96,64},{80,64},              {32,64},{16,64},{0,64}
    },
    {
      // LED Index to Flag
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4
    }
};

void keyboard_post_init_kb(void) {
    rgb_matrix_reload_from_eeprom();
}
bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
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
#endif

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