// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef RGBLIGHT_ENABLE

#if PRODUCT_YR_ID == 2
#    define WS2812_PWM_DRIVER PWMD2  // default: PWMD2
#    define WS2812_PWM_CHANNEL 2  // default: 2
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM2  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_DMA_CHANNEL 2  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.

#elif PRODUCT_YR_ID == 3

#    define WS2812_PWM_DRIVER PWMD2  // default: PWMD2
#    define WS2812_PWM_CHANNEL 3  // default: 2
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM2  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_DMA_CHANNEL 2  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.

#else

#    define WS2812_PWM_DRIVER PWMD3  // default: PWMD2
#    define WS2812_PWM_CHANNEL 1  // default: 2
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM3  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_DMA_CHANNEL 3  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.

#endif

#endif
