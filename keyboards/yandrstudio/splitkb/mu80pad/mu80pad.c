// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "mu80pad.h"
#include <string.h>
#include <transactions.h>

bool is_keyboard_left(void) {
#ifdef I_AM_LEFT
    return true;
#else
    return false;
#endif

}


#ifdef RGB_MATRIX_ENABLE

#include "rgb_matrix_layer.h"

extern rgb_task_states rgb_task_state;

led_config_t g_led_config = {
    {
        {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  11,  12,  13,  14,  15,  16},
        {33,  32,  31,  30,  29,  28,  27,  26,  25,  24,  23,  22,  21,  20,  19,  18,  17},
        {34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50},
        {69,  68,  67,  66,  65,  64,  63,  62,  61,  60,  59,  58,   NO_LED,  57,   NO_LED,   NO_LED,   NO_LED},
        {70,  71,  72,  73,  74,  75,  76,  77,  78,  79,  80,   NO_LED,  81,   NO_LED,   NO_LED,  82,   NO_LED},
        {92,  91,  90,  89,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,  88,  87,  86,  85,  84,  83},
        /*right*/
        {123,  125,  127,  129,               NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {133,  132,  131,  130,               NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {134,  135,  136,  137,             NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {140,  139,  138,   NO_LED,      NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {141,  142,  143,  144,           NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {146,   NO_LED,  145,   NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
    },
    {
        // LED Index to Physical Position
        // left
        {0,0},{14,0},{28,0},{42,0},{56,0},{70,0},{84,0},{98,0},{112,0},{126,0},{140,0},{154,0},{168,0},{182,0},{196,0},{210,0},{224,0},
        {224,13},{210,13},{196,13},{182,13},{168,13},{154,13},{140,13},{126,13},{112,13},{98,13},{84,13},{70,13},{56,13},{42,13},{28,13},{14,13},{0,13},
        {0,26},{14,26},{28,26},{42,26},{56,26},{70,26},{84,26},{98,26},{112,26},{126,26},{140,26},{154,26},{168,26},{182,26},{196,26},{210,26},{224,26},
        {196,26},{196,26},{210,26},{210,26},{224,26},{224,26}, // logo led
                            {182,38},       {154,38},{140,38},{126,38},{112,38},{98,38},{84,38},{70,38},{56,38},{42,38},{28,38},{14,38},{0,38},
        {0,51},{14,51},{28,51},{42,51},{56,51},{70,51},{84,51},{98,51},{112,51},{126,51},{140,51},       {168,51},              {210,51},       
        {224,64},{210,64},{196,64},{182,64},{168,64},{154,64},                                                 {42,64},{28,64},{14,64},{0,64},
        // left underglow
        {0,64},{20,64},{41,64},{61,64},{81,64},{102,64},{122,64},{143,64},{163,64},{183,64},{204,64},{224,64},
        {224, 48}, {224, 32}, {224, 16},
        {224,0},{204,0},{183,0},{163,0},{143,0},{122,0},{102,0},{81,0},{61,0},{41,0},{20,0},{0,0},
        {0, 16}, {0, 32}, {0, 48},
        // right
        {0,0},{37,0},{75,0},{112,0},{149,0},{186,0},{224,0},
        {224,13},{149,13},{75,13},{0,13},
        {0,26},{75,26},{149,26},{224,26},
            {149,38},{75,38},{0,38},
        {0,51},{75,51},{149,51},{224,51},
            {149,64},       {0,64},
        // right underglow
        {224,64}, {224,48},  {224,32}, {224,16}, {224,0},
        {0, 0},   {0, 16},   {0, 32},  {0, 48},  {0, 64},
        {56, 64}, {112, 64}, {168, 64}


    },
    {
      // LED Index to Flag
      4,4,4,4,4, 4,4,4,4,4, // 0
      4,4,4,4,4, 4,4,4,4,4, // 1 
      4,4,4,4,4, 4,4,4,4,4, // 2
      4,4,4,4,4, 4,4,4,4,4, // 3
      4,4,4,4,4, 4,4,4,4,4, // 4
      4,8,8,8,8, 8,8,4,4,4, // 5
      4,4,4,4,4, 4,4,4,4,4, // 6
      4,4,4,4,4, 4,4,4,4,4, // 7
      4,4,4,4,4, 4,4,4,4,4, // 8
      4,4,4,2,2, 2,2,2,2,2, // 9
      2,2,2,2,2, 2,2,2,2,2, // 10
      2,2,2,2,2, 2,2,2,2,2, // 11
      2,2,2,4,2, 4,2,4,2,4, // 12
      4,4,4,4,4, 4,4,4,4,4, // 13
      4,4,4,4,4, 4,4,2,2,2, // 14
      2,2,2,2,2, 2,2,2,2,2  // 15
    }
};

const rgb_matrix_adv_layer_segment_t PROGMEM my_capslock_layer[] = RGB_MATRIX_LAYER_SEGMENTS(
    {69, 1, HSV_RED}
);

const rgb_matrix_adv_layer_segment_t PROGMEM my_numblock_layer[] = RGB_MATRIX_LAYER_SEGMENTS(
    {133, 1, HSV_RED}
);

const rgb_matrix_adv_layer_segment_t* const PROGMEM my_rgb_matrix_layers[] = RGB_MATRIX_LAYERS_LIST(
    my_capslock_layer,
    my_numblock_layer
);

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    rgb_matrix_adv_blink_layer_repeat_helper();
    rgb_matrix_adv_set_layer_state(0, host_keyboard_led_state().caps_lock);
    rgb_matrix_adv_set_layer_state(1, host_keyboard_led_state().num_lock);

    // If not enabled, then nothing else will actually set the LEDs...
    if (!rgb_matrix_is_enabled()) {
        rgb_task_state = FLUSHING;
    }
    return true;
}


void keyboard_post_init_kb(void) {
    rgb_matrix_reload_from_eeprom();
    rgb_matrix_layers = my_rgb_matrix_layers;
#ifdef CONSOLE_ENABLE
    debug_enable = true;
    debug_matrix = true;
#endif
}

#endif


void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_TIM2_REMAP_PARTIALREMAP1;
}