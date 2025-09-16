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
#define PRODUCT_ID      0xAAED
#define DEVICE_VER      0x0001
#define MANUFACTURER    XRAY_Y&R
#define PRODUCT         Xray1xx

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 22

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

//                         0   1    2    3    4    5    6    7    8   9   10  11  12  13  14
#define MATRIX_COL_PINS {}
#define MATRIX_ROW_PINS { B10, A8,  B15, B14, B12, B13 }


#define NUM_OF_74HC595 3
#define COL_F2L_FOR_595 TRUE

#define SR_74HC595_ZERO_ONEP 0x00
#define SR_74HC595_ONES_ONEP 0xFF

                            //   a    b     c     d     e      f     g    h
#define SR_74HC595_LINE_MASK { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 }
                        //   c0    c1    c2    c3    c4    c5    c6    c7    c8    c9    c10,  c11   c12   c13   c14   c15   c16   c17   c18   c19   c20   c21
#define MATRIX_OF_74HC595 {{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x04, 0x08, 0x10, 0x20 },\
                           { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },\
                           { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }}


#define SPI_SCK_PIN_OF_595 B4
#define SPI_MOSI_PIN_OF_595 A15
#define SPI_74HC595_CS B3


#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN B5
#    define RGBLED_NUM 6
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLIGHT_LIMIT_VAL 180
#    define RGBLIGHT_ANIMATIONS

#endif

// enable the nkro when using the VIA.
#define FORCE_NKRO

// fix VIA RGB_light
#define VIA_HAS_BROKEN_KEYCODES

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define TAP_CODE_DELAY 15

#define HOLD_ON_OTHER_KEY_PRESS
#define TAP_HOLD_CAPS_DELAY 150

#ifdef VIA_ENABLE
#   define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2
#   define DYNAMIC_KEYMAP_LAYER_COUNT 4
#   define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 2048
#endif

// for ble
#define DISABLE_MAGIC_BOOTLOADER
#define DISABLE_EEPROM_CLEAR

// disable rgb when using ble
#define RGB_BLE_SW B6

#define BIUSTM32WKPin A0
#define BIUNRF52ResetPin A5
#define BIUNRF52WKPin A6

// USB Power
#define USB_PWR_READ
#define USB_PWR_READ_PIN B1
// ADC SETTING
#define SAMPLE_BATTERY
#define BATTERY_LEVEL_SW_PIN A7 // Adc pin
