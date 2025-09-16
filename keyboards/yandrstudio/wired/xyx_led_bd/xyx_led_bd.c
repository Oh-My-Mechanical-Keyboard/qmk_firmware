// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "xyx_led_bd.h"

void keyboard_post_init_kb(void) {
    rgblight_reload_from_eeprom();
}


