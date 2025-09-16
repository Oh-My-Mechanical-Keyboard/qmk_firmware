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
#define PRODUCT_ID      0xAAAC
#define DEVICE_VER      0x0001
#define MANUFACTURER    ZUOER_Y&R
#define PRODUCT         zpad_ble


/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 21


/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define NUM_OF_74HC595 3
#define COL_F2L_FOR_595 TRUE

#define SR_74HC595_ZERO_ONEP 0x00
#define SR_74HC595_ONES_ONEP 0xFF

//                        0       1       2       3       4       5       6       7       8       9       10      11
#define MATRIX_COL_PINS { }
#define MATRIX_ROW_PINS { B15 }

#if (COL_F2L_FOR_595==TRUE)
                                 // a    b     c     d     e      f     g    h
#   define SR_74HC595_LINE_MASK { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 }
//                               c0    c1    c2    c3    c4    c5    c6    c7    c8    c9    c10   c11  c12    c13  c14   c15   c16   c17   c18   c19   c20
#   define MATRIX_OF_74HC595 {{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x20, 0x40, 0x00, 0x00, 0x00},\
                              { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x02, 0x04, 0x08, 0x80, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},\
                              { 0x20, 0x10, 0x80, 0x40, 0x01, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00}}
#else
                                 // a    b     c     d     e      f     g    h
#   define SR_74HC595_LINE_MASK { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 }

#endif


#define SPI_SCK_PIN_OF_595 B14
#define SPI_MOSI_PIN_OF_595 B12
#define SPI_74HC595_CS B13


/* RGN Matrix */
#ifdef RGB_MATRIX_ENABLE

#    define RGB_DI_PIN A7
#    define RGBLED_NUM 16
#    define DRIVER_LED_TOTAL RGBLED_NUM

#define WS2812_PWM_DRIVER PWMD3  // default: PWMD2
#define WS2812_PWM_CHANNEL 2  // default: 2
#define WS2812_PWM_PAL_MODE 2  // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM2  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_DMA_CHANNEL 5  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.


#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 160
#    define RGBLIGHT_VAL_STEP 16
#    define RGB_DISABLE_WHEN_USB_SUSPENDED TRUE
#    define RGB_MATRIX_CENTER { 96, 32 }
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS

#endif


#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN A7
#    define RGBLED_NUM 16
#    define RGBLIGHT_ANIMATIONS
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLIGHT_LIMIT_VAL 160

#define WS2812_PWM_DRIVER PWMD3  // default: PWMD2
#define WS2812_PWM_CHANNEL 2  // default: 2
#define WS2812_PWM_PAL_MODE 2  // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM2  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_DMA_CHANNEL 5  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.

#endif

#ifdef ENCODER_ENABLE

#    define ENCODERS_PAD_A { A5 }
#    define ENCODERS_PAD_B { A8 }

#    define ENCODER_RESOLUTIONS { 2 }

#endif

// enable the nkro when using the VIA.
#define FORCE_NKRO

// fix VIA RGB_light
#define VIA_HAS_BROKEN_KEYCODES

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define TAP_CODE_DELAY 15

#define DISABLE_MAGIC_BOOTLOADER
#define DISABLE_EEPROM_CLEAR

// for ble
// disable rgb when using ble
// #define RGB_ONLY_ON_WHEN_USB
// rgb switch
#define RGB_BLE_SW A6
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
