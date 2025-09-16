// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAAD5
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Y&R"
#define PRODUCT         "Shadow 65X"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

//                            0    1    2    3    4   5   6    7   8   9   10  11  12  13  14
#   define MATRIX_COL_PINS {  B12, B13, B14, B15, A8, A9, A10, B3, B4, B5, B6, B7, B0, B1, B11 }
#   define MATRIX_ROW_PINS {  A4,  A3,  A6,  A5,  A2 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#ifdef ENCODER_ENABLE
#    define ENCODERS_PAD_A { B2 }
#    define ENCODERS_PAD_B { B10 }
#    define ENCODER_DEFAULT_POS 0x3
#endif

// #define FACTORY_TEST

#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN A7
#    define RGBLED_NUM 4

#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_VAL_STEP 10

#    ifdef FACTORY_TEST

#    define RGBLIGHT_LIMIT_VAL 80
#    define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_MODE_RGB_TEST)
#    define RGBLIGHT_EFFECT_RGB_TEST

#    else
#    define RGBLIGHT_LIMIT_VAL 200
#    define RGBLIGHT_ANIMATIONS

#    define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_MODE_RAINBOW_SWIRL+5)
#    define RGBLIGHT_DEFAULT_SPD 144
#    define RGBLIGHT_DEFAULT_VAL 200

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

#    define RGBLIGHT_LAYERS
#    define RGBLIGHT_LAYERS_RETAIN_VAL
#    define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF

#    endif

#endif


