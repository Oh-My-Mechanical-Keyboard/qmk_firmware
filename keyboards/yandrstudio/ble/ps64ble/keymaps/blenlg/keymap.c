// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "outputselect.h"
#include "biu_ble_common.h"
#include "distributors.h"
#include "usb_main.h"

enum user_keycodes_bt {
    BT_1 = QK_KB_0+7,
    BT_2,BT_3,
    BT_4,BT_5,BT_6
};

#ifdef FACTORY_TEST
enum user_keycodes_ft {
    FT_BT_1 = BT_6+1,
    FT_BT_2,
    FT_BT_3
};
#endif

#define MKC_LG     LOCK_GUI
#define MKC_MACOS  TOG_MACOS_KEYMAP_MAC
#define MKC_MCTL   KC_MISSION_CONTROL_MAC
#define MKC_LPAD   KC_LAUNCHPAD_MAC

// #define BLE_TOG     BT_1  // 打开蓝牙
#define USB_TOG     BT_1  // 打开USB
#define BL_SW_0     BT_2  // 开启蓝牙通道0（需要打开蓝牙的条件下才行）
#define BL_SW_1     BT_3  // 开启蓝牙通道1（需要打开蓝牙的条件下才行）
#define BL_SW_2     BT_4  // 开启蓝牙通道2（需要打开蓝牙的条件下才行）
#define BL_SW_3     BT_5  // 开启蓝牙通道3（需要打开蓝牙的条件下才行）
// #define BLE_DEL     BT_7  // 删除当前蓝牙绑定
// #define BLE_CLR     BT_8  // 清空所有蓝牙绑定
#define BLE_OFF     BT_6 // 关闭蓝牙连接

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,          KC_4,   KC_5, KC_6, KC_7, KC_8,          KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,          KC_R,   KC_T, KC_Y, KC_U, KC_I,          KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,          KC_F,   KC_G, KC_H, KC_J, KC_K,          KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,          KC_V,   KC_B, KC_N, KC_M, KC_COMM,       KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_DEL,
#ifdef FACTORY_TEST
        KC_LCTL, KC_LGUI, KC_LALT, FT_BT_1,       FT_BT_2,                  FT_BT_3,       KC_RALT, KC_SPC,  KC_LEFT, KC_DOWN, KC_RGHT),
#else
        KC_LCTL, KC_LGUI, KC_LALT, LT(1, KC_SPC), KC_SPC,                   LT(1, KC_SPC), KC_RALT, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT),
#endif
    [1] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,    KC_F11,  KC_F12,  KC_DEL,
        BLE_OFF, BL_SW_0, BL_SW_1, BL_SW_2, BL_SW_3, USB_TOG, BLE_OFF, KC_TRNS, KC_TRNS, KC_TRNS, KC_BTSH,   KC_TRNS, KC_TRNS, NK_TOGG,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS,
        KC_TRNS, RGB_TOG, RGB_MOD, RGB_RMOD,RGB_VAI, RGB_VAD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_KG_T,  KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, MKC_LG,  KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS),
    [2] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [3] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

#ifdef FACTORY_TEST
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case FT_BT_1:
            if (record->event.pressed) {
                tap_code(KC_SPC);
                bluetooth_switch_one(1);
                ble_channle_update(true);
            }
            return false;
        case FT_BT_2:
            if (record->event.pressed) {
                tap_code(KC_SPC);
                bluetooth_switch_one(2);
                ble_channle_update(true);
            }
            return false;
        case FT_BT_3:
            if (record->event.pressed) {
                tap_code(KC_SPC);
                bluetooth_switch_one(3);
                ble_channle_update(true);
            }
            return false;
    }
    return true;
}

#else


static uint8_t host_idx = 0;
static bool has_in_pairing =false;
// static uint8_t ble_op_type = 0;

static virtual_timer_t pairing_key_timer;
static virtual_timer_t ble_off_timer;
// static virtual_timer_t ble_binding_option_timer;

static void pairing_key_timer_cb(void *arg) {
    if (where_to_send() != OUTPUT_BLUETOOTH) {
        switch_output_driver(0);
    }
    bluetooth_switch_one_without_wl(host_idx);
    has_in_pairing = true;
    ble_channle_update(true);
}
// static void ble_binding_option_timer_cb(void *arg) {
//     switch (ble_op_type)
//     {
//     case 0:
//         bluetooth_unpair_current();
//         break;
//     case 1:
//         bluetooth_unpair_all();
//         break;
//     default:
//         break;
//     }
//     ble_channle_update(true);
// }
static void ble_off_timer_cb(void *arg) {
    stop_one_lilnk(0);
}

static uint32_t mode_tap_timer = 0;
static uint32_t ble_dev_sw_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case USB_TOG:
            if (record->event.pressed) {
                mode_tap_timer = timer_read32();
            } else {
                if (timer_elapsed32(mode_tap_timer) >= 500) {
                    switch_output_driver(1);
                    ble_channle_update(true);
                }
                mode_tap_timer = timer_read32();
            }
            return false;
        // case BLE_TOG:
        //     if (record->event.pressed) {
        //         mode_tap_timer = timer_read32();
        //     } else {
        //         if (timer_elapsed32(mode_tap_timer) >= 500) {
        //             switch_output_driver(0);
        //             ble_channle_update(true);
        //         }
        //         mode_tap_timer = timer_read32();
        //     }
        //     return false;
        case BL_SW_0 ... BL_SW_3:
            if (record->event.pressed) {
                ble_dev_sw_timer = timer_read32();
                has_in_pairing = false;
                host_idx = keycode - BL_SW_0;
                chVTSet(&pairing_key_timer, TIME_MS2I(2500), (vtfunc_t)pairing_key_timer_cb, NULL);
            } else {
                if (!has_in_pairing && timer_elapsed32(ble_dev_sw_timer) >= 500) {
                    if (where_to_send() != OUTPUT_BLUETOOTH) {
                        switch_output_driver(0);
                    }
                    bluetooth_switch_one(host_idx);
                    ble_channle_update(true);
                }
                ble_dev_sw_timer = timer_read32();
                chVTReset(&pairing_key_timer);
            }
            return false;
        // case BLE_DEL ... BLE_CLR:
        //     if (where_to_send() == OUTPUT_BLUETOOTH) {
        //         if (record->event.pressed) {
        //             ble_op_type = keycode - BLE_DEL;
        //             chVTSet(&ble_binding_option_timer, TIME_MS2I(2000), (vtfunc_t)ble_binding_option_timer_cb, NULL);
        //         } else {
        //             chVTReset(&ble_binding_option_timer);
        //         }
        //     }
        //     return false;
        case BLE_OFF:
            if (record->event.pressed) {
                chVTSet(&ble_off_timer, TIME_MS2I(2000), (vtfunc_t)ble_off_timer_cb, NULL);
            } else {
                chVTReset(&ble_off_timer);
            }
            return false;
        default:
            return true;
    }
    return true;
}

#endif
