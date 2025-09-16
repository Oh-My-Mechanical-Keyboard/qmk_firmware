// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum keyboard_keycodes {
    LOCK_GUI = QK_KB,
    TOG_MACOS_KEYMAP,
    TOG_CGTOP,
    KC_MISSION_CONTROL_MAC,
    KC_LAUNCHPAD_MAC
};

#define MKC_LG    LOCK_GUI
#define MKC_MACOS TOG_MACOS_KEYMAP
#define MKC_CGT   TOG_CGTOP
#define MKC_MCTL  KC_MISSION_CONTROL_MAC
#define MKC_LPAD  KC_LAUNCHPAD_MAC

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_F1,  KC_PSCR, KC_SCRL, KC_PAUS,  KC_NUM, KC_PSLS, KC_PAST, KC_PMNS,
        KC_F2,  KC_INS,  KC_HOME, KC_PGUP,  KC_P7,  KC_P8,   KC_P9,   KC_PPLS,
        KC_F3,  KC_DEL,  KC_END,  KC_PGDN,  KC_P4,  KC_P5,   KC_P6,   KC_PPLS,
        KC_F4,  KC_STOP, KC_UP,   KC_MPLY,  KC_P1,  KC_P2,   KC_P3,   KC_PENT,
        KC_F5,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_P0,  KC_P0,   KC_PDOT, KC_PENT),
    [1] = LAYOUT(
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [2] = LAYOUT(
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [3] = LAYOUT(
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case MKC_LG:
            if (record->event.pressed) {
                process_magic(GUI_TOG, record);
            }
            return false;
        case MKC_MACOS:
            if (record->event.pressed) {
                process_magic(AG_TOGG, record);
            }
            return false;
        case MKC_CGT:
            if (record->event.pressed) {
                process_magic(CG_TOGG, record);
            }
            return false;
        case MKC_MCTL:
            if (record->event.pressed) {
                host_consumer_send(0x29F);
            } else {
                host_consumer_send(0);
            }
            return false;
        case MKC_LPAD:
            if (record->event.pressed) {
                host_consumer_send(0x2A0);
            } else {
                host_consumer_send(0);
            }
            return false;
        default:
            return true;
    }
    return true;
}
