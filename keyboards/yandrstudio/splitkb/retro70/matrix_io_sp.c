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

#include <stdint.h>
#include <stdbool.h>
#include "util.h"
#include "matrix.h"
#include "wait.h"
#include "quantum.h"
#include "gpio.h"

#    include "split_common/split_util.h"
#    include "split_common/transactions.h"

#    define ROWS_PER_HAND_SP (MATRIX_ROWS / 2)


// row offsets for each hand
uint8_t thisHand, thatHand;

#ifdef USE_BOTH_595_AND_GPIO
static pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
#endif
static pin_t row_pins[ROWS_PER_HAND_SP] = MATRIX_ROW_PINS;

#ifdef I_AM_LEFT
static uint8_t mask_of_each_595[NUM_OF_74HC595][MATRIX_COLS] = MATRIX_OF_74HC595;

const uint8_t sr_zero = SR_74HC595_ZERO_ONEP;

static inline void setPinOutput_writeLow(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinOutput(pin);
        writePinLow(pin);
    }
}

static inline void setPinInputHigh_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON { setPinInputHigh(pin); }
}


static void shift_out_single(uint8_t value) {
    for (uint8_t i = 0; i < 8; i++) {
        writePinLow(SPI_SCK_PIN_OF_595);
        if ((value>>i)&1) {
            writePinHigh(SPI_MOSI_PIN_OF_595);
        } else {
            writePinLow(SPI_MOSI_PIN_OF_595);
        }
        writePinHigh(SPI_SCK_PIN_OF_595);
    }
}
#endif



// matrix code


static void select_col(uint8_t col) {
#if defined(USE_BOTH_595_AND_GPIO) || defined(I_AM_RIGHT)
    if (col_pins[col] != NO_PIN) {
        writePinHigh(col_pins[col]);
        return;
    }
#endif

#ifdef I_AM_LEFT
    uint8_t i = 0;
    writePinLow(SPI_74HC595_CS);
    for (i = 0; i < NUM_OF_74HC595; ++i) {
        shift_out_single(mask_of_each_595[i][col]);
    }
    writePinHigh(SPI_74HC595_CS);
#endif
}

static void unselect_cols(void) {
    uint8_t i = 0;
#if defined(USE_BOTH_595_AND_GPIO) || defined(I_AM_RIGHT)
    for (i = 0; i < MATRIX_COLS; ++i) {
        if (col_pins[i] != NO_PIN) {
            writePinLow(col_pins[i]);
        }
    }
#endif

#ifdef I_AM_LEFT
    writePinLow(SPI_74HC595_CS);
    for (i = 0; i < NUM_OF_74HC595; ++i) {
        shift_out_single(sr_zero);
    }
    writePinHigh(SPI_74HC595_CS);
#endif
}

static void unselect_rows(void) {
    for (uint8_t x = 0; x < ROWS_PER_HAND_SP; x++) {
        if (row_pins[x] != NO_PIN) {
            setPinInputLow(row_pins[x]);
        }
    }
}

static void init_pins(void) {
#ifdef I_AM_LEFT
    setPinOutput(SPI_SCK_PIN_OF_595);
    setPinOutput(SPI_MOSI_PIN_OF_595);
    setPinOutput(SPI_74HC595_CS);
    writePinHigh(SPI_SCK_PIN_OF_595);
    writePinHigh(SPI_MOSI_PIN_OF_595);
    writePinHigh(SPI_74HC595_CS);
#endif

    // Set pinout for right half if pinout for that half is defined
    if (!isLeftHand) {
#    ifdef MATRIX_ROW_PINS_RIGHT
        const pin_t row_pins_right[ROWS_PER_HAND_SP] = MATRIX_ROW_PINS_RIGHT;
        for (uint8_t i = 0; i < ROWS_PER_HAND_SP; i++) {
            row_pins[i] = row_pins_right[i];
        }
#    endif
#    ifdef MATRIX_COL_PINS_RIGHT
        const pin_t col_pins_right[MATRIX_COLS] = MATRIX_COL_PINS_RIGHT;
        for (uint8_t i = 0; i < MATRIX_COLS; i++) {
            col_pins[i] = col_pins_right[i];
        }
#    endif
    }
    thisHand = isLeftHand ? 0 : (ROWS_PER_HAND_SP);
    thatHand = ROWS_PER_HAND_SP - thisHand;

#   if defined(USE_BOTH_595_AND_GPIO) || defined(I_AM_RIGHT)
    uint8_t i = 0;
    for (i = 0; i < MATRIX_COLS; ++i) {
        if (col_pins[i] != NO_PIN) {
            setPinOutput(col_pins[i]);
        }
    }
#   endif
    unselect_rows();
    unselect_cols();
}

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    bool matrix_changed = false;

    // Select col
    select_col(current_col);
    matrix_output_select_delay();

    // For each row...
    for (uint8_t row_index = 0; row_index < ROWS_PER_HAND_SP; row_index++) {
        if (row_pins[row_index] == NO_PIN) continue;
        // Store last value of row prior to reading
        matrix_row_t last_row_value    = current_matrix[row_index];
        matrix_row_t current_row_value = last_row_value;
        // Check row pin state
        if (readPin(row_pins[row_index]) == 1) {
            // Pin HI, set col bit
            current_row_value |= (MATRIX_ROW_SHIFTER << current_col);
        } else {
            // Pin LO, clear col bit
            current_row_value &= ~(MATRIX_ROW_SHIFTER << current_col);
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_row_value)) {
            matrix_changed |= true;
            current_matrix[row_index] = current_row_value;
        }
    }

    // Unselect col
    unselect_cols();
    matrix_output_unselect_delay(current_col, matrix_changed);  // wait for all Row signals to go HIGH


    return matrix_changed;
}


void matrix_init_custom(void) {
    // initialize key pins
    init_pins();
}

uint8_t matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;
    // Set col, read rows
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        changed |= read_rows_on_col(current_matrix, current_col);
    }
    return (uint8_t)changed;
}
