// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#if (PRODUCT_YR_ID == 3) || (PRODUCT_YR_ID == 2)
#   undef STM32_PWM_USE_TIM2
#   define STM32_PWM_USE_TIM2 TRUE
#else
#   undef STM32_PWM_USE_TIM3
#   define STM32_PWM_USE_TIM3 TRUE
#endif

#undef  STM32_PLLXTPRE
#define STM32_PLLXTPRE STM32_PLLXTPRE_DIV2
