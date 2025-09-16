// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "process_magic.h"

#define MKC_LG     LOCK_GUI
#define MKC_MACOS  TOG_MACOS_KEYMAP_MAC
#define MKC_MCTL   KC_MISSION_CONTROL_MAC
#define MKC_LPAD   KC_LAUNCHPAD_MAC


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(
        KC_PGUP, KC_DEL,   KC_PGDN, KC_MUTE,
        KC_F1,   KC_F2,    KC_F3,   MO(1),
        KC_F4,   KC_F5,    KC_F6),
    LAYOUT(
        KC_TRNS,  KC_TRNS,    KC_TRNS,    TOP_RGB_TOG,
        KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,    RGB_TOG),
    LAYOUT(
        KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,    KC_TRNS),
    LAYOUT(
        KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,    KC_TRNS)
};

#if defined(ENCODER_MAP_ENABLE) && defined(ENCODER_ENABLE)

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT)},
    [1]  = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(RGB_MOD, RGB_RMOD)},
    [2]  = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [3]  = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS)}
};

#endif




bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MO(1):
        case LT(1, KC_SPC):
        case LT(2, KC_SPC):
            if (!yr_factory_test) return true;
            if (record->event.pressed) {
                register_code(KC_SPC);
            } else {
                unregister_code(KC_SPC);
            }
            return false;
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
