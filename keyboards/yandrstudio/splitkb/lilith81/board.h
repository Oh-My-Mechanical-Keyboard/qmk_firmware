// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next "board.h"

#undef STM32_HSECLK
#define STM32_HSECLK 8000000

#define BOARD_YANDR_BIU_F401
