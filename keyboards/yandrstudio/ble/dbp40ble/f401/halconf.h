// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include_next <halconf.h>

#undef HAL_USE_SERIAL
#define HAL_USE_SERIAL TRUE

#undef HAL_USE_ADC
#define HAL_USE_ADC TRUE

#undef  PAL_USE_CALLBACKS
#define PAL_USE_CALLBACKS TRUE
