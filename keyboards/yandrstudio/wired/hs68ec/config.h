// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAA2B
#define MANUFACTURER    "HS"
#define PRODUCT         "HS68EC"
/* USB Device descriptor parameter */
#define DEVICE_VER      0x0001

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL
/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* EC Keyboard no NEED */
#define DEBOUNCE 1

/*                            c0 c1 c2 c3 c4 c5 c6 | c7 c8 c9 c10 c11 c12 c13 c14 */
#define MATRIX_COL_CHANNELS { 6, 7, 5, 3, 0, 2, 1,    4, 6, 2, 0,  3,  7,  1,  5 }
#define MATRIX_ROW_PINS {  A8, A10, A9, C6, B15 }
#define MUX_SEL_PINS {  B0, B1, B2 }
#define DISCHARGE_PIN A5
#define APLEX_EN_PIN_0 A7
#define APLEX_EN_PIN_1 B12
#define ADC_READ_PIN A6 // ADC2 3

#define MS_MX_MASK {{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},\
                    {1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},\
                    {1,1,1,1,1, 1,1,1,1,1, 1,1,1,0,1},\
                    {1,0,1,1,1, 1,1,1,1,1, 1,1,1,1,1},\
                    {1,1,1,0,0, 0,1,0,0,0, 1,1,1,1,1}}


