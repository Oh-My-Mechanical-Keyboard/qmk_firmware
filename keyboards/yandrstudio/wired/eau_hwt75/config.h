// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAA52
#define DEVICE_VER      0x0001
#define MANUFACTURER    "HAVIT_chaosera_Y&R"
#define PRODUCT         "Astralforce-1"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

//                        0   1   2   3   4   5    6    7    8   9   10   11   12  13  14
#define MATRIX_COL_PINS { B7, B8, B9, A3, A4, B13, B14, B15, A8, A9, A10, A15, B3, B4, B5 }
#define MATRIX_ROW_PINS { A5, A6, A7, B0, B1, A2 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* RGB Matrix */
#ifdef RGB_MATRIX_ENABLE

#    define RGB_DI_PIN B6
#    define WS2812_DI_PIN B6
#    define RGBLED_NUM 84
#    define RGB_MATRIX_LED_COUNT RGBLED_NUM

#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 180
#    define RGBLIGHT_VAL_STEP 5
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#    define RGB_MATRIX_CENTER { 112, 32 }
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGBLIGHT_ANIMATIONS

#   define ENABLE_RGB_MATRIX_ALPHAS_MODS
#   define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#   define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#   define ENABLE_RGB_MATRIX_BREATHING
#   define ENABLE_RGB_MATRIX_BAND_SAT
#   define ENABLE_RGB_MATRIX_BAND_VAL
#   define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#   define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#   define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#   define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#   define ENABLE_RGB_MATRIX_CYCLE_ALL
#   define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#   define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#   define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#   define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#   define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#   define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#   define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#   define ENABLE_RGB_MATRIX_DUAL_BEACON
#   define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#   define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#   define ENABLE_RGB_MATRIX_RAINDROPS
#   define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#   define ENABLE_RGB_MATRIX_HUE_BREATHING
#   define ENABLE_RGB_MATRIX_HUE_PENDULUM
#   define ENABLE_RGB_MATRIX_HUE_WAVE
#   define ENABLE_RGB_MATRIX_PIXEL_RAIN
#   define ENABLE_RGB_MATRIX_PIXEL_FLOW
#   define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
// enabled only if RGB_MATRIX_FRAMEBUFFER_EFFECTS is defined
#   define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#   define ENABLE_RGB_MATRIX_DIGITAL_RAIN
// enabled only of RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#   define ENABLE_RGB_MATRIX_SPLASH
#   define ENABLE_RGB_MATRIX_MULTISPLASH
#   define ENABLE_RGB_MATRIX_SOLID_SPLASH
#   define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

#    define WS2812_PWM_DRIVER PWMD4
#    define WS2812_PWM_CHANNEL 1
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM7
#    define WS2812_DMA_CHANNEL 7
#endif

