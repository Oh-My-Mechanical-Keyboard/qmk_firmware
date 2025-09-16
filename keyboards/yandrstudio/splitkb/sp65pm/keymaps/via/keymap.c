// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum keyboard_keycodes {
    LOCK_GUI = QK_KB,
    TOG_MACOS_KEYMAP_MAC,
    KC_MISSION_CONTROL_MAC,
    KC_LAUNCHPAD_MAC
};

#define MKC_LG    LOCK_GUI
#define MKC_MACOS TOG_MACOS_KEYMAP_MAC
#define MKC_MCTL  KC_MISSION_CONTROL_MAC
#define MKC_LPAD  KC_LAUNCHPAD_MAC

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC, KC_F5,  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
        KC_F1,  KC_F6,  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        KC_F2,  KC_F7,  KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_F3,  KC_F8,  KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,
        KC_F4,  KC_F9,  KC_LCTL,          KC_LGUI, KC_LALT,          KC_SPC, // left
        KC_7,            KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BSPC,  KC_INS,
        KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_BSLS,  KC_DEL,
        KC_H,            KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,  KC_ENT,   KC_HOME,
        KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,  KC_UP,    KC_END,
                KC_SPC,           KC_RALT, MO(1),            KC_LEFT,  KC_DOWN,  KC_RIGHT,  // right
        KC_NUM, KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,  KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,  KC_P5,   KC_P6,
        KC_P1,  KC_P2,   KC_P3,   KC_PENT,
                KC_P0,   KC_PDOT // pad
        ),
    [1] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS, // left
        KC_F7,            KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS,  KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MKC_MACOS,KC_TRNS,
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
                 KC_TRNS,          KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,  KC_TRNS,  // right
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS // pad
        )
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