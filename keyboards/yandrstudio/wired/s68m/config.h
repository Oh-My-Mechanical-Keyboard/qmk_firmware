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
#define PRODUCT_ID      0xAAC9
#define DEVICE_VER      0x0001
#define MANUFACTURER    SAM_Y&R
#define PRODUCT         s68m

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

//                        0    1    2    3    4    5    6    7    8    9    10   11   12   13    14   15
#define MATRIX_COL_PINS { C14, B11, B10, B2,  B1,  B0,  A7,  A6,  A5,  A4,  B5,  B4,  B3,  A15,  A3,  A2 }
#define MATRIX_ROW_PINS { A1,  A0,  B6,  B8,  B9 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

#define LED_CAPS_LOCK_PIN B7
#define LED_PIN_ON_STATE  1

// enable the nkro when using the VIA.
#define FORCE_NKRO

// fix VIA RGB_light
#define VIA_HAS_BROKEN_KEYCODES

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

// #define DEBUG_MATRIX_SCAN_RATE
#define TAP_CODE_DELAY 15
