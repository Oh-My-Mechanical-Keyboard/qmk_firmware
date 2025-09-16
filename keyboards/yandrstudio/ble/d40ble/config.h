// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAAFC
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Y&R"
#define PRODUCT         "D40BLE"

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 13

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

//                        0    1   2   3    4    5    6    7    8   9   10  11  12
#define MATRIX_COL_PINS { A10, A9, A8, B15, B14, B13, B12, B10, B2, B0, A7, A4, B4}
#define MATRIX_ROW_PINS { B3,  B5, A6, A5 }

#define TAP_CODE_DELAY 15

#define HOLD_ON_OTHER_KEY_PRESS

#define TAP_HOLD_CAPS_DELAY 200

#ifdef RGBLIGHT_ENABLE

#    define WS2812_DI_PIN B7
#    define RGBLED_NUM 24
#    define RGBLIGHT_LIMIT_VAL 180
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_LAYERS
#    define RGBLIGHT_LAYER_BLINK
#    define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#    define RGBLIGHT_LAYERS_RETAIN_VAL
#    define RGBLIGHT_MAX_LAYERS 14

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

#    define WS2812_PWM_DRIVER PWMD4  // default: PWMD2
#    define WS2812_PWM_CHANNEL 2  // default: 2
#    define WS2812_PWM_PAL_MODE 2  // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM6  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_DMA_CHANNEL 2  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.


#endif

// for ble
#define USE_MUILT_THREAD_FOR_BLE

#define DISABLE_MAGIC_BOOTLOADER
#define DISABLE_EEPROM_CLEAR

#define BIUSTM32WKPin A0
#define BIUNRF52WKPin B6
#define BIUNRF52ResetPin A1

// disable rgb when using ble
#define RGB_BLE_SW B8
#define RGB_EN_STATE 1

// enable ble indicator
#define BleGetChannleEnable

// USB Power
#define USB_PWR_READ
#define USB_PWR_READ_PIN A15
#define ADVANCE_SLEEP_MODE_V1_NO_DP_UP_ESD

// ADC SETTING
#define SAMPLE_BATTERY
#define BATTERY_LEVEL_SW_PIN B1
#define USE_BAT_MAP_V2


#define SERIAL_DRIVER SD2
#define BIUNRF52RxPin A3
#define BIUNRF52TxPin A2
#define SD1_TX_PIN BIUNRF52TxPin
#define SD1_RX_PIN BIUNRF52RxPin
