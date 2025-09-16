// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define LAYOUT( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, \
          K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, \
          K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, \
          K301,       K303, K304, K305,       K307,       K309, K310, K311  \
) { \
    { K000,   K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011 }, \
    { KC_NO,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111 }, \
    { KC_NO,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211 }, \
    { KC_NO,  K301,  KC_NO, K303,  K304,  K305,  KC_NO, K307,  KC_NO, K309,  K310,  K311 }  \
}

void rgb_matrix_adv_unblink_all_batlayer_but_one_layer(uint8_t l);
