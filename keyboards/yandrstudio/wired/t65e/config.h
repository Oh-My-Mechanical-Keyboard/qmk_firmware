// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAADD
#define MANUFACTURER    "MACHINA"
#define PRODUCT         "MACHINA ORBIT"

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define TAP_CODE_DELAY 15

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define LED_CAPS_LOCK_PIN B1
#define LED_PIN_ON_STATE  1
