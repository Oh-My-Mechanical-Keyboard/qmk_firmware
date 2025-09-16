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
#include "cums_spi_master.h"
#include "util.h"
#include "matrix.h"
#include "quantum.h"

#ifdef DIRECT_PINS
#    error invalid DIRECT_PINS for 74hc595 matrix
#elif (DIODE_DIRECTION == ROW2COL)
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
#elif (DIODE_DIRECTION == COL2ROW)
static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
#else
#   error DIODE_DIRECTION must be defined
#endif
static const uint8_t line_mask_values[8] = SR_74HC595_LINE_MASK;

/* matrix state(1:on, 0:off) */
extern matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
extern matrix_row_t matrix[MATRIX_ROWS];      // debounced values

static inline void setPinOutput_writeLow(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinOutput(pin);
        writePinLow(pin);
    }
}

static inline void setPinInputHigh_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON { setPinInputHigh(pin); }
}

// matrix code

#ifdef DIRECT_PINS

#    error invalid DIRECT_PINS for 74hc595 matrix

#elif defined(DIODE_DIRECTION)
#    if (DIODE_DIRECTION == COL2ROW)

static void select_col(uint8_t col) {
    uint8_t i = 0;
    spi_start(false, 0, 2);
#if COL_F2L_FOR_595
    for (i = NUM_OF_74HC595; i >=1 ; --i) {
        if (i-1 == col/8) {
            spi_write(line_mask_values[col%8]);
        } else {
            spi_write(SR_74HC595_ZERO_ONEP);
        }
    }
#else
    for (i = 0; i < NUM_OF_74HC595; ++i) {
        if (i == NUM_OF_74HC595 - 1 - (col/8)) {
            spi_write(line_mask_values[col%8]);
        } else {
            spi_write(SR_74HC595_ZERO_ONEP);
        }
    }
#endif
    writePinHigh(SPI_74HC595_CS); // output to storge registor
    writePinLow(SPI_74HC595_CS);
    spi_stop();
}

static void unselect_cols(void) {
    uint8_t i = 0;
    spi_start(false, 0, 2);
    for (i = 0; i < NUM_OF_74HC595; ++i) {
        spi_write(SR_74HC595_ZERO_ONEP);
    }
    writePinHigh(SPI_74HC595_CS); // output to storge registor
    writePinLow(SPI_74HC595_CS);
    spi_stop();
}

static void unselect_rows(void) {
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInputLow(row_pins[x]);
    }
}

static void init_pins(void) {
    writePinLow(SPI_74HC595_CS);
    unselect_rows();
    unselect_cols();
}

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
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
    if (current_col + 1 < MATRIX_COLS) {
        matrix_output_unselect_delay();  // wait for col signal to go Low
    }

    return matrix_changed;
}

#    elif (DIODE_DIRECTION == ROW2COL)

static void select_row(uint8_t row) {
    uint8_t i = 0;
    spi_start(false, 0, 2);
#if COL_F2L_FOR_595
    for (i = NUM_OF_74HC595; i >=1 ; --i) {
        if (i-1 == row / 8) {
            spi_write(line_mask_values[row % 8]);
        } else {
            spi_write(SR_74HC595_ZERO_ONEP);
        }
    }
#else
    for (i = 0; i < NUM_OF_74HC595; ++i) {
        if (i == NUM_OF_74HC595 - 1 - (row / 8)) {
            spi_write(line_mask_values[row % 8]);
        } else {
            spi_write(SR_74HC595_ZERO_ONEP);
        }
    }
#endif
    writePinHigh(SPI_74HC595_CS); // output to storge registor
    writePinLow(SPI_74HC595_CS);
    spi_stop();
}

static void unselect_rows(void) {
    uint8_t i = 0;
    spi_start(false, 0, 2);
    for (i = 0; i < NUM_OF_74HC595; ++i) {
        spi_write(SR_74HC595_ZERO_ONEP);
    }
    writePinHigh(SPI_74HC595_CS); // output to storge registor
    writePinLow(SPI_74HC595_CS);
    spi_stop();
}

static void unselect_cols(void) {
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinInputLow(col_pins[x]);
    }
}

static void init_pins(void) {
    writePinLow(SPI_74HC595_CS);
    unselect_cols();
    unselect_rows();
}


static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;

    // Select row
    select_row(current_row);
    matrix_output_select_delay();

    // For each col...
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
        // Select the col pin to read (active low)
        uint8_t pin_state = readPin(col_pins[col_index]);

        // Populate the matrix row with the state of the col pin
        current_row_value |= pin_state ? (MATRIX_ROW_SHIFTER << col_index) : 0;
    }

    // Unselect row
    unselect_rows();
    if (current_row + 1 < MATRIX_ROWS) {
        matrix_output_unselect_delay();  // wait for row signal to go HIGH
    }

    // If the row has changed, store the row and return the changed flag.
    if (current_matrix[current_row] != current_row_value) {
        current_matrix[current_row] = current_row_value;
        return true;
    }
    return false;
}

#    else
#        error DIODE_DIRECTION must be one of COL2ROW or ROW2COL!
#    endif
#else
#    error DIODE_DIRECTION is not defined!
#endif

void matrix_init_custom(void) {
    spi_init();
    // initialize key pins
    init_pins();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }
}

uint8_t matrix_scan_custom(void) {
    bool changed = false;

#if defined(DIRECT_PINS) || (DIODE_DIRECTION == COL2ROW)
    // Set col, read rows
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        changed |= read_rows_on_col(raw_matrix, current_col);
    }
#elif (DIODE_DIRECTION == ROW2COL)
    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        changed |= read_cols_on_row(raw_matrix, current_row);
    }
#endif

    return (uint8_t)changed;
}
