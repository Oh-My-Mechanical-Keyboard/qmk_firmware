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
#include "quantum.h"
#include "analog.h"
#include "atomic_util.h"
#include "print.h"

#define WAIT_DISCHARGE()
#define WAIT_CHARGE()

// pin connections
const uint32_t row_pins[]     = MATRIX_ROW_PINS;
const uint8_t  col_channels[] = MATRIX_COL_CHANNELS;
const uint32_t mux_sel_pins[] = MUX_SEL_PINS;

static uint16_t      ecsm_sw_value[MATRIX_ROWS][MATRIX_COLS];
static uint16_t      ecsm_sw_top_value[MATRIX_ROWS][MATRIX_COLS];

static inline void discharge_capacitor(void) {
    setPinOutput(DISCHARGE_PIN);
    writePinLow(DISCHARGE_PIN);
}
static inline void charge_capacitor(uint8_t row) {
    setPinInput(DISCHARGE_PIN); // Z state
    // charge select row
    writePinHigh(row_pins[row]);
}

static inline void clear_all_row_pins(void) {
    for (int row = 0; row < MATRIX_ROWS; row++) {
        writePinLow(row_pins[row]);
    }
}

static inline void select_mux(uint8_t col) {
    if (col <= 6) {
        writePinHigh(APLEX_EN_PIN_0);
    } else {
        writePinHigh(APLEX_EN_PIN_1);
    }
    uint8_t ch = col_channels[col];
    writePin(mux_sel_pins[0], ch & 1);
    writePin(mux_sel_pins[1], ch & 2);
    writePin(mux_sel_pins[2], ch & 4);
    if (col <= 6) {
        writePinLow(APLEX_EN_PIN_0);
    } else {
        writePinLow(APLEX_EN_PIN_1);
    }
}

static inline void init_row(void) {
    for (int idx = 0; idx < MATRIX_ROWS; idx++) {
        setPinOutput(row_pins[idx]);
        writePinLow(row_pins[idx]);
    }
}

static uint16_t ecsm_readkey_raw(uint8_t row, uint8_t col) {
    uint16_t sw_value = 0;
    discharge_capacitor();
    select_mux(col);
    clear_all_row_pins();
    wait_us(20); // 5*1nf*1k = 5us

    charge_capacitor(row); // 5*100K*10pf = 5us
    wait_us(5);
    sw_value = analogReadPin(ADC_READ_PIN);


    return sw_value;
}

// Update press/release state of key at (row, col)
static bool ecsm_update_key(matrix_row_t* current_row, uint8_t row, uint8_t col, uint16_t sw_value) {
    bool current_state = (*current_row >> col) & 1;

    // press to release
    // if (current_state && sw_value < config.low_threshold_matrix[row][col]) {
    if (current_state && sw_value < ecsm_sw_top_value[row][col]+100) {
        *current_row &= ~(1 << col);
        return true;
    }

    // release to press
    // if ((!current_state) && sw_value > config.high_threshold_matrix[row][col]) {
    if ((!current_state) && sw_value > ecsm_sw_top_value[row][col]+200) {
        *current_row |= (1 << col);
        return true;
    }

    return false;
}

// Scan key values and update matrix state
bool ecsm_matrix_scan(matrix_row_t current_matrix[]) {
    bool updated = false;

    writePinHigh(APLEX_EN_PIN_1);
    for (int col = 0; col <= 6; col++) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            ecsm_sw_value[row][col] = ecsm_readkey_raw(row, col);
            updated |= ecsm_update_key(&current_matrix[row], row, col, ecsm_sw_value[row][col]);
        }
    }

    writePinHigh(APLEX_EN_PIN_0);
    for (int col = 7; col < MATRIX_COLS; col++) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            ecsm_sw_value[row][col] = ecsm_readkey_raw(row, col);
            updated |= ecsm_update_key(&current_matrix[row], row, col, ecsm_sw_value[row][col]);
        }
    }
    return updated;
}

void set_ec_top_init_val(void) {
    writePinHigh(APLEX_EN_PIN_1);
    for (int col = 0; col <= 6; col++) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            ecsm_sw_top_value[row][col] = ecsm_readkey_raw(row, col);
            if (ecsm_sw_top_value[row][col] <= 0 || ecsm_sw_top_value[row][col] >= 600) {
                ecsm_sw_top_value[row][col] = 600;
            }
        }
    }

    writePinHigh(APLEX_EN_PIN_0);
    for (int col = 7; col < MATRIX_COLS; col++) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            ecsm_sw_top_value[row][col] = ecsm_readkey_raw(row, col);
            if (ecsm_sw_top_value[row][col] <= 0 || ecsm_sw_top_value[row][col] >= 600) {
                ecsm_sw_top_value[row][col] = 600;
            }
        }
    }
}

// Debug print key values
void ecsm_print_matrix(void) {
    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < MATRIX_COLS; col++) {
            uprintf("%4d", ecsm_sw_value[row][col]);
            if (col < MATRIX_COLS-1) {
                print(",");
            }
        }
        print("\n");
    }
    print("\n");
}

void matrix_init_custom(void) {

    // initialize discharge pin as discharge mode
    setPinOutput(DISCHARGE_PIN);
    writePinLow(DISCHARGE_PIN);

    // initialize key pins
    // initialize drive lines
    init_row();

    // initialize multiplexer select pin
    for (int idx = 0; idx < 3; idx++) {
        setPinOutput(mux_sel_pins[idx]);
        writePinLow(mux_sel_pins[idx]);
    }

    // Disnable AMUX
    setPinOutput(APLEX_EN_PIN_0);
    writePinHigh(APLEX_EN_PIN_0);
    setPinOutput(APLEX_EN_PIN_1);
    writePinHigh(APLEX_EN_PIN_1);
    
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        for (uint8_t j = 0; j < MATRIX_COLS; j++) {
            ecsm_sw_top_value[i][j] = 1024;
        }
    }
}

uint8_t matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool updated = ecsm_matrix_scan(current_matrix);
    // RAW matrix values on console
#ifdef CONSOLE_ENABLE
    static int cnt = 0;
    if (cnt++ == 100) {
        cnt = 0;
        ecsm_print_matrix();
    }
#endif
    return (uint8_t)updated;
    // return false;
}
