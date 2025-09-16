// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAAD6
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Y&R"
#define PRODUCT         "MAN40"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 8

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

//                        0    1   2   3   4   5   6   7
#define MATRIX_COL_PINS { A6,  A5, A4, A3, B7, B6, B5, B4 }
#define MATRIX_ROW_PINS { A10, B3, B0, B1, B2 }

#define TAP_HOLD_CAPS_DELAY 250

#define LED_SCROLL_LOCK_PIN  A9
#define LED_NUM_LOCK_PIN A15
#define LED_PIN_ON_STATE  1


#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN A7
#    define RGBLED_NUM 18

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
#    define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_MODE_RAINBOW_SWIRL+5)

#   define WS2812_PWM_DRIVER PWMD3
#   define WS2812_PWM_CHANNEL 2
#   define WS2812_PWM_PAL_MODE 2
#   define WS2812_DMA_STREAM STM32_DMA1_STREAM3
#   define WS2812_DMA_CHANNEL 3

#endif
