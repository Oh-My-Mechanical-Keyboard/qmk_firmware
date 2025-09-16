// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAA51
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Y&R"
#define PRODUCT         "WYSE65"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

//                            0    1    2    3    4   5   6    7   8   9   10  11  12  13  14  15
#   define MATRIX_COL_PINS {  B12, B13, B14, B15, A8, A9, A10, B3, B4, B5, B6, B7, B8, A2, A3, A4 }
#   define MATRIX_ROW_PINS {  B1,  B2,  A6,  A5,  B10 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#ifdef ENCODER_ENABLE
#    define ENCODERS_PAD_A { A7 }
#    define ENCODERS_PAD_B { B0 }
#    define ENCODER_RESOLUTIONS { 2 }
#    define ENCODER_DEFAULT_POS 0x3
#endif

#define LED_CAPS_LOCK_PIN B11
#define LED_PIN_ON_STATE  1
