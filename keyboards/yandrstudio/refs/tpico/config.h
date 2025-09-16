// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID  0xAA96
#define PRODUCT_ID 0xFFFF
#define DEVICE_VER 0x0001
#define MANUFACTURER "TEST_Y&R"
#define PRODUCT "tpico"

// enable the nkro when using the VIA.
#define FORCE_NKRO

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define TAP_CODE_DELAY 15

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 3

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW
