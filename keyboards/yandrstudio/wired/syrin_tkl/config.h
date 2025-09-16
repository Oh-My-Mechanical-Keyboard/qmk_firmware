// Copyright 2024 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
// PID-yr80
#define PRODUCT_ID      0xAA35
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Y&R"
#define PRODUCT         "syrin tkl"


/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 18

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

//                           0   1   2    3   4   5   6   7   8    9    10   11   12   13   14  15  16  17
#   define MATRIX_COL_PINS { B0, A7, A6,  A5, A4, A3, A9, A8, B15, B14, B13, B12, B11, B10, A2, B8, B7, B6 }
#   define MATRIX_ROW_PINS { B5, B4, A10, B2, A1, B9 }

#define TAP_CODE_DELAY 15


#ifdef RGBLIGHT_ENABLE

#    define WS2812_DI_PIN B3
#    define RGBLED_NUM 5
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_VAL_STEP 5
#    define RGBLIGHT_LIMIT_VAL 200
#    define RGBLIGHT_ANIMATIONS

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

#define LED_CAPS_LOCK_PIN B1
#define LED_PIN_ON_STATE  1
