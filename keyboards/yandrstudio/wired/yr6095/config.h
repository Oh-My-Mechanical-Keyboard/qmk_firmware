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

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAA0C
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Y&R"
#define PRODUCT         "YR6095"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

//                         0    1    2    3    4    5    6    7    8   9    10   11   12   13
#define MATRIX_COL_PINS {  B6,  B15, B14, B13, B12, B11, B10, B2,  B1, B0,  A7,  A6,  A5,  A4 }
#define MATRIX_ROW_PINS {  A1,  A3,  A8,  A9,  A10 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define TAP_HOLD_CAPS_DELAY 250

#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN B5
#    define RGBLED_NUM 33
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_VAL_STEP 5
#    define RGBLIGHT_LIMIT_VAL 200
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true
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

#ifdef VIA_ENABLE
#    define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 4
#    define DYNAMIC_KEYMAP_LAYER_COUNT 10
// Wear-leveling driver configuration
#    define WEAR_LEVELING_LOGICAL_SIZE 2048
#    define WEAR_LEVELING_BACKING_SIZE (WEAR_LEVELING_LOGICAL_SIZE * 2)
#endif
