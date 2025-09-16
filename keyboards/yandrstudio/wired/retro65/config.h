// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
// TBD
#define PRODUCT_ID      0xAABA
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Retro_Y&R"
#define PRODUCT         "Retro65"
/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16



//                               0      1       2       3       4       5       6       7       8       9       10      11      12      13      14      15
#define MATRIX_COL_PINS       { NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, A4,     A3 }
#define MATRIX_ROW_PINS       { A5,     A6,     A7,     B0,     B1 }


#define USE_BOTH_595_AND_GPIO
#define NUM_OF_74HC595 2
#define COL_F2L_FOR_595 TRUE

#define SR_74HC595_ZERO_ONEP 0x00
#define SR_74HC595_ONES_ONEP 0xFF

//                             a     b     c     d     e     f     g     h
#define SR_74HC595_LINE_MASK { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 }
//                           c0    c1    c2    c3    c4    c5    c6    c7    c8    c9    c10,  c11   c12   c13   c14   c15
#define MATRIX_OF_74HC595 {{ 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },\
                           { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x01, 0x00, 0x00 }}

#define SPI_SCK_PIN_OF_595 B5
#define SPI_MOSI_PIN_OF_595 B7
#define SPI_74HC595_CS B6

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define FORCE_NKRO

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define WEAR_LEVELING_BACKING_SIZE 4096
#define WEAR_LEVELING_LOGICAL_SIZE 2048

#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN A10
#    define RGBLED_NUM 16

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
#    define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_MOOD

#    define WS2812_PWM_DRIVER PWMD1
#    define WS2812_PWM_CHANNEL 3
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM5
#    define WS2812_DMA_CHANNEL 5

#endif
