// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#define LAYOUT( \
    L00,   L01,   L02,   L03,   L04,   L05,        \
    L10,   L11,   L12,   L13,   L14,   L15,   L16, \
    L20,   L21,   L22,   L23,   L24,   L25,   L26, \
    L30,   L31,   L32,   L33,   L34,   L35,        \
                         L43,   L44,   L45,   L46, \
           R01,   R02,   R03,   R04,   R05,   R06, \
    R10,   R11,   R12,   R13,   R14,   R15,   R16, \
    R20,   R21,   R22,   R23,   R24,   R25,   R26, \
           R31,   R32,   R33,   R34,   R35,   R36, \
    R40,   R41,   R42,   R43    \
) { \
	{ L00,   L01,   L02,   L03,   L04,   L05,   KC_NO }, \
	{ L10,   L11,   L12,   L13,   L14,   L15,   L16   }, \
	{ L20,   L21,   L22,   L23,   L24,   L25,   L26   }, \
	{ L30,   L31,   L32,   L33,   L34,   L35,   KC_NO }, \
	{ KC_NO, KC_NO, KC_NO, L43,   L44,   L45,   L46   }, \
                                                         \
   	{ KC_NO, R01,   R02,   R03,   R04,   R05,   R06   }, \
	{ R10,   R11,   R12,   R13,   R14,   R15,   R16   }, \
	{ R20,   R21,   R22,   R23,   R24,   R25,   R26   }, \
	{ KC_NO, R31,   R32,   R33,   R34,   R35,   R36   }, \
	{ R40,   R41,   R42,   R43,   KC_NO, KC_NO, KC_NO }  \
}
