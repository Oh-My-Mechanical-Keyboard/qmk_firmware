// Copyright 2024 HackStone-HAL9000 (@Jason)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "wls_port.h"

#define ___ KC_NO

// clang-format off


#define LAYOUT( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211,       K213, \
    K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, \
    K400, K401, K402,             K405,                   K409, K410, K411, K412, K413  \
) { \
    { K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013 }, \
    { K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113 }, \
    { K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  KC_NO, K213 }, \
    { K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313 }, \
    { K400,  K401,  K402,  KC_NO, KC_NO, K405,  KC_NO, KC_NO, KC_NO, K409,  K410,  K411,  K412,  K413 }  \
}


// clang-format on
enum wl_port_keys {
    KC_BT1 = QK_KB_0,
    KC_BT2,
    KC_BT3,
    KC_2G4,
    KC_USB,
    KC_BATQ,
    KRGB_TOG,
    LRGB_TOG,
    LRGB_COL,
    LRGB_VAL,
    LRGB_SPD
};

typedef struct {
    uint8_t  flag : 1;
    uint8_t  key_rgb_sw : 8;
    uint8_t  box_rgb_mode : 8;
    uint8_t  box_rgb_colored : 1;
    uint8_t  box_rgb_val : 8;
    uint8_t  box_rgb_speed : 8;
    uint8_t  box_rgb_r : 8;
    uint8_t  box_rgb_g : 8;
    uint8_t  box_rgb_b : 8;
} kb_cstm_config_t;

extern kb_cstm_config_t kb_cstm_config;
