// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAA57
#define DEVICE_VER      0x0001
#define MANUFACTURER    "StudioX_Y&R"
#define PRODUCT         "C800"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

//                           0   1    2   3   4   5   6   7   8   9   10   11   12  13    14   15   16
#   define MATRIX_COL_PINS { A1, A2,  A3, A4, A5, A6, A7, B0, B1, B2, B10, B11, B12, B13, B14, B15, A8 }
#   define MATRIX_ROW_PINS { B3, A15, B6, B5, B4, B7}

#define TAP_CODE_DELAY 15

#ifdef RGBLIGHT_ENABLE

#    define WS2812_DI_PIN A9
#    define RGBLED_NUM 36
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
