// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define PRODUCT_ID      0xAA7E
#define DEVICE_VER      0x0001

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

//                         0   1   2    3   4   5   6   7   8   9   10  11  12   13   14
#define MATRIX_COL_PINS {  B7, A0, A1, A2, A3,  A4, A5, A6, A7, B0, B1, B2, B10, B11, B12 }
#define MATRIX_ROW_PINS {  B3, B4, B5,  B6, A15 }
