// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define DEBOUNCE 10
#define EECONFIG_USER_DATA_SIZE 1

// 精简 RGB 矩阵配置
#define RGB_MATRIX_LED_COUNT 117

// 禁用所有高级 RGB 功能
#undef RGB_MATRIX_LAYERS
#undef RGB_MATRIX_LAYER_BLINK
#undef RGB_MATRIX_LAYERS_OVERRIDE_RGB_OFF
#undef RGB_MATRIX_LAYERS_RETAIN_VAL
#define RGB_MATRIX_MAX_LAYERS 1

// 禁用帧缓冲和按键效果
#undef RGB_MATRIX_FRAMEBUFFER_EFFECTS
#undef RGB_MATRIX_KEYPRESSES

// 只保留最基本的效果


// 降低最大亮度
//#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 128

// 硬件配置（保留）
#define WS2812_PWM_DRIVER PWMD2
#define WS2812_PWM_CHANNEL 4
#define WS2812_DMA_STREAM STM32_DMA1_STREAM2
#define WS2812_DMA_CHANNEL 2

// 暂时使用内置效果作为默认，确保编译通过
// #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_sine_wave_effect
// 在 config.h 中临时使用内置效果

#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_sine_wave

