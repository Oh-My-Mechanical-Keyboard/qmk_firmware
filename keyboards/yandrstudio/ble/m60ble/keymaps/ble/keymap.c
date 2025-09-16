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
#include "anm.h"
#include <stdio.h>

enum keyboard_keycodes {
    BLE_TOG = SAFE_RANGE, // ble
    USB_TOG,              // usb
    BAU_TOG,              // if ble then usb, if usb then ble
    BL_SW_0,              // ble id 0
    BL_SW_1,
    BL_SW_2,
    BL_SW_3,
    BLE_DEL,              // delete current ble bound
    BLE_CLR,              // delete all ble bound
    NEW_SAFE_RANGE  // Important!
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(
		BLE_TOG,USB_TOG, BAU_TOG, BL_SW_0, BL_SW_2, BLE_DEL, BLE_CLR, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
		KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(1), KC_RGUI, KC_RCTL),
    LAYOUT(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
		KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_LSFT,
		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(1), KC_RGUI, KC_RCTL),
    LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

};

void keyboard_post_init_user(void) {
    // eeconfig_init();
    // uart_init(115200);
    // debug_enable=true;
    //   debug_matrix=true;
    //   debug_keyboard=true;
    //     //debug_mouse=true;
}

#ifdef OLED_ENABLE
uint32_t wpm_graph_timer_update = 0;
static const char caps_head[] PROGMEM = {
    0x00, 0xFE, 0x02, 0xFA, 0x0A, 0x0A,
    0x0A, 0x02, 0x02, 0xC2, 0x32, 0x1A,
    0x1A, 0x32, 0xC2, 0x02, 0x02, 0xFA,
    0x8A, 0x8A, 0x72, 0x02, 0xFE, 0x00
};
static const char caps_on_1[] PROGMEM = {
    0x00, 0xFF, 0x00, 0x07, 0xE4, 0xE4,
    0xE4, 0xE0, 0xE0, 0xE7, 0xE1, 0xE1,
    0xE1, 0xE1, 0xE7, 0xE0, 0xE0, 0xE7,
    0xE0, 0xE0, 0x00, 0x00, 0xFF, 0x00
};
static const char caps_on_2[] PROGMEM = {
    0x00, 0x7F, 0x40, 0x40, 0x4F, 0x4F,
    0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F,
    0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F,
    0x4F, 0x4F, 0x40, 0x40, 0x7F, 0x00
};
static const char caps_off_1[] PROGMEM = {
    0x00, 0xFF, 0x00, 0x07, 0x04, 0x04,
    0x04, 0x00, 0x00, 0x07, 0x01, 0x01,
    0x01, 0x01, 0x07, 0x00, 0x00, 0x07,
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x00
};
static const char caps_off_2[] PROGMEM = {
    0x00, 0x7F, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x7F, 0x00
};

static const char wpm_str_0[] PROGMEM = {
    0xF0, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0xF0
};
static const char wpm_str_1[] PROGMEM = {
    0xFF, 0x00, 0x7E, 0x80, 0x80, 0x70,
    0x80, 0x80, 0x7E, 0x00, 0xFE, 0x12,
    0x12, 0x0C, 0x00, 0xFE, 0x04, 0x04,
    0x78, 0x04, 0x04, 0xFE, 0x00, 0xFF
};
static const char wpm_str_2[] PROGMEM = {
    0x0F, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x0F
};

void oled_render_normal(void) {
    /* Host output mode */
    char out_model[5] = {0};
    out_model[2] = ' ';
    out_model[3] = ' ';
    out_model[4] = 0;
    if (where_to_send() == OUTPUT_BLUETOOTH) {
        out_model[0] = 3;
        out_model[1] = 4;
        oled_write_P(out_model, false);
    } else if (where_to_send() == OUTPUT_USB) {
        out_model[0] = 1;
        out_model[1] = 2;
        oled_write_P(out_model, false);
    } else if (where_to_send() == OUTPUT_AUTO) {
        oled_write_P(PSTR("AUTO"), false);
    } else {
        oled_write_P(PSTR("NONE"), false);
    }

    /* Host Keyboard Layer Status */
    oled_set_cursor(4,0);
    oled_write_P(PSTR("  LAYER "), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("0"), false);
            break;
        case 1:
            oled_write_P(PSTR("1"), false);
            break;
        case 2:
            oled_write_P(PSTR("2"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("X"), false);
    }

    /* bat info */
    uint8_t bat_l = get_bat_level();
    bat_l = bat_l >= 99 ? 99 : bat_l;
    char bat_str[5] = {0};
    snprintf(bat_str, sizeof(bat_str), "%02u%%", bat_l);
    bat_str[3] = 0;
    bat_str[4] = 0;
    oled_write_P(PSTR(" BAT "), false);
    oled_write_P(PSTR(bat_str), false);

    /*Caps state */
    oled_set_cursor(0,1);
    oled_write_raw(caps_head, 24);
    if (host_keyboard_led_state().caps_lock) {
        oled_set_cursor(0,2);
        oled_write_raw(caps_on_1, 24);
        oled_set_cursor(0,3);
        oled_write_raw(caps_on_2, 24);
    } else {
        oled_set_cursor(0,2);
        oled_write_raw(caps_off_1, 24);
        oled_set_cursor(0,3);
        oled_write_raw(caps_off_2, 24);
    }

    /* device name */
    oled_set_cursor(6,2);
    oled_write_P(PSTR("Moonlight Re 75"), false);

    /* split h line */
    for (uint16_t i = 512; i < 640; ++i) {
        oled_write_raw_byte(0x18, i);
    }

    /* wpm curve */
    uint8_t height_mask[9] = {0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff};
    uint16_t cur_wpm = get_current_wpm();
    uint8_t cur_height = (float)(cur_wpm*24)/199.0;
    cur_height = cur_height > 24 ? 24 : cur_height;
    if (cur_height <= 8) {
        oled_write_raw_byte(height_mask[cur_height], 7*128+12*6);
        oled_write_raw_byte(0x00, 6*128+12*6);
        oled_write_raw_byte(0x00, 5*128+12*6);
    } else if (cur_height > 8 && cur_height <= 16) {
        oled_write_raw_byte(0xff, 7*128+12*6);
        oled_write_raw_byte(height_mask[cur_height-8], 6*128+12*6);
        oled_write_raw_byte(0x00, 5*128+12*6);
    } else if (cur_height > 16 && cur_height <= 24) {
        oled_write_raw_byte(0xff, 7*128+12*6);
        oled_write_raw_byte(0xff, 6*128+12*6);
        oled_write_raw_byte(height_mask[cur_height-16], 5*128+12*6);
    } else {
        oled_write_raw_byte(0x00, 7*128+12*6);
        oled_write_raw_byte(0x00, 6*128+12*6);
        oled_write_raw_byte(0x00, 5*128+12*6);
    }
    bool need_pan =true;
    if (wpm_graph_timer_update == 0) {
        wpm_graph_timer_update = timer_read32();
        need_pan = false;
    }

    // 3 frame
    if (timer_elapsed32(wpm_graph_timer_update) < 330) {
        need_pan = false;
    }
    if (need_pan) {
        wpm_graph_timer_update = timer_read32();
        oled_pan_area(5, 7, 0, 12*6, true);
    }


    /* wpm number */
    oled_set_cursor(13, 5);
    oled_write_raw(wpm_str_0, 24);
    oled_set_cursor(13, 6);
    oled_write_raw(wpm_str_1, 24);
    oled_set_cursor(13, 7);
    oled_write_raw(wpm_str_2, 24);

    oled_set_cursor(18, 6);
    cur_wpm = cur_wpm > 199 ? 199 : cur_wpm;
    char wpm_str[5] = {0};
    snprintf(wpm_str, sizeof(wpm_str), "%03d", cur_wpm);
    wpm_str[3] = 0;
    wpm_str[4] = 0;
    oled_write_P(PSTR(wpm_str), false);
}

extern uint32_t oled_timeout;

static bool has_start = false;
static uint32_t start_time_anm = 0;
static uint32_t start_frame_index = 0;
void oled_render_anm(void) {
    uint32_t one_frame_time = 25*1000/60;
    if (!has_start) {
        has_start = true;
        start_time_anm = timer_read32();
        start_frame_index = 0;
    }
    uint32_t els_time = timer_elapsed32(start_time_anm);
    if (els_time >= start_frame_index*one_frame_time && els_time < (start_frame_index+1)*one_frame_time) {
        if (start_frame_index >= 60) {
            has_start = false;
            start_time_anm = 0;
            start_frame_index = 0;
            oled_off();
        } else  {
            if (start_frame_index >= 40) {
                oled_write_raw(anms[start_frame_index-40], 128*8);
            } else if (start_frame_index >= 20) {
                oled_write_raw(anms[start_frame_index-20], 128*8);
            } else {
                oled_write_raw(anms[start_frame_index], 128*8);
            }
            start_frame_index++;
        }
    }
}

static bool need_clear_1 = true;
static bool need_clear_2 = true;
bool start_render_anm = false;

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    oled_timeout = timer_read32() + OLED_TIMEOUT;
    start_render_anm = false;
    has_start = false;
    start_time_anm = 0;
    start_frame_index = 0;

    need_clear_1 = false;
    need_clear_2 = false;
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
}

bool oled_task_user(void) {
    if (!start_render_anm && timer_expired32(timer_read32(), (oled_timeout-35000))) {
        start_render_anm = true;
    }

    if (start_render_anm) {
        if (need_clear_1) {
            oled_clear();
            need_clear_1 = false;
        }
        oled_render_anm();
        need_clear_2 = true;
    } else {
        if (need_clear_2) {
            oled_clear();
            need_clear_2 = false;
        }
        oled_render_normal();
        need_clear_1 = true;
        has_start = false;
    }
    return false;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
    start_render_anm = false;
#endif
    // if (record->event.pressed) {
    //     uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    // }
    switch(keycode) {
        case BLE_TOG:
            if (record->event.pressed) {
                set_output(OUTPUT_BLUETOOTH);
            }
            return false;
        case USB_TOG:
            if (record->event.pressed) {
                set_output(OUTPUT_USB);
            }
            return false;
        case BAU_TOG:
            if (record->event.pressed) {
                if (where_to_send() == OUTPUT_USB) {
                    set_output(OUTPUT_BLUETOOTH);
                } else {
                    set_output(OUTPUT_USB);
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
        case BLE_DEL:
            if (record->event.pressed) {
                bluetooth_unpair_current();
            }
            return false;
        case BLE_CLR:
            if (record->event.pressed) {
                bluetooth_unpair_all();
            }
            return false;
        default:
            return true;
    }
    return true;
}
