// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "point65.h"

#define LAYOUT( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K015, \
    K100, K110, K109, K108, K107, K106, K105, K104, K103, K102, K101, K113, K112, K111,       K115,\
    K200, K210, K209, K208, K207, K206, K205, K204, K203, K202, K201, K213, K212,             K215,\
    K300, K310, K309, K308, K307, K306, K305, K304, K303, K302, K301, K313, K312,             K315,\
    K400, K401, K402, K403,                                           K411, K412, K413, K414, K415 \
) { \
    { K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014,  K015  }, \
    { K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  KC_NO, K115  }, \
    { K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  KC_NO, K212,  K213,  KC_NO, K215  }, \
    { K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  KC_NO, K312,  K313,  KC_NO, K315  }, \
    { K400,  K401,  K402,  K403,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K411,  K412,  K413,  K414,  K415 }  \
}

