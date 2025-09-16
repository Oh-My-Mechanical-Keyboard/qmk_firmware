// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAA59
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Y&R"
#define PRODUCT         "Glory80"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17
/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

//                         0    1    2    3    4    5    6   7   8   9   10   11  12  13  14      15      16
#define MATRIX_COL_PINS {  A3,  A2,  A1,  A5,  A6,  A7, B0, B1, B14, A9, A10, B7, B8, B9, NO_PIN, NO_PIN, NO_PIN }
#define MATRIX_ROW_PINS {  B2,  B10, B11, B12, B13, A4 }

#define USE_BOTH_595_AND_GPIO
#define NUM_OF_74HC595 2
#define COL_F2L_FOR_595 TRUE

#define SR_74HC595_ZERO_ONEP 0x00
#define SR_74HC595_ONES_ONEP 0xFF

//                             a     b     c     d     e     f     g     h
#define SR_74HC595_LINE_MASK { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 }
//                             c14       c15        c16
#define MATRIX_OF_74HC595 { { {1, 0x01}, {0, 0x80}, {0, 0x40} },\
                            { {1, 0x02}, {0, 0x10}, {0, 0x20} },\
                            { {1, 0x04}, {0, 0x08}, {0, 0x01} },\
                            { {0, 0x00}, {0, 0x00}, {0, 0x00} },\
                            { {1, 0x08}, {1, 0x10}, {0, 0x02} },\
                            { {1, 0x40}, {1, 0x20}, {0, 0x04} }}

#define TAP_HOLD_CAPS_DELAY 250

#define SPI_SCK_PIN_OF_595 B3
#define SPI_MOSI_PIN_OF_595 B5
#define SPI_74HC595_CS B4

#define ROW_AUX_READ_PIN B15

#ifdef RGBLIGHT_ENABLE

#    define WS2812_DI_PIN B6
#    define RGBLED_NUM 8
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_VAL_STEP 10

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

#    define WS2812_PWM_DRIVER PWMD4
#    define WS2812_PWM_CHANNEL 1
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM7
#    define WS2812_DMA_CHANNEL 7
#endif


