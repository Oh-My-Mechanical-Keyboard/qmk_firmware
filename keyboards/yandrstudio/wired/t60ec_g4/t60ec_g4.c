// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "t60e_ec.h"

extern void set_ec_top_init_val(void);

void keyboard_post_init_kb() {
    keyboard_post_init_user();
    debug_enable = true;
    // debug_matrix = true;
    set_ec_top_init_val();
}
