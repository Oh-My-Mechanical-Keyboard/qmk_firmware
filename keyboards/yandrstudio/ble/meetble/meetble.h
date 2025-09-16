// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define LAYOUT( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K015, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, \
    K200, K206, K205, K204, K203, K202, K201,       K208, K209, K210, K211, K212, K213, K214, K215, \
          K306, K305, K304, K303, K302, K301, K307, K308, K309, K310, K311, K312, K313, K314,       \
          K404, K403, K402, K401,                               K411, K410, K412, K413, K414, K415  \
) { \
    { K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013, K014, K015 }, \
    { K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113, K114, K115 }, \
    { K200,  K201,  K202,  K203,  K204,  K205,  K206,  KC_NO, K208,  K209,  K210,  K211,  K212,  K213, K214, K215 }, \
    { KC_NO, K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313, K314, KC_NO}, \
    { KC_NO, K401,  K402,  K403,  K404,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K410,  K411,  K412,  K413, K414, K415 }  \
}

#if defined(RGBLIGHT_ENABLE) && defined(BIU_BLE5_ENABLE)
void rgb_adv_unblink_all_layer(void);
#endif
