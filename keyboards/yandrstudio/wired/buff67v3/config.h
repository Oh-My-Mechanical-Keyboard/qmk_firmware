// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAA88
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Y&R"

#define PRODUCT_YR_ID   3
#define PRODUCT         "Razor65"
// #define PRODUCT_YR_ID   2
// #define PRODUCT         "Luck65"
// #define PRODUCT_YR_ID   1
// #define PRODUCT         "Rose65"
// #define PRODUCT_YR_ID   0
// #define PRODUCT         "buff67v3"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

//                            0    1    2    3    4    5    6    7    8    9    10   11   12   13   14
#if PRODUCT_YR_ID == 2
#   define MATRIX_COL_PINS {  B5,  B6,  B7,  B8,  B9,  C13, C14, B0,  B1,  B2,  B10, B11, B12, A15, B4 }
#elif PRODUCT_YR_ID == 3
#   define MATRIX_COL_PINS {  B11, B12, B13, B14, B15, A9,  A10, B3,  B4,  B5,  B6,  B7,  A5,  A6,  A7 }
#else
#   define MATRIX_COL_PINS {  B5,  B6,  B7,  B8,  B9,  C13, C14, B0,  B1,  B2,  B10, B11, B12, A15, B3 }
#endif

#if PRODUCT_YR_ID == 3
#   define MATRIX_ROW_PINS {  B2,  B1,  B0,  A15, A8 }
#else
#   define MATRIX_ROW_PINS {  A3,  A4,  A5,  A7,  C15 }
#endif
/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 8

// #define FACTORY_TEST

#ifdef RGBLIGHT_ENABLE
#   if PRODUCT_YR_ID == 2
#       define RGB_DI_PIN B3
#   elif PRODUCT_YR_ID == 3
#       define RGB_DI_PIN B10
#   else
#       define RGB_DI_PIN B4
#   endif

#   if PRODUCT_YR_ID == 3
#        define RGBLED_NUM 4
#   else
#        define RGBLED_NUM 1
#endif
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


