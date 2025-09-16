// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID 0xAA96
#define PRODUCT_ID 0xAA12
#define DEVICE_VER 0x0001
#define MANUFACTURER "Y&R"
#define PRODUCT "YR80"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define TAP_CODE_DELAY 15

//                        0   1   2   3    4    5    6    7    8    9    10   11  12  13  14  15  16
#define MATRIX_COL_PINS { C2, A8, C9, C8,  C12, C11, C10, B15, B14, B13, B12, C4, A7, C7, D2, B3, B4 }
#define MATRIX_ROW_PINS { C1, B6, B5, B10, A2,  C3 }

#ifdef RGBLIGHT_ENABLE

#    define WS2812_DI_PIN C6
#    define RGBLED_NUM 1
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_VAL_STEP 5
#    define RGBLIGHT_LIMIT_VAL 200
#    define RGBLIGHT_ANIMATIONS

#    define RGBLIGHT_LAYERS
#    define RGBLIGHT_LAYER_BLINK
#    define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#    define RGBLIGHT_LAYERS_RETAIN_VAL
#    define RGBLIGHT_MAX_LAYERS 3

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

#endif

#define HOLD_ON_OTHER_KEY_PRESS
#define TAP_HOLD_CAPS_DELAY 200

// for ble
#define USE_MUILT_THREAD_FOR_BLE
#define DISABLE_MAGIC_BOOTLOADER
#define DISABLE_EEPROM_CLEAR

#define BIUSTM32WKPin A0
#define BIUNRF52WKPin A6
#define BIUNRF52ResetPin A15

// rgb switch
#define RGB_BLE_SW A4
#define RGB_EN_STATE 1

// enable ble indicator
#define BleGetChannleEnable

// USB Power
#define USB_PWR_READ
#define USB_PWR_READ_PIN C0
// #define ADVANCE_SLEEP_MODE_V1_NO_DP_UP_ESD

// ADC SETTING
#define SAMPLE_BATTERY
#define USE_BAT_MAP_V2
