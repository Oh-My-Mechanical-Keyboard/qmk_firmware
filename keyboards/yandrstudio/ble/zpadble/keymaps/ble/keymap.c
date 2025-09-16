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

#define MV2X        KC_F14  // FNX
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
    TD_FN_LAYER_TOG,
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
            set_output(OUTPUT_BLUETOOTH);
            break;
        case USB_TOG:
            usb_event_queue_init();
            init_usb_driver(&USB_DRIVER, false);
            set_output(OUTPUT_USB);
            break;
        case BAU_TOG:
            if (where_to_send() == OUTPUT_USB) {
                set_output(OUTPUT_BLUETOOTH);
            } else {
                usb_event_queue_init();
                init_usb_driver(&USB_DRIVER, false);
                set_output(OUTPUT_USB);
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

void dance_layer_to_layer_count_pre(tap_dance_state_t *state, void *user_data) {
    if (state->count <= 4) {
        layer_on(state->count);
    }
}

void dance_layer_to_layer_count_finsh(tap_dance_state_t *state, void *user_data) {
    if (state->count <= 4) {
        layer_off(state->count);
    }
}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_FN_LAYER_TOG] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,dance_layer_to_layer_count_pre,dance_layer_to_layer_count_finsh),
    [TD_FN_BLE_TOG]   = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BLE_TOG, dance_tab_ble_on_finished),
    [TD_FN_USB_TOG]   = ACTION_TAP_DANCE_FN_ADVANCED_BLE(USB_TOG, dance_tab_ble_on_finished),
    [TD_FN_BAU_TOG]   = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BAU_TOG, dance_tab_ble_on_finished),
    [TD_FN_BLE_SW_0]  = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BL_SW_0, dance_tab_ble_on_finished),
    [TD_FN_BLE_SW_1]  = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BL_SW_1, dance_tab_ble_on_finished),
    [TD_FN_BLE_SW_2]  = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BL_SW_2, dance_tab_ble_on_finished),
    [TD_FN_BLE_SW_3]  = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BL_SW_3, dance_tab_ble_on_finished),
    [TD_FN_BLE_DEL]   = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BLE_DEL, dance_tab_ble_on_finished),
    [TD_FN_BLE_CLR]   = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BLE_CLR, dance_tab_ble_on_finished),
    [TD_FN_BLE_OFF]   = ACTION_TAP_DANCE_FN_ADVANCED_BLE(BLE_OFF, dance_tab_ble_on_finished),
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
    LAYOUT(
        MV2X,                      KC_MUTE,
        KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,
        KC_P1,   KC_P2,   KC_P3,   KC_PENT,
                 KC_P0,   KC_PDOT,
                 KC_VOLU, KC_VOLD
    ),
    LAYOUT(
        KC_TRNS,                   KC_TRNS,
        RGB_TOG, RGB_RMOD, RGB_MOD, KC_TRNS,
        BLE_TOG, USB_TOG, BAU_TOG, KC_TRNS,
        BLE_DEL, BLE_CLR, BLE_OFF,
        BL_SW_0, BL_SW_1, BL_SW_2, KC_TRNS,
                 KC_TRNS, KC_TRNS,
                 RGB_VAI, RGB_VAD
    ),
    LAYOUT(
        KC_TRNS,                   KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS
    ),
    LAYOUT(
        KC_TRNS,                   KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS
    )

};



#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    uint16_t keycode = 0;
    if (clockwise) {
        // tap_code16(KC_VOLU);
        keycode = dynamic_keymap_get_keycode(biton32(layer_state), 0, 19);
    } else {
        // tap_code16(KC_VOLD);
        keycode = dynamic_keymap_get_keycode(biton32(layer_state), 0, 20);
    }
    if (keycode >= MACRO00 && keycode <= MACRO15) {
        dynamic_keymap_macro_send(keycode - MACRO00);
    } else {
        tap_code16(keycode);
    }
    return false;
}

#endif


#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("FN\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("ADJ\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    return false;
}
#endif
