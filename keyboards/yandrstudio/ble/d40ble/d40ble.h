// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define LAYOUT( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110,       K112, \
    K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210,             \
    K300, K301, K302,       K304, K305,       K307,       K309, K310, K311, K312  \
) { \
    { K000, K001,  K002, K003,  K004,  K005, K006,  K007, K008,  K009, K010,  K011,  K012  }, \
    { K100, K101,  K102, K103,  K104,  K105, K106,  K107, K108,  K109, K110,  KC_NO, K112  }, \
    { K200, KC_NO, K202, K203,  K204,  K205, K206,  K207, K208,  K209, K210,  KC_NO, KC_NO }, \
    { K300, K301,  K302, KC_NO, K304,  K305, KC_NO, K307, KC_NO, K309, K310,  K311,  K312  }  \
}

