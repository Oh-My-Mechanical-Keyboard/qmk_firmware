// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
/*
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K015, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113,       K115, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211,       K213,       K215, \
    K300, K301, K306, K305, K304, K303, K302, K307, K308, K309, K310, K311, K312, K313,       K315, \
    K400, K401, K402,                         K407, K408, K409,             K412, K413,       K415  \
*/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,   KC_4,    KC_5,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_BSPC, KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_END,
        KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,    KC_G,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGUP,
        KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,   KC_V,  KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,            KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                                  KC_SPC,  KC_RALT, MO(1),                     KC_LEFT, KC_DOWN,          KC_RGHT),
    LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_DEL,  KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,                                      KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS,          KC_TRNS),
    LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS,          KC_TRNS),
    LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS,          KC_TRNS)
};

#if defined(ENCODER_MAP_ENABLE) && defined(ENCODER_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1]  = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [2]  = {ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
    [3]  = {ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)}
};
#endif
