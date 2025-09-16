// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "gwydd65.h"
#include "process_magic.h"

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) { return false; }
    switch(keycode) {
        case MKC_LG:
            if (record->event.pressed) {
                process_magic(GUI_TOG, record);
            }
            return false;
        case MKC_MACOS:
            if (record->event.pressed) {
                process_magic(CG_TOGG, record);
            }
            return false;
        case MKC_MCTL:
            if (record->event.pressed) {
                register_code16(KC_MCTL);
            } else {
                unregister_code16(KC_MCTL);
            }
            return false;
        case MKC_LPAD:
            if (record->event.pressed) {
                register_code16(KC_LPAD);
            } else {
                unregister_code16(KC_LPAD);
            }
            return false;
        default:
            return true;
    }
    return true;
}
