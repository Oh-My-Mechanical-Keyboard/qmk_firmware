/* Copyright 2021 JasonRen(biu)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0xAA96
#define PRODUCT_ID 0xAA00
#define DEVICE_VER 0x0001
#define MANUFACTURER Y&R_Magic Mvp
#define PRODUCT rainbow65

/* key matrix set */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS { B5, B4, A3, A2, B9 }
#define MATRIX_COL_PINS { A10, A9, A8, B14, B13, B12, B11, B10, B1, B0, A7, A6, A5, A4, B8 }


#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5



// enable the nkro when using the VIA.
#define FORCE_NKRO

// fix VIA RGB_light
#define VIA_HAS_BROKEN_KEYCODES




#ifdef RGBLIGHT_ENABLE
#    define RGB_DI_PIN B15
#    define RGBLED_NUM 68
#    define RGBLIGHT_ANIMATIONS
#endif // RGBLIGHT_ENABLE




/* RGN Matrix */
#ifdef RGB_MATRIX_ENABLE

#    define RGB_DI_PIN B15
#    define RGBLED_NUM 68
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define WS2812_SPI SPID2 // default: SPID1
#    define WS2812_SPI_MOSI_PAL_MODE 5

#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 180
#    define RGBLIGHT_VAL_STEP 18
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true
#    define RGB_MATRIX_CENTER { 112, 32 }
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS

#endif

/* Encoder */
#ifdef ENCODER_ENABLE
#    define ENCODERS_PAD_A { A15 }
#    define ENCODERS_PAD_B { B3 }
#    define ENCODER_RESOLUTION 4
#endif


/* Others */
#define TAP_HOLD_CAPS_DELAY 20
#define TAP_CODE_DELAY 10


#define BIND_SPACE_RGB_WITH_OTHER
#define BIND_SPACE_RGB_INDEX 59
#define BIND_WITH_SPACE_INDEXS { 57, 58, 60, 61 }
#define BIND_SPACE_RGB_NUM 4

#endif
