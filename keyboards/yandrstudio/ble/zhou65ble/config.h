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

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAAC5
#define DEVICE_VER      0x0001
#define MANUFACTURER    "ZHOU_Y&R"
#define PRODUCT         "zhou65ble"

// enable the nkro when using the VIA.
#define FORCE_NKRO

// fix VIA RGB_light
#define VIA_HAS_BROKEN_KEYCODES

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

// #define DEBUG_MATRIX_SCAN_RATE
#define TAP_CODE_DELAY 15

#define HOLD_ON_OTHER_KEY_PRESS
// #define USE_MUILT_THREAD_FOR_BLE
#define TAP_HOLD_CAPS_DELAY 200

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
#define SLEEP_IN_STOP_MATRIX_LOW
