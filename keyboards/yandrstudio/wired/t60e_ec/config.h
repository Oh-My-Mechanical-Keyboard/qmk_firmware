// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAA40
#define MANUFACTURER    "MACHINA"
#define PRODUCT         "MACHINA Cloudnine EC"
/* USB Device descriptor parameter */
#define DEVICE_VER      0x0001

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL
/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

//                         0   1    2    3    4   5   6   7   8   9   10  11  12  13
// #define MATRIX_COL_PINS {  B2, B10, B11, A15, B3, B4, B5, B7, B8, B9, A3, A4, A5, A6}
#define MATRIX_ROW_PINS {  A3, A4, A5, A6, A7 }
#define DISCHARGE_PIN B1
#define APLEX_EN_PIN_0 A7
#define APLEX_EN_PIN_1 A5
#define ADC_READ_PIN B0
