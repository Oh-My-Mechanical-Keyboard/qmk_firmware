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

#ifdef BOOTLOADER_TINYUF2
#   define FEE_PAGE_BASE_ADDRESS 0x08008000
#endif

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16
//                          0    1    2    3    4    5    6    7    8   9   10  11  12  13  14
/* key matrix pins */
#define MATRIX_ROW_PINS { B15, B14,  A4,  A3, C15 }
// #define MATRIX_ROW_PINS { B15, B14,  A4,  A3, C13 }
#define MATRIX_COL_PINS {}

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define LED_CAPS_LOCK_PIN B12
#define LED_PIN_ON_STATE    0

#define NUM_OF_74HC595 2
#define COL_F2L_FOR_595 TRUE

#define SR_74HC595_ZERO_ONEP 0x00
#define SR_74HC595_ONES_ONEP 0xFF

                                 // a    b     c     d     e      f     g    h
#   define SR_74HC595_LINE_MASK { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 }
//                               c0    c1    c2    c3    c4    c5    c6    c7    c8    c9    c10,  c11   c12   c13   c14  c15
#   define MATRIX_OF_74HC595 {{ 0x80, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },\
                              { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 }}

#define SPI_SCK_PIN_OF_595 A5
#define SPI_MOSI_PIN_OF_595 A7
#define SPI_74HC595_CS A6

#define COL_ROW_DIODE_INVERSE_FOR_595
