// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdint.h>
#include <stdbool.h>
#include "util.h"
#include "matrix.h"
#include "quantum.h"
#    include "split_common/split_util.h"
#    include "split_common/transactions.h"

#define ROWS_PER_HAND_ (MATRIX_ROWS / 2)

static  pin_t row_pins[ROWS_PER_HAND_] = MATRIX_ROW_PINS;
static  pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;


static void select_col(uint8_t col) { writePinHigh(col_pins[col]); }

static void unselect_col(uint8_t col) { writePinLow(col_pins[col]); }

static void unselect_rows(void) {
    for (uint8_t x = 0; x < ROWS_PER_HAND_; x++) {
        setPinInputLow(row_pins[x]);
    }
}

static void init_pins(void) {
    unselect_rows();
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinOutput(col_pins[x]);
        writePinLow(col_pins[x]);
    }
}
static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    bool matrix_changed = false;

    // Select col
    select_col(current_col);
    matrix_output_select_delay();

    // For each row...
    for (uint8_t row_index = 0; row_index < ROWS_PER_HAND_; row_index++) {
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
            matrix_changed = true;
            current_matrix[row_index] = current_row_value;
        }
    }

    // Unselect col
    unselect_col(current_col);
    matrix_output_unselect_delay(current_col, matrix_changed);  // wait for all Row signals to go HIGH


    return matrix_changed;
}

void matrix_init_custom(void) {
    // init pins based on hand
    if (!isLeftHand) {
        const pin_t row_pins_right[ROWS_PER_HAND_] = MATRIX_ROW_PINS_RIGHT;
        for (uint8_t i = 0; i < ROWS_PER_HAND_; i++) {
            row_pins[i] = row_pins_right[i];
        }
        const pin_t col_pins_right[MATRIX_COLS] = MATRIX_COL_PINS_RIGHT;
        for (uint8_t i = 0; i < MATRIX_COLS; i++) {
            col_pins[i] = col_pins_right[i];
        }
    }
    // initialize key pins
    init_pins();
}
extern bool force_change_matrix;
uint8_t matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;
    // Set col, read rows
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        changed |= read_rows_on_col(current_matrix, current_col);
    }
    return (uint8_t)changed;
}
