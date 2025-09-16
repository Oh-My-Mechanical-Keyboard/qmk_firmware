// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* RGB Matrix */
#ifdef RGB_MATRIX_ENABLE
#   define WS2812_PWM_DRIVER PWMD1
#   define WS2812_PWM_CHANNEL 3
#   define WS2812_PWM_PAL_MODE 2
#   define WS2812_DMA_STREAM STM32_DMA1_STREAM5
#   define WS2812_DMA_CHANNEL 5
#endif
