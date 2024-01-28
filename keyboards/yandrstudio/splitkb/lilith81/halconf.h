// Copyright 2023 FxStudio <FXS@fx-studio.cn>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define HAL_USE_PWM TRUE

#define HAL_USE_SERIAL TRUE

#define PAL_USE_CALLBACKS TRUE
#define PAL_USE_WAIT TRUE
#include_next <halconf.h>
