// Copyright 2024 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef RGBLIGHT_ENABLE
#    define WS2812_PWM_DRIVER PWMD2
#    define WS2812_PWM_CHANNEL 2
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM2
#    define WS2812_DMA_CHANNEL 2
#endif
