// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// 设置复位和boot0
void board_init(void) {
    PWR->CR3 |= PWR_CR3_UCPD_DBDIS;
    setPinInput(G10);
    setPinInput(B8);
}
