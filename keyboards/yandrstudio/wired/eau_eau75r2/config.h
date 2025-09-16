// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAA47
#define DEVICE_VER      0x0001
#define MANUFACTURER    "chaosera_Y&R"
#define PRODUCT         "EAU"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

//                        0   1   2   3    4    5     6   7    8    9   10  11   12  13  14
#define MATRIX_COL_PINS { B0, B1, B2, B10, B11, B12, B13, B14, B15, A8, A9, A10, B3, B4, B5 }
#define MATRIX_ROW_PINS { A3, A4, A5, A6,  A7,  A2 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN A15
#    define WS2812_DI_PIN A15
#    define RGBLED_NUM 19
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

#    define WS2812_PWM_DRIVER PWMD2
#    define WS2812_PWM_CHANNEL 1
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM2  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_DMA_CHANNEL 2  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.


#endif
