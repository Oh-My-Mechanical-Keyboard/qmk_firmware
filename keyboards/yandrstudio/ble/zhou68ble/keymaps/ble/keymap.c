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
 * along with this program.  If not, see <http: //www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "outputselect.h"
#include "biu_ble_common.h"
#include "distributors.h"
#include "usb_main.h"

#define MKC_LG     LOCK_GUI
#define MKC_MACOS  TOG_MACOS_KEYMAP_MAC
#define MKC_MCTL   KC_MISSION_CONTROL_MAC
#define MKC_LPAD   KC_LAUNCHPAD_MAC

#ifdef RGB_MATRIX_ENABLE
#include "rgb_matrix_layer.h"
#   define KC_BTSH BAT_SHOW
#else
#   define KC_BTSH KC_TRNS
#endif

#define BLE_TOG     BT_1  // 打开蓝牙
#define USB_TOG     BT_2  // 打开USB
#define BAU_TOG     BT_3  // 蓝牙和USB之间切换
#define BL_SW_0     BT_4  // 开启蓝牙通道0（需要打开蓝牙的条件下才行）
#define BL_SW_1     BT_5  // 开启蓝牙通道1（需要打开蓝牙的条件下才行）
#define BL_SW_2     BT_6  // 开启蓝牙通道2（需要打开蓝牙的条件下才行）
#define BL_SW_3     BT_7  // 开启蓝牙通道3（需要打开蓝牙的条件下才行）
#define BLE_DEL     BT_8  // 删除当前蓝牙绑定
#define BLE_CLR     BT_9  // 清空所有蓝牙绑定
#define BLE_OFF     BT_10 // 关闭蓝牙连接

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
            ble_channle_update(true);
            break;
        case USB_TOG:
            switch_output_driver(1);
            ble_channle_update(true);
            break;
        case BAU_TOG:
            if (where_to_send() == OUTPUT_USB) {
                switch_output_driver(0);
            } else {
                switch_output_driver(1);
            }
            ble_channle_update(true);
            break;
        case BL_SW_0:
        case BL_SW_1:
        case BL_SW_2:
        case BL_SW_3:
            if (where_to_send() == OUTPUT_BLUETOOTH) {
                bluetooth_switch_one(keycode - BL_SW_0);
            }
            ble_channle_update(true);
            break;
        case BLE_DEL:
            if (where_to_send() == OUTPUT_BLUETOOTH) {
                bluetooth_unpair_current();
            }
            ble_channle_update(true);
            break;
        case BLE_CLR:
            if (where_to_send() == OUTPUT_BLUETOOTH) {
                bluetooth_unpair_all();
            }
            ble_channle_update(true);
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
    [TD_FN_BLE_TOG]  = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BLE_TOG, dance_tab_ble_on_finished),
    [TD_FN_USB_TOG]  = ACTION_TAP_DANCE_FN_ADVANCED_BLE(USB_TOG, dance_tab_ble_on_finished),
    [TD_FN_BAU_TOG]  = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BAU_TOG, dance_tab_ble_on_finished),
    [TD_FN_BLE_SW_0] = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BL_SW_0, dance_tab_ble_on_finished),
    [TD_FN_BLE_SW_1] = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BL_SW_1, dance_tab_ble_on_finished),
    [TD_FN_BLE_SW_2] = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BL_SW_2, dance_tab_ble_on_finished),
    [TD_FN_BLE_SW_3] = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BL_SW_3, dance_tab_ble_on_finished),
    [TD_FN_BLE_DEL]  = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BLE_DEL, dance_tab_ble_on_finished),
    [TD_FN_BLE_CLR]  = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BLE_CLR, dance_tab_ble_on_finished),
    [TD_FN_BLE_OFF]  = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BLE_OFF, dance_tab_ble_on_finished),
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
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,   KC_3,    KC_4,  KC_5,  KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_GRV,   KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,   KC_E,    KC_R,  KC_T,  KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,   KC_PGDN,
        KC_CAPS, KC_A,    KC_S,   KC_D,    KC_F,  KC_G,  KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,   KC_C,    KC_V,  KC_B,  KC_N,            KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,            KC_UP,
        KC_LCTL, KC_LGUI,                                KC_LALT, KC_SPC, KC_RCTL, MO(1),                     KC_RALT,  KC_LEFT,  KC_DOWN,  KC_RGHT),
    [1] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS,  KC_TRNS,
        KC_TRNS, BL_SW_0, BL_SW_1, BL_SW_2, BL_SW_3, BAU_TOG, TOG_TFT_SCREEN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
        KC_TRNS, BLE_TOG, USB_TOG, BLE_DEL, BLE_CLR, BLE_OFF, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, RGB_TOG, RGB_MOD, RGB_RMOD,RGB_VAI, RGB_VAD, RGB_HUI,          RGB_HUD, RGB_SAI, RGB_SAD, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [2] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [3] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};
#ifdef RGB_MATRIX_ENABLE
extern rgb_task_states rgb_task_state;
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef RGB_MATRIX_ENABLE
        case BAT_SHOW: {
            if (record->event.pressed) {
                uint8_t bat_l_t = get_bat_level();
                if (bat_l_t <= 10) {
                    rgb_matrix_adv_unblink_all_batlayer_but_one_layer(11);
                    rgb_matrix_adv_blink_layer_repeat(11, 1500, 1);
                } else {
                    rgb_matrix_adv_unblink_all_batlayer_but_one_layer((bat_l_t % 101) / 10 + 10);
                    rgb_matrix_adv_blink_layer_repeat((bat_l_t % 101) / 10 + 10, 1500, 1);
                }
                if (!rgb_matrix_is_enabled()) {
                    rgb_task_state = FLUSHING;
                }
            }
        }
            return false;
#endif

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
