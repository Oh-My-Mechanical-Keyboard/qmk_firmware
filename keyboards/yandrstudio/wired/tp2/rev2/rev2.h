// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "tp2.h"

#define LAYOUT( \
    K000,\
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114,      K115, K116, K117, K118,\
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213,            K215, K216, K217, K218,\
    K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312,                  K315, K316, K317,\
    K400, K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411,       K413, K414,      K415, K416, K417, K418,\
    K500, K501, K502,                         K507,             K510, K511, K512, K513, K514,      K515,       K517\
) { \
    { K000,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,       KC_NO, KC_NO, KC_NO, KC_NO }, \
    { K100,   K101,   K102,   K103,   K104,   K105,   K106,   K107,   K108,   K109,   K110,   K111,   K112,   K113,   K114,        K115,  K116,  K117,  K118  }, \
    { K200,   K201,   K202,   K203,   K204,   K205,   K206,   K207,   K208,   K209,   K210,   K211,   K212,   K213,   KC_NO,       K215,  K216,  K217,  K218  }, \
    { K300,   K301,   K302,   K303,   K304,   K305,   K306,   K307,   K308,   K309,   K310,   K311,   K312,   KC_NO,  KC_NO,       K315,  K316,  K317,  KC_NO }, \
    { K400,   K401,   K402,   K403,   K404,   K405,   K406,   K407,   K408,   K409,   K410,   K411,   KC_NO,  K413,   K414,        K415,  K416,  K417,  K418  }, \
    { K500,   K501,   K502,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  K507,   KC_NO,  KC_NO,  K510,   K511,   K512,   K513,   K514,        K515,  KC_NO, K517,  KC_NO }, \
}

