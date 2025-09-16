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
#include "my_adc_drv.h"

#define WAIT_DISCHARGE()
#define WAIT_CHARGE()

// pin connections
const uint32_t row_pins[]     = MATRIX_ROW_PINS;
const uint8_t  col_channels[] = MATRIX_COL_CHANNELS;
const uint32_t mux_sel_pins[] = MUX_SEL_PINS;

static bool auto_fine_f = false;

static bool matrix_no_point[MATRIX_ROWS][MATRIX_COLS] = MS_MX_MASK;

static uint16_t ecsm_sw_init_top_value[MATRIX_ROWS][MATRIX_COLS] = {
    {207, 301, 252, 234, 172, 463, 213, 416, 251,  98, 212, 239, 273, 146, 256},
    {228, 282, 249, 312, 326, 311, 284, 305, 349, 272, 263, 349, 219, 290, 252},
    {178, 195, 269, 303, 248, 271, 730, 340, 201, 183, 219, 274, 252,   0, 185},
    {265,   0, 225, 293, 238, 287, 299, 301, 236, 223, 166, 287, 368, 270, 226},
    {170, 265, 177,   0,   0,   0, 260,   0,   0,   0, 264, 228,1501, 614, 242}
};


static uint16_t ecsm_sw_top_value[MATRIX_ROWS][MATRIX_COLS] = {
    {207, 301, 252, 234, 172, 463, 213, 416, 251,  98, 212, 239, 273, 146, 256},
    {228, 282, 249, 312, 326, 311, 284, 305, 349, 272, 263, 349, 219, 290, 252},
    {178, 195, 269, 303, 248, 271, 730, 340, 201, 183, 219, 274, 252,   0, 185},
    {265,   0, 225, 293, 238, 287, 299, 301, 236, 223, 166, 287, 368, 270, 226},
    {170, 265, 177,   0,   0,   0, 260,   0,   0,   0, 264, 228,1501, 614, 242}
};

static uint16_t ecsm_sw_init_bottom_value[MATRIX_ROWS][MATRIX_COLS] = {
    {1407, 1501, 1452, 1434, 1372, 1663, 1413, 1616, 1451, 1298, 1412, 1439, 1473, 1346, 1456},
    {1428, 1482, 1449, 1512, 1526, 1511, 1484, 1505, 1549, 1472, 1463, 1549, 1419, 1490, 1452},
    {1378, 1395, 1469, 1503, 1448, 1471, 1930, 1540, 1401, 1383, 1419, 1474, 1452, 1200, 1385},
    {1465, 1200, 1425, 1493, 1438, 1487, 1499, 1501, 1436, 1423, 1366, 1487, 1568, 1470, 1426},
    {1370, 1465, 1377, 1200, 1200, 1200, 1460, 1200, 1200, 1200, 1464, 1428, 2701, 1814, 1442}
};

static uint16_t ecsm_sw_bottom_value[MATRIX_ROWS][MATRIX_COLS] = {
    {1407, 1501, 1452, 1434, 1372, 1663, 1413, 1616, 1451, 1298, 1412, 1439, 1473, 1346, 1456},
    {1428, 1482, 1449, 1512, 1526, 1511, 1484, 1505, 1549, 1472, 1463, 1549, 1419, 1490, 1452},
    {1378, 1395, 1469, 1503, 1448, 1471, 1930, 1540, 1401, 1383, 1419, 1474, 1452, 1200, 1385},
    {1465, 1200, 1425, 1493, 1438, 1487, 1499, 1501, 1436, 1423, 1366, 1487, 1568, 1470, 1426},
    {1370, 1465, 1377, 1200, 1200, 1200, 1460, 1200, 1200, 1200, 1464, 1428, 2701, 1814, 1442}
};

static uint16_t ecsm_sw_value[MATRIX_ROWS][MATRIX_COLS];

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
    // for (int row = 0; row < MATRIX_ROWS; row++) {
        writePinLow(row_pins[row]);
    // }
}

static inline void select_mux(uint8_t col) {
    uint8_t ch = col_channels[col];
    writePin(mux_sel_pins[0], ch & 1);
    writePin(mux_sel_pins[1], ch & 2);
    writePin(mux_sel_pins[2], ch & 4);
}

static uint16_t ecsm_readkey_raw(uint8_t row, uint8_t col) {
    uint16_t sw_value = 0;

    charge_capacitor(row);

    sw_value = analogReadPin_my(ADC_READ_PIN);

    discharge_capacitor();
    clear_row_pin(row);
    wait_us(15); // 5*1nf*1k = 5us
    return sw_value;
}

// Update press/release state of key at (row, col)
static bool ecsm_update_key(matrix_row_t* current_row, uint8_t row, uint8_t col, uint16_t sw_value) {
    bool current_state = (*current_row >> col) & 1;

    // press to release

    uint16_t up_th = 400;
    uint16_t down_th = 800;

    if (ecsm_sw_bottom_value[row][col] > ecsm_sw_top_value[row][col] + 1000) {
        up_th = (ecsm_sw_bottom_value[row][col] - ecsm_sw_top_value[row][col]) / 3;
        down_th = up_th*2;
    }

    if (current_state && sw_value < ecsm_sw_top_value[row][col]+up_th) {
        *current_row &= ~(1 << col);
        return true;
    }

    // release to press
    if ((!current_state) && sw_value > ecsm_sw_top_value[row][col]+down_th) {
        *current_row |= (1 << col);
        return true;
    }

    return false;
}

void auto_fine_sw_th(uint8_t row, uint8_t col) {
    // 是否是顶部值范围
    if (ecsm_sw_value[row][col] < ecsm_sw_init_top_value[row][col]+400 && ecsm_sw_value[row][col] + 400 > ecsm_sw_init_top_value[row][col]) {
        ecsm_sw_top_value[row][col] = MIN(ecsm_sw_top_value[row][col], ecsm_sw_value[row][col]);
        return;
    }
    if (ecsm_sw_value[row][col] < ecsm_sw_init_bottom_value[row][col]+400 && ecsm_sw_value[row][col] + 400 > ecsm_sw_init_bottom_value[row][col]) {
        ecsm_sw_bottom_value[row][col] = MAX(ecsm_sw_bottom_value[row][col], ecsm_sw_value[row][col]);
        return;
    }
}

// Scan key values and update matrix state
bool ecsm_matrix_scan(matrix_row_t current_matrix[]) {
    bool updated = false;

    discharge_capacitor();
    wait_us(100);
    for (int col = 0; col < MATRIX_COLS; col++) {
        select_mux(col);

        if (col < 7) {
            writePinLow(APLEX_EN_PIN_0);
        } else {
            writePinLow(APLEX_EN_PIN_1);
        }

        for (int row = 0; row < MATRIX_ROWS; row++) {
            if (matrix_no_point[row][col] == 0) continue;
            ecsm_sw_value[row][col] = ecsm_readkey_raw(row, col);
            if (auto_fine_f) {
                auto_fine_sw_th(row, col);
            }
            updated |= ecsm_update_key(&current_matrix[row], row, col, ecsm_sw_value[row][col]);
        }
        writePinHigh(APLEX_EN_PIN_1);
        writePinHigh(APLEX_EN_PIN_0);
    }
    return updated;
}

void set_ec_top_init_val(void) {
    discharge_capacitor();
    wait_us(200);
    for (int col = 0; col < MATRIX_COLS; col++) {
        select_mux(col);

        if (col < 7) {
            writePinLow(APLEX_EN_PIN_0);
        } else {
            writePinLow(APLEX_EN_PIN_1);
        }

        for (int row = 0; row < MATRIX_ROWS; row++) {
            if (matrix_no_point[row][col] == 0) continue;
            ecsm_sw_value[row][col] = ecsm_readkey_raw(row, col);
            auto_fine_sw_th(row, col);
        }
        writePinHigh(APLEX_EN_PIN_1);
        writePinHigh(APLEX_EN_PIN_0);
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
    print("TOP\n");

    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < MATRIX_COLS; col++) {
            uprintf("%4d", ecsm_sw_top_value[row][col]);
            if (col < MATRIX_COLS-1) {
                print(",");
            }
        }
        print("\n");
    }

    print("BOTTOM\n");

    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < MATRIX_COLS; col++) {
            uprintf("%4d", ecsm_sw_bottom_value[row][col]);
            if (col < MATRIX_COLS-1) {
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

uint8_t matrix_scan_custom(matrix_row_t current_matrix[]) {
    if (!scan_enable) {
        if (timer_elapsed32(scan_timer) >= 500) {
            set_ec_top_init_val();
            scan_enable = true;
        }
        return false;
    }
    if (timer_elapsed32(scan_timer) >= 500) {
        scan_timer = timer_read32();
        auto_fine_f = true;
    }
    bool updated = ecsm_matrix_scan(current_matrix);
    auto_fine_f = false;

    // RAW matrix values on console
// #ifdef CONSOLE_ENABLE
//     static int cnt = 0;
//     if (cnt++ == 500) {
//         cnt = 0;
//         ecsm_print_matrix();
//     }
// #endif
    return (uint8_t)updated;
    // // return false;
}
