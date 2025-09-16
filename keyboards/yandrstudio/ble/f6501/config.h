// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID 0xAA96
#define PRODUCT_ID 0xAA13
#define DEVICE_VER 0x0001
#define MANUFACTURER "OMMK_Y&R"
#define PRODUCT "F6501"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW
#define COL_ROW_DIODE_INVERSE_FOR_595
#define SLEEP_IN_STOP_MATRIX_LOW

#define MATRIX_COL_PINS { }
#define MATRIX_ROW_PINS { B3, B4, B5, B6, B7 }

#define NUM_OF_74HC595 2
#define COL_F2L_FOR_595 TRUE

#define SR_74HC595_ZERO_ONEP 0x00
#define SR_74HC595_ONES_ONEP 0xFF

//                             a     b     c     d     e     f     g     h
#define SR_74HC595_LINE_MASK { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 }
//                           c0    c1    c2    c3    c4    c5    c6    c7    c8    c9    c10,  c11   c12   c13   c14
#define MATRIX_OF_74HC595 {{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 },\
                           { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }}


#define SPI_SCK_PIN_OF_595 A7
#define SPI_MOSI_PIN_OF_595 A5
#define SPI_74HC595_CS A6

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define TAP_CODE_DELAY 15

// for ble
#define USE_MUILT_THREAD_FOR_BLE
#define DISABLE_MAGIC_BOOTLOADER
#define DISABLE_EEPROM_CLEAR

#define BIUSTM32WKPin A0
#define BIUNRF52WKPin A1
#define BIUNRF52ResetPin B9

// enable ble indicator
#define BleGetChannleEnable

// USB Power
#define USB_PWR_READ
#define USB_PWR_READ_PIN A3


// ADC SETTING
#define SAMPLE_BATTERY
#define BATTERY_LEVEL_PIN A4
#define ADVANCE_SLEEP_MODE_V1_NO_DP_UP_ESD
#define USE_BAT_MAP_V2

/* W25QXX */
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN B12
#define EXTERNAL_FLASH_PAGE_SIZE 256
#define EXTERNAL_FLASH_SECTOR_SIZE (4 * 1024)
#define EXTERNAL_FLASH_BLOCK_SIZE (64 * 1024)
#define EXTERNAL_FLASH_ADDRESS_SIZE 3
/* w25q32*/
#define EXTERNAL_FLASH_SIZE (4 * 1024 * 1024)
#define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR 8

#define EXTERNAL_FLASH_SPI_TIMEOUT 500

// Wear-leveling driver configuration
// #define WEAR_LEVELING_LOGICAL_SIZE 1024
// #define WEAR_LEVELING_BACKING_SIZE (WEAR_LEVELING_LOGICAL_SIZE * 2)

/* ST7735 TFT*/
// reset
#define ST7735_RES_PIN A8
// display/command rs pin
#define ST7735_DC_PIN C6
// chip select
#define ST7735_CS_PIN B11
// LED Anode
#define ST7735_BLK_PIN B10
// Byte Order
// #define TFT_COLOR_BYTE_ORDER TFT_COLOR_BYTE_ORDER_BGR
#define TFT_COLOR_BYTE_ORDER TFT_COLOR_BYTE_ORDER_RGB

#define ST7735S_NO_AUTOMATIC_VIEWPORT_OFFSETS
#define ST7735_NO_AUTOMATIC_VIEWPORT_OFFSETS

/* SPI For Flash and TFT*/
#define SPI_DRIVER SPID2
#define SPI_SCK_PIN B13
#define SPI_SCK_PAL_MODE 5
#define SPI_MOSI_PIN B15
#define SPI_MOSI_PAL_MODE 5
#define SPI_MISO_PIN B14
#define SPI_MISO_PAL_MODE 5


#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0

#define QUANTUM_PAINTER_SUPPORTS_256_PALETTE TRUE
#define QUANTUM_PAINTER_CONCURRENT_ANIMATIONS 1
#define QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE 2048
// #define QUANTUM_PAINTER_DEBUG
// #define DEBUG_FLASH_SPI_OUTPUT

#define QP_STREAM_HAS_SPI_FLASH_IO
#define QP_USE_MULTI_THREAD


#define QP_THD_SIZE 640
#define KB_THD_SIZE 4096
#define BLE_THD_SIZE 2048
