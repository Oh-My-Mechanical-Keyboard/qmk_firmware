// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAA69
#define DEVICE_VER      0x0001
#define MANUFACTURER    SOUL_Y&R
#define PRODUCT         keit75

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

//                        0    1    2    3     4    5    6    7    8    9    10   11   12   13   14
#define MATRIX_COL_PINS { A4,  B10, B13, B14,  B15, A8,  A9,  A10, B4,  B5,  B6,  B7,  C13, C14, C15 }
#define MATRIX_ROW_PINS { B2,  B1,  B0,  A6,   A5,  B11 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

// enable the nkro when using the VIA.
#define FORCE_NKRO

// fix VIA RGB_light
#define VIA_HAS_BROKEN_KEYCODES

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN A7
#    define RGBLED_NUM 4
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLIGHT_LIMIT_VAL 180
#    define RGBLIGHT_SLEEP


#    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_EFFECT_TWINKLE
#    define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_MOOD

#    define RGBLIGHT_LAYERS
#    define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#    define RGBLIGHT_LAYERS_RETAIN_VAL

#endif
