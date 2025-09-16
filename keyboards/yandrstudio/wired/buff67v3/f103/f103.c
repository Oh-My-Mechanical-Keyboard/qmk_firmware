// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

void board_init(void) {
#if PRODUCT_YR_ID == 2
    AFIO->MAPR |= AFIO_MAPR_TIM2_REMAP_PARTIALREMAP1;
#elif PRODUCT_YR_ID == 3
    AFIO->MAPR |= AFIO_MAPR_TIM2_REMAP_PARTIALREMAP2;
#else
    AFIO->MAPR |= AFIO_MAPR_TIM3_REMAP_PARTIALREMAP;
#endif
}
