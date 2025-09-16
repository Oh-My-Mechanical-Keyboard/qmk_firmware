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
#define VENDOR_ID 0xAA96
#define PRODUCT_ID 0xAABB
#define DEVICE_VER 0x0001
#define MANUFACTURER "Y&R"
#define PRODUCT "tagar98ble"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 18

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

//                         0  1   2   3    4  5
#define MATRIX_COL_PINS { }
#define MATRIX_ROW_PINS { A7, A3, A4, A5, A6, B10 }

#define NUM_OF_74HC595 3
#define COL_F2L_FOR_595 TRUE

#define SR_74HC595_ZERO_ONEP 0x00
#define SR_74HC595_ONES_ONEP 0xFF

//                             a     b     c     d     e     f     g     h
#define SR_74HC595_LINE_MASK { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 }
//                           c0    c1    c2    c3    c4    c5    c6    c7    c8    c9    c10,  c11   c12   c13   c14   c15   c16   c17
#define MATRIX_OF_74HC595 {{ 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },\
                           { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00 },\
                           { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x10, 0x08, 0x40 }}


#define SPI_SCK_PIN_OF_595 A8
#define SPI_MOSI_PIN_OF_595 B14
#define SPI_74HC595_CS B15

// enable the nkro when using the VIA.
#define FORCE_NKRO

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define TAP_CODE_DELAY 15

#define TAP_HOLD_CAPS_DELAY 200

#ifdef RGBLIGHT_ENABLE

#    define WS2812_DI_PIN B12
#    define RGBLED_NUM 3
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


// for ble
// #define USE_MUILT_THREAD_FOR_BLE
#define DISABLE_MAGIC_BOOTLOADER
#define DISABLE_EEPROM_CLEAR

#define BIUSTM32WKPin A0
#define BIUNRF52WKPin A1
#define BIUNRF52ResetPin A2
// disable rgb when using ble
#define RGB_BLE_SW B13
#define RGB_EN_STATE 1

// enable ble indicator
#define BleGetChannleEnable

// USB Power
#define USB_PWR_READ
#define USB_PWR_READ_PIN B1

// ADC SETTING
#define SAMPLE_BATTERY
#define BATTERY_LEVEL_SW_PIN C13


/* W25QXX */
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN B6
#define EXTERNAL_FLASH_PAGE_SIZE 256
#define EXTERNAL_FLASH_SECTOR_SIZE (4 * 1024)
#define EXTERNAL_FLASH_BLOCK_SIZE (64 * 1024)
#define EXTERNAL_FLASH_ADDRESS_SIZE 3
/* w25q32*/
#define EXTERNAL_FLASH_SIZE (4 * 1024 * 1024)
#define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR 1

#define EXTERNAL_FLASH_SPI_TIMEOUT 50

// Wear-leveling driver configuration
// #define WEAR_LEVELING_LOGICAL_SIZE 1024
// #define WEAR_LEVELING_BACKING_SIZE (WEAR_LEVELING_LOGICAL_SIZE * 2)

/* ST7735 TFT*/
// reset
#define ST7735_RES_PIN B8
// display/command rs pin
#define ST7735_DC_PIN B7
// chip select
#define ST7735_CS_PIN A15
// LED Anode
#define ST7735_BLK_PIN B9
// Byte Order
#define TFT_COLOR_BYTE_ORDER TFT_COLOR_BYTE_ORDER_BGR
// #define TFT_COLOR_BYTE_ORDER TFT_COLOR_BYTE_ORDER_RGB

#define ST7735S_NO_AUTOMATIC_VIEWPORT_OFFSETS

/* SPI For Flash and TFT*/
#define SPI_DRIVER SPID3
#define SPI_SCK_PIN B3
#define SPI_SCK_PAL_MODE 6
#define SPI_MOSI_PIN B5
#define SPI_MOSI_PAL_MODE 6
#define SPI_MISO_PIN B4
#define SPI_MISO_PAL_MODE 6


#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0

#define QUANTUM_PAINTER_SUPPORTS_256_PALETTE TRUE
#define QUANTUM_PAINTER_CONCURRENT_ANIMATIONS 1
#define QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE 2048
// #define QUANTUM_PAINTER_DEBUG
// #define DEBUG_FLASH_SPI_OUTPUT

#define QP_STREAM_HAS_SPI_FLASH_IO
// #define QP_USE_MULTI_THREAD
