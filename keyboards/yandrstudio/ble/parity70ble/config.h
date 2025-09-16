// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID 0xAA96
#define PRODUCT_ID 0xAAD9
#define DEVICE_VER 0x0001
#define MANUFACTURER "MXRSKEY_Y&R"
#define PRODUCT "Y70"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 17

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define MATRIX_COL_PINS { }
#define MATRIX_ROW_PINS { A7, A6, A5, A4, A3 }

#define NUM_OF_74HC595 3
#define COL_F2L_FOR_595 TRUE

#define SR_74HC595_ZERO_ONEP 0x00
#define SR_74HC595_ONES_ONEP 0xFF

//                             a     b     c     d     e     f     g     h
#define SR_74HC595_LINE_MASK { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 }
//                           c0    c1    c2    c3    c4    c5    c6    c7    c8    c9    c10,  c11   c12   c13   c14   c15   c16
#define MATRIX_OF_74HC595 {{ 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },\
                           { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00 },\
                           { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x20, 0x40 }}


#define SPI_SCK_PIN_OF_595 C15
#define SPI_MOSI_PIN_OF_595 C13
#define SPI_74HC595_CS C14

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define TAP_CODE_DELAY 15

// for ble
#define USE_MUILT_THREAD_FOR_BLE
#define DISABLE_MAGIC_BOOTLOADER
#define DISABLE_EEPROM_CLEAR

#define BIUSTM32WKPin A0
#define BIUNRF52WKPin A1
#define BIUNRF52ResetPin A2
// disable rgb when using ble
#define RGB_BLE_SW B8
#define RGB_EN_STATE 1

// enable ble indicator
#define BleGetChannleEnable

// USB Power
#define USB_PWR_READ
#define USB_PWR_READ_PIN A8
#define ADVANCE_SLEEP_MODE_V1_NO_DP_UP_ESD


// ADC SETTING
#define SAMPLE_BATTERY
#define USE_BAT_MAP_V2

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
#define ST7735_RES_PIN B14
// display/command rs pin
#define ST7735_DC_PIN B13
// chip select
#define ST7735_CS_PIN B12
// LED Anode
#define ST7735_BLK_PIN B15
// Byte Order
#define TFT_COLOR_BYTE_ORDER TFT_COLOR_BYTE_ORDER_BGR
// #define TFT_COLOR_BYTE_ORDER TFT_COLOR_BYTE_ORDER_RGB

#define ST7735S_NO_AUTOMATIC_VIEWPORT_OFFSETS

/* SPI For Flash and TFT*/
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN B3
#define SPI_SCK_PAL_MODE 5
#define SPI_MOSI_PIN B5
#define SPI_MOSI_PAL_MODE 5
#define SPI_MISO_PIN B4
#define SPI_MISO_PAL_MODE 5


#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0

#define QUANTUM_PAINTER_SUPPORTS_256_PALETTE TRUE
#define QUANTUM_PAINTER_CONCURRENT_ANIMATIONS 1
#define QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE 2048
#define QUANTUM_PAINTER_DEBUG
// #define DEBUG_FLASH_SPI_OUTPUT

#define QP_STREAM_HAS_SPI_FLASH_IO
#define QP_USE_MULTI_THREAD

#ifdef RGBLIGHT_ENABLE

#    define WS2812_DI_PIN A15
#    define RGBLED_NUM 4
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_VAL_STEP 5

#    ifdef FACTORY_TEST

#    define RGBLIGHT_LIMIT_VAL 24
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_MODE_RGB_TEST)

#    else

#    define RGBLIGHT_LIMIT_VAL 200
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_MODE_RAINBOW_SWIRL+4)
#    define RGBLIGHT_LAYERS
#    define RGBLIGHT_LAYER_BLINK
#    define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#    define RGBLIGHT_LAYERS_RETAIN_VAL
#    define RGBLIGHT_MAX_LAYERS 15

#   endif


#endif
