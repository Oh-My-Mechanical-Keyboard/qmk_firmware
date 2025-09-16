// Copyright 2025 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAB00
#define DEVICE_VER      0x0001

#define MANUFACTURER    "MACHINA"
#define PRODUCT         "TIGA"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

//                         0   1    2    3    4   5   6   7   8   9   10  11  12  13  14
#define MATRIX_COL_PINS {  B2, B10, B11, A15, B3, B4, B5, B6, B8, B9, A3, A4, A5, A6, A7 }
#define MATRIX_ROW_PINS {  A2, A1,  A0,  B7,  B0 }

#define TAP_CODE_DELAY 15

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5


#ifdef RGBLIGHT_ENABLE

#    define WS2812_DI_PIN B1
#    define RGBLIGHT_LED_COUNT 3
#    define RGBLIGHT_LIMIT_VAL 180
#    define RGBLIGHT_DEFAULT_SPD 200
#    define RGBLIGHT_SLEEP

#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_MODE_RAINBOW_SWIRL+4)

#    define RGBLIGHT_LAYERS
#    define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#    define RGBLIGHT_LAYERS_RETAIN_VAL

#   define WS2812_PWM_DRIVER PWMD3  // default: PWMD2
#   define WS2812_PWM_CHANNEL 4     // default: 2
#   define WS2812_DMA_STREAM STM32_DMA1_STREAM3
#   define WS2812_DMA_CHANNEL 3

#endif
