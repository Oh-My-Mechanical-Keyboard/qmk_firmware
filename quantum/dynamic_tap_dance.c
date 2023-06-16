/* Copyright 2023 zhaqian
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

#include "dynamic_tap_dance.h"
#include "dynamic_keymap.h"
#include "keymap_common.h"
#include "keymap_introspection.h"

#define KEYLOC_DYNAMIC_TAP_DANCE 251

static uint16_t   td_keycode;
static td_info_t  td_infos[DYNAMIC_TAP_DANCE_ENTRIES];
tap_dance_action_t tap_dance_actions[DYNAMIC_TAP_DANCE_ENTRIES];

#define TD_REGISTER_KEYCODE(td_kc, kc)                      \
do {                                                        \
    td_kc = kc;                                             \
    if (kc < QK_MODS_MAX) {                                 \
        register_code16(kc);                                \
    } else {                                                \
        action_exec(MAKE_KEYEVENT(KEYLOC_DYNAMIC_TAP_DANCE, \
                    KEYLOC_DYNAMIC_TAP_DANCE, true));       \
    }                                                       \
} while(0)

#define TD_UNREGISTER_KEYCODE(td_kc, kc)                    \
do {                                                        \
    td_kc = kc;                                             \
    if (kc < QK_MODS_MAX) {                                 \
        unregister_code16(kc);                              \
    } else {                                                \
        action_exec(MAKE_KEYEVENT(KEYLOC_DYNAMIC_TAP_DANCE, \
                    KEYLOC_DYNAMIC_TAP_DANCE, false));      \
    }                                                       \
} while(0)

#define TD_TAP_KEYCODE(td_kc, kc)                           \
do {                                                        \
    TD_REGISTER_KEYCODE(td_kc, kc);                         \
    wait_ms(CUSTOM_TAP_CODE_DELAY);                         \
    TD_UNREGISTER_KEYCODE(td_kc, kc);                       \
} while(0)

uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key) {
#ifdef DYNAMIC_TAP_DANCE_ENABLE
    if (key.row == KEYLOC_DYNAMIC_TAP_DANCE && key.col == KEYLOC_DYNAMIC_TAP_DANCE) {
        return td_keycode;
    }
#endif
    if (key.row < MATRIX_ROWS && key.col < MATRIX_COLS) {
        return keycode_at_keymap_location(layer, key.row, key.col);
    }
#ifdef ENCODER_MAP_ENABLE
    else if (key.row == KEYLOC_ENCODER_CW && key.col < NUM_ENCODERS) {
        return keycode_at_encodermap_location(layer, key.col, true);
    } else if (key.row == KEYLOC_ENCODER_CCW && key.col < NUM_ENCODERS) {
        return keycode_at_encodermap_location(layer, key.col, false);
    }
#endif
    return KC_NO;
}

static td_state_t current_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            return TD_SINGLE_TAP;
        } else {
            return TD_SINGLE_HOLD;
        }
    } else if (state->count == 2) {
        if (state->interrupted) {
            return TD_DOUBLE_SINGLE_TAP;
        } else if (state->pressed) {
            return TD_DOUBLE_HOLD;
        } else {
            return TD_DOUBLE_TAP;
        }
    }
    return TD_UNKNOWN;
}

static void on_dance_finished(tap_dance_state_t *state, void *user_data) {
    td_info_t *info = (td_info_t *)user_data;
    td_entry_t td_entry;
    if (info->entry < DYNAMIC_TAP_DANCE_ENTRIES) {
        dynamic_get_tap_dance(info->entry, &td_entry);
    } else {
        return;
    }
    info->state = current_dance(state);
    switch (info->state) {
        case TD_SINGLE_TAP: {
            if (td_entry.on_tap) {
                TD_REGISTER_KEYCODE(td_keycode, td_entry.on_tap);
            }
            break;
        }
        case TD_SINGLE_HOLD: {
            if (td_entry.on_hold) {
                TD_REGISTER_KEYCODE(td_keycode, td_entry.on_hold);
            }
            break;
        }
        case TD_DOUBLE_TAP: {
            if (td_entry.on_double_tap) {
                TD_REGISTER_KEYCODE(td_keycode, td_entry.on_double_tap);
            }
            break;
        }
        case TD_DOUBLE_HOLD: {
            if (td_entry.on_tap_hold) {
                TD_REGISTER_KEYCODE(td_keycode, td_entry.on_tap_hold);
            }
            break;
        }
        case TD_DOUBLE_SINGLE_TAP: {
            if (td_entry.on_tap) {
                TD_TAP_KEYCODE(td_keycode, td_entry.on_tap);
                TD_REGISTER_KEYCODE(td_keycode, td_entry.on_tap);
            }
            break;
        }
        default: {
            break;
        }
    }
}

static void on_dance_reset(tap_dance_state_t *state, void *user_data) {
    td_info_t *info = (td_info_t *)user_data;
    td_entry_t td_entry;
    if (info->entry < DYNAMIC_TAP_DANCE_ENTRIES) {
        dynamic_get_tap_dance(info->entry, &td_entry);
    } else {
        return;
    }
    switch (info->state) {
        case TD_SINGLE_TAP: {
            if (td_entry.on_tap) {
                TD_UNREGISTER_KEYCODE(td_keycode, td_entry.on_tap);
            }
            break;
        }
        case TD_SINGLE_HOLD: {
            if (td_entry.on_hold) {
                TD_UNREGISTER_KEYCODE(td_keycode, td_entry.on_hold);
            }
            break;
        }
        case TD_DOUBLE_TAP: {
            if (td_entry.on_double_tap) {
                TD_UNREGISTER_KEYCODE(td_keycode, td_entry.on_double_tap);
            }
            break;
        }
        case TD_DOUBLE_HOLD: {
            if (td_entry.on_tap_hold) {
                TD_UNREGISTER_KEYCODE(td_keycode, td_entry.on_tap_hold);
            }
            break;
        }
        case TD_DOUBLE_SINGLE_TAP: {
            if (td_entry.on_tap) {
                TD_UNREGISTER_KEYCODE(td_keycode, td_entry.on_tap);
            }
            break;
        }
        default: {
            break;
        }
    }
    info->state = TD_NONE;
}

void dynamic_tap_dance_init(void) {
    for (uint8_t i = 0; i < DYNAMIC_TAP_DANCE_ENTRIES; i++) {
        td_infos[i].entry = i;
        td_infos[i].state = TD_NONE;
        tap_dance_actions[i].fn.on_dance_finished = on_dance_finished;
        tap_dance_actions[i].fn.on_reset = on_dance_reset;
        tap_dance_actions[i].user_data = &td_infos[i];
    }
}
