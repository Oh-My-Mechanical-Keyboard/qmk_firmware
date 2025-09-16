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
#include "spi_master.h"

const uint8_t mask_of_each_595[MATRIX_ROWS-1][MATRIX_COLS][2] = MATRIX_OF_74HC595;


const uint8_t sr_zero = SR_74HC595_ZERO_ONEP;

static void select_col_aux(uint8_t col_595_i, uint8_t val_595) {
    spi_start(SPI_74HC595_CS, true, 0, 4);
    for (uint8_t i = 0; i < NUM_OF_74HC595; ++i) {
        if (i == col_595_i) {
            spi_write(val_595);
        } else {
            spi_write(sr_zero);
        }
    }
    spi_stop();
}

static void select_key(uint8_t row, uint8_t col) {
    row -= 1;
    select_col_aux(mask_of_each_595[row][col][0], mask_of_each_595[row][col][1]);
}

static void unselect_cols(void) {
    uint8_t i = 0;

    spi_start(SPI_74HC595_CS, true, 0, 4);
    for (i = 0; i < NUM_OF_74HC595; ++i) {
        spi_write(sr_zero);
    }
    spi_stop();

    writePinLow(EC_COL_PIN);
}


static void init_pins(void) {

    setPinOutput(EC_COL_PIN);

    setPinInputLow(ROW_AUX_READ_PIN);
    
    unselect_cols();
}

static bool read_matrix(matrix_row_t current_matrix[], uint8_t current_row, uint8_t current_col) {
    bool matrix_changed = false;
    matrix_row_t last_row_value    = current_matrix[current_row];
    matrix_row_t current_row_value = last_row_value;

    if (current_row == 0) {
        writePinHigh(EC_COL_PIN);
        matrix_output_select_delay();
        if (readPin(ROW_AUX_READ_PIN) == 1) {
            current_row_value |= (MATRIX_ROW_SHIFTER << current_col);
        } else {
            current_row_value &= ~(MATRIX_ROW_SHIFTER << current_col);
        }
    } else {
        // Select col
        select_key(current_row, current_col);
        matrix_output_select_delay();
        if (readPin(ROW_AUX_READ_PIN) == 1) {
            current_row_value |= (MATRIX_ROW_SHIFTER << current_col);
        } else {
            current_row_value &= ~(MATRIX_ROW_SHIFTER << current_col);
        }
    }

    // Determine if the matrix changed state
    if ((last_row_value != current_row_value)) {
        matrix_changed |= true;
        current_matrix[current_row] = current_row_value;
    }

    // Unselect col
    unselect_cols();
    matrix_output_unselect_delay(current_col, matrix_changed);  // wait for all Row signals to go HIGH
    return matrix_changed;
}

void matrix_init_custom(void) {
    // initialize key pins
    init_pins();
    spi_init();
}

uint8_t matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    // Set col, read rows
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
            changed |= read_matrix(current_matrix, current_row, current_col);
        }
    }
    return (uint8_t)changed;
}
