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
#include QMK_KEYBOARD_H


#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
        {41,  40,  39,  38,  37,  36,  35,  34,  33,  32,  31,  30},
        {19,  20,  21,  22,  23,  24,  25,  26,  27,  28,   NO_LED,  29},
        {18,   NO_LED,  17,  16,  15,  14,  13,  12,  11,  10,  9,  8},
        {0,  1,  2,   NO_LED,  3,   NO_LED,   NO_LED,  4,   NO_LED,  5,  6,  7}
    },
    {
      // LED Index to Physical Position
        {0,64},{20,64},{41,64},       {81,64},              {143,64},       {183,64},{204,64},{224,64},
        {224,43},{204,43},{183,43},{163,43},{143,43},{122,43},{102,43},{81,43},{61,43},{41,43},       {0,43},
        {0,21},{20,21},{41,21},{61,21},{81,21},{102,21},{122,21},{143,21},{163,21},{183,21},       {224,21},
        {224,0},{204,0},{183,0},{163,0},{143,0},{122,0},{102,0},{81,0},{61,0},{41,0},{20,0},{0,0}
    },
    {
      // LED Index to Flag
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4
    }
};


#endif


