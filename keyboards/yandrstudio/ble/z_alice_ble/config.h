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
#define PRODUCT_ID      0xAAC2
#define DEVICE_VER      0x0001
#define MANUFACTURER    "ZUOER_Y&R"
#define PRODUCT         "Z_Alice"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define TAP_CODE_DELAY 15

#define HOLD_ON_OTHER_KEY_PRESS
#define TAP_HOLD_CAPS_DELAY 150

/* RGN Matrix */
#ifdef RGB_MATRIX_ENABLE

#   define RGB_DI_PIN A7
#   define RGB_MATRIX_LED_COUNT 69

#   define WS2812_PWM_DRIVER PWMD3  // default: PWMD2
#   define WS2812_PWM_CHANNEL 2  // default: 2
#   define WS2812_PWM_PAL_MODE 2  // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#   define WS2812_DMA_STREAM STM32_DMA1_STREAM2  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#   define WS2812_DMA_CHANNEL 5  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.

#   define RGB_MATRIX_MAXIMUM_BRIGHTNESS 180
#   define RGBLIGHT_VAL_STEP 18
#   define RGB_DISABLE_WHEN_USB_SUSPENDED true
#   define RGB_MATRIX_CENTER { 96, 32 }


#   define RGB_MATRIX_KEYPRESSES
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#   define ENABLE_RGB_MATRIX_SPLASH
#   define ENABLE_RGB_MATRIX_MULTISPLASH
#   define ENABLE_RGB_MATRIX_SOLID_SPLASH
#   define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH


#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#   define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#   define ENABLE_RGB_MATRIX_DIGITAL_RAIN


#   define ENABLE_RGB_MATRIX_ALPHAS_MODS
#   define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#   define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#   define ENABLE_RGB_MATRIX_BREATHING
#   define ENABLE_RGB_MATRIX_BAND_SAT
#   define ENABLE_RGB_MATRIX_BAND_VAL
#   define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#   define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#   define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#   define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#   define ENABLE_RGB_MATRIX_CYCLE_ALL
#   define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#   define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#   define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#   define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#   define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#   define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#   define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#   define ENABLE_RGB_MATRIX_DUAL_BEACON
#   define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#   define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#   define ENABLE_RGB_MATRIX_RAINDROPS
#   define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#   define ENABLE_RGB_MATRIX_HUE_BREATHING
#   define ENABLE_RGB_MATRIX_HUE_PENDULUM
#   define ENABLE_RGB_MATRIX_HUE_WAVE
#   define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#   define ENABLE_RGB_MATRIX_PIXEL_RAIN

#endif


#ifdef RGBLIGHT_ENABLE

#    define RGB_DI_PIN A7
#    define RGBLED_NUM 69
#    define RGBLIGHT_LIMIT_VAL 180
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLIGHT_ANIMATIONS


#    define WS2812_PWM_DRIVER PWMD3  // default: PWMD2
#    define WS2812_PWM_CHANNEL 2  // default: 2
#    define WS2812_PWM_PAL_MODE 2  // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM2  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_DMA_CHANNEL 5  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.

#endif

//                         0   1    2    3    4    5    6    7    8   9   10  11  12  13  14
#define MATRIX_COL_PINS {}
#define MATRIX_ROW_PINS { B6, A5,  A4,  B8,  B9 }


#define NUM_OF_74HC595 2
#define COL_F2L_FOR_595 TRUE

#define SR_74HC595_ZERO_ONEP 0x00
#define SR_74HC595_ONES_ONEP 0xFF

                               // a    b     c     d     e      f     g    h
#define SR_74HC595_LINE_MASK { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 }
//                            c0    c1    c2    c3    c4    c5    c6    c7    c8    c9    c10,  c11   c12   c13   c14  c15
#define MATRIX_OF_74HC595 {{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40 },\
                              { 0x80, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }}


#define SPI_SCK_PIN_OF_595 B13
#define SPI_SCK_PAL_MODE_OF_595 5
#define SPI_MOSI_PIN_OF_595 B15
#define SPI_MOSI_PAL_MODE_OF_595 5
#define SPI_MISO_PIN_OF_595 B14
#define SPI_MISO_PAL_MODE_OF_595 5
#define SPI_74HC595_CS B12


// for ble
// #define USE_MUILT_THREAD_FOR_BLE
#define Z_ALICE_REV1
// rgb switch
#ifdef Z_ALICE_REV1

#   define DISABLE_MAGIC_BOOTLOADER
#   define DISABLE_EEPROM_CLEAR

// disable rgb when using ble
#   define RGB_ONLY_ON_WHEN_USB
#   define RGB_BLE_SW A6

#   define BIUNRF52ResetPin A0
#   define BIUNRF52WKPin A1
#   define BIUSTM32WKPin A3


// USB Power
#   define USB_PWR_READ
#   define USB_PWR_READ_PIN A8

// ADC SETTING
#   define SAMPLE_BATTERY
#   define BATTERY_LEVEL_SW_PIN A2 // Adc pin


#else

#   define DISABLE_MAGIC_BOOTLOADER
#   define DISABLE_EEPROM_CLEAR

// disable rgb when using ble
#   define RGB_ONLY_ON_WHEN_USB
#   define RGB_BLE_SW A6

#   define BIUSTM32WKPin A0
#   define BIUNRF52ResetPin A1
#   define BIUNRF52WKPin A3

// USB Power
#   define USB_PWR_READ
#   define USB_PWR_READ_PIN A8
// ADC SETTING
#   define SAMPLE_BATTERY
#   define BATTERY_LEVEL_SW_PIN A2 // Adc pin

#endif
