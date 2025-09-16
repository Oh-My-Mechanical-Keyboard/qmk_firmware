// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef RGBLIGHT_ENABLE

#   define WS2812_PWM_DRIVER PWMD2  // default: PWMD2
#   define WS2812_PWM_CHANNEL 4     // default: 2
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM2  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_DMA_CHANNEL 2
#endif
