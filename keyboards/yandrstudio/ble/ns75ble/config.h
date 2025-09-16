// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID 0xAA96
#define PRODUCT_ID 0xAAF9
#define DEVICE_VER 0x0001
#define MANUFACTURER "Y&R"
#define PRODUCT "Star75"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW
#define SLEEP_IN_STOP_MATRIX_LOW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define TAP_CODE_DELAY 15

//                        0   1   2    3    4    5   6   7   8   9   10   11   12   13   14
#define MATRIX_COL_PINS { B6, A6, A5,  A4,  B9,  B8, B7, C8, C7, C6, B15, B14, B13, B12, B4}
#define MATRIX_ROW_PINS { B3, D2, C12, C11, C10, B5 }

#ifdef RGBLIGHT_ENABLE

#    define WS2812_DI_PIN A8
#    define RGBLED_NUM 16
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_VAL_STEP 5
#    define RGBLIGHT_LIMIT_VAL 200
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
#    define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL

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
#define BIUNRF52ResetPin C3

// rgb switch
#define RGB_BLE_SW C9
#define RGB_EN_STATE 1

// enable ble indicator
#define BleGetChannleEnable

// USB Power
#define USB_PWR_READ
#define USB_PWR_READ_PIN C0

// ADC SETTING
#define SAMPLE_BATTERY
#define BATTERY_LEVEL_PIN C1
#define ADVANCE_SLEEP_MODE_V1_NO_DP_UP_ESD
#define USE_BAT_MAP_V2
