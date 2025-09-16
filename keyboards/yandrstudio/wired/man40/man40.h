// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "quantum.h"

#define LAYOUT( \
    K000, K001, K002, K003, K004, K005, K006, K007, \
    K100, K101, K102, K103, K104, K105, K106, K107, \
    K200, K201, K202, K203, K204, K205, K206, K207, \
    K300, K301, K302, K303, K304, K305, K306, K307, \
    K400, K401, K402, K403, K404, K405, K406, K407  \
    )\
    { \
    { K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007 }, \
    { K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107 }, \
    { K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207 }, \
    { K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307 }, \
    { K400,  K401,  K402,  K403,  K404,  K405,  K406,  K407 }}
