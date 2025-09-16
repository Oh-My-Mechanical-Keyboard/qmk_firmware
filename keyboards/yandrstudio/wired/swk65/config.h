// Copyright 2023 Y&R-studio (@superYoungMonk)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAA5C
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Y&R"
#define PRODUCT         "SWK65"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* key matrix pins */
//                        0    1    2    3    4    5   6   7    8   9   10  11  12  13  14
#define MATRIX_COL_PINS { B10, B11, A10, B14, B15, A8, A9, A15, B7, A3, A5, A4, A6, A7, B0 }
#define MATRIX_ROW_PINS { B3,  B4,  B5,  B6,  B1 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define TAP_CODE_DELAY 15

#define TAP_HOLD_CAPS_DELAY 250

#define LED_CAPS_LOCK_PIN B2
#define LED_PIN_ON_STATE  1
