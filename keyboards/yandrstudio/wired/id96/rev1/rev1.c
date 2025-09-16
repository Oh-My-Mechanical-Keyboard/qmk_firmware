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
#include "rev1.h"


#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {
    {
        {101,  100,  99,  98,  97,  96,  95,  94,  93,  92,  91,  90,  89,  88,  87,  86,  85,  84,  83},
        {65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,   NO_LED,  78,  79,  80,  81,  82},
        {64,  63,  62,  61,  60,  59,  58,  57,  56,  55,  54,  53,  52,   NO_LED,  51,  50,  49,  48,  47},
        {31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,   NO_LED,  44,  45,  46,   NO_LED,   NO_LED},
        {30,  29,  28,  27,  26,  25,  24,  23,  22,  21,  20,  19,  18,   NO_LED,  17,  16,  15,   NO_LED,  14},
        {0,  1,  2,   NO_LED,  NO_LED,  4,  NO_LED,   NO_LED,  6,  7,  8,  9,  10,   NO_LED,  11,  12,  13,   NO_LED,   NO_LED}
    },
    {
        {0,64},{12,64},{25,64},       {50,64},       {75,64},{87,64},{100,64},{112,64},{124,64},{137,64},{149,64},       {174,64},{187,64},{199,64},
        {224,51},       {199,51},{187,51},{174,51},       {149,51},{137,51},{124,51},{112,51},{100,51},{87,51},{75,51},{62,51},{50,51},{37,51},{25,51},{12,51},{0,51},
        {0,38},{12,38},{25,38},{37,38},{50,38},{62,38},{75,38},{87,38},{100,38},{112,38},{124,38},{137,38},{149,38},       {174,38},{187,38},{199,38},
        {224,26},{212,26},{199,26},{187,26},{174,26},       {149,26},{137,26},{124,26},{112,26},{100,26},{87,26},{75,26},{62,26},{50,26},{37,26},{25,26},{12,26},{0,26},
        {0,13},{12,13},{25,13},{37,13},{50,13},{62,13},{75,13},{87,13},{100,13},{112,13},{124,13},{137,13},{149,13},       {174,13},{187,13},{199,13},{212,13},{224,13},
        {224,0},{212,0},{199,0},{187,0},{174,0},{162,0},{149,0},{137,0},{124,0},{112,0},{100,0},{87,0},{75,0},{62,0},{50,0},{37,0},{25,0},{12,0},{0,0},
        {0,64},{20,64},{41,64},{61,64},{81,64},{102,64},{122,64},{143,64},{163,64},{183,64},{204,64},{224,64},
        {224,0},{204,0},{183,0},{163,0},{143,0},{122,0},{102,0},{81,0},{61,0},{41,0},{20,0},{0,0}
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
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4,
      2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
      2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
      2, 2, 2, 2
    }
};

void keyboard_post_init_kb(void) {
    rgb_matrix_reload_from_eeprom();
    rgb_matrix_driver.flush();
}

#endif


#ifdef RGBLIGHT_ENABLE

void keyboard_post_init_kb(void) {
    rgblight_reload_from_eeprom();
}

#endif


bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case KC_LG:
            if (record->event.pressed) {
                process_magic(GUI_TOG, record);
            }
            return false;
        case KC_MACOS:
            if (record->event.pressed) {
                process_magic(CG_TOGG, record);
            }
            return false;
        case KC_MCTL:
            if (record->event.pressed) {
                host_consumer_send(0x29F);
            } else {
                host_consumer_send(0);
            }
            return false;
        case KC_LPAD:
            if (record->event.pressed) {
                host_consumer_send(0x2A0);
            } else {
                host_consumer_send(0);
            }
            return false;
        default:
            return true;
    }
    return true;
}
