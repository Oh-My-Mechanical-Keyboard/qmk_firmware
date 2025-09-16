// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
// #    define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_STATIC_LIGHT
#    define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL+5



#define USB_DRIVER USBD2

// #define WAIT_FOR_USB

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define ADC_RESOLUTION ADC_CFGR1_RES_12BIT
#define ADC_SAMPLING_RATE ADC_SMPR_SMP_55P5

#define NUM_OF_MUX   10
#define MUX_ADD_PIN0 C8
#define MUX_ADD_PIN1 C9
#define MUX_ADD_PIN2 A8
#define MUX_CHANNLE_NUMS 8
// ADC PIN               L                   R
#define MUX_OUT_PIN2MCU {A4, C0, A5, C1, A6, C2, C3, A1, A0, A2}
#define DRIN_ADDR 3

// #define _ 0xff
#define MUX_ADDR_TO_MX { \
    {{2,0}, {3,3}, {4,1}, {4,3}, {2,3}, {2,8}, {3, 9}, {4, 6}, {2,11}, {4, 8}}, \
    {{1,0}, {1,5}, {3,1}, {3,5}, {1,3}, {3,7}, {1, 9}, {3,11}, {1,11}, {3,12}}, \
    {{0,0}, {0,5}, {2,1}, {2,6}, {0,3}, {0xff,0}, {0, 9}, {0xff, 0}, {0,11}, {0xff, 0}}, \
    {{0xff,0}, {0xff,0}, {0xff,0}, {0xff,0}, {0xff,0}, {0xff,0}, {0xff, 0}, {0xff, 0}, {0xff, 0}, {0xff, 0}}, \
    {{1,1}, {1,6}, {1,2}, {1,7}, {1,4}, {1,8}, {1,10}, {1,13}, {1,12}, {1,14}}, \
    {{3,0}, {2,5}, {2,2}, {2,7}, {2,4}, {3,8}, {2,10}, {2,12}, {3,10}, {2,13}}, \
    {{0,1}, {0,6}, {0,2}, {0,7}, {0,4}, {0,8}, {0,10}, {0,13}, {0,12}, {0,14}}, \
    {{4,0}, {3,4}, {4,2}, {3,6}, {3,2}, {2,9}, {4, 4}, {4, 7}, {4, 5}, {4, 9}}  \
}

#define EECONFIG_YR_FLASH_BASE 0x0800C000 // +48K
#define EECONFIG_YR_DATA_SIZE (16384)
