// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define LAYOUT( \
    L000, L001,  L002,  L003,  L004,  L005,  L006, L007, L008, L009, L010, L011, L012, L013, L014, L015, L016, \
    L100, L101,  L102,  L103,  L104,  L105,  L106, L107, L108, L109, L110, L111, L112, L113, L114, L115, L116, \
    L200, L201,  L202,  L203,  L204,  L205,  L206, L207, L208, L209, L210, L211, L212, L213, L214, L215, L216, \
    L300, L301,  L302,  L303,  L304,  L305,  L306, L307, L308, L309, L310, L311,       L313,                   \
    L400, L401,  L402,  L403,  L404,  L405,  L406, L407, L408, L409, L410,       L412,             L415,       \
    L500, L501,  L502,  L503,                                              L511, L512, L513, L514, L515, L516, \
    \
    R000, R001,  R002,  R003, \
    R100, R101,  R102,  R103, \
    R200, R201,  R202,  R203, \
    R300, R301,  R302,        \
    R400, R401,  R402,  R403, \
    R500,        R502         \
) { \
	{ L000, L001,  L002,  L003,  L004,   L005,   L006,   L007,   L008,   L009,   L010,   L011,  L012,  L013,  L014,  L015,  L016 },  \
	{ L100, L101,  L102,  L103,  L104,   L105,   L106,   L107,   L108,   L109,   L110,   L111,  L112,  L113,  L114,  L115,  L116 },  \
	{ L200, L201,  L202,  L203,  L204,   L205,   L206,   L207,   L208,   L209,   L210,   L211,  L212,  L213,  L214,  L215,  L216 },  \
	{ L300, L301,  L302,  L303,  L304,   L305,   L306,   L307,   L308,   L309,   L310,   L311,  KC_NO, L313,  KC_NO, KC_NO, KC_NO }, \
	{ L400, L401,  L402,  L403,  L404,   L405,   L406,   L407,   L408,   L409,   L410,   KC_NO, L412,  KC_NO, KC_NO, L415,  KC_NO }, \
	{ L500, L501,  L502,  L503,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  L511,  L512,  L513,  L514,  L515,  L516 },  \
    \
	{ R000, R001,  R002,  R003,  KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ R100, R101,  R102,  R103,  KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ R200, R201,  R202,  R203,  KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ R300, R301,  R302,  KC_NO, KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ R400, R401,  R402,  R403,  KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ R500, KC_NO, R502,  KC_NO, KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }  \
}
