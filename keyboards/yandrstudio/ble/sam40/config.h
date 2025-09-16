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
#define PRODUCT_ID      0xAA84
#define DEVICE_VER      0x0001
#define MANUFACTURER    "SAM_Y&R"
#define PRODUCT         "sam40"

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 13

//                        0    1    2    3    4   5    6    7    8    9    10   11,  12
#define MATRIX_COL_PINS { A3,  A4,  A5,  A6,  A7, B12, B13, B14, B15, A8,  B8,  B3,  C13 }
#define MATRIX_ROW_PINS { B7,  B6,  B5,  B4 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

// enable the nkro when using the VIA.
#define FORCE_NKRO


// fix VIA RGB_light
#define VIA_HAS_BROKEN_KEYCODES


/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define TAP_CODE_DELAY 15

#define DISABLE_MAGIC_BOOTLOADER
#define DISABLE_EEPROM_CLEAR

// for ble
// USB Power
#define USB_PWR_READ
#define USB_PWR_READ_PIN B10
// ADC SETTING
#define SAMPLE_BATTERY
#define BATTERY_LEVEL_SW_PIN  B1
// wake pin
#define BIUSTM32WKPin         A0
#define BIUNRF52ResetPin      A1
#define BIUNRF52WKPin         A2

// for ble
// #   define SLEEP_IN_STOP_MATRIX_LOW
