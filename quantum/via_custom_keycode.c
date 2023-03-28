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

#include "quantum.h"
#include "via_custom_keycode.h"

bool process_via_custom_keycode(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef AUTO_SWITCH_LAYERS_ENABLE
        case WINDOWS_FN_VKEY: {
            action_t action;
            action.code = ACTION_LAYER_MOMENTARY(system_layers.windows_fn_layer);
            process_action(record, action);
            return false;
        }
        case MACOS_FN_VKEY: {
            action_t action;
            action.code = ACTION_LAYER_MOMENTARY(system_layers.macos_fn_layer);
            process_action(record, action);
            return false;
        }
#endif
#ifdef RADIAL_CONTROLLER_ENABLE
        case RD_BUT: {
            if (record->event.pressed) {
                radial_controller_button_update(true);
            } else {
                radial_controller_button_update(false);
            }
            return false;
        }
        case RD_L: {
            if (record->event.pressed) {
                radial_controller_dial_update(false, false);
            }
            return false;
        }
        case RD_R: {
            if (record->event.pressed) {
                radial_controller_dial_update(true, false);
            }
            return false;
        }
        case RD_LC: {
            if (record->event.pressed) {
                radial_controller_dial_update(false, true);
            } else {
                radial_controller_dial_finished();
            }
            return false;
        }
        case RD_RC: {
            if (record->event.pressed) {
                radial_controller_dial_update(true, true);
            } else {
                radial_controller_dial_finished();
            }
            return false;
        }
#endif

#ifdef RGB_MATRIX_CONTROL_ENABLE
#ifndef RGB_MATRIX_CONTROL_SWITCH_ENABLE
        case UG_R_T: {
            if (record->event.pressed) {
                underglow_rgb_toggle();
            }
            return false;
        }
        case K_R_T: {
            if (record->event.pressed) {
                key_rgb_toggle();
            }
            return false;
        }
#ifdef LOGO_RGB_CONTROL_ENABLE
        case L_R_T: {
            if (record->event.pressed) {
                logo_rgb_toggle();
            }
            return false;
        }
#endif
#else
        case R_C_SW: {
            if (record->event.pressed) {
                rgb_matrix_control_switch();
            }
            return false;
        }
#endif
        case IND_ON_TOG: {
            if (record->event.pressed) {
                indicator_rgb_override_toggle();
            }
            return false;     
        }
#endif

#ifdef UNDERGLOW_RGB_MATRIX_ENABLE
        case UG_R_MS: {
            if (record->event.pressed) {
                underglow_rgb_mode_sync();
            }
            return false;
        }
        case UG_R_MF: {
            if (record->event.pressed) {
                underglow_rgb_mode_step();
            }
            return false;
        }
        case UG_R_MR: {
            if (record->event.pressed) {
                underglow_rgb_mode_step_reverse();
            }
            return false;
        }
#ifndef UNDERGLOW_RGB_MATRIX_API_DISABLE
        case UG_R_HI: {
            if (record->event.pressed) {
                underglow_rgb_matrix_increase_hue();
            }
            return false;
        }
        case UG_R_HD: {
            if (record->event.pressed) {
                underglow_rgb_matrix_decrease_hue();
            }
            return false;
        }
        case UG_R_SI: {
            if (record->event.pressed) {
                underglow_rgb_matrix_increase_sat();
            }
            return false;
        }
        case UG_R_SD: {
            if (record->event.pressed) {
                underglow_rgb_matrix_decrease_sat();
            }
            return false;
        }
        case UG_R_VI: {
            if (record->event.pressed) {
                underglow_rgb_matrix_increase_val();
            }
            return false;
        }
        case UG_R_VD: {
            if (record->event.pressed) {
                underglow_rgb_matrix_decrease_val();
            }
            return false;
        }
        case UG_R_SPI: {
            if (record->event.pressed) {
                underglow_rgb_matrix_increase_speed();
            }
            return false;
        }
        case UG_R_SPD: {
            if (record->event.pressed) {
                underglow_rgb_matrix_decrease_speed();
            }
            return false;
        }
#endif
#endif

#if defined(RGB_INDICATORS_ENABLE) && !defined(DYNAMIC_RGB_INDICATORS_ENABLE)
        case RGB_IND_TOG:
            if (record->event.pressed) {
                rgb_indicators_toggle();
            }
            return false;
        case RGB_IND_MF:
            if (record->event.pressed) {
                rgb_indicators_mode_step();
            }
            return false;
        case RGB_IND_MR:
            if (record->event.pressed) {
                rgb_indicators_mode_step_reverse();
            }
            return false;
#endif

    }
    return true;
}
