// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAAD6
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Y&R"
#define PRODUCT         "TC80"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

//                           0    1   2   3   4   5   6   7   8   9   10  11  12  13   14  15  16
#   define MATRIX_COL_PINS { A15, B4, B5, B6, B7, B8, B9, A3, A4, A5, A6, B0, B1, B15, A8, A9, A10}
#   define MATRIX_ROW_PINS { B10, B2, A0, A1, A2, B14 }

#define TAP_CODE_DELAY 15


#define LED_CAPS_LOCK_PIN B3
#define LED_PIN_ON_STATE  1
