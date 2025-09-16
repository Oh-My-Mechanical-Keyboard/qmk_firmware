// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define LAYOUT( \
    L000, L001,  L002,  L003,  L004,  L005,  L006, L007, L008, L009, L010, L011, L012, L013, R000, R001, R002, \
    L100, L101,  L102,  L103,  L104,  L105,  L106, L107, L108, L109, L110, L111, L112, L113, R100, R101, R102, \
    L200, L201,  L202,  L203,  L204,  L205,  L206, L207, L208, L209, L210, L211, L212, L213, R200, R201, R202, \
    L300, L301,  L302,  L303,  L304,  L305,  L306, L307, L308, L309, L310, L311, L312,                         \
    L400, L401,  L402,  L403,  L404,  L405,  L406, L407, L408, L409, L410, L411,                   R401,       \
    L500, L501,  L502,  L503,                                              L511, L512, L513, R500, R501, R502  \
) { \
	{ L000, L001,  L002,  L003,  L004,   L005,   L006,   L007,   L008,   L009,   L010,   L011,  L012,  L013  },  \
	{ L100, L101,  L102,  L103,  L104,   L105,   L106,   L107,   L108,   L109,   L110,   L111,  L112,  L113  },  \
	{ L200, L201,  L202,  L203,  L204,   L205,   L206,   L207,   L208,   L209,   L210,   L211,  L212,  L213  },  \
	{ L300, L301,  L302,  L303,  L304,   L305,   L306,   L307,   L308,   L309,   L310,   L311,  L212,  KC_NO }, \
	{ L400, L401,  L402,  L403,  L404,   L405,   L406,   L407,   L408,   L409,   L410,   L411,  KC_NO, KC_NO }, \
	{ L500, L501,  L502,  L503,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  L511,  L512,  L513  },  \
    \
	{ R000,  R001,  R002,  KC_NO, KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ R100,  R101,  R102,  KC_NO, KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ R200,  R201,  R202,  KC_NO, KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ KC_NO, R401,  KC_NO, KC_NO, KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ R500,  R501,  R502,  KC_NO, KC_NO,  KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }  \
}
