// Copyright 2023 Y&R-studio (@superYoungMonk)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAAF3
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Y&R"
#define PRODUCT         "STAR STONE-65"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* key matrix pins */
//                        0   1   2   3   4   5   6   7    8    9   10  11  12  13   14
#define MATRIX_COL_PINS { A0, A6, A5, A4, A3, A2, A1, B11, B10, B2, B1, B0, A7, B13, B12 }
#define MATRIX_ROW_PINS { B3, B4, B5, B6, B7}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define TAP_CODE_DELAY 15

#define TAP_HOLD_CAPS_DELAY 250
