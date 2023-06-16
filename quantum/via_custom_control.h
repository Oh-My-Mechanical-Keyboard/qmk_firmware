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

#pragma once

#include "quantum.h"

#if defined(RGB_MATRIX_CONTROL_ENABLE) || defined(UNDERGLOW_RGB_MATRIX_ENABLE)
#    define VIA_CUSTOM_RGB_MATRIX_ENABLE
#endif

#if defined(DYNAMIC_RGB_INDICATORS_ENABLE)
#    define VIA_CUSTOM_RGB_INDICATORS_ENABLE
#endif

#if defined(MAGIC_SETTINGS_ENABLE)
#    define VIA_CUSTOM_MAGIC_SETTINGS_ENABLE
#endif

#if defined(DYNAMIC_TAP_DANCE_ENABLE)
#    define VIA_CUSTOM_DYNAMIC_TAP_DANCE_ENABLE
#endif

#if defined(DYNAMIC_COMBOS_ENABLE)
#    define VIA_CUSTOM_DYNAMIC_COMBOS_ENABLE
#endif

#if defined(AUTO_SWITCH_LAYERS_ENABLE)
#    define VIA_CUSTOM_AUTO_SWITCH_LAYERS_ENABLE
#endif

enum via_custom_channel_id {
    id_custom_rgb_matrix_channel             = 5,
    id_custom_rgb_indicators_channel         = 6,
    id_custom_magic_setting_channel          = 7,
    id_custom_advanced_magic_setting_channel = 8,
    id_custom_dynamic_tap_dance_channel      = 9,
    id_custom_dynamic_combos_channel         = 10,
    id_custom_auto_switch_layers_channel     = 11,
};

enum via_custom_rgb_matrix_value {
    id_rgb_matrix_toggle                 = 1, // rgb matrix control
    id_underglow_rgb_matrix_brightness   = 2, // underglow rgb matrix brightness
    id_underglow_rgb_matrix_effect       = 3, // underglow rgb matrix effect
    id_underglow_rgb_matrix_effect_speed = 4, // underglow rgb matrix speed
    id_underglow_rgb_matrix_color        = 5, // underglow rgb matrix color
};

enum via_custom_rgb_indicators_value {
    id_rgb_indicators_override      = 1, // rgb indicator override
    // rgb indicator {num lock, caps lock, scroll lock}
    id_rgb_indicators_brightness    = 2, // rgb indicator brightness
    id_rgb_indicators_effect        = 3, // rgb indicator effect
    id_rgb_indicators_color         = 4, // rgb indicator color
    id_rgb_indicators_led           = 5, // rgb indicator led
};

enum via_custom_magic_setting_value {
    id_magic_nkro                     = 1,
    id_magic_no_gui                   = 2,
    id_magic_capslock_to_control      = 3,
    id_magic_swap_control_capslock    = 4,
    id_magic_swap_escape_capslock     = 5,
    id_magic_swap_lalt_lgui           = 6,
    id_magic_swap_ralt_rgui           = 7,
    id_magic_swap_lctl_lgui           = 8,
    id_magic_swap_rctl_rgui           = 9,
    id_magic_swap_grave_esc           = 10,
    id_magic_swap_backslash_backspace = 11,
    id_magic_oneshot_enable           = 12,
    id_magic_autocorrect_enable       = 13,
};

enum via_custom_advanced_magic_setting_value {
    id_advanced_magic_settings_reset            = 0,
    id_advanced_magic_debounce                  = 1,
    id_advanced_magic_mk_delay                  = 2,
    id_advanced_magic_mk_interval               = 3,
    id_advanced_magic_mk_move_delta             = 4,
    id_advanced_magic_mk_max_speed              = 5,
    id_advanced_magic_mk_time_to_max            = 6,
    id_advanced_magic_mk_wheel_delay            = 7,
    id_advanced_magic_mk_wheel_interval         = 8,
    id_advanced_magic_mk_wheel_max_speed        = 9,
    id_advanced_magic_mk_wheel_time_to_max      = 10,
    id_advanced_magic_grave_esc_override        = 11,
    id_advanced_magic_tap_hold_config           = 12,
    id_advanced_magic_tapping_toggle_times      = 13,
    id_advanced_magic_tapping_term              = 14,
    id_advanced_magic_quick_tap_term            = 15,
    id_advanced_magic_tap_code_delay            = 16,
    id_advanced_magic_tap_hold_caps_delay       = 17,
    id_advanced_magic_auto_shift_config         = 18,
    id_advanced_magic_auto_shift_timeout        = 19,
    id_advanced_magic_oneshot_tap_toggle        = 20,
    id_advanced_magic_oneshot_timeout           = 21,
    id_advanced_magic_combo_config              = 22,
    id_advanced_magic_combo_term                = 23,
    id_advanced_magic_combo_hold_term           = 24,
};

enum via_custom_dynamic_tap_dance_value {
    id_dynamic_tap_dance_reset                   = 0,
    id_dynamic_tap_dance_on_tap_keycode          = 1,
    id_dynamic_tap_dance_on_hold_keycode         = 2,
    id_dynamic_tap_dance_on_double_tap_keycode   = 3,
    id_dynamic_tap_dance_on_tap_hold_keycode     = 4,
    id_dynamic_tap_dance_tapping_term            = 5,
};

enum via_custom_dynamic_combos_value {
    id_dynamic_combos_reset                      = 0,
    id_dynamic_combos_keys                       = 1,
    id_dynamic_combos_keycode                    = 2,
    id_dynamic_combos_combo_term                 = 3,
};

enum via_custom_auto_switch_layers {
    id_auto_switch_layers_reset                  = 0,
    id_auto_switch_layers_config                 = 1,
    id_auto_switch_layers_layer                  = 2,
};

#if defined(VIA_CUSTOM_RGB_MATRIX_ENABLE)
void via_custom_rgb_matrix_command(uint8_t *data, uint8_t length);
void via_custom_rgb_matrix_set_value(uint8_t *data);
void via_custom_rgb_matrix_get_value(uint8_t *data);
void via_custom_rgb_matrix_save(void);
#endif

#if defined(VIA_CUSTOM_RGB_INDICATORS_ENABLE)
void via_custom_rgb_indicators_command(uint8_t *data, uint8_t length);
void via_custom_rgb_indicators_set_value(uint8_t *data);
void via_custom_rgb_indicators_get_value(uint8_t *data);
void via_custom_rgb_indicators_save(void);
#endif

#if defined(VIA_CUSTOM_MAGIC_SETTINGS_ENABLE)
void via_custom_magic_setting_command(uint8_t *data, uint8_t length);
void via_custom_magic_setting_set_value(uint8_t *data);
void via_custom_magic_setting_get_value(uint8_t *data);
void via_custom_magic_setting_save(void);

void via_custom_advanced_magic_setting_command(uint8_t *data, uint8_t length);
void via_custom_advanced_magic_setting_set_value(uint8_t *data);
void via_custom_advanced_magic_setting_get_value(uint8_t *data);
void via_custom_advanced_magic_setting_save(void);
#endif

#if defined(VIA_CUSTOM_DYNAMIC_TAP_DANCE_ENABLE)
void via_custom_dynamic_tap_dance_command(uint8_t *data, uint8_t length);
void via_custom_dynamic_tap_dance_set_value(uint8_t *data);
void via_custom_dynamic_tap_dance_get_value(uint8_t *data);
void via_custom_dynamic_tap_dance_save(void);
#endif

#if defined(VIA_CUSTOM_DYNAMIC_COMBOS_ENABLE)
void via_custom_dynamic_combos_command(uint8_t *data, uint8_t length);
void via_custom_dynamic_combos_set_value(uint8_t *data);
void via_custom_dynamic_combos_get_value(uint8_t *data);
void via_custom_dynamic_combos_save(void);
#endif

#if defined(VIA_CUSTOM_AUTO_SWITCH_LAYERS_ENABLE)
void via_custom_auto_switch_layers_command(uint8_t *data, uint8_t length);
void via_custom_auto_switch_layers_set_value(uint8_t *data);
void via_custom_auto_switch_layers_get_value(uint8_t *data);
void via_custom_auto_switch_layers_save(void);
#endif