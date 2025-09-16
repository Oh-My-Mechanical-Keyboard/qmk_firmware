// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAAEE
#define MANUFACTURER    "Y&R"
#define PRODUCT         "TP2"

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define TAP_CODE_DELAY 15

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#ifdef ENCODER_ENABLE
#    define ENCODERS_PAD_A { B6 }
#    define ENCODERS_PAD_B { B8 }
#    define ENCODER_DEFAULT_POS 0x3
#endif

#define LED_NUM_LOCK_PIN  B9
#define LED_CAPS_LOCK_PIN A1
#define LED_PIN_ON_STATE  1

#define AUDIO_PIN A8
#define AUDIO_PWM_DRIVER PWMD1
#define AUDIO_PWM_CHANNEL 1
#define AUDIO_CLICKY
#define AUDIO_CLICKY_FREQ_DEFAULT 2360.0f
#define AUDIO_CLICKY_FREQ_MAX 9500.0f
#define AUDIO_CLICKY_FREQ_RANDOMNESS 0.05f
// #define AUDIO_CLICKY_FREQ_DEFAULT AUDIO_CLICKY_FREQ_MAX


#define SOLENOID_PIN B15
#define SOLENOID_DEFAULT_BUZZ 1
#define SOLENOID_DEFAULT_DWELL 40

#ifdef RGBLIGHT_ENABLE

#    define WS2812_DI_PIN B7
#    define RGBLED_NUM 3
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

#    define WS2812_PWM_DRIVER PWMD4  // default: PWMD2
#    define WS2812_PWM_CHANNEL 2  // default: 2
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM7  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_DMA_CHANNEL 7  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.


#endif

#define TAP_HOLD_CAPS_DELAY 250

#define SPI_SCK_PIN_OF_595 A5
#define SPI_MOSI_PIN_OF_595 A7
#define SPI_74HC595_CS A4

#define ROW_AUX_READ_PIN A3

#define EC_COL_PIN A2

#define WEAR_LEVELING_BACKING_SIZE 4096
#define WEAR_LEVELING_LOGICAL_SIZE 2048

#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
#define SPI_MOSI_PIN A7
#define SPI_MISO_PIN A6