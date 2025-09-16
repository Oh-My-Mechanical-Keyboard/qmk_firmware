// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "dk8710.h"


const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Each AW20216 channel is controlled by a register at some offset between 0x00
 * and 0xD7 inclusive.
 * See drivers/awinic/aw20216.h for the mapping between register offsets and
 * driver pin locations.
 *    driver
 *    |  R location
 *    |  |        G location
 *    |  |        |        B location
 *    |  |        |        | */
    /* Line 1*/
    { 0,  CS1_SW1,    CS2_SW1,    CS3_SW1  },
    { 0,  CS7_SW1,    CS8_SW1,    CS9_SW1  },
    { 0,  CS13_SW1,   CS14_SW1,   CS15_SW1  },
    { 0,  CS19_SW1,   CS20_SW1,   CS21_SW1  },
    { 0,  CS25_SW1,   CS26_SW1,   CS27_SW1  },
    { 0,  CS28_SW1,   CS29_SW1,   CS30_SW1  },
    { 0,  CS1_SW2,    CS2_SW2,    CS3_SW2  },
    { 0,  CS7_SW2,    CS8_SW2,    CS9_SW2  },
    { 0, CS13_SW2,   CS14_SW2,   CS15_SW2  },
    { 0, CS19_SW2,   CS20_SW2,   CS21_SW2  },
    { 0, CS28_SW2,   CS29_SW2,   CS30_SW2  },
    { 0,  CS1_SW3,    CS2_SW3,    CS3_SW3  },
    { 0,  CS7_SW3,    CS8_SW3,    CS9_SW3  },
    { 0, CS13_SW3,   CS14_SW3,   CS15_SW3  },
    { 0, CS19_SW3,   CS20_SW3,   CS21_SW3  },
    { 0, CS25_SW3,   CS26_SW3,   CS27_SW3  },
    { 0, CS28_SW3,   CS29_SW3,   CS30_SW3  },
    { 0,  CS1_SW4,    CS2_SW4,    CS3_SW4  },
    { 0,  CS7_SW4,    CS8_SW4,    CS9_SW4  },
    { 0, CS13_SW4,   CS14_SW4,   CS15_SW4  },
    { 0, CS19_SW4,   CS20_SW4,   CS21_SW4  },
    { 0, CS25_SW4,   CS26_SW4,   CS27_SW4  },
    { 0, CS28_SW4,   CS29_SW4,   CS30_SW4  },
    { 0,  CS1_SW5,    CS2_SW5,    CS3_SW5  },
    { 0,  CS7_SW5,    CS8_SW5,    CS9_SW5  },
    { 0, CS13_SW5,   CS14_SW5,   CS15_SW5  },
    { 0, CS19_SW5,   CS20_SW5,   CS21_SW5  },
    { 0, CS25_SW5,   CS26_SW5,   CS27_SW5  },
    { 0, CS28_SW5,   CS29_SW5,   CS30_SW5  },
    { 0,  CS1_SW6,    CS2_SW6,    CS3_SW6  },
    { 0,  CS7_SW6,    CS8_SW6,    CS9_SW6  },
    { 0, CS13_SW6,   CS14_SW6,   CS15_SW6  },
    { 0, CS19_SW6,   CS20_SW6,   CS21_SW6  },
    { 0, CS25_SW6,   CS26_SW6,   CS27_SW6  },
    { 0, CS28_SW6,   CS29_SW6,   CS30_SW6  },
    { 0,  CS1_SW7,    CS2_SW7,    CS3_SW7  },
    { 0,  CS7_SW7,    CS8_SW7,    CS9_SW7  },
    { 0, CS13_SW7,   CS14_SW7,   CS15_SW7  },
    { 0, CS19_SW7,   CS20_SW7,   CS21_SW7  },
    { 0, CS25_SW7,   CS26_SW7,   CS27_SW7  },
    { 0, CS28_SW7,   CS29_SW7,   CS30_SW7  },
    { 0,  CS1_SW8,    CS2_SW8,    CS3_SW8  },
    { 0,  CS7_SW8,    CS8_SW8,    CS9_SW8  },
    { 0, CS13_SW8,   CS14_SW8,   CS15_SW8  },
    { 0, CS19_SW8,   CS20_SW8,   CS21_SW8  },
    { 0, CS25_SW8,   CS26_SW8,   CS27_SW8  },
    { 0, CS28_SW8,   CS29_SW8,   CS30_SW8  },
    { 0,  CS1_SW9,    CS2_SW9,    CS3_SW9  },
    { 0,  CS7_SW9,    CS8_SW9,    CS9_SW9  },
    { 0, CS13_SW9,   CS14_SW9,   CS15_SW9  },
    { 0, CS19_SW9,   CS20_SW9,   CS21_SW9  },
    { 0, CS25_SW9,   CS26_SW9,   CS27_SW9  },
    { 0, CS28_SW9,   CS29_SW9,   CS30_SW9  },
    { 0, CS4_SW1,   CS5_SW1,   CS6_SW1  },
    { 0, CS4_SW2,   CS5_SW2,   CS6_SW2  },
    { 0, CS4_SW3,   CS5_SW3,   CS6_SW3  },
    { 0, CS4_SW4,   CS5_SW4,   CS6_SW4  },
    { 0, CS10_SW1,   CS11_SW1,   CS12_SW1  },
    { 0, CS10_SW2,   CS11_SW2,   CS12_SW2  },
    { 0, CS10_SW3,   CS11_SW3,   CS12_SW3  },
    { 0, CS10_SW4,   CS11_SW4,   CS12_SW4  },
    { 0, CS10_SW5,   CS11_SW5,   CS12_SW5  },
    { 0, CS10_SW6,   CS11_SW6,   CS12_SW6  },
    { 0, CS10_SW7,   CS11_SW7,   CS12_SW7  },
    { 0, CS10_SW8,   CS11_SW8,   CS12_SW8  },
    { 0, CS10_SW9,   CS11_SW9,   CS12_SW9  },
    { 0, CS16_SW1,   CS17_SW1,   CS18_SW1  },
    { 0, CS16_SW2,   CS17_SW2,   CS18_SW2  },
    { 0, CS16_SW3,   CS17_SW3,   CS18_SW3  },
    { 0, CS16_SW4,   CS17_SW4,   CS18_SW4  },
    { 0, CS16_SW5,   CS17_SW5,   CS18_SW5  },
    { 0, CS16_SW6,   CS17_SW6,   CS18_SW6  },
    { 0, CS16_SW7,   CS17_SW7,   CS18_SW7  },
    { 0, CS22_SW1,   CS23_SW1,   CS24_SW1  },
    { 0, CS22_SW2,   CS23_SW2,   CS24_SW2  },
    { 0, CS22_SW3,   CS23_SW3,   CS24_SW3  },
    { 0, CS22_SW5,   CS23_SW5,   CS24_SW5  },
    { 0, CS22_SW6,   CS23_SW6,   CS24_SW6  },
    { 0, CS22_SW7,   CS23_SW7,   CS24_SW7  },
    { 0, CS22_SW8,   CS23_SW8,   CS24_SW8  },
    { 0, CS22_SW9,   CS23_SW9,   CS24_SW9  }
};


led_config_t g_led_config = {
    {
        {0,  6,      11,  17,  23,  29,  35,  41,  47,  53,  54,  55,  56,   NO_LED},
        {1,  7,      12,  18,  24,  30,  36,  42,  48,  57,  58,  59,  60,   NO_LED},
        {2,  8,      13,  19,  25,  31,  37,  43,  49,  66,  67,  68,  69,  70},
        {3,  9,      14,  20,  26,  32,  38,  44,  50,  73,  74,  75,  NO_LED,  76},
        {4,  NO_LED, 15,  21,  27,  33,  39,  45,  51,  77,  78,  79,   NO_LED,  80},
        {5,  10,     16,   NO_LED,   NO_LED,  22,   NO_LED,   NO_LED,   NO_LED,  28,  34,   NO_LED,  40,  61},
        {62, 63,   NO_LED,  64,  65,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,  52,  72,  46,  71}
    },
    {
     {207,0},{190,0},{172,0},{155,0},{138,0},{121,0},{103,0},{86,0},{69,0},{52,0},{34,0},{17,0},{0,0},
    {0,11},{17,11},{34,11},{52,11},{69,11},{86,11},{103,11},{121,11},{138,11},{155,11},{172,11},{190,11},{207,11},
    {224,21},{207,21},{190,21},{172,21},{155,21},{138,21},{121,21},{103,21},{86,21},{69,21},{52,21},{34,21},{17,21},{0,21},
    {0,32},{17,32},{34,32},{52,32},{69,32},{86,32},{103,32},{121,32},{138,32},{155,32},{172,32},{190,32},       {224,32},
    {224,43},       {190,43},{172,43},{155,43},{138,43},{121,43},{103,43},{86,43},{69,43},{52,43},{34,43},       {0,43},
    {0,53},{17,53},{34,53},              {86,53},                     {155,53},{172,53},       {207,53},{224,53},
    {224,64},{207,64},{190,64},{172,64},                                   {69,64},{52,64},       {17,64},{0,64}
    },
    {
      // LED Index to Flag
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4

    }
};
