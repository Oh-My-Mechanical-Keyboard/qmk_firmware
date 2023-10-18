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


#   ifdef USE_BOTH_595_AND_GPIO
const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
#   endif
const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
const uint8_t mask_of_each_595[MATRIX_ROWS][2][2] = MATRIX_OF_74HC595;


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


static void select_col(uint8_t col) {
    if (col > 14) return;
#   ifdef USE_BOTH_595_AND_GPIO
    if (col_pins[col] != NO_PIN) {
        writePinHigh(col_pins[col]);
        return;
    }
#   endif
}

static void unselect_cols(void) {
    uint8_t i = 0;
#   ifdef USE_BOTH_595_AND_GPIO
    for (i = 0; i < MATRIX_COLS; ++i) {
        if (col_pins[i] != NO_PIN) {
            writePinLow(col_pins[i]);
        }
    }
#   endif

    writePinLow(SPI_74HC595_CS);
    for (i = 0; i < NUM_OF_74HC595; ++i) {
        shift_out_single(sr_zero);
    }
    writePinHigh(SPI_74HC595_CS);
}

static void unselect_rows(void) {
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInputLow(row_pins[x]);
    }
    setPinInputLow(ROW_AUX_READ_PIN);
}

static void init_pins(void) {
    setPinOutput(SPI_SCK_PIN_OF_595);
    setPinOutput(SPI_MOSI_PIN_OF_595);
    setPinOutput(SPI_74HC595_CS);
    writePinHigh(SPI_SCK_PIN_OF_595);
    writePinHigh(SPI_MOSI_PIN_OF_595);
    writePinHigh(SPI_74HC595_CS);
#   ifdef USE_BOTH_595_AND_GPIO
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

static void select_col_aux(uint8_t col_595_i, uint8_t val_595) {
    writePinLow(SPI_74HC595_CS);
    for (uint8_t i = 0; i < NUM_OF_74HC595; ++i) {
        if (i == col_595_i) {
            shift_out_single(val_595);
        } else {
            shift_out_single(sr_zero);
        }
    }
    writePinHigh(SPI_74HC595_CS);
}

static void unselect_cols_aux(void) {
    writePinLow(SPI_74HC595_CS);
    for (uint8_t i = 0; i < NUM_OF_74HC595; ++i) {
        shift_out_single(sr_zero);
    }
    writePinHigh(SPI_74HC595_CS);
}
static bool read_rows_on_col_aux(matrix_row_t current_matrix[], uint8_t current_col) {
    bool matrix_changed = false;

    uint8_t col_595 = current_col - 15;
    uint8_t col_595_i = 0;
    uint8_t val_595 = sr_zero;
    uint8_t row_index = 0;
    for (row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        col_595_i = mask_of_each_595[row_index][col_595][0];
        val_595   = mask_of_each_595[row_index][col_595][1];
        // update the 595 state
        select_col_aux(col_595_i, val_595);
        matrix_output_select_delay();
        // Store last value of row prior to reading
        matrix_row_t last_row_value    = current_matrix[row_index];
        matrix_row_t current_row_value = last_row_value;
        if (readPin(ROW_AUX_READ_PIN) == 1) {
            current_row_value |= (MATRIX_ROW_SHIFTER << current_col);
        } else {
            current_row_value &= ~(MATRIX_ROW_SHIFTER << current_col);
        }
        if ((last_row_value != current_row_value)) {
            matrix_changed |= true;
            current_matrix[row_index] = current_row_value;
        }
        unselect_cols_aux();
        matrix_output_unselect_delay(current_col, matrix_changed);  // wait for all Row signals to go HIGH
    }


    return matrix_changed;
}

static bool read_rows_on_col_norm(matrix_row_t current_matrix[], uint8_t current_col) {
    bool matrix_changed = false;

    // Select col
    select_col(current_col);
    matrix_output_select_delay();

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
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
        if (current_col <= 14) {
            changed |= read_rows_on_col_norm(current_matrix, current_col);
        } else {
            changed |= read_rows_on_col_aux(current_matrix, current_col);
        }
    }

    return (uint8_t)changed;
}
