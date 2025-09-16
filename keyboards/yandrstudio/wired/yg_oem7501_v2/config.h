// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAA5A
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Y&R"
#define PRODUCT         "Aurora75"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

//                        0    1   2   3   4   5   6   7   8    9   10  11  12  13  14
#define MATRIX_COL_PINS { A15, B9, B8, B7, B6, B5, B4, B3, B10, B2, B1, B0, A7, A6, B11 }
#define MATRIX_ROW_PINS { A9,  A8, B15, B14, B13, B12 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define TAP_CODE_DELAY 15

#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN A3
#    define WS2812_DI_PIN A3
#    define RGBLED_NUM 12
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

#   define WS2812_PWM_DRIVER PWMD2
#   define WS2812_PWM_CHANNEL 4
#   define WS2812_DMA_STREAM STM32_DMA1_STREAM2
#   define WS2812_DMA_CHANNEL 2

#endif


#define LED_CAPS_LOCK_PIN A10
#define LED_PIN_ON_STATE  1
