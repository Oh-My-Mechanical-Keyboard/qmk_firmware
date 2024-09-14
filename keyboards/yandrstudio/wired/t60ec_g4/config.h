// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAA45
#define MANUFACTURER    "MACHINA"
#define PRODUCT         "Cloudnine EC"
/* USB Device descriptor parameter */
#define DEVICE_VER      0x0001

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL
/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14
/*                            c0 c1 c2 c3 c4 c5 c6 | c7 c8 c9 c10 c11 c12 c13*/
#define MATRIX_COL_CHANNELS { 3, 0, 1, 2, 7, 4, 6,    3, 0, 1, 2, 6,  4,  7 }
#define MATRIX_ROW_PINS {  B14, B13, B12, B2, B7 }
#define MUX_SEL_PINS {  C4, B0, B1 }
#define DISCHARGE_PIN A5
#define APLEX_EN_PIN_0 B15
#define APLEX_EN_PIN_1 A7
#define ADC_READ_PIN A6 // ADC2 3

