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
#include QMK_KEYBOARD_H

#include "outputselect.h"
#include "biu_ble_common.h"
#include "distributors.h"
#include "usb_main.h"


enum keyboard_keycodes {
    BLE_TOG_EXT = SAFE_RANGE, // ble
    USB_TOG_EXT,              // usb
    BAU_TOG_EXT,              // if ble then usb, if usb then ble
    BL_SW_0_EXT,              // ble id 0
    BL_SW_1_EXT,
    BL_SW_2_EXT,
    BL_SW_3_EXT,
    BL_SW_4_EXT,
    BL_SW_5_EXT,
    BL_SW_6_EXT,
    BL_SW_7_EXT,
    BLE_DEL_EXT,              // delete current ble bound
    BLE_CLR_EXT,              // delete all ble bound
    BLE_OFF_EXT,          // power off
    NEW_SAFE_RANGE  // Important!
};

#define BLE_TOG     KC_F15  // 打开蓝牙
#define USB_TOG     KC_F16  // 打开USB
#define BAU_TOG     KC_F17  // 蓝牙和USB之间切换
#define BL_SW_0     KC_F18  // 开启蓝牙通道0（需要打开蓝牙的条件下才行）
#define BL_SW_1     KC_F19  // 开启蓝牙通道1（需要打开蓝牙的条件下才行）
#define BL_SW_2     KC_F20  // 开启蓝牙通道2（需要打开蓝牙的条件下才行）
#define BL_SW_3     KC_F21  // 开启蓝牙通道3（需要打开蓝牙的条件下才行）
#define BLE_DEL     KC_F22  // 删除当前蓝牙绑定
#define BLE_CLR     KC_F23  // 清空所有蓝牙绑定
#define BLE_OFF     KC_F24  // 关闭蓝牙连接


#ifdef TAP_DANCE_ENABLE
// Tap Dance declarations
enum {
    TD_FN_BLE_TOG,
    TD_FN_USB_TOG,
    TD_FN_BAU_TOG,
    TD_FN_BLE_SW_0,
    TD_FN_BLE_SW_1,
    TD_FN_BLE_SW_2,
    TD_FN_BLE_SW_3,
    TD_FN_BLE_DEL,
    TD_FN_BLE_CLR,
    TD_FN_BLE_OFF
};

typedef struct {
    uint16_t kc;
} qk_kc;


void dance_tab_ble_on_finished(tap_dance_state_t *state, void *user_data) {
    if (!state->pressed || state->interrupted) return;
    qk_kc * p_keycode = (qk_kc *)user_data;
    uint16_t keycode = p_keycode->kc;
    switch (keycode)
    {
        case BLE_TOG:
            switch_output_driver(0);
            break;
        case USB_TOG:
            switch_output_driver(1);
            break;
        case BAU_TOG:
            if (where_to_send() == OUTPUT_USB) {
                switch_output_driver(0);
            } else {
                switch_output_driver(1);
            }
            break;
        case BL_SW_0:
        case BL_SW_1:
        case BL_SW_2:
        case BL_SW_3:
            if (where_to_send() == OUTPUT_BLUETOOTH) {
                bluetooth_switch_one(keycode - BL_SW_0);
            }
            break;
        case BLE_DEL:
            if (where_to_send() == OUTPUT_BLUETOOTH) {
                bluetooth_unpair_current();
            }
            break;
        case BLE_CLR:
            if (where_to_send() == OUTPUT_BLUETOOTH) {
                bluetooth_unpair_all();
            }
            break;
        case BLE_OFF:
            stop_one_lilnk(0);
            break;
        default:
            break;
    }
}


#define ACTION_TAP_DANCE_FN_ADVANCED_BLE(kc, user_fn_on_dance_finished) \
        { .fn = {NULL, user_fn_on_dance_finished, NULL}, .user_data = (void *)&(qk_kc){kc}, }

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_FN_BLE_TOG] = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BLE_TOG, dance_tab_ble_on_finished),
    [TD_FN_USB_TOG] = ACTION_TAP_DANCE_FN_ADVANCED_BLE(USB_TOG, dance_tab_ble_on_finished),
    [TD_FN_BAU_TOG] = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BAU_TOG, dance_tab_ble_on_finished),
    [TD_FN_BLE_SW_0] = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BL_SW_0, dance_tab_ble_on_finished),
    [TD_FN_BLE_SW_1] = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BL_SW_1, dance_tab_ble_on_finished),
    [TD_FN_BLE_SW_2] = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BL_SW_2, dance_tab_ble_on_finished),
    [TD_FN_BLE_SW_3] = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BL_SW_3, dance_tab_ble_on_finished),
    [TD_FN_BLE_DEL] = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BLE_DEL, dance_tab_ble_on_finished),
    [TD_FN_BLE_CLR] = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BLE_CLR, dance_tab_ble_on_finished),
    [TD_FN_BLE_OFF] = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BLE_OFF, dance_tab_ble_on_finished),
};


uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_FN_BLE_TOG):
        case TD(TD_FN_USB_TOG):
        case TD(TD_FN_BAU_TOG):
            return 500;
        case TD(TD_FN_BLE_SW_0):
        case TD(TD_FN_BLE_SW_1):
        case TD(TD_FN_BLE_SW_2):
        case TD(TD_FN_BLE_SW_3):
            return  500;
        case TD(TD_FN_BLE_DEL):
        case TD(TD_FN_BLE_CLR):
        case TD(TD_FN_BLE_OFF):
            return 2000;
        default:
            return TAPPING_TERM;
    }
}

#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        // 0     1       2        3       4      5         6              7       8        9        10       11       12
	LAYOUT(
		KC_ESC,  KC_Q,   KC_W,    KC_E,   KC_R,  KC_T,     KC_Y,          KC_U,   KC_I,    KC_O,    KC_P,    KC_PGUP, KC_BSPC,
		KC_CAPS, KC_A,   KC_S,    KC_D,   KC_F,  KC_G,     KC_H,          KC_J,   KC_K,    KC_L,    KC_ENT,  KC_INS,
		KC_LSFT, KC_Z,   KC_X,    KC_C,   KC_V,  KC_B,     KC_N,          KC_M,   KC_COMM, KC_RSFT, KC_UP,   KC_DEL,
		KC_LCTL, KC_LGUI,KC_LALT, KC_SPC,                  LT(1, KC_SPC),         MO(2),   KC_LEFT, KC_DOWN, KC_RGHT),
	LAYOUT(
		KC_GRV,  KC_1,   KC_2,    KC_3,   KC_4,   KC_5,    KC_6,          KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
		KC_TAB,  KC_BSLS,KC_QUOT, KC_SCLN,KC_COMM,KC_DOT,  KC_MINS,       KC_EQL, KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,       KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS,                 KC_TRNS,               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	LAYOUT(
		KC_GRV,  KC_F1,  KC_F2,   KC_F3,  KC_F4,  KC_F5,   KC_F6,         KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
		KC_TRNS, BL_SW_0,BL_SW_1, BL_SW_2,BL_SW_3,BAU_TOG, KC_TRNS,       KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, BLE_TOG,USB_TOG, BLE_DEL,BLE_CLR,BLE_OFF, KC_TRNS,       KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS,                 KC_TRNS,               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	LAYOUT(
		KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,       KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,       KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,       KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS,KC_TRNS, KC_TRNS,                 KC_TRNS,               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
#ifndef CUSTOM_DELAY_KEYCODE
        case BLE_TOG:
        case BLE_TOG_EXT:
            if (record->event.pressed) {
                switch_output_driver(0);
            }
            return false;
        case USB_TOG:
        case USB_TOG_EXT:
            if (record->event.pressed) {
                switch_output_driver(1);
            }
            return false;
        case BAU_TOG:
        case BAU_TOG_EXT:
            if (record->event.pressed) {
                if (where_to_send() == OUTPUT_USB) {
                    switch_output_driver(0);
                } else {
                    switch_output_driver(1);
                }
            }
            return false;
        case BL_SW_0:
        case BL_SW_1:
        case BL_SW_2:
        case BL_SW_3:
            if (where_to_send() == OUTPUT_BLUETOOTH) {
                if (record->event.pressed) {
                    set_output(OUTPUT_BLUETOOTH);
                    bluetooth_switch_one(keycode - BL_SW_0);
                }
            }
            return false;
        case BL_SW_0_EXT:
        case BL_SW_1_EXT:
        case BL_SW_2_EXT:
        case BL_SW_3_EXT:
        case BL_SW_4_EXT:
        case BL_SW_5_EXT:
        case BL_SW_6_EXT:
        case BL_SW_7_EXT:
            if (where_to_send() == OUTPUT_BLUETOOTH) {
                if (record->event.pressed) {
                    bluetooth_switch_one(keycode - BL_SW_0_EXT);
                }
            }
            return false;
        case BLE_DEL:
        case BLE_DEL_EXT:
            if (record->event.pressed) {
                if (where_to_send() == OUTPUT_BLUETOOTH) {
                    bluetooth_unpair_current();
                }
            }
            return false;
        case BLE_CLR:
        case BLE_CLR_EXT:
            if (record->event.pressed) {
                if (where_to_send() == OUTPUT_BLUETOOTH) {
                    bluetooth_unpair_all();
                }
            }
            return false;
        case BLE_OFF:
        case BLE_OFF_EXT:
            stop_one_lilnk(0);
            return false;
#endif
        default:
            return true;
    }
    return true;
}
