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
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAA08
#define DEVICE_VER      0x0001
#define MANUFACTURER    Y&R
#define PRODUCT         nz60ble

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14
//                         0   1    2    3    4    5    6    7    8    9    10   11   12   13
/* key matrix pins */
#define MATRIX_ROW_PINS { C13, C14, C15, B8,  B7 }
#define MATRIX_COL_PINS { A3,  A4,  A5,  A6,  A7,  B12, B13, B14, B15, A8,  B3,  B4,  B5,  B6 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define LED_CAPS_LOCK_PIN A15
#define LED_PIN_ON_STATE    1

// enable the nkro when using the VIA.
#define FORCE_NKRO

// fix VIA RGB_light
#define VIA_HAS_BROKEN_KEYCODES

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

// #define DEBUG_MATRIX_SCAN_RATE
#define TAP_CODE_DELAY 15

#define TAP_HOLD_CAPS_DELAY 200

//for caps
#define HOLD_ON_OTHER_KEY_PRESS
// #define USE_MUILT_THREAD_FOR_BLE

// for ble
#define DISABLE_MAGIC_BOOTLOADER
#define DISABLE_EEPROM_CLEAR

#define BIUSTM32WKPin A0
#define BIUNRF52ResetPin A1
#define BIUNRF52WKPin A2
// USB Power
#define USB_PWR_READ
#define USB_PWR_READ_PIN B10
// ADC SETTING
#define SAMPLE_BATTERY
#define BATTERY_LEVEL_SW_PIN B1
