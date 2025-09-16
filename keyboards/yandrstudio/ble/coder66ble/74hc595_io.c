#include "74hc595.h"
#include "matrix.h"
#include "gpio.h"
#include "wait.h"

#ifdef DIRECT_PINS
#    error invalid DIRECT_PINS for 74hc595 matrix
#elif (DIODE_DIRECTION == ROW2COL)
#   ifdef USE_BOTH_595_AND_GPIO
extern const pin_t row_pins[MATRIX_ROWS];
#   endif
extern const pin_t col_pins[MATRIX_COLS];
extern const uint8_t mask_of_each_595[NUM_OF_74HC595][MATRIX_ROWS];
#elif (DIODE_DIRECTION == COL2ROW)
#   ifdef USE_BOTH_595_AND_GPIO
extern const pin_t col_pins[MATRIX_COLS];
#   endif
extern const pin_t row_pins[MATRIX_ROWS];
extern const uint8_t mask_of_each_595[NUM_OF_74HC595][MATRIX_COLS];
#else
#   error DIODE_DIRECTION must be defined
#endif


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


#if (DIODE_DIRECTION == COL2ROW)
void select_cols_595(void) {
    uint8_t i = 0;
#   ifdef USE_BOTH_595_AND_GPIO
    for (i = 0; i < MATRIX_COLS; ++i) {
        if (col_pins[i] != NO_PIN) {
            writePinHigh(col_pins[i]);
        }
    }
#   endif
    writePinLow(SPI_74HC595_CS);
    for (i = 0; i < NUM_OF_74HC595; ++i) {
        shift_out_single(SR_74HC595_ONES_ONEP);
    }
    writePinHigh(SPI_74HC595_CS);
}
void unselect_cols_595(void) {
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
        shift_out_single(SR_74HC595_ZERO_ONEP);
    }
    writePinHigh(SPI_74HC595_CS);
}
#else
void select_rows_595(void) {
    uint8_t i = 0;
#   ifdef USE_BOTH_595_AND_GPIO
    for (i = 0; i < MATRIX_ROWS; ++i) {
        if (row_pins[i] != NO_PIN) {
            writePinHigh(row_pins[i]);
        }
    }
#   endif
    writePinLow(SPI_74HC595_CS);
    for (i = 0; i < NUM_OF_74HC595; ++i) {
        shift_out_single(SR_74HC595_ONES_ONEP);
    }
    writePinHigh(SPI_74HC595_CS);
}
void unselect_rows_595(void) {
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
        shift_out_single(SR_74HC595_ZERO_ONEP);
    }
    writePinHigh(SPI_74HC595_CS);
}
#endif
