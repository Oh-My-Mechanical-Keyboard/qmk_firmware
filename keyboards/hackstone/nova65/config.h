// Copyright 2024 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB */
#define MANUFACTURER "TOUCHKEYS"
#define PRODUCT "OLLEH65"
#define VENDOR_ID 0xAA96
#define PRODUCT_ID 0xAA2A
#define DEVICE_VER 0x0001

#    define MD_BT1_NAME PRODUCT " BT1"
#    define MD_BT2_NAME PRODUCT " BT2"
#    define MD_BT3_NAME PRODUCT " BT3"
#    define MD_BT4_NAME PRODUCT " BT4"
#    define MD_BT5_NAME PRODUCT " BT5"
#    define MD_DONGLE_PRODUCT PRODUCT " 2.4G"

#define FORCE_NKRO
#define USB_SUSPEND_WAKEUP_DELAY 1000

// #define RGB_MATRIX_TIMEOUT (5 * 60000) // 5 min

#define LPWR_TIMEOUT (10 * 60000) // 无线休眠用时
#define WLS_KEYBOARD_REPORT_KEYS 6 // 无线模式默认按键无冲数量，最大是6

#define USB_CABLE_PIN A15 // USB线接入时为高
#define LED_POWER_EN_PIN C15 // 灯光电源或者GND控制

/* UART */
#define UART_TX_PIN A9
#define UART_RX_PIN A10

/* SPI Config for spi flash*/
#define SPI_DRIVER SPIDM2
#define SPI_SCK_PIN C1
#define SPI_MOSI_PIN C3
#define SPI_MISO_PIN C2

#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN C0
#define WEAR_LEVELING_BACKING_SIZE (4 * 1024)
#define WEAR_LEVELING_LOGICAL_SIZE (WEAR_LEVELING_BACKING_SIZE / 2)

/* 存储数据比较多 */
#define WIRELESS_CONFIG_KB_SIZE 4 // 4个字节的设备信息
#define BOX_LED_CONFIG_KB_SIZE 10 // 10个字节的灯信息
#define EECONFIG_KB_DATA_SIZE (WIRELESS_CONFIG_KB_SIZE + BOX_LED_CONFIG_KB_SIZE)
#define WIRELESS_EECONFIG_ADDR (uint8_t *)(EECONFIG_KB_DATABLOCK)
#define BOX_LED_EECONFIG_ADDR (uint32_t *)((uint32_t)WIRELESS_EECONFIG_ADDR + (uint32_t)WIRELESS_CONFIG_KB_SIZE)

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW
#define TAP_CODE_DELAY 10
#define DEBOUNCE 8
#define HOLD_ON_OTHER_KEY_PRESS

#define LPWR_DIODE_DIRECTION ROW2COL
#define LPWR_OUTPUT_STATE 1

#define LPWR_UART_WAKEUP_DISABLE

#define LPWR_WAK_MODE PAL_EVENT_MODE_RISING_EDGE

/* Key Matrix */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS \
    { C6, C7, C8, C9, B15 }
#define MATRIX_COL_PINS \
    { A4, B0, C5, C4, A7, A6, A5, B6, B3, D2, C12, C11, C10, B7, B4 }

#define DYNAMIC_KEYMAP_LAYER_COUNT 4

/* RGB Matrix */
#define WS2812_DI_PIN B5
#define WS2812_SPI_DRIVER SPIDQ
#define WS2812_SPI_DIVISOR 24

/* It is not mandatory to configure; adjust according to the datasheet of WS2812 LEDs. */
// #define WS2812_TIMING 1500
// #define WS2812_T1H 1200
// #define WS2812_T0H 400

#define RGB_MATRIX_LED_COUNT (6)
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#define RGB_MATRIX_SPD_STEP 70
#define RGB_MATRIX_VAL_STEP 70
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT
#define RGB_MATRIX_SLEEP
#define RGB_MATRIX_DEFAULT_SPD 50

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
// RGB Matrix Animation modes. Explicitly enabled
// For full list of effects, see:
// https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
#define ENABLE_RGB_MATRIX_BREATHING
#undef ENABLE_RGB_MATRIX_HUE_BREATHING
#define ENABLE_RGB_MATRIX_CYCLE_ALL
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
