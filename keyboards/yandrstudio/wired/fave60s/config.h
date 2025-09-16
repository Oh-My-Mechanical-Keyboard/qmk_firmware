// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAADA
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Y&R"
#define PRODUCT         "Fave60S"

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

//                        0    1    2    3   4   5   6   7   8   9    10  11  12  13
#define MATRIX_COL_PINS { A3,  A2,  A1,  A5, A6, A7, A0, B0, B1, B15, B3, B4, B5, B6}
#define MATRIX_ROW_PINS { B12, B13, B14, A8, B7 }

#define TAP_CODE_DELAY 15

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define LED_CAPS_LOCK_PIN A4
#define LED_PIN_ON_STATE  1

#ifdef BACKLIGHT_ENABLE

#define BACKLIGHT_PIN A10
#define BACKLIGHT_ON_STATE 1

#define BACKLIGHT_PWM_DRIVER PWMD1
#define BACKLIGHT_PWM_CHANNEL 3

#define BACKLIGHT_BREATHING
#define BACKLIGHT_LEVELS 3
#define BREATHING_PERIOD 5

#endif
