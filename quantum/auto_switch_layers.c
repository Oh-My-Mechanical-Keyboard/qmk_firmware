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

#include "auto_switch_layers.h"
#include "os_detection.h"
#include "eeprom.h"

system_layers_t system_layers;

#ifndef DEFAULT_WINDOWS_LAYER
#    define DEFAULT_WINDOWS_LAYER 0
#endif

#ifndef DEFAULT_MACOS_LAYER
#    define DEFAULT_MACOS_LAYER 2
#endif

#ifndef DEFAULT_WINDOWS_FN_KEY_POS
#    define DEFAULT_WINDOWS_FN_KEY_POS {0, 0}
#endif

#ifndef DEFAULT_MACOS_FN_KEY_POS
#    define DEFAULT_MACOS_FN_KEY_POS {0, 0}
#endif

static keypos_t system_fn_key_pos[] = {DEFAULT_WINDOWS_FN_KEY_POS, DEFAULT_MACOS_FN_KEY_POS};

EECONFIG_DEBOUNCE_HELPER(auto_switch_layers, EECONFIG_AUTO_SWITCH_LAYERS, system_layers);

void eeconfig_update_auto_switch_layers(void) {
    eeconfig_flush_auto_switch_layers(true);
}

static void eeconfig_update_auto_switch_layers_default(void) {
    system_layers.config = 0x80;
    system_layers.windows_layer = DEFAULT_WINDOWS_LAYER;
    system_layers.windows_fn_layer = DEFAULT_WINDOWS_FN_LAYER;
    system_layers.macos_layer = DEFAULT_MACOS_LAYER;
    system_layers.macos_fn_layer = DEFAULT_MACOS_FN_LAYER;
    eeconfig_update_auto_switch_layers();
};

void auto_switch_layers_init(void) {
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
        eeconfig_update_auto_switch_layers_default();
    }
    eeconfig_init_auto_switch_layers();

    if (!CUSTOM_AUTO_SWITCH_LAYERS_EECONFIG_FLAG) {
        eeconfig_update_auto_switch_layers_default();
    }
    // need time to guess
    // auto_switch_layers_update(); 
}

void auto_switch_layers_update(void) {
    os_variant_t os = detected_host_os();
    switch (os) {
        case OS_WINDOWS: {
            default_layer_set(0x01<<system_layers.windows_layer);
            if (CUSTOM_AUTO_SWITCH_LAYERS_UPDATE_FN_KEYCODE) {
                dynamic_keymap_set_keycode(system_layers.windows_layer, system_fn_key_pos[0].row, system_fn_key_pos[0].col, ASL_WIN_FN_KEY);
            }
            break;
        }
        case OS_MACOS: {
            default_layer_set(0x01<<system_layers.macos_layer);
            if (CUSTOM_AUTO_SWITCH_LAYERS_UPDATE_FN_KEYCODE) {
                dynamic_keymap_set_keycode(system_layers.macos_layer, system_fn_key_pos[1].row, system_fn_key_pos[1].col, ASL_MAC_FN_KEY);
            }
            break;
        }
        default: {
            default_layer_set(0x01);
            break;
        }
    }
}

bool os_detection_update(os_variant_t os) {
    if (CUSTOM_AUTO_SWITCH_LAYERS_ENABLE) {
        auto_switch_layers_update();
    }
    return os_detection_update_kb(os);
}

void auto_switch_layers_set_config(uint8_t index, uint8_t value, bool update) {
    uint8_t tmp = (system_layers.config & (~(0x01 << index)));
    tmp |= (value << index);
    system_layers.config = tmp;
    if (update) {
        eeconfig_update_auto_switch_layers();
    }
    if (CUSTOM_AUTO_SWITCH_LAYERS_ENABLE || CUSTOM_AUTO_SWITCH_LAYERS_UPDATE_FN_KEYCODE) {
        auto_switch_layers_update();
    } else {
        default_layer_set(0x01);
    }
}

uint8_t auto_switch_layers_get_config(uint8_t index) {
    return (system_layers.config & (0x01 << index));
}

void auto_switch_layers_set_layer(uint8_t sys, uint8_t layer, bool update) {
    switch (sys) {
        case 0: {
            system_layers.windows_layer = layer;
            break;
        }
        case 1: {
            system_layers.windows_fn_layer = layer;
            break;
        }
        case 2: {
            system_layers.macos_layer = layer;
            break;
        }
        case 3: {
            system_layers.macos_fn_layer = layer;
            break;
        }
    }
    if (update) {
        eeconfig_update_auto_switch_layers();
    }
    if (CUSTOM_AUTO_SWITCH_LAYERS_ENABLE) {
        auto_switch_layers_update();
    }
}

uint8_t auto_switch_layers_get_layer(uint8_t sys) {
    switch (sys) {
        case 0: {
            return system_layers.windows_layer;
        }
        case 1: {
            return system_layers.windows_fn_layer;
        }
        case 2: {
            return system_layers.macos_layer;
        }
        case 3: {
            return system_layers.macos_fn_layer;
        }
    }
    return 0;
}

bool process_auto_switch_layers(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case WINDOWS_FN_KEY: {
            action_t action;
            action.code = ACTION_LAYER_MOMENTARY(system_layers.windows_fn_layer);
            process_action(record, action);
            return false;
        }
        case MACOS_FN_KEY: {
            action_t action;
            action.code = ACTION_LAYER_MOMENTARY(system_layers.macos_fn_layer);
            process_action(record, action);
            return false;
        }
    }
    return true;
}

