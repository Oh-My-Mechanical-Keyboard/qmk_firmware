// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rev2.h"

#ifdef RGBLIGHT_ENABLE

void keyboard_post_init_kb(void) {
    rgblight_reload_from_eeprom();
}

#endif