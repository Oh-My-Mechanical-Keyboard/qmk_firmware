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
#define PRODUCT_ID      0xAAC5
#define DEVICE_VER      0x0001
#define MANUFACTURER    SAM_Y&R
#define PRODUCT         s68mble

// enable the nkro when using the VIA.
#define FORCE_NKRO

// fix VIA RGB_light
#define VIA_HAS_BROKEN_KEYCODES

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 3

// #define DEBUG_MATRIX_SCAN_RATE
#define TAP_CODE_DELAY 15

// for ble
// #define S68M_REV1
// rgb switch
// #ifdef S68M_REV1

#define DISABLE_MAGIC_BOOTLOADER
#define DISABLE_EEPROM_CLEAR

#   define BIUNRF52ResetPin A1
#   define BIUNRF52WKPin A0
#   define BIUSTM32WKPin A2

// USB Power
#   define USB_PWR_READ
#   define USB_PWR_READ_PIN B13

// ADC SETTING
#   define SAMPLE_BATTERY
#   define BATTERY_LEVEL_SW_PIN B1 // Adc pin

#   define SLEEP_IN_STOP_MATRIX_LOW

// #endif
