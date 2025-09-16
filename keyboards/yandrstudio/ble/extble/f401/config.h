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

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 24

/* key matrix pins */
#define MATRIX_ROW_PINS { A4, A5}
#define MATRIX_COL_PINS {}


/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define LED_CAPS_LOCK_PIN A15
#define LED_PIN_ON_STATE    0


#define NUM_OF_74HC595 3
#define COL_F2L_FOR_595 FALSE

#if COL_F2L_FOR_595
#   define SR_74HC595_LINE_MASK { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 }
#else
#   define SR_74HC595_LINE_MASK { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 }
#endif
#define SR_74HC595_ZERO_ONEP 0x00

#define SPI_SCK_PIN_OF_595 B13
#define SPI_SCK_PAL_MODE_OF_595 5
#define SPI_MOSI_PIN_OF_595 B15
#define SPI_MOSI_PAL_MODE_OF_595 5

#define SPI_74HC595_CS B12
