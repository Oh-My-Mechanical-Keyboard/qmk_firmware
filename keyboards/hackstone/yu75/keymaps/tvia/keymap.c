// Copyright 2024 Jason
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "eeprom.h"

enum layers{
    WIN_BASE = 0,
    WIN_FN,
    MAC_BASE,
    MAC_FN
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [WIN_BASE] = LAYOUT( /* Base */
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,  KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,    KC_F11,   KC_F12,    KC_PSCR, KC_SCRL,
        KC_GRV,  KC_1,    KC_2,    KC_3,   KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      KC_MINS,  KC_EQL,    KC_BSPC, KC_INS,  KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_LBRC,  KC_RBRC,   KC_BSLS, KC_DEL,  KC_END,
        KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,   KC_QUOT,             KC_ENT,  KC_PGUP, KC_PGDN,
        KC_LSFT, KC_Z,    KC_X,   KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_RSFT,             KC_DEL,  KC_UP,   KC_MUTE,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,          KC_SPC,                                      KC_SPC,    KC_RALT, MO(WIN_FN), KC_LEFT, KC_DOWN, KC_RIGHT),
    [WIN_FN] = LAYOUT(  /* FN */
        _______,  KC_BRID,  KC_BRIU,  LWIN(KC_TAB),   LWIN(KC_D),     RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,   KC_VOLD,  KC_VOLU, _______, _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______, _______, _______, _______,
        _______,  KC_BT1,   KC_BT2,   KC_BT3,   KC_2G4,   KC_USB,   _______,  _______,  _______,  _______,  _______,   _______,  _______, _______, _______, _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,           _______, _______, _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  NK_TOGG,  DF(2),    _______,  _______,   _______,           _______, _______, _______,
        _______,  GU_TOGG,  _______,  _______,            _______,                                          _______,   _______,  _______, _______, _______, _______),
    [MAC_BASE] = LAYOUT(  /* Base */
        KC_ESC,  KC_BRID, KC_BRIU, KC_MCTL,KC_LPAD, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,   KC_VOLD,  KC_VOLU,   KC_PSCR, KC_SCRL,
        KC_GRV,  KC_1,    KC_2,    KC_3,   KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      KC_MINS,  KC_EQL,    KC_BSPC, KC_INS,  KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_LBRC,  KC_RBRC,   KC_BSLS, KC_DEL,  KC_END,
        KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,   KC_QUOT,             KC_ENT,  KC_PGUP, KC_PGDN,
        KC_LSFT, KC_Z,    KC_X,   KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_RSFT,             KC_DEL,  KC_UP,   KC_MUTE,
        KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,          KC_SPC,                                      KC_SPC,    KC_RALT, MO(MAC_FN), KC_LEFT, KC_DOWN, KC_RIGHT),
    [MAC_FN] = LAYOUT(  /* FN */
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,   KC_F12,  _______, _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______, _______, _______, _______,
        _______,  KC_BT1,   KC_BT2,   KC_BT3,   KC_2G4,   KC_USB,   _______,  _______,  _______,  _______,  _______,   _______,  _______, _______, _______, _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,           _______, _______, _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  NK_TOGG,  DF(0),    _______,  _______,   _______,           _______, _______, _______,
        _______,  _______,  _______,  _______,            _______,                                          _______,   _______,  _______, _______, _______, _______),
};
