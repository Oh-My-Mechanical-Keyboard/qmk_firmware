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
 * along with this program.  If not, see <http: //www.gnu.org/licenses/>.
 */
#include "z_alice_ble.h"

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {
    {
        { 68,  67,  66,  65,  64,  63,  62,  61,  60,  59,  58,  57,  56,  55,  54,  53 },
        { 52,  51,  50,  49,  48,  47,  46,  45,  44,  43,  42,  41,  40,  39,  38,   NO_LED },
        { 37,  36,  35,  34,  33,  32,  31,  30,  29,  28,  27,  26,  25,   NO_LED,  24,   NO_LED },
        { NO_LED,  23,  22,  21,  20,  19,  18,  17,  16,  15,  14,  13,  12,  11,  10,   NO_LED },
        { NO_LED,  9,   NO_LED,  8,   NO_LED,  7,  6,   NO_LED,  5,   NO_LED,  4,   NO_LED,  3,  2,  1,  0 }
    },
    {


        {224,64},{209,64},{194,64},{179,64},       {149,64},       {119,64},       {90,64},{75,64},       {45,64},       {15,64},
               {209,48},{194,48},{179,48},{164,48},{149,48},{134,48},{119,48},{105,48},{90,48},{75,48},{60,48},{45,48},{30,48},{15,48},
               {209,32},       {179,32},{164,32},{149,32},{134,32},{119,32},{105,32},{90,32},{75,32},{60,32},{45,32},{30,32},{15,32},{0,32},
               {209,16},{194,16},{179,16},{164,16},{149,16},{134,16},{119,16},{105,16},{90,16},{75,16},{60,16},{45,16},{30,16},{15,16},{0,16},
        {224,0},{209,0},{194,0},{179,0},{164,0},{149,0},{134,0},{119,0},{105,0},{90,0},{75,0},{60,0},{45,0},{30,0},{15,0},{0,0}
    },
    {
      // LED Index to Flag
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4
    }
};


#endif

#ifdef Z_ALICE_REV1
void keyboard_pre_init_kb(void) {
    palSetLineMode(B5, PAL_MODE_INPUT_PULLDOWN);
}
#endif

void keyboard_post_init_kb(void) {
    // debug_enable = true;
}

#ifndef BIU_BLE5_ENABLE
void keyboard_pre_init_kb(void) {
    palSetLineMode(RGB_BLE_SW, PAL_MODE_OUTPUT_PUSHPULL);
    writePin(RGB_BLE_SW, 0);
}
#endif
