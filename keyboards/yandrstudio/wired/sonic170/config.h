// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAAB9
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Y&R"
#define PRODUCT         "Sonic170"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 17
/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

//                         0    1    2    3   4   5   6   7   8   9    10   11   12  13  14  15      16
#define MATRIX_COL_PINS {  A2,  A3,  A4, A5,  A6, A7, B0, B1, B2, B10, B11, A15, B3, B4, B5, NO_PIN, NO_PIN }
#define MATRIX_ROW_PINS {  B13, B12, A1, B14, C13 }

#define USE_BOTH_595_AND_GPIO
#define NUM_OF_74HC595 2
#define COL_F2L_FOR_595 TRUE

#define SR_74HC595_ZERO_ONEP 0x00
#define SR_74HC595_ONES_ONEP 0xFF

//                             a     b     c     d     e     f     g     h
#define SR_74HC595_LINE_MASK { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 }
//                             c15          c16  
#define MATRIX_OF_74HC595 { { {0, 0x02},   {0, 0x04} },\
                            { {0, 0x01},   {0, 0x08} },\
                            { {1, 0x02},   {1, 0x04} },\
                            { {1, 0x01},   {1, 0x08} },\
                            { {1, 0x40},   {1, 0x20} }}

#define TAP_HOLD_CAPS_DELAY 250

#define SPI_SCK_PIN_OF_595 B7
#define SPI_MOSI_PIN_OF_595 B8
#define SPI_74HC595_CS B6

#define ROW_AUX_READ_PIN B9

#ifdef ENCODER_ENABLE
#    define ENCODERS_PAD_A { B15 }
#    define ENCODERS_PAD_B { A9 }
#    define ENCODER_DEFAULT_POS 0x3
#endif

#ifdef RGBLIGHT_ENABLE
#    define WS2812_DI_PIN A8
#    define RGBLED_NUM 10
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_VAL_STEP 10

#    ifdef FACTORY_TEST

#    define RGBLIGHT_LIMIT_VAL 80
#    define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_MODE_RGB_TEST)
#    define RGBLIGHT_EFFECT_RGB_TEST

#    else
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

#    endif

#    define WS2812_PWM_DRIVER PWMD1  // default: PWMD2
#    define WS2812_PWM_CHANNEL 1  // default: 2
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM5  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_DMA_CHANNEL 5  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.

#endif


