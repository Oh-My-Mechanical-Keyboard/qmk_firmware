// Copyright 2023 FxStudio <FXS@fx-studio.cn>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "adam0110.h"

#if defined(I_AM_LEFT) || defined(I_AM_RIGHT)
bool is_keyboard_left(void) {
#ifdef I_AM_LEFT
    return true;
#else
    return false;
#endif
}
#endif

#ifdef RGB_MATRIX_ENABLE

#define xx NO_LED

led_config_t g_led_config = {
    {
       //Left Hand
       // 0   1   2   3   4   5   6   7   8   9   10  11  12  13
        { 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63 },
        { 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36 },
        { 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, xx, 35 },
        { 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9  },
        { 0 , 1 , 2,  xx, xx, 3 , xx, xx, xx, 4 , 5 , 6 , 7 , 8  },
       //Right Hand
        { 80, 79, 66, 65, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx },
        { 77, 78, 67, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx },
        { 76, 75, 68, 64, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx },
        { 73, 74, 69, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx },
        { 72, xx, 71, 70, xx, xx, xx, xx, xx, xx, xx, xx, xx, xx }
    },{
        //Left Hand
        {0,64},{17,64},{34,64},              {86,64},                     {155,64},{172,64},{190,64},{207,64},{224,64},
        {224,48},{207,48},{190,48},{172,48},{155,48},{138,48},{121,48},{103,48},{86,48},{69,48},{52,48},{34,48},{17,48},{0,48},
        {0,32},{17,32},{34,32},{52,32},{69,32},{86,32},{103,32},{121,32},{138,32},{155,32},{172,32},{190,32},       {224,32},
        {224,16},{207,16},{190,16},{172,16},{155,16},{138,16},{121,16},{103,16},{86,16},{69,16},{52,16},{34,16},{17,16},{0,16},
        {0,0},{17,0},{34,0},{52,0},{69,0},{86,0},{103,0},{121,0},{138,0},{155,0},{172,0},{190,0},{207,0},{224,0},
        //Right Hand
        {224,32},{224,0},{149,0},{75,16},{149,32},{75,48},{224,64},{149,64},{0,64},{224,48},{149,48},{75,32},{0,32},{224,16},{149,16},{75,0},{0,0}
    },
    {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4,       4,          4, 4, 4, 4, 4,
    //Right Hand
    4, 4, 4, 4,
    4, 4, 4,
    4, 4, 4, 4,
    4, 4, 4,
    4,    4, 4
    }
};

#endif

void keyboard_post_init_kb(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_reload_from_eeprom();
#endif
}
