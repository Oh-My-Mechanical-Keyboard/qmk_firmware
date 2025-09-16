// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include_next <mcuconf.h>

#undef STM32_PLLM_VALUE
#define STM32_PLLM_VALUE 16

// Used for RGB
#undef STM32_PWM_USE_TIM5
#define STM32_PWM_USE_TIM5 TRUE

// Used for RGB
#undef STM32_ADC_USE_ADC1
#define STM32_ADC_USE_ADC1 TRUE

#undef STM32_USB_USE_OTG1
#define STM32_USB_USE_OTG1                  FALSE
#undef STM32_USB_USE_OTG2
#define STM32_USB_USE_OTG2                  TRUE

