// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAAD0
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Y&R"
#define PRODUCT         "NAGARE 80"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

//                           0    1   2   3   4   5   6   7   8   9   10  11  12  13   14  15  16
#   define MATRIX_COL_PINS { A15, B4, B5, B6, B7, B8, B9, A3, A4, A5, A6, B0, B1, B13, A8, A9, A10}
#   define MATRIX_ROW_PINS { B10, B2, A0, A1, A2, B12 }

#define TAP_CODE_DELAY 15

#ifdef ENCODER_ENABLE
#    define ENCODERS_PAD_A { B14 }
#    define ENCODERS_PAD_B { B15 }
#    define ENCODER_DEFAULT_POS 0x3
#endif

#define LED_CAPS_LOCK_PIN B3
#define LED_PIN_ON_STATE  1

#ifdef RGBLIGHT_ENABLE
#    define RGB_DI_PIN A7
#    define RGBLED_NUM 2
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_VAL_STEP 10

#    ifdef FACTORY_TEST

#    define RGBLIGHT_LIMIT_VAL 80
#    define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_MODE_RGB_TEST)
#    define RGBLIGHT_EFFECT_RGB_TEST

#    else
#    define RGBLIGHT_LIMIT_VAL 200
#    define RGBLIGHT_ANIMATIONS

#    define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_MODE_RGB_TEST)
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

#    define WS2812_PWM_DRIVER PWMD3  // default: PWMD2
#    define WS2812_PWM_CHANNEL 2  // default: 2
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM3  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_DMA_CHANNEL 3  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.

#endif
