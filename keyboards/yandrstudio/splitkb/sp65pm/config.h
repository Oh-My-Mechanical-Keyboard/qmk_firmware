// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID     0xAA96
#define PRODUCT_ID    0xAA0F
#define DEVICE_VER    0x0001
#define MANUFACTURER  "Y&R"
#define PRODUCT       "SPKB_ProMax"

/* key matrix size */
#define MATRIX_ROWS 15
#define MATRIX_COLS 9

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define DYNAMIC_KEYMAP_LAYER_COUNT 2

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

// UART settings for communication with the RF microcontroller
#define SERIAL_UART_BAUD 1000000
#define SERIAL_UART_DATA UDR1
#define SERIAL_UART_UBRR (F_CPU / (16UL * SERIAL_UART_BAUD) - 1)
#define SERIAL_UART_TXD_READY (UCSR1A & _BV(UDRE1))
#define SERIAL_UART_RXD_PRESENT (UCSR1A & _BV(RXC1))
#define SERIAL_UART_INIT()                  \
    do {                                    \
        /* baud rate */                     \
        UBRR1L = SERIAL_UART_UBRR;          \
        /* baud rate */                     \
        UBRR1H = SERIAL_UART_UBRR >> 8;     \
        /* enable TX and RX */              \
        UCSR1B = _BV(TXEN1) | _BV(RXEN1);   \
        /* 8-bit data */                    \
        UCSR1C = _BV(UCSZ11) | _BV(UCSZ10); \
    } while (0)
