// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define LAYOUT( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211,       K213, K214, \
    K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K313, K314, \
          K401, K402, K403,                               K409, K410, K411,       K413        \
) { \
    { K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014 }, \
    { K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114 }, \
    { K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  KC_NO, K213,  K214 }, \
    { K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  KC_NO, K313,  K314 }, \
    { KC_NO, K401,  K402,  K403,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K409,  K410,  K411,  KC_NO, K413,  KC_NO }  \
}

enum keyboard_keycodes {
    LOCK_GUI = QK_KB,
#ifdef RGB_MATRIX_ENABLE
    BAT_SHOW,
#endif
    TOG_MACOS_KEYMAP_MAC,
    KC_MISSION_CONTROL_MAC,
    KC_LAUNCHPAD_MAC,
    KC_KEY_RGB,
    KC_HEAD_RGB
};

#define MKC_LG     LOCK_GUI
#define MKC_MACOS  TOG_MACOS_KEYMAP_MAC
#define MKC_MCTL   KC_MISSION_CONTROL_MAC
#define MKC_LPAD   KC_LAUNCHPAD_MAC
#define TK_RGB     KC_KEY_RGB
#define TH_RGB     KC_HEAD_RGB

#ifndef RGB_MATRIX_ENABLE
#   define RGB_KG_T  KC_NO
#   define BAT_SHOW  KC_NO
#endif
