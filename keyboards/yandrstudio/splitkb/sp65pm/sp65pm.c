// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later]

#include "sp65pm.h"
#include "print.h"

void uart_init(void) {
    SERIAL_UART_INIT();
}

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    matrix_init_user();
    uart_init();
}
void matrix_scan_kb(void) {
    // put your looping keyboard code here
    // runs every cycle (a lot)
    matrix_scan_user();
}

extern uint16_t adc_val;
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) { return false; }

    if (record->event.pressed) {
        uprintf("adc %d\n", adc_val);
    }
    return true;
}