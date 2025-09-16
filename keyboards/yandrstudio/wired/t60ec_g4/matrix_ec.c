/* Copyright 2024 JasonRen(biu)
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
#include "my_adc_drv.h"

struct ec_key_t {
    uint16_t adc_min;
    uint16_t adc_max;
    uint16_t adc_diff;
    uint16_t diff_idx;
    uint16_t adc_value;
    uint16_t lv_value;
} ec_keys[MATRIX_ROWS][MATRIX_COLS];


// pin connections
const uint32_t row_pins[]     = MATRIX_ROW_PINS;
const uint8_t  col_channels[] = MATRIX_COL_CHANNELS;
const uint32_t mux_sel_pins[] = MUX_SEL_PINS;

static bool matrix_no_point[MATRIX_ROWS][MATRIX_COLS] = MS_MX_MASK;

static inline void discharge_capacitor(void) {
    setPinOutput(DISCHARGE_PIN);
    writePinLow(DISCHARGE_PIN);
}
static inline void charge_capacitor(uint8_t row) {
    setPinInput(DISCHARGE_PIN); // Z state
    // charge select row
    writePinHigh(row_pins[row]);
}

static inline void clear_row_pin(uint8_t row) {
    writePinLow(row_pins[row]);
}

static inline void select_mux(uint8_t col) {
    uint8_t ch = col_channels[col];
    writePin(mux_sel_pins[0], ch & 1);
    writePin(mux_sel_pins[1], ch & 2);
    writePin(mux_sel_pins[2], ch & 4);
}

static uint16_t ecsm_readkey_raw(uint8_t row, uint8_t col) {
    uint16_t sw_value = 0;

    charge_capacitor(row); // 拉高这一行, 给这一行的电容充电
    // 理论上这里要等下等待充电完成
    analogStart_my(); // 开启ADC转换
    sw_value = analogReadPin_my(row, col); // 获取ADC的读数

    discharge_capacitor();
    clear_row_pin(row);
    wait_us(5); // 5*1nf*1k = 5us
    return sw_value;
}

// Update press/release state of key at (row, col)
static bool ecsm_update_key(matrix_row_t* current_row, uint8_t row, uint8_t col) {
    bool current_state = (*current_row >> col) & 1;


    uint32_t diff_idx = 0;
    uint32_t scal_10 = 2048;

    if (ec_keys[row][col].adc_max > ec_keys[row][col].adc_min + 1000) {
        scal_10 = (2048<<11) / (ec_keys[row][col].adc_max - ec_keys[row][col].adc_min); // avoid float
    } else {
        scal_10 = 2048;
    }

    diff_idx = (scal_10 * (ec_keys[row][col].adc_value - ec_keys[row][col].adc_min))>>11;

    if (diff_idx > 2049 - 1) {
        diff_idx = 2048;
    }
    ec_keys[row][col].diff_idx = diff_idx;

    bool change = false;

    // press to release
    if (current_state && diff_idx < 600) {
        *current_row &= ~(1 << col);
        change = true;
    }

    // 中间带不管

    // release to press
    if ((!current_state) && diff_idx > 1024) {
        *current_row |= (1 << col);
        change = true;
    }

    if (change) {
        printf("%d,%d: %ld\n", row, col, diff_idx);
    }

    return change;
}

// Scan key values and update matrix state
bool ecsm_matrix_scan(matrix_row_t current_matrix[]) {
    bool updated = false;

    discharge_capacitor();
    wait_us(16);
    for (int col = 0; col < MATRIX_COLS; col++) {
        select_mux(col);

        if (col < 7) {
            writePinLow(APLEX_EN_PIN_0);
        } else {
            writePinLow(APLEX_EN_PIN_1);
        }

        for (int row = 0; row < MATRIX_ROWS; row++) {
            if (matrix_no_point[row][col] == 0) continue;
            ec_keys[row][col].adc_value = ecsm_readkey_raw(row, col);
            ec_keys[row][col].adc_min = MIN(ec_keys[row][col].adc_min,  ec_keys[row][col].adc_value);
            ec_keys[row][col].adc_max = MAX(ec_keys[row][col].adc_max,  ec_keys[row][col].adc_value);
            ec_keys[row][col].adc_diff = ec_keys[row][col].adc_max - ec_keys[row][col].adc_min;
            updated |= ecsm_update_key(&current_matrix[row], row, col);
        }
        writePinHigh(APLEX_EN_PIN_1);
        writePinHigh(APLEX_EN_PIN_0);
    }
    return updated;
}

// Debug print key values
void ecsm_print_matrix(void) {
    print("ADC VAL\n");
    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < MATRIX_COLS; col++) {
            uprintf("%4d:%4d", ec_keys[row][col].adc_value, ec_keys[row][col].diff_idx);
            // uprintf("%4d:%4d:%4d:%4d", ec_keys[row][col].adc_max, ec_keys[row][col].adc_min, ec_keys[row][col].adc_diff, ec_keys[row][col].adc_value);
            if (col < MATRIX_COLS - 1) {
                print(",");
            }
        }
        print("\n");
    }
    print("\n");
}

uint32_t scan_timer = 0;
bool scan_enable = 0;

void matrix_init_custom(void) {

    // initialize discharge pin as discharge mode
    setPinOutput(DISCHARGE_PIN);
    writePinLow(DISCHARGE_PIN);

    for (int idx = 0; idx < MATRIX_ROWS; idx++) {
        setPinOutput(row_pins[idx]);
        writePinLow(row_pins[idx]);
    }

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

    scan_timer = timer_read32();
    scan_enable = false;
}

void reinit_ec_mx(void) {
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        for (uint8_t c = 0; c < MATRIX_COLS; c++)
        {
            ec_keys[r][c].adc_min = 4096;
            ec_keys[r][c].adc_max = 0;
            ec_keys[r][c].adc_value = 0;
            ec_keys[r][c].lv_value = 0;
        }
    }
}

void ecsm_matrix_scan_dummy(void) {
    discharge_capacitor();
    wait_us(20); // 把电放完
    for (int col = 0; col < MATRIX_COLS; col++) {
        select_mux(col);

        if (col < 7) {
            writePinLow(APLEX_EN_PIN_0);
        } else {
            writePinLow(APLEX_EN_PIN_1);
        }

        for (int row = 0; row < MATRIX_ROWS; row++) {
            if (matrix_no_point[row][col] == 0) continue;
            ecsm_readkey_raw(row, col);
        }
        writePinHigh(APLEX_EN_PIN_1);
        writePinHigh(APLEX_EN_PIN_0);
    }
}

uint8_t matrix_scan_custom(matrix_row_t current_matrix[]) {
    if (!scan_enable) { // 500ms后开始扫描
        ecsm_matrix_scan_dummy();
        if (timer_elapsed32(scan_timer) >= 1500) {
            scan_enable = true;
            reinit_ec_mx();
        }
        return false;
    }
    if (timer_elapsed32(scan_timer) >= 500) {
        scan_timer  = timer_read32();
#ifdef CONSOLE_ENABLE
        ecsm_print_matrix();
#endif
    }

    bool updated = ecsm_matrix_scan(current_matrix);
    if (updated) {
        dprintf("MATRIX\n");
    }
    return (uint8_t)updated;
}