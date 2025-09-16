// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define LAYOUT( \
    K000, K001, K002, K003, K004, K005,       \
    K106, K107, K108, K109, K110, K111, K112, \
    K200, K201, K202, K203, K204, K205,       \
    K306, K307, K308, K309, K310,       K312, \
    K400, K401, K402, K403, K404, K405,       \
    K506, K507, K508, K509, K510, K511, K512, \
    K600, K601,       K603, K604,             \
          K707, K708,       K710, K711, K712  \
) { \
    { K000, K001, K002, K003, K004, K005, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K106, K107, K108, K109, K110, K111, K112 }, \
    { K200, K201, K202, K203, K204, K205, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K306, K307, K308, K309, K310, KC_NO, K312 }, \
    { K400, K401, K402, K403, K404, K405, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K506, K507, K508, K509, K510, K511, K512 }, \
    { K600, K601, KC_NO, K603, K604, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K707, K708, KC_NO, K710, K711, K712 }  \
}

void rgb_matrix_adv_unblink_all_batlayer_but_one_layer(uint8_t l);
