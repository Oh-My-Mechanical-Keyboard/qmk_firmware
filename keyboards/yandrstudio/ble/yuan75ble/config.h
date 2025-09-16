// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID 0xAA96
#define PRODUCT_ID 0xAA5A
#define DEVICE_VER 0x0001
#define MANUFACTURER "Y&R"
#define PRODUCT "Yuan75"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 16

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define TAP_CODE_DELAY 15

//                        0       1       2       3       4       5       6       7       8       9       10      11      12      13      14      15
#define MATRIX_COL_PINS { NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, B8 }
#define MATRIX_ROW_PINS { A15,    B3,     B4,     B5,     B6,     B7 }

#define USE_BOTH_595_AND_GPIO
#define COL_ROW_DIODE_INVERSE_FOR_595
#define SLEEP_IN_STOP_MATRIX_LOW

#define NUM_OF_74HC595 2
#define COL_F2L_FOR_595 TRUE

#define SR_74HC595_ZERO_ONEP 0x00
#define SR_74HC595_ONES_ONEP 0xFF

//                              a    b     c     d     e     f     g     h
#define SR_74HC595_LINE_MASK { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 }
//                          c0    c1    c2    c3    c4    c5    c6    c7    c8    c9    c10,  c11   c12   c13   c14
#define MATRIX_OF_74HC595 {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 },\
                           {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }}

#define SPI_SCK_PIN_OF_595 A5
#define SPI_MOSI_PIN_OF_595 A7
#define SPI_74HC595_CS A6

#ifdef RGBLIGHT_ENABLE

#    define WS2812_DI_PIN A8
#    define RGBLED_NUM 3
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_VAL_STEP 5

#ifdef FACTORY_TEST

#    define RGBLIGHT_LIMIT_VAL 24
#    define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_MODE_RGB_TEST)
#    define RGBLIGHT_EFFECT_RGB_TEST

#else

#    define RGBLIGHT_LIMIT_VAL 200
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_MODE_RAINBOW_SWIRL+4)

#endif

#    define RGBLIGHT_LAYERS
#    define RGBLIGHT_LAYER_BLINK
#    define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#    define RGBLIGHT_LAYERS_RETAIN_VAL
#    define RGBLIGHT_MAX_LAYERS 5

#    define WS2812_PWM_DRIVER PWMD1  // default: PWMD2
#    define WS2812_PWM_CHANNEL 1  // default: 2
#    define WS2812_PWM_PAL_MODE 1  // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#    define WS2812_DMA_STREAM STM32_DMA2_STREAM5  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_DMA_CHANNEL 6  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.

#endif

#define HOLD_ON_OTHER_KEY_PRESS
#define TAP_HOLD_CAPS_DELAY 200

// for ble
#define USE_MUILT_THREAD_FOR_BLE
#define DISABLE_MAGIC_BOOTLOADER
#define DISABLE_EEPROM_CLEAR

#define BIUSTM32WKPin A0
#define BIUNRF52WKPin A1
#define BIUNRF52ResetPin A4

// rgb switch
#define RGB_BLE_SW B12
#define RGB_EN_STATE 1

// enable ble indicator
#define BleGetChannleEnable

// USB Power
#define USB_PWR_READ
#define USB_PWR_READ_PIN B14
#define ADVANCE_SLEEP_MODE_V1_NO_DP_UP_ESD

// ADC SETTING
#define SAMPLE_BATTERY
#define BATTERY_LEVEL_PIN B0
#define USE_BAT_MAP_V2

#define SERIAL_DRIVER SD2
#define BIUNRF52RxPin A3
#define BIUNRF52TxPin A2
#define SD1_TX_PIN BIUNRF52TxPin
#define SD1_RX_PIN BIUNRF52RxPin
