// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "eau_eau75r2.h"

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_kb(void) {
    // Enable the LED layers
    rgblight_reload_from_eeprom();
}
#endif


void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_TIM2_REMAP_FULLREMAP;
}
