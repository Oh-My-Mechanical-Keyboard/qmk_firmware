// Copyright 2024 HackStone-HAL9000 (@Jason)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    WIN_BASE,
    WIN_FN,
    MAC_BASE,
    MAC_FN,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [WIN_BASE] = LAYOUT( /* Base */
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   KC_MUTE, KC_HOME, KC_END,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,   KC_BSPC, KC_INS,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC,  KC_BSLS, KC_DEL,  KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT, KC_UP,
        KC_LCTL,  KC_LALT,  KC_LGUI,                                KC_SPC,                                 KC_RALT,  MO(WIN_FN), KC_RCTL, KC_LEFT,   KC_DOWN, KC_RGHT),
    [WIN_FN] = LAYOUT(  /* FN */
        _______,  KC_BRID,  KC_BRIU,  G(KC_TAB),G(KC_D),  KC_WBAK,  KC_WSCH,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU, _______,  _______, _______,
        _______,  KC_BT1,   KC_BT2,   KC_BT3,   KC_2G4,   KC_USB,   _______,  _______,  _______,  _______,  _______,  RGB_SPD,  RGB_SPI, _______,  _______, _______,
        KRGB_TOG, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  LRGB_SPD, LRGB_VAL,LRGB_TOG, _______, _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,           _______,
        _______,            RGB_MOD,  RGB_RMOD, _______,  _______,  KC_BATQ,  NK_TOGG,  DF(2),    _______,  _______,  _______,           _______,  RGB_VAI,
        _______,  GU_TOGG,  _______,                                _______,                                _______,  _______,  _______, RGB_HUI,  RGB_VAD, RGB_HUD),

    [MAC_BASE] = LAYOUT(  /* Base */
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  G(KC_DOWN),  KC_WSCH,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU, KC_MUTE,   KC_HOME, KC_END,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,    KC_EQL,  KC_BSPC,   KC_INS,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,    KC_RBRC, KC_BSLS,   KC_DEL,  KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,             KC_ENT,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,             KC_RSFT,   KC_UP,
        KC_LCTL,  KC_LALT,  KC_LGUI,                                KC_SPC,                                 KC_RALT,  MO(MAC_FN), KC_RCTL, KC_LEFT,   KC_DOWN, KC_RGHT),
    [MAC_FN] = LAYOUT(  /* FN */
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,  _______,  _______, _______,
        _______,  KC_BT1,   KC_BT2,   KC_BT3,   KC_2G4,   KC_USB,   _______,  _______,  _______,  _______,  _______,  RGB_SPD,  RGB_SPI, _______,  _______, _______,
        KRGB_TOG, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  LRGB_SPD, LRGB_VAL,LRGB_TOG, _______, _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,           _______,
        _______,            RGB_MOD,  RGB_RMOD, _______,  _______,  KC_BATQ,  NK_TOGG,  DF(0),    _______,  _______,  _______,           _______,  RGB_VAI,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______, RGB_HUI,  RGB_VAD, RGB_HUD)
};
// clang-format on
