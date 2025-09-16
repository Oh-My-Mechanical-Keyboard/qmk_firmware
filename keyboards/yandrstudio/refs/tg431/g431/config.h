// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once


//                        0     1     2
#define MATRIX_COL_PINS { B2, B0, B1 }
#define MATRIX_ROW_PINS { B10, B3, B4}

#ifdef RGBLIGHT_ENABLE

#    define WS2812_DI_PIN B6
#    define RGBLED_NUM 9

// #    define RGBLIGHT_LAYERS
// #    define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
// #    define RGBLIGHT_LAYERS_RETAIN_VAL

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

#    define WS2812_PWM_DRIVER PWMD4
#    define WS2812_PWM_CHANNEL 1
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM3
// #    define WS2812_DMA_CHANNEL 4 // 对G4系列没有意义
#    define WS2812_DMAMUX_ID STM32_DMAMUX1_TIM4_UP  // DMAMUX configuration for TIMx_UP -- only required if your MCU has a DMAMUX peripheral, see the respective reference manual for the appropriate values for your MCU.


#endif

// Bitbang WS2812
#define NOP_FUDGE 0.4

#ifdef EEPROM_TRANSIENT
#   define TRANSIENT_EEPROM_SIZE (64+2048)
#endif

// lib/chibios/os/hal/ports/STM32/STM32G4xx/stm32_registry.h->Line:608
// #undef STM32_FLASH_NUMBER_OF_BANKS
// #define STM32_FLASH_NUMBER_OF_BANKS 1
