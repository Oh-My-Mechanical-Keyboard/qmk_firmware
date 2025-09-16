/* Copyright 2023 JasonRen(biu)
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
#include <string.h>
#include "util.h"
#include "matrix.h"
#include "wait.h"
#include "quantum.h"
#include "gpio.h"
#include "analog.h"

const pin_t mux_adc_pins[NUM_OF_MUX] = MUX_OUT_PIN2MCU;
const uint8_t mux2matrix_dict[8][NUM_OF_MUX][2] = MUX_ADDR_TO_MX;

struct mag_key_t {
    uint16_t last_adc; // 上次扫描值ADC
} mag_keys[MATRIX_ROWS][MATRIX_COLS];


static uint32_t get_curr_adc_val(uint8_t current_mux, uint8_t current_addr) {
    return analogReadPin(mux_adc_pins[current_mux]);
}

uint16_t get_adc_my(uint8_t r, uint8_t c) {
    return mag_keys[r][c].last_adc;
}

static uint32_t adc_debug_timer = 0;
void debug_for_adc(void) {
    uint32_t timer_now = timer_read32();
    if (TIMER_DIFF_32(timer_now, adc_debug_timer) >= 1000) {
        dprintf("==========RFV12:%d=============\n", adc_read(TO_MUX(17,1)));
        dprintf("     ");
        for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
            dprintf("C%2d  ", current_col+1);
        }
        dprintf("\n");
        for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
            dprintf("R%d: ", current_row+1);
            for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
                dprintf("%4d ", mag_keys[current_row][current_col].last_adc);
            }
            dprintf("\n");
        }
        adc_debug_timer = timer_now;
    }
}

inline void update_key_state(uint8_t current_row, uint8_t current_col, uint16_t adc_val) {
    mag_keys[current_row][current_col].last_adc = adc_val;
}



static bool read_matrix(matrix_row_t current_matrix[], uint8_t current_row, uint8_t current_col, uint8_t current_mux, uint8_t current_addr) {
    bool matrix_changed = false;

    // 多次采样取平均值
    mag_keys[current_row][current_col].last_adc = get_curr_adc_val(current_mux, current_addr);
    // wait_ms(1);
    debug_for_adc();
    matrix_row_t last_row_value = current_matrix[current_row];

    matrix_row_t current_row_value = last_row_value;
    if (mag_keys[current_row][current_col].last_adc <= 2000) {
        current_row_value |= (MATRIX_ROW_SHIFTER << current_col);
    } else {
        current_row_value &= ~(MATRIX_ROW_SHIFTER << current_col);
    }
    // 防止按键调试乱触发
    // Determine if the matrix changed state
    if ((last_row_value != current_row_value)) {
        matrix_changed |= true;
        current_matrix[current_row] = current_row_value;
    }
    return matrix_changed;
}


void set_sk_args(void) {
    // 先设置矩阵
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
            mag_keys[current_row][current_col].last_adc = 4096;
        }
    }
}

void matrix_init_custom(void) {
    // initialize key pins
    analogReadPin(C0);
    analogReadPin(C1);
    analogReadPin(C2);
    analogReadPin(C3);
    analogReadPin(A0);
    analogReadPin(A1);
    analogReadPin(A2);
    analogReadPin(A4);
    analogReadPin(A5);
    analogReadPin(A6);

    analogReadPin(B0);
    analogReadPin(B1);

    gpio_set_pin_output(MUX_ADD_PIN0);
    gpio_set_pin_output(MUX_ADD_PIN1);
    gpio_set_pin_output(MUX_ADD_PIN2);
    writePin(MUX_ADD_PIN0, 1);
    writePin(MUX_ADD_PIN1, 1);
    writePin(MUX_ADD_PIN2, 0);
}


static inline void set_mux_addr(uint8_t addr) {
    writePin(MUX_ADD_PIN0, addr & 1);
    writePin(MUX_ADD_PIN1, addr & 2);
    writePin(MUX_ADD_PIN2, addr & 4);
}

uint8_t matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;
    // Set addr, scan key
    uint8_t current_col = 0;
    uint8_t current_row = 0;
    adc_read(TO_MUX(ADC_CHANNEL_VREFINT, 0));
    adc_read(TO_MUX(ADC_CHANNEL_VREFINT, 0));
    adc_read(TO_MUX(ADC_CHANNEL_VREFINT, 0));
    for (uint8_t current_addr = 0; current_addr < 8; ++current_addr) {
        set_mux_addr(current_addr);
        for (uint8_t current_mux = 0; current_mux < NUM_OF_MUX; ++current_mux) {
            current_row = mux2matrix_dict[current_addr][current_mux][0];
            current_col = mux2matrix_dict[current_addr][current_mux][1];
            if (current_row >= MATRIX_ROWS || current_col >= MATRIX_COLS) continue;
            // 计算当前按键行程参数
            changed |= read_matrix(current_matrix, current_row, current_col, current_mux, current_addr);
        }
    }
    return (uint8_t)changed;
}
