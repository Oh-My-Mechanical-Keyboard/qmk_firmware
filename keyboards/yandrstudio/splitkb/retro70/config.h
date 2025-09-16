// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAABA
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Retro_Y&R"
/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 16

//                               0      1       2       3       4       5       6       7       8       9       10      11      12      13      14      15
#define MATRIX_COL_PINS       { NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, A4,     A3 }
#define MATRIX_ROW_PINS       { A5,     A6,     A7,     B0,     B1 }
#define MATRIX_COL_PINS_RIGHT { B1,     B2,     B10,    B11,    B12,    A0,     A2,     A1,     A3,     A4,     A5,     A6,     A7,     B0,     NO_PIN, NO_PIN }
#define MATRIX_ROW_PINS_RIGHT { B13,    NO_PIN, NO_PIN, NO_PIN, NO_PIN }

#ifdef I_AM_LEFT
#    define BOOTMAGIC_LITE_ROW 0
#    define BOOTMAGIC_LITE_COLUMN 0
#else
#    define BOOTMAGIC_LITE_ROW 5
#    define BOOTMAGIC_LITE_COLUMN 0
#endif

#define USE_BOTH_595_AND_GPIO
#define NUM_OF_74HC595 2
#define COL_F2L_FOR_595 TRUE

#define SR_74HC595_ZERO_ONEP 0x00
#define SR_74HC595_ONES_ONEP 0xFF

//                             a     b     c     d     e     f     g     h
#define SR_74HC595_LINE_MASK { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 }
//                           c0    c1    c2    c3    c4    c5    c6    c7    c8    c9    c10,  c11   c12   c13   c14   c15
#define MATRIX_OF_74HC595 {{ 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },\
                           { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x01, 0x00, 0x00 }}

#define SPI_SCK_PIN_OF_595 B5
#define SPI_MOSI_PIN_OF_595 B7
#define SPI_74HC595_CS B6

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define WEAR_LEVELING_BACKING_SIZE 4096
#define WEAR_LEVELING_LOGICAL_SIZE 2048

#ifdef SPLIT_KEYBOARD

#   define SERIAL_USART_TX_PIN A9
#   define SERIAL_USART_DRIVER SD1

#    define SPLIT_TRANSPORT_MIRROR

#    define SPLIT_USB_DETECT

#    define SPLIT_WATCHDOG_ENABLE

#    define SPLIT_MODS_ENABLE
#    define SPLIT_LAYER_STATE_ENABLE
#    define SPLIT_LED_STATE_ENABLE

#endif
