// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* RGN Matrix */
#ifdef WS2812_DRIVER_PWM

#    define WS2812_PWM_DRIVER PWMD3  // default: PWMD2
#    define WS2812_PWM_CHANNEL 2  // default: 2
#    define WS2812_PWM_PAL_MODE 2  // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM2  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_DMA_CHANNEL 5  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_PWM_TARGET_PERIOD 800000

#endif
