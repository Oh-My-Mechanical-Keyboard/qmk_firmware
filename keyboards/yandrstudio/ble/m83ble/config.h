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
#define PRODUCT_ID      0xAA62
#define DEVICE_VER      0x0001
#define MANUFACTURER    "JOJO_Y&R"
#define PRODUCT         "m83"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 20

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW


#define MATRIX_COL_PINS { }
#define MATRIX_ROW_PINS { A3, A4, A5, A6, A7 }

#define NUM_OF_74HC595 3
#define COL_F2L_FOR_595 TRUE

#define SR_74HC595_ZERO_ONEP 0x00
#define SR_74HC595_ONES_ONEP 0xFF

                            //   a    b     c     d     e      f     g    h
#define SR_74HC595_LINE_MASK { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 }
                        //   c0    c1    c2    c3    c4    c5    c6    c7     c8    c9    c10,  c11   c12   c13   c14   c15   c16   c17   c18   c19
#define MATRIX_OF_74HC595 {{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 },\
                           { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },\
                           { 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }}


#define SPI_SCK_PIN_OF_595 B12
#define SPI_MOSI_PIN_OF_595 B14
#define SPI_74HC595_CS B13


#ifdef RGBLIGHT_ENABLE

#    define WS2812_DI_PIN B4
#    define RGBLED_NUM 87
#    define RGBLIGHT_LIMIT_VAL 180
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_LAYERS
#    define RGBLIGHT_LAYER_BLINK
#    define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#    define RGBLIGHT_LAYERS_RETAIN_VAL
#    define RGBLIGHT_MAX_LAYERS 11

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

#define LED_CAPS_LOCK_PIN    A15
#define LED_PIN_ON_STATE     1

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define TAP_CODE_DELAY 15

#define HOLD_ON_OTHER_KEY_PRESS
#define TAP_HOLD_CAPS_DELAY 150

// for ble
#define DISABLE_MAGIC_BOOTLOADER
#define DISABLE_EEPROM_CLEAR

// disable rgb when using ble
#define RGB_BLE_SW B3
#define RGB_EN_STATE 1

#define BleGetChannleEnable

#define BIUSTM32WKPin A0
#define BIUNRF52ResetPin A1
#define BIUNRF52WKPin A2

// USB Power
#define USB_PWR_READ
#define USB_PWR_READ_PIN B6
// ADC SETTING
#define SAMPLE_BATTERY
#define BATTERY_LEVEL_SW_PIN B5 // Adc sw
// row2col
#define SLEEP_IN_STOP_MATRIX_LOW
