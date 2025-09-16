// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define LAYOUT( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K015, K016, K017, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112,       K114, K115, K116, K117, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,                         \
    K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312,                   K316,       \
    K400, K401, K402,                   K406,             K409, K410, K411, K412,             K415, K416, K417  \
) { \
    { K000, K001,  K002, K003,  K004,  K005,  K006, K007,  K008,  K009, K010, K011, K012, K013,  K014,  K015,  K016,  K017  }, \
    { K100, K101,  K102, K103,  K104,  K105,  K106, K107,  K108,  K109, K110, K111, K112, KC_NO, K114,  K115,  K116,  K117  }, \
    { K200, K201,  K202, K203,  K204,  K205,  K206, K207,  K208,  K209, K210, K211, K212, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { K300, KC_NO, K302, K303,  K304,  K305,  K306, K307,  K308,  K309, K310, K311, K312, KC_NO, KC_NO, KC_NO, K316,  KC_NO }, \
    { K400, K401,  K402, KC_NO, KC_NO, KC_NO, K406, KC_NO, KC_NO, K409, K410, K411, K412, KC_NO, KC_NO, K415,  K416,  K417  }  \
}


enum keyboard_keycodes {
    LOCK_GUI = QK_KB,
    TOG_MACOS_KEYMAP_MAC,
    KC_MISSION_CONTROL_MAC,
    KC_LAUNCHPAD_MAC,
    BT_1,BT_2,BT_3,
    BT_4,BT_5,BT_6,BT_7,
    BT_8,BT_9,BT_10
};

#if defined(RGBLIGHT_ENABLE) && defined(BIU_BLE5_ENABLE)
void rgb_adv_unblink_all_layer(void);
#endif
