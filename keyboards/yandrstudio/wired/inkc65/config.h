// Copyright 2023 Y&R-studio (@superYoungMonk)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
// #define PRODUCT_ID      0xAAF2
#define PRODUCT_ID      0xAA88
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Y&R"
#define PRODUCT         "iNKC65"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* key matrix pins */
//                        0    1    2    3    4   5   6    7    8   9   10  11  12  13  14
#define MATRIX_COL_PINS { B12, B13, B14, B15, A8, A9, A10, A15, B3, B4, B5, B6, A2, A5, A6 }
#define MATRIX_ROW_PINS { B0,  B1,  B2,  B10, B11}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define TAP_CODE_DELAY 15

#define TAP_HOLD_CAPS_DELAY 250

#ifdef RGBLIGHT_ENABLE
// #    define RGB_DI_PIN A7
#    define WS2812_DI_PIN A7
#    define RGBLED_NUM 2
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_VAL_STEP 15
#    define RGBLIGHT_LIMIT_VAL 255

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
#    define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_MODE_RAINBOW_SWIRL+4)

#    define RGBLIGHT_LAYERS
#    define RGBLIGHT_LAYERS_RETAIN_VAL
#    define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF

#   define WS2812_PWM_DRIVER PWMD3
#   define WS2812_PWM_CHANNEL 2
#   define WS2812_PWM_PAL_MODE 2
#   define WS2812_DMA_STREAM STM32_DMA1_STREAM3
#   define WS2812_DMA_CHANNEL 3
#endif
