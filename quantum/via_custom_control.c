/* Copyright 2022 zhaqian
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

#include "via_custom_control.h"
#include "via.h"

#if defined(MOUSEKEY_ENABLE)
#include "mousekey.h"
#endif

__attribute__((weak)) bool via_custom_value_command_user(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id = &(data[0]);
    // Return the unhandled state
    *command_id = id_unhandled;
    return false;
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id = &(data[0]);
    uint8_t *channel_id = &(data[1]);
#if defined(VIA_CUSTOM_RGB_MATRIX_ENABLE)
    if (*channel_id == id_custom_rgb_matrix_channel) {
        via_custom_rgb_matrix_command(data, length);
        return;
    }
#endif

#if defined(VIA_CUSTOM_RGB_INDICATORS_ENABLE)
    if (*channel_id == id_custom_rgb_indicators_channel) {
        via_custom_rgb_indicators_command(data, length);
        return;
    }
#endif

#if defined(VIA_CUSTOM_MAGIC_SETTINGS_ENABLE)
    if (*channel_id == id_custom_magic_setting_channel) {
        via_custom_magic_setting_command(data, length);
        return;
    }

    if (*channel_id == id_custom_advanced_magic_setting_channel) {
        via_custom_advanced_magic_setting_command(data, length);
        return;
    }
#endif

#if defined(VIA_CUSTOM_DYNAMIC_TAP_DANCE_ENABLE)
    if (*channel_id == id_custom_dynamic_tap_dance_channel) {
        via_custom_dynamic_tap_dance_command(data, length);
        return;
    }
#endif

#if defined(VIA_CUSTOM_DYNAMIC_COMBOS_ENABLE)
    if (*channel_id == id_custom_dynamic_combos_channel) {
        via_custom_dynamic_combos_command(data, length);
        return;
    }
#endif

#if defined(VIA_CUSTOM_AUTO_SWITCH_LAYERS_ENABLE)
    if (*channel_id == id_custom_auto_switch_layers_channel) {
        via_custom_auto_switch_layers_command(data, length);
        return;
    }
#endif

    if (via_custom_value_command_user(data, length)) {
        return;
    }   
    *command_id = id_unhandled;
    *channel_id = *channel_id;  // force use of variable
}

#if defined(VIA_CUSTOM_RGB_MATRIX_ENABLE)
void via_custom_rgb_matrix_command(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *value_id_and_data = &(data[2]);

    switch (*command_id) {
        case id_custom_set_value: {
            via_custom_rgb_matrix_set_value(value_id_and_data);
            break;
        }
        case id_custom_get_value: {
            via_custom_rgb_matrix_get_value(value_id_and_data);
            break;
        }
        case id_custom_save: {
            via_custom_rgb_matrix_save();
            break;
        }
        default: {
            *command_id = id_unhandled;
            break;
        }
    }
}

void via_custom_rgb_matrix_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
#if defined(RGB_MATRIX_CONTROL_ENABLE)
        case id_rgb_matrix_toggle: {
            switch (*value_data) {
                case 0: {
                    if (value_data[1] == 0) {
                        rgb_matrix_disable();
                    } else {
                        rgb_matrix_enable();
                    }
                    break;
                } 
                case 1: {
                    if (value_data[1] == 0) {
                        key_rgb_disable(true);
                    } else {
                        key_rgb_enable(true);
                    }
                    break;
                }      
                case 2: {
                    if (value_data[1] == 0) {
                        underglow_rgb_disable(true);
                    } else {
                        underglow_rgb_enable(true);
                    }
                    break;
                } 
                case 3: {
                    if (value_data[1] == 0) {
                        logo_rgb_disable(true);
                    } else {
                        logo_rgb_enable(true);
                    }
                    break;
                } 
            }
            break;
        }
#endif
#if (defined(UNDERGLOW_RGB_MATRIX_ENABLE) && !defined(UNDERGLOW_RGB_MATRIX_API_DISABLE))
        case id_underglow_rgb_matrix_brightness: {
            underglow_rgb_matrix_set_hsv(underglow_rgb_matrix_get_hue(), underglow_rgb_matrix_get_sat(), value_data[0], false);
            break;
        }
        case id_underglow_rgb_matrix_effect: {
            underglow_rgb_enable(false);
            underglow_rgb_matrix_set_mode(value_data[0], false);
            break;
        }
        case id_underglow_rgb_matrix_effect_speed: {
            underglow_rgb_matrix_set_speed(value_data[0], false);
            break;
        }
        case id_underglow_rgb_matrix_color: {
            underglow_rgb_matrix_set_hsv(value_data[0], value_data[1], underglow_rgb_matrix_get_val(), false);
            break;
        }
#endif
    }
}

void via_custom_rgb_matrix_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
#if defined(RGB_MATRIX_CONTROL_ENABLE)
        case id_rgb_matrix_toggle: {
           switch (*value_data) {
                case 0: {
                    value_data[1] = rgb_matrix_is_enabled() ? 1 : 0;
                    break;
                } 
                case 1: {
                    value_data[1] = key_rgb_is_enabled() ? 1 : 0;
                    break;
                }      
                case 2: {
                    value_data[1] = underglow_rgb_is_enabled() ? 1 : 0;
                    break;
                } 
                case 3: {
                    value_data[1] = logo_rgb_is_enabled() ? 1 : 0;
                    break;
                } 
            }
            break;
        }
#endif
#if (defined(UNDERGLOW_RGB_MATRIX_ENABLE) && !defined(UNDERGLOW_RGB_MATRIX_API_DISABLE))
        case id_underglow_rgb_matrix_brightness: {
            value_data[0] = underglow_rgb_matrix_get_val();
            break;
        }
        case id_underglow_rgb_matrix_effect: {
            value_data[0] = underglow_rgb_matrix_get_mode();
            break;
        }
        case id_underglow_rgb_matrix_effect_speed: {
            value_data[0] = underglow_rgb_matrix_get_speed();
            break;
        }
        case id_underglow_rgb_matrix_color: {
            value_data[0] = underglow_rgb_matrix_get_hue();
            value_data[1] = underglow_rgb_matrix_get_sat();
            break;
        }
#endif
    }
}

void via_custom_rgb_matrix_save(void) {
#if defined(UNDERGLOW_RGB_MATRIX_ENABLE)
    eeconfig_update_underglow_rgb_matrix();
#endif
}
#endif

#if defined(VIA_CUSTOM_RGB_INDICATORS_ENABLE)
void via_custom_rgb_indicators_command(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *value_id_and_data = &(data[2]);

    switch (*command_id) {
        case id_custom_set_value: {
            via_custom_rgb_indicators_set_value(value_id_and_data);
            break;
        }
        case id_custom_get_value: {
            via_custom_rgb_indicators_get_value(value_id_and_data);
            break;
        }
        case id_custom_save: {
            via_custom_rgb_indicators_save();
            break;
        }
        default: {
            *command_id = id_unhandled;
            break;
        }
    }
}

void via_custom_rgb_indicators_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
#if defined(RGB_MATRIX_CONTROL_ENABLE)
        case id_rgb_indicators_override: {
            set_indicator_rgb_override(value_data[0], true);
            break;
        }
#endif
#if defined(DYNAMIC_RGB_INDICATORS_ENABLE)
        case id_rgb_indicators_brightness: {
            rgb_indicators_set_val(value_data[0], value_data[1], false);
            break;
        }
        case id_rgb_indicators_effect: {
            if (value_data[1] == 0) {
                rgb_indicators_disable(value_data[0], false);
            } else {
                rgb_indicators_enable(value_data[0], false);
                rgb_indicators_set_mode(value_data[0], value_data[1], false);
            }
            break;
        }
        case id_rgb_indicators_color: {
            rgb_indicators_set_hsv(value_data[0], value_data[1], value_data[2], rgb_indicators_get_val(value_data[0]), false);
            break;
        }
        case id_rgb_indicators_led: {
            rgb_indicators_enable_all_led(value_data[0], 0, false);
            rgb_indicators_enable_key_led(value_data[0], 0, false);
            rgb_indicators_enable_underglow_led(value_data[0], 0, false);
            rgb_indicators_enable_logo_led(value_data[0], 0, false);
            switch (value_data[1]) {
                case 0: {
                    rgb_indicators_enable_all_led(value_data[0], 1, false); 
                    break;
                }
                case 1: {
                    rgb_indicators_enable_key_led(value_data[0], 1, false); 
                    break;
                }
                case 2: {
                    rgb_indicators_enable_underglow_led(value_data[0], 1, false); 
                    break;
                }
                case 3: {
                    rgb_indicators_enable_logo_led(value_data[0], 1, false);
                    break;
                }
                default: {
                    rgb_indicators_set_led(value_data[0], value_data[1] - 4, false);
                    break;
                }
            }
            break;
        }
#endif
    }
}

void via_custom_rgb_indicators_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
#if defined(RGB_MATRIX_CONTROL_ENABLE)
        case id_rgb_indicators_override: {
            value_data[0] = indicator_rgb_is_override() ? 1 : 0;
            break;
        }
#endif
#if defined(DYNAMIC_RGB_INDICATORS_ENABLE)
        case id_rgb_indicators_brightness: {
            value_data[1] = rgb_indicators_get_val(value_data[0]);
            break;
        }
        case id_rgb_indicators_effect: {
            if (!is_rgb_indicator_enabled(value_data[0])) {
                value_data[1] = 0;
            } else {
                value_data[1] = rgb_indicators_get_mode(value_data[0]);
            }
            break;
        }
        case id_rgb_indicators_color: {
            value_data[1] = rgb_indicators_get_hue(value_data[0]);
            value_data[2] = rgb_indicators_get_sat(value_data[0]);
            break;
        }
        case id_rgb_indicators_led: {
            if (rgb_indicators_get_all_led(value_data[0])) {
                value_data[1] = 0;
            } else if (rgb_indicators_get_key_led(value_data[0])) {
                value_data[1] = 1;
            } else if (rgb_indicators_get_underglow_led(value_data[0])) {
                value_data[1] = 2;
            } else if (rgb_indicators_get_logo_led(value_data[0])) {
                value_data[1] = 3;
            } else {
                value_data[1] = rgb_indicators_get_led(value_data[0]) + 4;
            }
            break;
        }
#endif
    }
}

void via_custom_rgb_indicators_save(void) {
#if defined(DYNAMIC_RGB_INDICATORS_ENABLE)
    update_dynamic_rgb_indicators();
#endif
}
#endif

#if defined(VIA_CUSTOM_MAGIC_SETTINGS_ENABLE)
void via_custom_magic_setting_command(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *value_id_and_data = &(data[2]);

    switch (*command_id) {
        case id_custom_set_value: {
            via_custom_magic_setting_set_value(value_id_and_data);
            break;
        }
        case id_custom_get_value: {
            via_custom_magic_setting_get_value(value_id_and_data);
            break;
        }
        case id_custom_save: {
            via_custom_magic_setting_save();
            break;
        }
        default: {
            *command_id = id_unhandled;
            break;
        }
    }
}

void via_custom_magic_setting_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case id_magic_nkro: {
            clear_keyboard(); 
            keymap_config.nkro = value_data[0];
            break;
        }
        case id_magic_no_gui: {
            keymap_config.no_gui = value_data[0];
            break;
        }
        case id_magic_capslock_to_control: {
            keymap_config.capslock_to_control = value_data[0];
            break;
        }
        case id_magic_swap_control_capslock: {
            keymap_config.swap_control_capslock = value_data[0];
            break;
        }
        case id_magic_swap_escape_capslock: {
            keymap_config.swap_escape_capslock = value_data[0];
            break;
        }
        case id_magic_swap_lalt_lgui: {
            keymap_config.swap_lalt_lgui = value_data[0];
            break;
        }
        case id_magic_swap_ralt_rgui: {
            keymap_config.swap_ralt_rgui = value_data[0];
            break;
        }
        case id_magic_swap_lctl_lgui: {
            keymap_config.swap_lctl_lgui = value_data[0];
            break;
        }
        case id_magic_swap_rctl_rgui: {
            keymap_config.swap_rctl_rgui = value_data[0];
            break;
        }
        case id_magic_swap_grave_esc: {
            keymap_config.swap_grave_esc = value_data[0];
            break;
        }
        case id_magic_swap_backslash_backspace: {
            keymap_config.swap_backslash_backspace = value_data[0];
            break;
        }
        case id_magic_oneshot_enable: {
            keymap_config.oneshot_enable = value_data[0];
            break;
        }
        case id_magic_autocorrect_enable: {
            keymap_config.autocorrect_enable = value_data[0];
            break;
        }
        default: {
            break;
        }
    }
    clear_keyboard();
}

void via_custom_magic_setting_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case id_magic_nkro: {
            value_data[0] = keymap_config.nkro;
            break;
        }
        case id_magic_no_gui: {
            value_data[0] =  keymap_config.no_gui;
            break;
        }
        case id_magic_capslock_to_control: {
            value_data[0] = keymap_config.capslock_to_control;
            break;
        }
        case id_magic_swap_control_capslock: {
            value_data[0] = keymap_config.swap_control_capslock;
            break;
        }
        case id_magic_swap_escape_capslock: {
            value_data[0] = keymap_config.swap_escape_capslock;
            break;
        }
        case id_magic_swap_lalt_lgui: {
            value_data[0] = keymap_config.swap_lalt_lgui;
            break;
        }
        case id_magic_swap_ralt_rgui: {
            value_data[0] = keymap_config.swap_ralt_rgui;
            break;
        }
        case id_magic_swap_lctl_lgui: {
            value_data[0] = keymap_config.swap_lctl_lgui;
            break;
        }
        case id_magic_swap_rctl_rgui: {
            value_data[0] = keymap_config.swap_rctl_rgui;
            break;
        }
        case id_magic_swap_grave_esc: {
            value_data[0] = keymap_config.swap_grave_esc;
            break;
        }
        case id_magic_swap_backslash_backspace: {
            value_data[0] = keymap_config.swap_backslash_backspace;
            break;
        }
        case id_magic_oneshot_enable: {
            value_data[0] = keymap_config.oneshot_enable;
            break;
        }
        case id_magic_autocorrect_enable: {
            value_data[0] = keymap_config.autocorrect_enable;
            break;
        }
        default: {
            break;
        }
    }
}

void via_custom_magic_setting_save(void) {
    eeconfig_update_keymap(keymap_config.raw);
}

void via_custom_advanced_magic_setting_command(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *value_id_and_data = &(data[2]);

    switch (*command_id) {
        case id_custom_set_value: {
            via_custom_advanced_magic_setting_set_value(value_id_and_data);
            break;
        }
        case id_custom_get_value: {
            via_custom_advanced_magic_setting_get_value(value_id_and_data);
            break;
        }
        case id_custom_save: {
            via_custom_advanced_magic_setting_save();
            break;
        }
        default: {
            *command_id = id_unhandled;
            break;
        }
    }
}

void via_custom_advanced_magic_setting_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case id_advanced_magic_settings_reset: {
            magic_settings_reset();
            break;
        }
        case id_advanced_magic_debounce: {
            clear_keyboard();
            MAGIC_SETTINGS_SET(debounce, value_data[0]);
            break;
        }
#if defined(MOUSEKEY_ENABLE)
        case id_advanced_magic_mk_delay: {
            MAGIC_SETTINGS_SET(mk_delay, value_data[0]);
            mk_delay = MAGIC_SETTINGS_GET(mk_delay);
            break; 
        }
        case id_advanced_magic_mk_interval: {
            MAGIC_SETTINGS_SET(mk_interval, value_data[0]);
            mk_interval = MAGIC_SETTINGS_GET(mk_interval);
            break; 
        }
        case id_advanced_magic_mk_move_delta: {
            MAGIC_SETTINGS_SET(mk_move_delta, value_data[0]);
            break; 
        }
        case id_advanced_magic_mk_max_speed: {
            MAGIC_SETTINGS_SET(mk_max_speed, value_data[0]);
            mk_max_speed = MAGIC_SETTINGS_GET(mk_max_speed);
            break; 
        }
        case id_advanced_magic_mk_time_to_max: {
            MAGIC_SETTINGS_SET(mk_time_to_max, value_data[0]);
            mk_time_to_max = MAGIC_SETTINGS_GET(mk_time_to_max);
            break; 
        }
        case id_advanced_magic_mk_wheel_delay: {
            MAGIC_SETTINGS_SET(mk_wheel_delay, value_data[0]);
            mk_wheel_delay = MAGIC_SETTINGS_GET(mk_wheel_delay);
            break; 
        }
        case id_advanced_magic_mk_wheel_interval: {
            MAGIC_SETTINGS_SET(mk_wheel_interval, value_data[0]);
            mk_wheel_interval = MAGIC_SETTINGS_GET(mk_wheel_interval);
            break; 
        }
        case id_advanced_magic_mk_wheel_max_speed: {
            MAGIC_SETTINGS_SET(mk_wheel_max_speed, value_data[0]);
            mk_wheel_max_speed = MAGIC_SETTINGS_GET(mk_wheel_max_speed);
            break; 
        }
        case id_advanced_magic_mk_wheel_time_to_max: {
            MAGIC_SETTINGS_SET(mk_wheel_time_to_max, value_data[0]);
            mk_wheel_time_to_max = MAGIC_SETTINGS_GET(mk_wheel_time_to_max);
            break; 
        }
#endif
        case id_advanced_magic_grave_esc_override: {
            uint8_t tmp = MAGIC_SETTINGS_GET(grave_esc_override) & (~(0x1 << value_data[0]));
            tmp |= value_data[1] << value_data[0];
            MAGIC_SETTINGS_SET(grave_esc_override, tmp);
            break;
        }
#if !defined(NO_ACTION_TAPPING)
        case id_advanced_magic_tap_hold_config: {
            uint8_t tmp = MAGIC_SETTINGS_GET(tap_hold_config) & (~(0x1 << value_data[0]));
            tmp |= value_data[1] << value_data[0];
            MAGIC_SETTINGS_SET(tap_hold_config, tmp);
            break;
        }
        case id_advanced_magic_tapping_toggle_times: {
            MAGIC_SETTINGS_SET(tapping_toggle_times, value_data[0]);
            break;
        }
        case id_advanced_magic_tapping_term: {
            MAGIC_SETTINGS_SET(tapping_term, (value_data[0] << 8 | value_data[1]));
            break;
        }
        case id_advanced_magic_quick_tap_term: {
            MAGIC_SETTINGS_SET(quick_tap_term, (value_data[0] << 8 | value_data[1]));
            break;
        }
        case id_advanced_magic_tap_code_delay: {
            MAGIC_SETTINGS_SET(tap_code_delay, (value_data[0] << 8 | value_data[1]));
            break;
        }
        case id_advanced_magic_tap_hold_caps_delay: {
            MAGIC_SETTINGS_SET(tap_hold_caps_delay, (value_data[0] << 8 | value_data[1]));
            break;
        }
#endif
#if defined(AUTO_SHIFT_ENABLE)
        case id_advanced_magic_auto_shift_config: {
            uint8_t tmp = MAGIC_SETTINGS_GET(auto_shift_config) & (~(0x1 << value_data[0]));
            tmp |= value_data[1] << value_data[0];
            MAGIC_SETTINGS_SET(auto_shift_config, tmp);
            break;
        }
        case id_advanced_magic_auto_shift_timeout: {
            MAGIC_SETTINGS_SET(auto_shift_timeout, (value_data[0] << 8 | value_data[1]));
            break;
        }
#endif
#if !defined(NO_ACTION_ONESHOT)
        case id_advanced_magic_oneshot_tap_toggle: {
            MAGIC_SETTINGS_SET(oneshot_tap_toggle, value_data[0]);
            break;
        }
        case id_advanced_magic_oneshot_timeout: {
            MAGIC_SETTINGS_SET(oneshot_timeout, (value_data[0] << 8 | value_data[1]));
            break;
        }
#endif
#if defined(COMBO_ENABLE)
        case id_advanced_magic_combo_config: {
            uint8_t tmp = MAGIC_SETTINGS_GET(combo_config) & (~(0x1 << value_data[0]));
            tmp |= value_data[1] << value_data[0];
            MAGIC_SETTINGS_SET(combo_config, tmp);
            if (value_data[0] == 0) {
                combo_maigc_settings_update();
            }
            break;
        }
        case id_advanced_magic_combo_term: {
            MAGIC_SETTINGS_SET(combo_term, (value_data[0] << 8 | value_data[1]));
            break;
        }
        case id_advanced_magic_combo_hold_term: {
            MAGIC_SETTINGS_SET(combo_hold_term, (value_data[0] << 8 | value_data[1]));
            break;
        }
#endif
        default: {
            break;
        }
    }
}

void via_custom_advanced_magic_setting_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case id_advanced_magic_settings_reset: {
            value_data[0] = 0;
            break;
        }
        case id_advanced_magic_debounce: {
            value_data[0] = MAGIC_SETTINGS_GET(debounce);
            break;
        }
#if defined(MOUSEKEY_ENABLE)
        case id_advanced_magic_mk_delay: {
            value_data[0] = MAGIC_SETTINGS_GET(mk_delay);
            break; 
        }
        case id_advanced_magic_mk_interval: {
            value_data[0] = MAGIC_SETTINGS_GET(mk_interval);
            break; 
        }
        case id_advanced_magic_mk_move_delta: {
            value_data[0] = MAGIC_SETTINGS_GET(mk_move_delta);
            break; 
        }
        case id_advanced_magic_mk_max_speed: {
            value_data[0] = MAGIC_SETTINGS_GET(mk_max_speed);
            break; 
        }
        case id_advanced_magic_mk_time_to_max: {
            value_data[0] = MAGIC_SETTINGS_GET(mk_time_to_max);
            break; 
        }
        case id_advanced_magic_mk_wheel_delay: {
            value_data[0] = MAGIC_SETTINGS_GET(mk_wheel_delay);
            break; 
        }
        case id_advanced_magic_mk_wheel_interval: {
            value_data[0] = MAGIC_SETTINGS_GET(mk_wheel_interval);
            break; 
        }
        case id_advanced_magic_mk_wheel_max_speed: {
            value_data[0] = MAGIC_SETTINGS_GET(mk_wheel_max_speed);
            break; 
        }
        case id_advanced_magic_mk_wheel_time_to_max: {
            value_data[0] = MAGIC_SETTINGS_GET(mk_wheel_time_to_max);
            break; 
        }
#endif
        case id_advanced_magic_grave_esc_override: {
            value_data[1] = MAGIC_SETTINGS_GET(grave_esc_override) & (0x1 << value_data[0]) ? 1 : 0;
            break;
        }
#if !defined(NO_ACTION_TAPPING)
        case id_advanced_magic_tap_hold_config: {
            value_data[1] = MAGIC_SETTINGS_GET(tap_hold_config) & (0x1 << value_data[0]) ? 1 : 0;
            break;
        }
        case id_advanced_magic_tapping_toggle_times: {
            value_data[0] = MAGIC_SETTINGS_GET(tapping_toggle_times);
            break;
        }
        case id_advanced_magic_tapping_term: {
            value_data[0] = MAGIC_SETTINGS_GET(tapping_term) >> 8;
            value_data[1] = MAGIC_SETTINGS_GET(tapping_term) & 0xFF;
            break;
        }
        case id_advanced_magic_quick_tap_term: {
            value_data[0] = MAGIC_SETTINGS_GET(quick_tap_term) >> 8;
            value_data[1] = MAGIC_SETTINGS_GET(quick_tap_term) & 0xFF;
            break;
        }
        case id_advanced_magic_tap_code_delay: {
            value_data[0] = MAGIC_SETTINGS_GET(tap_code_delay) >> 8;
            value_data[1] = MAGIC_SETTINGS_GET(tap_code_delay) & 0xFF;
            break;
        }
        case id_advanced_magic_tap_hold_caps_delay: {
            value_data[0] = MAGIC_SETTINGS_GET(tap_hold_caps_delay) >> 8;
            value_data[1] = MAGIC_SETTINGS_GET(tap_hold_caps_delay) & 0xFF;
            break;
        }
#endif
#if defined(AUTO_SHIFT_ENABLE)
        case id_advanced_magic_auto_shift_config: {
            value_data[1] = MAGIC_SETTINGS_GET(auto_shift_config) & (0x1 << value_data[0]) ? 1 : 0;
            break;
        }
        case id_advanced_magic_auto_shift_timeout: {
            value_data[0] = MAGIC_SETTINGS_GET(auto_shift_timeout) >> 8;
            value_data[1] = MAGIC_SETTINGS_GET(auto_shift_timeout) & 0xFF;
            break;
        }
#endif
#if !defined(NO_ACTION_ONESHOT)
        case id_advanced_magic_oneshot_tap_toggle: {
            value_data[0] = MAGIC_SETTINGS_GET(oneshot_tap_toggle);
            break;
        }
        case id_advanced_magic_oneshot_timeout: {
            value_data[0] = MAGIC_SETTINGS_GET(oneshot_timeout) >> 8;
            value_data[1] = MAGIC_SETTINGS_GET(oneshot_timeout) & 0xFF;
            break;
        }
#endif
#if defined(COMBO_ENABLE)
        case id_advanced_magic_combo_config: {
            value_data[1] = MAGIC_SETTINGS_GET(combo_config) & (0x1 << value_data[0]) ? 1 : 0;
            break;
        }
        case id_advanced_magic_combo_term: {
            value_data[0] = MAGIC_SETTINGS_GET(combo_term) >> 8;
            value_data[1] = MAGIC_SETTINGS_GET(combo_term) & 0xFF;
            break;
        }
        case id_advanced_magic_combo_hold_term: {
            value_data[0] = MAGIC_SETTINGS_GET(combo_hold_term) >> 8;
            value_data[1] = MAGIC_SETTINGS_GET(combo_hold_term) & 0xFF;
            break;
        }
#endif
        default: {
            break;
        }
    }
}

void via_custom_advanced_magic_setting_save(void) {
    eeconfig_update_magic_settings();
}
#endif

#if defined(VIA_CUSTOM_DYNAMIC_TAP_DANCE_ENABLE)
void via_custom_dynamic_tap_dance_command(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *value_id_and_data = &(data[2]);

    switch (*command_id) {
        case id_custom_set_value: {
            via_custom_dynamic_tap_dance_set_value(value_id_and_data);
            break;
        }
        case id_custom_get_value: {
            via_custom_dynamic_tap_dance_get_value(value_id_and_data);
            break;
        }
        case id_custom_save: {
            via_custom_dynamic_tap_dance_save();
            break;
        }
        default: {
            *command_id = id_unhandled;
            break;
        }
    }
}

void via_custom_dynamic_tap_dance_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case id_dynamic_tap_dance_reset: {
            dynamic_tap_dance_reset();
            break;
        }
        case id_dynamic_tap_dance_on_tap_keycode: {
            uint16_t keycode = KC_NO;
            keycode = ((value_data[1] << 8) | value_data[2]);
            dynamic_set_tap_dance_keycode(value_data[0], 0, keycode);
            break;
        }
        case id_dynamic_tap_dance_on_hold_keycode: {
            uint16_t keycode = KC_NO;
            keycode = ((value_data[1] << 8) | value_data[2]);
            dynamic_set_tap_dance_keycode(value_data[0], 1, keycode);
            break;
        }
        case id_dynamic_tap_dance_on_double_tap_keycode: {
            uint16_t keycode = KC_NO;
            keycode = ((value_data[1] << 8) | value_data[2]);
            dynamic_set_tap_dance_keycode(value_data[0], 2, keycode);
            break;
        }
        case id_dynamic_tap_dance_on_tap_hold_keycode: {
            uint16_t keycode = KC_NO;
            keycode = ((value_data[1] << 8) | value_data[2]);
            dynamic_set_tap_dance_keycode(value_data[0], 3, keycode);
            break;
        }
        case id_dynamic_tap_dance_tapping_term: {
            uint16_t term = 0;
            term = ((value_data[1] << 8) | value_data[2]);
            dynamic_set_tap_dance_term(value_data[0], term);
            break;
        }
        default: {
            break;
        }
    }
}

void via_custom_dynamic_tap_dance_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case id_dynamic_tap_dance_reset: {
            value_data[0] = 0;
            break;
        }
        case id_dynamic_tap_dance_on_tap_keycode: {
            uint16_t keycode = dynamic_get_tap_dance_keycode(value_data[0], 0);
            value_data[1] = keycode >> 8;
            value_data[2] = keycode & 0xFF;
            break;
        }
        case id_dynamic_tap_dance_on_hold_keycode: {
            uint16_t keycode = dynamic_get_tap_dance_keycode(value_data[0], 1);
            value_data[1] = keycode >> 8;
            value_data[2] = keycode & 0xFF;
            break;
        }
        case id_dynamic_tap_dance_on_double_tap_keycode: {
            uint16_t keycode = dynamic_get_tap_dance_keycode(value_data[0], 2);
            value_data[1] = keycode >> 8;
            value_data[2] = keycode & 0xFF;
            break;
        }
        case id_dynamic_tap_dance_on_tap_hold_keycode: {
            uint16_t keycode = dynamic_get_tap_dance_keycode(value_data[0], 3);
            value_data[1] = keycode >> 8;
            value_data[2] = keycode & 0xFF;
            break;
        }
        case id_dynamic_tap_dance_tapping_term: {
            uint16_t term = dynamic_get_tap_dance_term(value_data[0]);
            value_data[1] = term >> 8;
            value_data[2] = term & 0xFF;
            break;
        }
        default: {
            break;
        }
    }
}

void via_custom_dynamic_tap_dance_save(void) {
    // No action is required
}
#endif

#if defined(VIA_CUSTOM_DYNAMIC_COMBOS_ENABLE)
void via_custom_dynamic_combos_command(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *value_id_and_data = &(data[2]);

    switch (*command_id) {
        case id_custom_set_value: {
            via_custom_dynamic_combos_set_value(value_id_and_data);
            break;
        }
        case id_custom_get_value: {
            via_custom_dynamic_combos_get_value(value_id_and_data);
            break;
        }
        case id_custom_save: {
            via_custom_dynamic_combos_save();
            break;
        }
        default: {
            *command_id = id_unhandled;
            break;
        }
    }
}

void via_custom_dynamic_combos_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case id_dynamic_combos_reset: {
            dynamic_combos_reset();
            break;
        }
        case id_dynamic_combos_keys: {
            uint16_t keycode = KC_NO;
            keycode = ((value_data[2] << 8) | value_data[3]);
            dynamic_set_combos_keycode(value_data[0], value_data[1], keycode);
            dynamic_combos_update(value_data[0]);
            break;
        }
        case id_dynamic_combos_keycode: {
            uint16_t keycode = KC_NO;
            keycode = ((value_data[1] << 8) | value_data[2]);
            dynamic_set_combos_keycode(value_data[0], 4, keycode);
            dynamic_combos_update(value_data[0]);
            break;
        }
        case id_dynamic_combos_combo_term: {
            uint16_t term = 0;
            term = ((value_data[1] << 8) | value_data[2]);
            dynamic_set_combos_term(value_data[0], term);
            break;
        }
        default: {
            break;
        }
    }
}

void via_custom_dynamic_combos_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case id_dynamic_combos_reset: {
            value_data[0] = 0;
            break;
        }
        case id_dynamic_combos_keys: {
            uint16_t keycode = dynamic_get_combos_keycode(value_data[0], value_data[1]);
            value_data[2] = keycode >> 8;
            value_data[3] = keycode & 0xFF;
            break;
        }
        case id_dynamic_combos_keycode: {
            uint16_t keycode = dynamic_get_combos_keycode(value_data[0], 4);
            value_data[1] = keycode >> 8;
            value_data[2] = keycode & 0xFF;
            break;
        }
        case id_dynamic_combos_combo_term: {
            uint16_t term = dynamic_get_combos_term(value_data[0]);
            value_data[1] = term >> 8;
            value_data[2] = term & 0xFF;
            break;
        }
        default: {
            break;
        }
    }
}

void via_custom_dynamic_combos_save(void) {
    // No action is required
}
#endif

#if defined(VIA_CUSTOM_AUTO_SWITCH_LAYERS_ENABLE)
void via_custom_auto_switch_layers_command(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *value_id_and_data = &(data[2]);

    switch (*command_id) {
        case id_custom_set_value: {
            via_custom_auto_switch_layers_set_value(value_id_and_data);
            break;
        }
        case id_custom_get_value: {
            via_custom_auto_switch_layers_get_value(value_id_and_data);
            break;
        }
        case id_custom_save: {
            via_custom_auto_switch_layers_save();
            break;
        }
        default: {
            *command_id = id_unhandled;
            break;
        }
    }
}

void via_custom_auto_switch_layers_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case id_auto_switch_layers_reset: {
            // todo
            break;
        }
        case id_auto_switch_layers_config: {
            auto_switch_layers_set_config(value_data[0], value_data[1], false);
            break;
        }
        case id_auto_switch_layers_layer: {
            auto_switch_layers_set_layer(value_data[0], value_data[1], false);
            break;
        }
        default: {
            break;
        }
    }
}

void via_custom_auto_switch_layers_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case id_auto_switch_layers_reset: {
            value_data[0] = 0;
            break;
        }
        case id_auto_switch_layers_config: {
            value_data[1] = auto_switch_layers_get_config(value_data[0]);
            break;
        }
        case id_auto_switch_layers_layer: {
            value_data[1] = auto_switch_layers_get_layer(value_data[0]);
            break;
        }
        default: {
            break;
        }
    }
}

void via_custom_auto_switch_layers_save(void) {
    eeconfig_update_auto_switch_layers();
}
#endif