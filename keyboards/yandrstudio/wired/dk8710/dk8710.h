// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "quantum.h"

#define LAYOUT( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012,       \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112,       \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, \
    K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K313, \
    K400,       K402, K403, K404, K405, K406, K407, K408, K409, K410, K411,       K413, \
    K500, K501, K502,             K505,                   K509, K510,       K512, K513, \
    K600, K601,       K603, K604,                               K610, K611, K612, K613  \
) { \
    { K000, K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010, K011,  K012,  KC_NO }, \
    { K100, K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110, K111,  K112,  KC_NO }, \
    { K200, K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210, K211,  K212,  K213  }, \
    { K300, K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310, K311,  KC_NO, K313  }, \
    { K400, KC_NO, K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410, K411,  KC_NO, K413  }, \
    { K500, K501,  K502,  KC_NO, KC_NO, K505,  KC_NO, KC_NO, KC_NO, K509 , K510, KC_NO, K512,  K513  },  \
    { K600, K601,  KC_NO, K603,  K604,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K610, K611,  K612,  K613  } \
}
extern bool yr_factory_test;
