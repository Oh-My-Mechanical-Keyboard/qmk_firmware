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

#include "magic_settings.h"
#include "eeprom.h"

#ifdef MOUSEKEY_ENABLE
#include "mousekey.h"
#endif

magic_settings_t magic_settings_config;

EECONFIG_DEBOUNCE_HELPER(magic_settings, EECONFIG_MAGIC_SETTINGS, magic_settings_config);

void eeconfig_update_magic_settings(void) {
    eeconfig_flush_magic_settings(true);
}

static void eeconfig_update_magic_settings_default(void) {
    magic_settings_config.debounce = DEBOUNCE;
#ifdef MOUSEKEY_ENABLE
    mousekey_maigc_settings_reset();
#endif
    magic_settings_config.grave_esc_override = 0x10;    // bit for eeconfig init check
#ifndef NO_ACTION_TAPPING
    tap_hold_maigc_settings_reset();
#endif
#ifdef AUTO_SHIFT_ENABLE
    auto_shift_maigc_settings_reset();
#endif
#ifndef NO_ACTION_ONESHOT
    oneshot_maigc_settings_reset();
#endif
#ifdef COMBO_ENABLE
    combo_maigc_settings_reset();
#endif
    eeconfig_update_magic_settings();
    clear_keyboard();
};

void magic_settings_init(void) {
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
        eeconfig_update_magic_settings_default();
    }
    eeconfig_init_magic_settings();
    if (!(magic_settings_config.grave_esc_override & 0x10)) {
        eeconfig_update_magic_settings_default();
    }
#ifdef MOUSEKEY_ENABLE
    mousekey_maigc_settings_update();
#endif
#ifdef AUTO_SHIFT_ENABLE
    auto_shift_maigc_settings_update();
#endif
#ifdef COMBO_ENABLE
    combo_maigc_settings_update();
#endif
}

void magic_settings_reset(void) {
    eeconfig_update_magic_settings_default();
}

#ifdef MOUSEKEY_ENABLE
void mousekey_maigc_settings_update(void) {
    mk_delay = magic_settings_config.mk_delay;
    mk_interval = magic_settings_config.mk_interval;
    mk_max_speed = magic_settings_config.mk_max_speed;
    mk_time_to_max = magic_settings_config.mk_time_to_max;
    mk_wheel_delay = magic_settings_config.mk_wheel_delay;
    mk_wheel_interval = magic_settings_config.mk_wheel_interval;
    mk_wheel_max_speed = magic_settings_config.mk_wheel_max_speed;
    mk_wheel_time_to_max = magic_settings_config.mk_wheel_time_to_max;
}

void mousekey_maigc_settings_reset(void) {
    magic_settings_config.mk_delay = MOUSEKEY_DELAY / 10;
    magic_settings_config.mk_interval = MOUSEKEY_INTERVAL;
    magic_settings_config.mk_move_delta = MOUSEKEY_MOVE_DELTA;
    magic_settings_config.mk_max_speed = MOUSEKEY_MAX_SPEED;
    magic_settings_config.mk_time_to_max = MOUSEKEY_TIME_TO_MAX;
    magic_settings_config.mk_wheel_delay = MOUSEKEY_WHEEL_DELAY / 10;
    magic_settings_config.mk_wheel_interval = MOUSEKEY_WHEEL_INTERVAL;
    magic_settings_config.mk_wheel_max_speed = MOUSEKEY_WHEEL_MAX_SPEED;
    magic_settings_config.mk_wheel_time_to_max = MOUSEKEY_WHEEL_TIME_TO_MAX;
    mousekey_maigc_settings_update();
}
#endif

#ifndef NO_ACTION_TAPPING
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
#ifdef DYNAMIC_TAP_DANCE_ENABLE
    if (keycode >= QK_TAP_DANCE && keycode <= QK_TAP_DANCE_MAX) {
        uint8_t index = keycode - QK_TAP_DANCE;
        if (index < DYNAMIC_TAP_DANCE_ENTRIES) {
            return dynamic_get_tap_dance_term(index);
        }
    }
#endif
    return magic_settings_config.tapping_term;
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    return magic_settings_config.quick_tap_term;
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    return (magic_settings_config.tap_hold_config & 0x01);
}

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    return (magic_settings_config.tap_hold_config & 0x02);
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    return (magic_settings_config.tap_hold_config & 0x04);
}

void tap_hold_maigc_settings_reset(void) {
    magic_settings_config.tap_hold_config = 0;
    magic_settings_config.tapping_toggle_times = TAPPING_TOGGLE;
    magic_settings_config.tapping_term = TAPPING_TERM;
    magic_settings_config.quick_tap_term = QUICK_TAP_TERM;
    magic_settings_config.tap_code_delay = TAP_CODE_DELAY;
    magic_settings_config.tap_hold_caps_delay = TAP_HOLD_CAPS_DELAY;
}
#endif

#ifdef AUTO_SHIFT_ENABLE
bool get_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case AUTO_SHIFT_ALPHA: {
            if (!(magic_settings_config.auto_shift_config & 0x04)) {
                return true;
            }
            break;
        }
        case AUTO_SHIFT_NUMERIC: {
            if (!(magic_settings_config.auto_shift_config & 0x08)) {
                return true;
            }
            break;
        }
        case AUTO_SHIFT_SPECIAL: {
            if (!(magic_settings_config.auto_shift_config & 0x10)) {
                return true;
            }
            break;
        }
    }
    return get_custom_auto_shifted_key(keycode, record);
}

bool get_auto_shift_repeat(uint16_t keycode, keyrecord_t *record) {
    return (magic_settings_config.auto_shift_config & 0x20);
}

bool get_auto_shift_no_auto_repeat(uint16_t keycode, keyrecord_t *record) {
    return (magic_settings_config.auto_shift_config & 0x40);
}

void auto_shift_maigc_settings_update(void) {
    set_autoshift_timeout(magic_settings_config.auto_shift_timeout);
}

void auto_shift_maigc_settings_reset(void) {
    magic_settings_config.auto_shift_config = 0;
    magic_settings_config.auto_shift_timeout = AUTO_SHIFT_TIMEOUT;
    auto_shift_maigc_settings_update();
}
#endif

#ifndef NO_ACTION_ONESHOT
void oneshot_maigc_settings_reset(void) {
    magic_settings_config.oneshot_tap_toggle = ONESHOT_TAP_TOGGLE;
    magic_settings_config.oneshot_timeout = ONESHOT_TIMEOUT;
}
#endif

#ifdef COMBO_ENABLE

bool get_combo_must_hold(uint16_t index, combo_t *combo) {
    return (magic_settings_config.combo_config & 0x02);
}

bool get_combo_must_tap(uint16_t index, combo_t *combo) {
    return (magic_settings_config.combo_config & 0x04);
}

bool get_combo_must_press_in_order(uint16_t combo_index, combo_t *combo) {
    return (magic_settings_config.combo_config & 0x08);
}

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
#ifdef DYNAMIC_COMBOS_ENABLE
    if (index < DYNAMIC_COMBOS_ENTRIES) {
        return dynamic_get_combos_term(index);
    }
#endif
    return magic_settings_config.combo_term;
}

void combo_maigc_settings_update(void) {
    if (magic_settings_config.combo_config & 0x01) {
        combo_enable();
    } else {
        combo_disable();
    }
}

void combo_maigc_settings_reset(void) {
    magic_settings_config.combo_config = 0x09;
    magic_settings_config.combo_term = COMBO_TERM;
    magic_settings_config.combo_hold_term = COMBO_HOLD_TERM;
    combo_maigc_settings_update();
}
#endif