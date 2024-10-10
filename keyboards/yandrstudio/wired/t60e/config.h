// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAA40
#define MANUFACTURER    "MACHINA"
#define PRODUCT         "MACHINA Cloudnine"
/* USB Device descriptor parameter */
#define DEVICE_VER      0x0001

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL
/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

// 焊接 V1.02热拔插
#define MATRIX_COL_PINS {  B2, B10, B11, A15, B3, B4, B5, B7, B8, B9, A3, A4, A5, A6}
#define MATRIX_ROW_PINS {  A2, A1,  A0,  B6,  A7 }

// V1 热拔插
// #define MATRIX_COL_PINS {  B2, B10, B11, A15, B3, B4, B5, B6, B8, B9, A3, A4, A5, A6}
// #define MATRIX_ROW_PINS {  A2, A1,  A0,  B7,  B0 }

#define LED_CAPS_LOCK_PIN B1
#define LED_PIN_ON_STATE  1

#define TAP_CODE_DELAY 15

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5
