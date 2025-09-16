// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAAE0
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Y&R"
#define PRODUCT         "leap"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

//                        0    1    2   3   4   5   6   7   8   9   10  11   12   13   14
#define MATRIX_COL_PINS { A15, B3,  B4, B5, B6, B7, A5, A7, B0, B1, B2, B10, B11, B12, A10 }
#define MATRIX_ROW_PINS { B14, B15, A8, A9, A6, B8 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define TAP_CODE_DELAY 15

#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN B13
#    define RGBLED_NUM 2
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLIGHT_LIMIT_VAL 180
#    define RGBLIGHT_SLEEP
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
#    define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_MODE_RAINBOW_SWIRL + 4)

#    define RGBLIGHT_LAYERS
#    define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#    define RGBLIGHT_LAYERS_RETAIN_VAL

#   define WS2812_PWM_DRIVER PWMD1  // default: PWMD2
#   define WS2812_PWM_CHANNEL 1     // default: 2
#   define WS2812_DMA_STREAM STM32_DMA1_STREAM5
#   define WS2812_DMA_CHANNEL 5
#   define WS2812_PWM_COMPLEMENTARY_OUTPUT

#endif
