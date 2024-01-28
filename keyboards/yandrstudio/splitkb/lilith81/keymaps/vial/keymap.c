// Copyright 2023 FxStudio <FXS@fx-studio.cn>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,    KC_1,    KC_2,    KC_3,   KC_4,    KC_5,  KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_MINS,   KC_EQL,  KC_BSPC,    LT(1,KC_NUM),   KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,    KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,  KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_LBRC,   KC_RBRC,             KC_P7,          KC_P8,     KC_P9,
        KC_CAPS,   KC_A,    KC_S,    KC_D,   KC_F,    KC_G,  KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,   KC_BSLS, KC_ENT,     KC_P4,          KC_P5,     KC_P6,   KC_PPLS,
        KC_LSFT,   KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,  KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,   KC_UP,   KC_DEL,     KC_P1,          KC_P2,     KC_P3,
        KC_LCTL,   KC_LGUI, KC_LALT,                  KC_SPC,                           KC_RALT,MO(1),   KC_LEFT,   KC_DOWN, KC_RIGHT,   KC_P0,          KC_PDOT,            KC_PENT
    ),
    [1] = LAYOUT(
        KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,   KC_F7,             KC_F8,   KC_F9,         KC_F10,     KC_F11,       KC_F12,  KC_DEL,     KC_NO,     RGB_MOD,   RGB_RMOD, RGB_VAD,
        KC_NO,    RGB_TOG, RGB_VAI, RGB_VAD, RGB_MOD, RGB_RMOD, RGB_HUI, RGB_HUD,           RGB_SAI, RGB_SAD,       KC_PSCR,    KC_SCRL,      KC_NO,   KC_HOME,    KC_UP,     KC_PGUP,
        KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   KC_NO,             RGB_SPI, RGB_SPD,       KC_HOME,    KC_PAUSE,     KC_PGUP, KC_NO,      KC_LEFT,   KC_NO,     KC_RIGHT, RGB_VAI,
        KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,   NK_TOGG,           KC_NO,   KC_INSERT,     KC_END,     KC_PGDN,      KC_VOLU, KC_MUTE,    KC_END,    KC_DOWN,   KC_PGDN,
        KC_NO,    KC_NO,   KC_NO,                     KC_NO,                                KC_NO,   KC_NO,         RGB_MOD,    KC_VOLD,      RGB_RMOD,KC_INS,     KC_DEL,    RGB_TOG
    ),
    [2] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,          KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                      KC_NO, KC_NO, KC_NO
    ),
    [3] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,          KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                      KC_NO, KC_NO, KC_NO
    )
};
