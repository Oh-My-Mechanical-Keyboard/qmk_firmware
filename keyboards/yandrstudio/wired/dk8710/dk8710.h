// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

        KC_ESC,  KC_F1,   KC_F2,   KC_F3,  KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,    KC_F11,   KC_F12,
        KC_GRV,  KC_1,    KC_2,    KC_3,   KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      KC_MINS,  KC_EQL,   KC_BACKSPACE, KC_INS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_LBRC,  KC_RBRC,  KC_BSLS,      KC_DEL,
        KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,   KC_QUOT,            KC_ENT,       KC_PGUP,
        KC_LSFT,          KC_Z,    KC_X,   KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,    KC_SLSH,  KC_RSFT,  KC_UP,        KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                  KC_SPC,                             KC_RALT, MO(1),     KC_RCTL,  KC_LEFT,  KC_DOWN,      KC_RGHT)

#define LAYOUT( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012,       \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K513, K600, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K601, \
    K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K313, K603, \
    K400,       K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K413, K613, K604,\
    K500, K501, K502,             K505,                   K509, K510, K512, K612, K610, K611 \
) { \
    { K000, K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010, K011,  K012,  KC_NO }, \
    { K100, K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110, K111,  K112,  KC_NO }, \
    { K200, K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210, K211,  K212,  K213  }, \
    { K300, K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310, K311,  KC_NO, K313  }, \
    { K400, KC_NO, K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410, K411,  KC_NO, K413  }, \
    { K500, K501,  K502,  KC_NO, KC_NO, K505,  KC_NO, KC_NO, KC_NO, K509,  K510, KC_NO, K512,  K513  }, \
    { K600, K601,  KC_NO, K603,  K604,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K610, K611,  K612,  K613   } \
}

