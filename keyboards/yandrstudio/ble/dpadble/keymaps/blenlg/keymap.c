// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "rgb_matrix_layer.h"
#include "outputselect.h"
#include "biu_ble_common.h"
#include "distributors.h"
#include "usb_main.h"

enum keyboard_bt_keycodes {
    BAT_SHOW = QK_KB+5,
    BT_1,BT_2,BT_3,BT_4
};

#ifdef FACTORY_TEST
enum user_keycodes_ft {
    FT_BT_1 = BT_4+1,
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
#define BLE_OFF     BT_4 // 关闭蓝牙连接

/*
    K000, K001, K002, K003, \
    K100, K101, K102, K103, \
    K200, K201, K202,       \
    K300, K301, K302        \
*/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(
        KC_PGUP, KC_DEL,  KC_PGDN, KC_MUTE,
        KC_F1,   KC_F2,   KC_F3,   MO(1),
#ifdef FACTORY_TEST
        FT_BT_1, FT_BT_2, FT_BT_3),
#else
        KC_F4,   KC_F5,    KC_F6),
#endif
    LAYOUT(
        KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        BL_SW_0,  BL_SW_1,    USB_TOG,    KC_TRNS,
        BLE_OFF,  BAT_SHOW,   RGB_TOG),
    LAYOUT(
        KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,    KC_TRNS),
    LAYOUT(
        KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,  KC_TRNS,    KC_TRNS)
};

#if defined(ENCODER_MAP_ENABLE) && defined(ENCODER_ENABLE)

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT)},
    [1]  = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(RGB_MOD, RGB_RMOD)},
    [2]  = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [3]  = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS)}
};

#endif

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
        case BL_SW_0 ... BL_SW_1:
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
                    rgb_matrix_adv_unblink_all_batlayer_but_one_layer(6);
                    rgb_matrix_adv_blink_layer_repeat(6, 1500, 1);
                } else if (bat_l_t <= 30) {
                    rgb_matrix_adv_unblink_all_batlayer_but_one_layer(7);
                    rgb_matrix_adv_blink_layer_repeat(7, 1500, 1);
                } else if (bat_l_t <= 50) {
                    rgb_matrix_adv_unblink_all_batlayer_but_one_layer(8);
                    rgb_matrix_adv_blink_layer_repeat(8, 1500, 1);
                } else if (bat_l_t <= 70) {
                    rgb_matrix_adv_unblink_all_batlayer_but_one_layer(9);
                    rgb_matrix_adv_blink_layer_repeat(9, 1500, 1);
                }  else if (bat_l_t <= 90) {
                    rgb_matrix_adv_unblink_all_batlayer_but_one_layer(10);
                    rgb_matrix_adv_blink_layer_repeat(10, 1500, 1);
                } else {
                    rgb_matrix_adv_unblink_all_batlayer_but_one_layer(11);
                    rgb_matrix_adv_blink_layer_repeat(11, 1500, 1);
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
