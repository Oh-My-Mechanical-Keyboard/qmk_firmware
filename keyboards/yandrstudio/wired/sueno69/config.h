/* Copyright 2022 JasonRen(biu)
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

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

/* key matrix pins */
//                        0    1   2   3  4  5   6   7   8  9  10 11  12  13 14   
#define MATRIX_COL_PINS { B10,B11,B12,A9,B13,B14,B15,B6,B5,A8,A10,B3,B4,A15,A0,B9}
#define MATRIX_ROW_PINS { A3,A4,A7,A6,A5}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define TAP_CODE_DELAY 15

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

#ifdef RGBLIGHT_ENABLE
#    define RGB_DI_PIN B7
#    define RGBLED_NUM 3
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_VAL_STEP 15
#    define RGBLIGHT_LIMIT_VAL 255
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true
#    define RGBLIGHT_ANIMATIONS
#endif

#       define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 3
#       define DYNAMIC_KEYMAP_LAYER_COUNT 4
#       define FEE_PAGE_COUNT 4