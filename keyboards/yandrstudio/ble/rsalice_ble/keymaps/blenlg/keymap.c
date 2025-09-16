// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "rgb_matrix_layer.h"
#include "outputselect.h"
#include "biu_ble_common.h"
#include "distributors.h"
#include "usb_main.h"

enum keyboard_keycodes {
    LOCK_GUI = QK_KB,
    TOG_MACOS_KEYMAP_MAC,
    KC_MISSION_CONTROL_MAC,
    KC_LAUNCHPAD_MAC,
    BAT_SHOW,
    BT_1,BT_2,BT_3,
    BT_4,BT_5
};

#ifdef FACTORY_TEST
enum user_keycodes_ft {
    FT_BT_1 = BT_5+1,
    FT_BT_2,
    FT_BT_3
};
#endif

#define MKC_LG     LOCK_GUI
#define MKC_MACOS  TOG_MACOS_KEYMAP_MAC
#define MKC_MCTL   KC_MISSION_CONTROL_MAC
#define MKC_LPAD   KC_LAUNCHPAD_MAC

#define USB_TOG     BT_1  // 打开USB
#define BL_SW_0     BT_2  // 开启蓝牙通道0（需要打开蓝牙的条件下才行）
#define BL_SW_1     BT_3  // 开启蓝牙通道1（需要打开蓝牙的条件下才行）
#define BL_SW_2     BT_4  // 开启蓝牙通道2（需要打开蓝牙的条件下才行）
#define BLE_OFF     BT_5 // 关闭蓝牙连接

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, KC_DEL, // r0
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,          KC_ENT, // r1
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
        KC_B,    KC_N,    KC_M,    KC_COMM, KC_RSFT, KC_UP,   KC_DEL, // r2
#ifdef FACTORY_TEST
        KC_LCTL, KC_LGUI,          KC_LALT, FT_BT_1,
                 FT_BT_2, FT_BT_3,          KC_LEFT, KC_DOWN, KC_RGHT), // r3
#else
        KC_LCTL, KC_LGUI,          KC_LALT, KC_SPC,
                 LT(1, KC_SPC), MO(2),      KC_LEFT, KC_DOWN, KC_RGHT), // r3
#endif
    LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  // r0
        KC_TAB,  KC_BSLS, KC_QUOT, KC_SCLN, KC_COMM, KC_DOT,
        KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_TRNS,          KC_TRNS, // r1
        KC_TRNS, RGB_TOG, RGB_MOD, RGB_RMOD, RGB_VAI, RGB_VAD,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, // r2
        KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS), // r3
    LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  // r0
        KC_TRNS, BL_SW_0, BL_SW_1, BL_SW_2, USB_TOG, BLE_OFF,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, BAT_SHOW,          KC_TRNS, // r1
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, // r2
        KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS), // r3
    LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  // r0
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, // r1
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, // r2
        KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS)
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
                tap_code(KC_RALT);
                bluetooth_switch_one(2);
                ble_channle_update(true);
            }
            return false;
        case FT_BT_3:
            if (record->event.pressed) {
                tap_code(KC_RCTL);
                bluetooth_switch_one(3);
                ble_channle_update(true);
            }
            return false;
    }
    return true;
}

#else // FACTORY_TEST

// Debug的情况可能会导致卡死，print有延时函数和中断
static uint8_t host_idx = 0;
static bool has_in_pairing =false;
static virtual_timer_t pairing_key_timer;
static virtual_timer_t ble_off_timer;

static void pairing_key_timer_cb(void *arg) {
    if (where_to_send() != OUTPUT_BLUETOOTH) {
        switch_output_driver(0);
    }
    bluetooth_switch_one_without_wl(host_idx);
    has_in_pairing = true;
    ble_channle_update(true);
}

static void ble_off_timer_cb(void *arg) {
    stop_one_lilnk(0);
}

static uint32_t mode_tap_timer = 0;
static uint32_t ble_dev_sw_timer = 0;
extern rgb_task_states rgb_task_state;

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
        case BL_SW_0 ... BL_SW_2:
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
        case BLE_OFF:
            if (record->event.pressed) {
                chVTSet(&ble_off_timer, TIME_MS2I(2500), (vtfunc_t)ble_off_timer_cb, NULL);
            } else {
                chVTReset(&ble_off_timer);
            }
            return false;
        case BAT_SHOW: {
            if (record->event.pressed) {
                uint8_t bat_l_t = get_bat_level();
                if (bat_l_t <= 10) {
                    rgb_matrix_adv_unblink_all_batlayer_but_one_layer(9);
                    rgb_matrix_adv_blink_layer_repeat(9, 1500, 1);
                } else {
                    rgb_matrix_adv_unblink_all_batlayer_but_one_layer((bat_l_t % 101) / 10 + 8);
                    rgb_matrix_adv_blink_layer_repeat((bat_l_t % 101) / 10 + 8, 1500, 1);
                }
                if (!rgb_matrix_is_enabled()) {
                    rgb_task_state = FLUSHING;
                }
            }
        }
            return false;
        case MKC_LG:
            if (record->event.pressed) {
                process_magic(GUI_TOG, record);
            }
            return false;
        case MKC_MACOS:
            if (record->event.pressed) {
                process_magic(CG_TOGG, record);
            }
            return false;
        case MKC_MCTL:
            if (record->event.pressed) {
                host_consumer_send(0x29F);
            } else {
                host_consumer_send(0);
            }
            return false;
        case MKC_LPAD:
            if (record->event.pressed) {
                host_consumer_send(0x2A0);
            } else {
                host_consumer_send(0);
            }
            return false;
        default:
            return true;
    }
    return true;
}

#endif
