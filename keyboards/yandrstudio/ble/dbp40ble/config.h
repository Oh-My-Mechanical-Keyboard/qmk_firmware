// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xAA96
#define PRODUCT_ID      0xAAB6
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Y&R"
#define PRODUCT         "DBP46"

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 13

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

//                        0    1    2    3    4    5    6   7   8   9   10  11  12
#define MATRIX_COL_PINS { B10, B12, B13, B14, B15, A8, A15, B3, B4, A6, B7, B8, B6}
#define MATRIX_ROW_PINS { A3,  A4,  A5,  B9 }

#define TAP_CODE_DELAY 15

#define HOLD_ON_OTHER_KEY_PRESS

#define TAP_HOLD_CAPS_DELAY 200

// for ble
#define USE_MUILT_THREAD_FOR_BLE

#define DISABLE_MAGIC_BOOTLOADER
#define DISABLE_EEPROM_CLEAR

#define BIUSTM32WKPin A0
#define BIUNRF52WKPin A1
#define BIUNRF52ResetPin A2
// USB Power
#define USB_PWR_READ
#define USB_PWR_READ_PIN A7

// ADC SETTING
#define SAMPLE_BATTERY
#define BATTERY_LEVEL_SW_PIN B1
#define USE_BAT_MAP_V1
