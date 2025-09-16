// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next "board.h"

#undef VAL_GPIOACRL
#define VAL_GPIOACRL 0x88888888

#undef VAL_GPIOBCRH
#define VAL_GPIOBCRH 0x88888888

#undef VAL_GPIOCCRH
#define VAL_GPIOCCRH 0x88888888

#undef STM32_HSECLK
#define STM32_HSECLK 16000000

#define BOARD_YANDR_BIU_F103
