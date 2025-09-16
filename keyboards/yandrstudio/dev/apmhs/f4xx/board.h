// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include_next <board.h>

#undef STM32_HSECLK
#define STM32_HSECLK 16000000

// #define BOARD_OTG2_USES_ULPI
#define BOARD_OTG_NOVBUSSENS
