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
#define PRODUCT_ID      0xAACE
#define DEVICE_VER      0x0001
#define MANUFACTURER    "zhou_y&r"
#define PRODUCT         "zhou980"

/* key matrix size */
#define MATRIX_COLS 19
#define MATRIX_ROWS 6

//                        1    2    3     4    5    6    7    8    9    10   11   12   13   14   15   16   17   18   19
#define MATRIX_COL_PINS { A2,  A9,  B12,  B11, B10, B2,  B1,  B0,  A7,  A6,  A5,  A4,  B9,  B8,  B7,  B6,  B5,  B4,  B3}
#define MATRIX_ROW_PINS { A8,  B15, B14, B13,  A10, A3}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN A15
#    define RGBLED_NUM 4
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLIGHT_LIMIT_VAL 180
#    define RGBLIGHT_SLEEP

#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_EFFECT_TWINKLE
#    define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_MOOD

#endif

#define DYNAMIC_KEYMAP_LAYER_COUNT 2

#define LED_NUM_LOCK_PIN  C14
#define LED_CAPS_LOCK_PIN C15
#define LED_PIN_ON_STATE  1
