// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef STM32_PWM_USE_TIM2
#define STM32_PWM_USE_TIM2 TRUE

#undef STM32_PPRE2
#define STM32_PPRE2 STM32_PPRE2_DIV1

#undef STM32_ADCPRE
#define STM32_ADCPRE STM32_ADCPRE_DIV8

#undef STM32_PLLXTPRE
#define STM32_PLLXTPRE STM32_PLLXTPRE_DIV2
