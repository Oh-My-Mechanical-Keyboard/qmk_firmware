// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                    
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LGUI,        
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_PSCR,
        MO(1),   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
                                   KC_LSFT, KC_LCTL, KC_SPC,  KC_LALT,
                 KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_INS,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
        KC_ENT,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
                 KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MO(2), 
        KC_RALT, KC_RCTL, KC_BSPC, KC_RSFT),
    [1] = LAYOUT(
        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                    
        KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS,        
        KC_TRNS, C(KC_A), KC_HOME, KC_PGDN, KC_END,  KC_TRNS, KC_TRNS,
        KC_TRNS, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_INS,  KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_F12,
        KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT,KC_LBRC, KC_RBRC,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSLS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [2] = LAYOUT(
        KC_MUTE, KC_VOLU, KC_VOLD, KC_MPRV, KC_MNXT, KC_MPLY,                    
        KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS,        
        RGB_TOG, RGB_MOD, RGB_VAI, RGB_MOD, RGB_SAI, RGB_HUI, KC_TRNS,
        KC_TRNS, RGB_RMOD,RGB_VAD, RGB_RMOD,RGB_SAD, RGB_HUD,
                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_LBRC,    KC_P7,   KC_P8,   KC_P9,   KC_PMNS, S(KC_LBRC),
        KC_NUM,  KC_RBRC,    KC_P4,   KC_P5,   KC_P6,   KC_PPLS, S(KC_RBRC),
        KC_ENT, S(KC_LBRC),  KC_P1,   KC_P2,   KC_P3,   KC_PENT, KC_TRNS,
                S(KC_RBRC),  KC_P0,   KC_PDOT, KC_PSLS, KC_PAST, KC_TRNS, 
        KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS),
    [3] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                    
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};
