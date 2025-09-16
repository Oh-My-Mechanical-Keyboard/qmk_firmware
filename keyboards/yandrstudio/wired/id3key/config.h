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

/* USB Device descriptor parameter */
#define VENDOR_ID 0x6964
#define PRODUCT_ID 0xFF01
#define DEVICE_VER 0x0001
#define MANUFACTURER IDOBAO
#define PRODUCT ID3KEY


/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 3

/* key matrix pins */
#define MATRIX_ROW_PINS { D4 }
#define MATRIX_COL_PINS { D0, D1, D2 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN B1
#    define RGBLED_NUM 5
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_VAL_STEP 5
#    define RGBLIGHT_LIMIT_VAL 200
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true
#    define RGBLIGHT_ANIMATIONS

#endif
