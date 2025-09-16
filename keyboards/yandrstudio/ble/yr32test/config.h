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
#define PRODUCT_ID      0xAA0A
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Y&R"
#define PRODUCT         "yr32test"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 11

//                        0    1    2    3    4   5
#define MATRIX_COL_PINS {  }
#define MATRIX_ROW_PINS { A7,  A6,  C15,  C14, C13 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define NUM_OF_74HC595 2
#define COL_F2L_FOR_595 TRUE

#define SR_74HC595_ZERO_ONEP 0x00
#define SR_74HC595_ONES_ONEP 0xFF

                              // a    b     c     d     e      f     g    h
#define SR_74HC595_LINE_MASK { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 }
//                            c0    c1    c2    c3    c4    c5    c6    c7    c8    c9    c10
#define MATRIX_OF_74HC595 {{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x04, 0x02, 0x01 },\
                           { 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00 }}


#define SPI_SCK_PIN_OF_595 B13
#define SPI_MOSI_PIN_OF_595 B15
#define SPI_74HC595_CS B14

#ifdef ENCODER_ENABLE

#    define ENCODERS_PAD_A { B1 }
#    define ENCODERS_PAD_B { B2 }

#    define ENCODER_RESOLUTIONS { 4 }

#endif


#ifdef RGBLIGHT_ENABLE
#    define WS2812_DI_PIN B5
#    define RGBLED_NUM 6
#    define RGBLIGHT_LIMIT_VAL 180
#    define DRIVER_LED_TOTAL RGBLED_NUM

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

#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define TAP_CODE_DELAY 15

#define DISABLE_MAGIC_BOOTLOADER
#define DISABLE_EEPROM_CLEAR

// for ble
//RGB
#   define RGB_BLE_SW B4
// USB Power
#define USB_PWR_READ
#define USB_PWR_READ_PIN A8
// ADC SETTING
#define SAMPLE_BATTERY
#define BATTERY_LEVEL_SW_PIN  B10
// wake pin
#define BIUSTM32WKPin         A0
#define BIUNRF52ResetPin      A1
#define BIUNRF52WKPin         A2
