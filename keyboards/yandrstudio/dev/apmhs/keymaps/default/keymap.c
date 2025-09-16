// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-3.0-or-later
#include QMK_KEYBOARD_H
#include "debug.h"
#include "analog.h"
#include "apmhs.h"
#include "SEGGER_RTT.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,   KC_4,    KC_5,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,    KC_G,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,   KC_C,    KC_V,  KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                  KC_SPC,                           KC_RALT, MO(1),   KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT)
};


void keyboard_post_init_user(void) {

}
// static void dummy_vt_callback(virtual_timer_t *vtp, void *p) {}

uint16_t get_adc_my(uint8_t r, uint8_t c);
static uint32_t adc_debug_timer = 0;
void housekeeping_task_user(void) {
    uint32_t timer_now = timer_read32();
    if (TIMER_DIFF_32(timer_now, adc_debug_timer) >= 1000) {
        SEGGER_RTT_printf(0,"Demo Init!, V12:%d \r\n", adc_read(TO_MUX(ADC_CHANNEL_VREFINT, 0)));
        // 1487
        SEGGER_RTT_printf(0, "==========MATRIX ADC VAL, VHC:%d, VREF:%d, %d=============\n", analogReadPin(B0), adc_read(TO_MUX(ADC_CHANNEL_VREFINT, 0)), kb_cstm_config.raw[1]);
        // dprintf("     ");
        // for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        //     dprintf("C%2d  ", current_col+1);
        // }
        // dprintf("\n");
        // for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        //     dprintf("R%d: ", current_row+1);
        //     for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        //         dprintf("%4d ", get_adc_my(current_row,current_col));
        //     }
        //     dprintf("\n");
        // }
        adc_debug_timer = timer_now;
    }

    // Start a virtual timer so we'll still get periodic wakeups, now that USB SOF doesn't wake up the main loop
    // static virtual_timer_t vt;
    // chVTObjectInit(&vt);
    // chVTSetContinuous(&vt, TIME_MS2I(10), dummy_vt_callback, NULL);
}

void dummy_cb(USBDriver *usbp) {
    (void)usbp;
    rgblight_setrgb_at(0,0,100,0);
}
