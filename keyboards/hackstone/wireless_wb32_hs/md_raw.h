// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define RENAME_WITH_LINE(A, B) COMBINE(A, B)
#define COMBINE(A, B) A##B
#define raw_hid_send(a, b) RENAME_WITH_LINE(_temp_rhs_, __LINE__)(a, b)
#define _temp_rhs_29  replaced_hid_send  // raw_hid.h
#define _temp_rhs_461  replaced_hid_send  // via.c
// nova65.c nova75.c
#define _temp_rhs_36  replaced_hid_send
#define _temp_rhs_47  replaced_hid_send

// hk8710.c
#define _temp_rhs_21  replaced_hid_send

// luck65v2.c
#define _temp_rhs_136 replaced_hid_send

// ptg64a.c
#define _temp_rhs_239 replaced_hid_send
#define _temp_rhs_250 replaced_hid_send

// smart875.c
#define _temp_rhs_193 replaced_hid_send

// whale75.c
#define _temp_rhs_214 replaced_hid_send
#define _temp_rhs_225 replaced_hid_send

// x100mkll.c
#define _temp_rhs_38 replaced_hid_send
#define _temp_rhs_49 replaced_hid_send
