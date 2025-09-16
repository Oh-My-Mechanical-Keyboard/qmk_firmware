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

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAA0D
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Y&R"

#define PRODUCT_YR_ID   3
// for hyperboring
#define PRODUCT         "HYPERBORING TKL"
// #define PRODUCT_YR_ID   2
// #define PRODUCT         "alina"
// #define PRODUCT_YR_ID   1
// #define PRODUCT         "yr80"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#if PRODUCT_YR_ID == 3
//                           0    1    2    3    4   5   6   7   8   9   10  11  12  13  14  15  16
#   define MATRIX_COL_PINS { A8,  A9,  A10, A15, B3, B4, B5, A1, A2, A3, A4, A5, A6, A0, B1, B2, B10 }
#   define MATRIX_ROW_PINS { B12, B13, B14, B15, B6, B0 }
#else
//                        0    1    2    3    4    5    6   7    8    9    10   11   12   13    14   15   16
#   define MATRIX_COL_PINS { B12, B13, B14, A15, B3,  B4,  B5, B0,  A5,  A4,  A3,  A1,  A2,  B11,  B1,  B2,  B10 }
#   define MATRIX_ROW_PINS { B15, B6,  B7,  B8,  B9,  A6 }
#endif

#define TAP_CODE_DELAY 15


#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN A7
#    define RGBLED_NUM 1
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_VAL_STEP 5
#    define RGBLIGHT_LIMIT_VAL 200
#    define RGBLIGHT_ANIMATIONS

#    define RGBLIGHT_LAYERS
#    define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#    define RGBLIGHT_LAYERS_RETAIN_VAL

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
