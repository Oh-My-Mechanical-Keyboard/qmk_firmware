// Copyright 2024 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef AIR32_ST_USE_TIMER
#define AIR32_ST_USE_TIMER 5

#undef AIR32_PWM_USE_TIM2
#define AIR32_PWM_USE_TIM2 TRUE

#undef AIR32_PLLMUL_VALUE
#undef AIR32_ADCPRE
#undef AIR32_USBPRE
#undef AIR32_PLLXTPRE

// PLLCLKOUT = 216MHz
#define AIR32_PLLXTPRE                      AIR32_PLLXTPRE_DIV2
#define AIR32_PLLMUL_VALUE                  27
#define AIR32_ADCPRE                        AIR32_ADCPRE_DIV32
#define AIR32_USBPRE                        AIR32_USBPRE_DIV4P5