// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAACE
#define DEVICE_VER      0x0001
#define MANUFACTURER    "swk_y&r"
#define PRODUCT         "swk60"

/* key matrix size */
#define MATRIX_COLS 18
#define MATRIX_ROWS 5

//                        0   1   2   3   4   5   6   7   8    9    10   11  12  13   14  15  16  17
#define MATRIX_COL_PINS { A3, A4, A5, A6, A7, B0, B1, B2, B10, B11, B15, A8, A9, A10, B3, B4, B5, A15 }
#define MATRIX_ROW_PINS { B6, B7, A0, A1, A2}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW
