// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define PRODUCT_ID      0xAAE1
#define DEVICE_VER      0x0001

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

//                        0   1   2    3    4   5   6   7   8   9   10   11   12   13  14
#define MATRIX_COL_PINS { B5, B6, B7,  B0,  A7, A6, A5, A4, A3, B3, A15, B1,  B2, B10, B11 }
#define MATRIX_ROW_PINS { A10, A0, A1, B12, A2 }

#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN B4
#    define WS2812_DI_PIN B4
#    define RGBLED_NUM 20
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

#    define WS2812_PWM_DRIVER PWMD3
#    define WS2812_PWM_CHANNEL 1
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM3
#    define WS2812_DMA_CHANNEL 3

#endif
