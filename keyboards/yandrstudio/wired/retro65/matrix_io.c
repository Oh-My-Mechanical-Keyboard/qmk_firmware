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

#ifdef DIRECT_PINS
#    error invalid DIRECT_PINS for 74hc595 matrix
#elif (DIODE_DIRECTION == ROW2COL)
#   ifdef USE_BOTH_595_AND_GPIO
const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
#   endif
const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
const uint8_t mask_of_each_595[NUM_OF_74HC595][MATRIX_ROWS] = MATRIX_OF_74HC595;
#elif (DIODE_DIRECTION == COL2ROW)
#   ifdef USE_BOTH_595_AND_GPIO
const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
#   endif
const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
const uint8_t mask_of_each_595[NUM_OF_74HC595][MATRIX_COLS] = MATRIX_OF_74HC595;
#else
#   error DIODE_DIRECTION must be defined
#endif

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



// matrix code

#ifdef DIRECT_PINS

#    error invalid DIRECT_PINS for 74hc595 matrix

#elif defined(DIODE_DIRECTION)
#    if (DIODE_DIRECTION == COL2ROW)

static void select_col(uint8_t col) {
    uint8_t i = 0;
#   ifdef USE_BOTH_595_AND_GPIO
    if (col_pins[col] != NO_PIN) {
        writePinHigh(col_pins[col]);
        return;
    }
#   endif

    writePinLow(SPI_74HC595_CS);
#if (COL_F2L_FOR_595==TRUE)
    for (i = 0; i < NUM_OF_74HC595; ++i) {
        shift_out_single(mask_of_each_595[i][col]);
    }
#else
    for (i = NUM_OF_74HC595; i >=1 ; --i) {
        shift_out_single(mask_of_each_595[i][col]);
    }
#endif
    writePinHigh(SPI_74HC595_CS);
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

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    bool matrix_changed = false;

    // Select col
    select_col(current_col);
    matrix_output_select_delay();

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
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

#    elif (DIODE_DIRECTION == ROW2COL)

static void select_row(uint8_t row) {
    uint8_t i = 0;
#   ifdef USE_BOTH_595_AND_GPIO
    if (row_pins[row] != NO_PIN) {
        writePinHigh(row_pins[row]);
        return;
    }
#   endif

    writePinLow(SPI_74HC595_CS);
#if (COL_F2L_FOR_595==TRUE)
    for (i = 0; i < NUM_OF_74HC595; ++i) {
        shift_out_single(mask_of_each_595[i][row]);
    }
#else
    for (i = NUM_OF_74HC595; i >=1 ; --i) {
        shift_out_single(mask_of_each_595[i][row]);
    }
#endif
    writePinHigh(SPI_74HC595_CS);
}

static void unselect_rows(void) {
    uint8_t i = 0;
#   ifdef USE_BOTH_595_AND_GPIO
    for (i = 0; i < MATRIX_ROWS; ++i) {
        if (row_pins[i] != NO_PIN) {
            writePinLow(row_pins[i]);
        }
    }
#   endif

    writePinLow(SPI_74HC595_CS);
    for (i = 0; i < NUM_OF_74HC595; ++i) {
        shift_out_single(sr_zero);
    }
    writePinHigh(SPI_74HC595_CS);
}

static void unselect_cols(void) {
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinInputLow(col_pins[x]);
    }
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
    for (i = 0; i < MATRIX_ROWS; ++i) {
        if (row_pins[i] != NO_PIN) {
            setPinOutput(row_pins[i]);
        }
    }
#   endif
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
        // Populate the matrix row with the state of the col pin
        current_row_value |= readPin(col_pins[col_index]) ? (MATRIX_ROW_SHIFTER << col_index) : 0;
    }

    // Unselect row
    unselect_rows();
    matrix_output_unselect_delay(current_row, current_row_value != 1);  // wait for all Col signals to go HIGH


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
    // initialize key pins
    init_pins();
}

uint8_t matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

#if defined(DIRECT_PINS) || (DIODE_DIRECTION == COL2ROW)
    // Set col, read rows
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        changed |= read_rows_on_col(current_matrix, current_col);
    }
#elif (DIODE_DIRECTION == ROW2COL)
    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        changed |= read_cols_on_row(current_matrix, current_row);
    }
#endif

    return (uint8_t)changed;
}
