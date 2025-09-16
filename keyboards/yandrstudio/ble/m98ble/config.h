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
#define PRODUCT_ID      0xAAC7
#define DEVICE_VER      0x0001
#define MANUFACTURER    JOJO_Y&R
#define PRODUCT         M98

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

#define BOOTMAGIC_LITE_COLUMN 0
#define BOOTMAGIC_LITE_ROW 0

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

// enable the nkro when using the VIA.
#define FORCE_NKRO

// fix VIA RGB_light
#define VIA_HAS_BROKEN_KEYCODES

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define TAP_CODE_DELAY 15

#define LED_NUM_LOCK_PIN     A3
#define LED_CAPS_LOCK_PIN    A4
#define LED_BAT_LOW_PIN      A5
#define LED_PIN_ON_STATE     1


#define DISABLE_MAGIC_BOOTLOADER
#define DISABLE_EEPROM_CLEAR

// for ble
// #define USE_MUILT_THREAD_FOR_BLE
// disable rgb when using ble
#define RGB_ONLY_ON_WHEN_USB
// rgb switch
#define RGB_BLE_SW A6
// wk pin
#define BIUSTM32WKPin    A0
#define BIUNRF52ResetPin A1
#define BIUNRF52WKPin    A2
// USB Power
#define USB_PWR_READ
#define USB_PWR_READ_PIN B10
// ADC SETTING
#define SAMPLE_BATTERY
#define BATTERY_LEVEL_SW_PIN B1 // Adc pin

