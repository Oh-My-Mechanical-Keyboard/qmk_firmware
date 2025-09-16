/* Copyright 2022 JasonRen(biu)
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
#include "popo75.h"

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {
    {
        {0,   NO_LED,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  11,  12,  13}, 
        {28,  27,  26,  25,  24,  23,  22,  21,  20,  19,  18,  17,  16,  15,  14}, 
        {29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43}, 
        {57,  56,  55,  54,  53,  52,  51,  50,  49,  48,  47,  46,   NO_LED,  45,  44}, 
        {58,   NO_LED,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71}, 
        {82,  81,  80,   NO_LED,  79,   NO_LED,  78,   NO_LED,  77,   NO_LED,  76,  75,  74,  73,  72}
    },
    {
        {0,0},       {32,0},{48,0},{64,0},{80,0},{96,0},{112,0},{128,0},{144,0},{160,0},{176,0},{192,0},{208,0},{224,0},
        {224,13},{208,13},{192,13},{176,13},{160,13},{144,13},{128,13},{112,13},{96,13},{80,13},{64,13},{48,13},{32,13},{16,13},{0,13},
        {0,26},{16,26},{32,26},{48,26},{64,26},{80,26},{96,26},{112,26},{128,26},{144,26},{160,26},{176,26},{192,26},{208,26},{224,26},
        {224,38},{208,38},       {176,38},{160,38},{144,38},{128,38},{112,38},{96,38},{80,38},{64,38},{48,38},{32,38},{16,38},{0,38},
        {0,51},       {32,51},{48,51},{64,51},{80,51},{96,51},{112,51},{128,51},{144,51},{160,51},{176,51},{192,51},{208,51},{224,51},
        {224,64},{208,64},{192,64},{176,64},{160,64},       {128,64},       {96,64},       {64,64},       {32,64},{16,64},{0,64}
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
      4, 4, 4
    }
};

void keyboard_post_init_kb(void) {
    rgb_matrix_reload_from_eeprom();
}

#endif
