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
#define PRODUCT_ID      0xAAEA
#define DEVICE_VER      0x0001
#define MANUFACTURER    "MU_Y&R"
#define PRODUCT         "PRISM_PAD"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 4

//                        0    1    2    3    4   5   6   7   8   9   10  11  12  13
#define MATRIX_COL_PINS { A6,  A7,  A15, B4}
#define MATRIX_ROW_PINS { A5,  A4,  A3,  C13, C14 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define LED_NUM_LOCK_PIN     B12
#define LED_PIN_ON_STATE     1

#define HOLD_ON_OTHER_KEY_PRESS
#define TAP_HOLD_CAPS_DELAY 200

//for caps
// #define USE_MUILT_THREAD_FOR_BLE

// for ble
#define DISABLE_MAGIC_BOOTLOADER
#define DISABLE_EEPROM_CLEAR

#define BIUSTM32WKPin A0
#define BIUNRF52ResetPin A1
#define BIUNRF52WKPin A2
// USB Power
#define USB_PWR_READ
#define USB_PWR_READ_PIN B6
// ADC SETTING
#define SAMPLE_BATTERY
#define BATTERY_LEVEL_SW_PIN B7

