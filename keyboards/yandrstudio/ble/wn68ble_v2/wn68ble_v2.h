// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define LAYOUT( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K015, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211,       K213, K214, K215, \
    K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310,             K313, K314, K315, \
    K400, K401, K402, K403,                               K409, K410, K411,       K413, K414, K415  \
) { \
    { K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014,  K015 }, \
    { K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114,  K115 }, \
    { K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  KC_NO, K213, K214,  K215 }, \
    { K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  KC_NO, KC_NO, K313, K314,  K315 }, \
    { K400,  K401,  K402,  K403,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K409,  K410,  K411,  KC_NO, K413,  K414,  K415 }  \
}

enum keyboard_keycodes {
#ifdef VIA_ENABLE
    LOCK_GUI = USER00,
#else
    LOCK_GUI = SAFE_RANGE,
#endif
#ifdef RGB_MATRIX_ENABLE
    KC_KEY_UNDER_RGBSW,
    BAT_SHOW,
#endif
    TOG_MACOS_KEYMAP,
    KC_MISSION_CONTROL,
    KC_LAUNCHPAD,
#ifdef VIA_ENABLE
    NEW_SAFE_RANGE = SAFE_RANGE  // Important!
#else
    NEW_SAFE_RANGE   // Important!
#endif


};

#define KC_LG     LOCK_GUI
#define KC_MACOS  TOG_MACOS_KEYMAP
#define KC_MCTL   KC_MISSION_CONTROL
#define KC_LPAD   KC_LAUNCHPAD
#ifdef RGB_MATRIX_ENABLE
#   define RGB_KG_T  KC_KEY_UNDER_RGBSW
#   define KC_BTSH BAT_SHOW
#else
#   define RGB_KG_T KC_TRNS
#   define KC_BTSH KC_TRNS
#endif
