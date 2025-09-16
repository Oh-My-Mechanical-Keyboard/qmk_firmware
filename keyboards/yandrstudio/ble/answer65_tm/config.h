// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAAB1
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Y&R"
#define PRODUCT         "YR65TM_TV01"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

//                        0    1    2    3   4
#define MATRIX_COL_PINS { }
#define MATRIX_ROW_PINS { B13, B14, B15, A8, A3 }

#define NUM_OF_74HC595 2
#define COL_F2L_FOR_595 TRUE

#define SR_74HC595_ZERO_ONEP 0x00
#define SR_74HC595_ONES_ONEP 0xFF

//                              a    b     c     d     e     f     g     h
#define SR_74HC595_LINE_MASK { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 }
//                          c0    c1    c2    c3    c4    c5    c6    c7    c8    c9    c10,  c11   c12   c13   c13
#define MATRIX_OF_74HC595 {{0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},\
                           {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x80}}

#define SPI_SCK_PIN_OF_595 A4
#define SPI_MOSI_PIN_OF_595 A6
#define SPI_74HC595_CS A5

#define TAP_CODE_DELAY 15

#define HOLD_ON_OTHER_KEY_PRESS

#define TAP_HOLD_CAPS_DELAY 200

// for ble
#define USE_MUILT_THREAD_FOR_BLE

#define DISABLE_MAGIC_BOOTLOADER
#define DISABLE_EEPROM_CLEAR

#define BIUSTM32WKPin A0
#define BIUNRF52ResetPin A1
#define BIUNRF52WKPin A2
// USB Power
#define USB_PWR_READ
#define USB_PWR_READ_PIN A7
// ADC SETTING
#define SAMPLE_BATTERY
#define BATTERY_LEVEL_SW_PIN B1
#define USE_BAT_MAP_V1
