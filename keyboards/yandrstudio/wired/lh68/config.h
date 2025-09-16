/* Copyright 2021 JasonRen(biu)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAAAE
#define DEVICE_VER      0x0001
#define MANUFACTURER    JasonRen biu
#define PRODUCT         lh68

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

//                        0    1    2    3    4   5    6    7    8   9   10  11  12  13  14
#define MATRIX_COL_PINS { A0,  A1,  C15, A2,  A7, B12, B13, B3,  B14,B4, A15,A14,A13,B15,B5 }
#define MATRIX_ROW_PINS { A5,  A4,  A3,  A6,  C14}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL


// enable the nkro when using the VIA.
#define FORCE_NKRO

// fix VIA RGB_light
#define VIA_HAS_BROKEN_KEYCODES

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define USB_POLLING_INTERVAL_MS 1
#define QMK_KEYS_PER_SCAN 4

#define LED_CAPS_LOCK_PIN    B0
#define LED_PIN_ON_STATE     0