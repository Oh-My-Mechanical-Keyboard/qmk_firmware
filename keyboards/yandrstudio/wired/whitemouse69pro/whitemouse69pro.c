/* Copyright 2021 JasonRen(biu)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "whitemouse69pro.h"

#ifdef RGB_MATRIX_ENABLE

// globol
typedef union {
    uint32_t raw;
    uint8_t underground_rgb_sw :8;
} kb_cums_t;
kb_cums_t kb_cums;

led_config_t g_led_config = {
    {
        {69,  71,  72,  74,  75,  77,  78,  80,  81,  83,  84,  86,  87,  89,  91},
        {67,  66,  65,  64,  63,  62,  61,  60,  59,  58,  57,  56,  55,  54,  53},
        {38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,   NO_LED,  49,  50,  51},
        {36,  35,  34,  33,  32,  31,  30,  29,  28,  27,  26,  25,  24,  23,  22},
        {1,  3,  4,  6,   NO_LED,   NO_LED,   NO_LED,  9,  11,  12,  14,  15,  17,  18,  20}
    },
    {
      // LED Index to Physical Position
        {0,64},{0,64},{22,64},{16,64},{32,64},{45,64},{48,64},{67,64},{90,64},                     {112,64},{112,64},{128,64},{144,64},{134,64},{160,64},{176,64},{157,64},{192,64},{208,64},{179,64},{224,64},{202,64},
        {224,48},{208,48},{192,48},{176,48},{160,48},{144,48},{128,48},{112,48},{96,48},{80,48},{64,48},{48,48},{32,48},{16,48},{0,48},{224,64},
        {0,32},{16,32},{32,32},{48,32},{64,32},{80,32},{96,32},{112,32},{128,32},{144,32},{160,32},       {192,32},{208,32},{224,32},{224,0},
        {224,16},{208,16},{192,16},{176,16},{160,16},{144,16},{128,16},{112,16},{96,16},{80,16},{64,16},{48,16},{32,16},{16,16},{0,16},{202,0},
        {0,0},{179,0},{16,0},{32,0},{157,0},{48,0},{64,0},{134,0},{80,0},{96,0},{112,0},{112,0},{128,0},{90,0},{144,0},{160,0},{67,0},{176,0},{192,0},{45,0},{208,0},{22,0},{224,0},{0,0}
    },
    {
      // LED Index to Flag
      2,4,2,4,4,2,4,2,2,4,2, 4,4,2,4,4,2,4,\
      4,2,4,2,4,4,4, 4,4,4,4,4,\
      4,4,4,4,4, 4,4,2,4,4,4,\
      4,4,4,4,4, 4,4,4,4,4,\
      4,2,4,4,4,4, 4,4,4,4,4,\
      4,4,4,4,4, 4,2,4,2,4,4,2,4,\
      4,2,4,4,2,4,4,2, 4,4,2,4,4,2,4,2,\
      4,2\
    }
};


bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (rgb_matrix_is_enabled()) {
        if (kb_cums.underground_rgb_sw == 1) {
            for (uint8_t i = led_min; i < led_max; ++i) {
                if ((g_led_config.flags[i] == 4)) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
        } else if (kb_cums.underground_rgb_sw == 2) {
            for (uint8_t i = led_min; i < led_max; ++i) {
                if ((g_led_config.flags[i] == 2)) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
        }
    } else {
        rgb_matrix_set_color_all(0,0,0);
    }
    return true;
}

void eeconfig_init_kb(void) {
    kb_cums.raw = 0;
    eeconfig_update_kb(kb_cums.raw);
}

void keyboard_post_init_kb(void) {
    kb_cums.underground_rgb_sw = eeconfig_read_kb();
}

#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	if (!process_record_user(keycode, record)) {
        return false;
    }
    switch(keycode) {
#ifdef RGB_MATRIX_ENABLE
        case URGB_K:
            if (rgb_matrix_config.enable && record->event.pressed) {
                kb_cums.underground_rgb_sw += 1;
                kb_cums.underground_rgb_sw %= 3;
            }
            eeconfig_update_kb(kb_cums.raw);
            return false;
#endif
        case LOCK_GUI:
            process_magic(GUI_TOG, record);
            return false;
        default:
            return true;
    }
    return true;
}
