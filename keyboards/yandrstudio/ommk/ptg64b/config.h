// Copyright 2024 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* RGB Matrix */
#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_LED_COUNT 90

#    define WS2812_PWM_DRIVER PWMD2
#    define WS2812_PWM_CHANNEL 4
#    define WS2812_DMA_STREAM AIR32_DMA1_STREAM2
#    define RGB_DISABLE_WHEN_USB_SUSPENDED

#    define RGB_MATRIX_LAYERS
#    define RGB_MATRIX_LAYER_BLINK
#    define RGB_MATRIX_LAYERS_OVERRIDE_RGB_OFF
#    define RGB_MATRIX_LAYERS_RETAIN_VAL
#    define RGB_MATRIX_MAX_LAYERS 1

#endif

// for factory test
#define EECONFIG_KB_DATA_SIZE 1
