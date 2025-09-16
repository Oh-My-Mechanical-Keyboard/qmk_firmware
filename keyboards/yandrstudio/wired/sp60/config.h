// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define MANUFACTURER    TG_Y&R
#define PRODUCT         SP60


/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define TAP_CODE_DELAY 15

// enable the nkro when using the VIA.
#define FORCE_NKRO

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5
