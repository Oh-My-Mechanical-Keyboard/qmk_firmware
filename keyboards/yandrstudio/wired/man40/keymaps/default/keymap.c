// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_F1,  KC_INS,  KC_HOME, KC_PGUP,  KC_NUM, KC_PSLS, KC_PAST, KC_PMNS,
        KC_F2,  KC_DEL,  KC_END,  KC_PGDN,  KC_P7,  KC_P8,   KC_P9,   KC_PPLS,
        KC_F3,  KC_MUTE, KC_VOLU, KC_VOLD,  KC_P4,  KC_P5,   KC_P6,   KC_PPLS,
        KC_F4,  KC_STOP, KC_UP,   KC_MPLY,  KC_P1,  KC_P2,   KC_P3,   KC_PENT,
        KC_F5,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_P0,  KC_P0,   KC_PDOT, KC_PENT)
};
