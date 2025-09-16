// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

/*
    L000, L001,  L002,  L003,  L004,  L005,  L006, L007, L008, L009, L010, L011, L012, L013, L014, L015, L016, \
    L100, L101,  L102,  L103,  L104,  L105,  L106, L107, L108, L109, L110, L111, L112, L113, L114, L115, L116, \
    L200, L201,  L202,  L203,  L204,  L205,  L206, L207, L208, L209, L210, L211, L212, L213, L214, L215, L216, \
    L300, L301,  L302,  L303,  L304,  L305,  L306, L307, L308, L309, L310, L311,       L313,                   \
    L400, L401,  L402,  L403,  L404,  L405,  L406, L407, L408, L409, L410,       L412,             L415,       \
    L500, L501,  L502,  L503,                                              L511, L512, L513, L514, L515, L516, \
    \
    R000, R001,  R002,  R003, \
    R100, R101,  R102,  R103, \
    R200, R201,  R202,  R203, \
    R300, R301,  R302,        \
    R400, R401,  R402,  R403, \
    R500,        R502,        \
*/



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,  KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_F13,  KC_MUTE, KC_VOLU, KC_VOLD,
        KC_GRV,  KC_1,    KC_2,    KC_3,   KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,                   KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,                                                                KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT,

        KC_ESC,   KC_TAB,   KC_BSPC,  MO(1),
        KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_P7,    KC_P8,    KC_P9,    KC_PPLS,
        KC_P4,    KC_P5,    KC_P6,
        KC_P1,    KC_P2,    KC_P3,    KC_PENT,
        KC_P0,              KC_PDOT),
	[1] = LAYOUT(
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS,  RGB_TOG, RGB_MOD, RGB_RMOD,RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,                   KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,                                                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

        KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,   KC_TRNS,  KC_TRNS,
        KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,             KC_TRNS),
	[2] = LAYOUT(
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,                   KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,                                                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

        KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,   KC_TRNS,  KC_TRNS,
        KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,             KC_TRNS),
	[3] = LAYOUT(
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,                   KC_TRNS,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,                                                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

        KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,   KC_TRNS,  KC_TRNS,
        KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,             KC_TRNS),
};