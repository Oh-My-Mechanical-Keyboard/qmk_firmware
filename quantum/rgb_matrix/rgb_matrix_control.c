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

#include "rgb_matrix_control.h"
#include "eeprom.h"

rgb_matrix_control_config_t rgb_matrix_control_config = {1};
#ifdef RGB_MATRIX_CONTROL_SWITCH_ENABLE
const static uint8_t rgb_matrix_control_lut[4] = {3, 0, 1, 2};
#endif

void eeconfig_read_rgb_matrix_control(void) {
    rgb_matrix_control_config.raw = eeprom_read_byte(EECONFIG_RGB_MATRIX_CONTROL);
}

void eeconfig_update_rgb_matrix_control(void) {
    eeprom_update_byte(EECONFIG_RGB_MATRIX_CONTROL, rgb_matrix_control_config.raw);
}

void eeconfig_update_rgb_matrix_control_default(void) {
    rgb_matrix_control_config.is_key_rgb_enable = 0;
    rgb_matrix_control_config.is_underglow_rgb_enable = 0;
    rgb_matrix_control_config.is_logo_rgb_enable = 0;
    rgb_matrix_control_config.is_indicator_override = 0;
    rgb_matrix_control_config.reverse = 0;
    eeconfig_update_rgb_matrix_control();
}

void rgb_matrix_control_init(void) {
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
        eeconfig_update_rgb_matrix_control_default();
    }
    eeconfig_read_rgb_matrix_control();
}

void rgb_matrix_control_task(void) {
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i ++) {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
            if (rgb_matrix_control_config.is_underglow_rgb_enable == 1)
                rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
        } else if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_INDICATOR)) {
            if (rgb_matrix_control_config.is_logo_rgb_enable == 1)
                rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
        } else {
            if (rgb_matrix_control_config.is_key_rgb_enable == 1)
                rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
        }
    }
}

void key_rgb_toggle(void) {
    if (rgb_matrix_is_enabled()) {
        rgb_matrix_control_config.is_key_rgb_enable ^= 1;
        eeconfig_update_rgb_matrix_control();
    }
}

void underglow_rgb_toggle(void) {
    if (rgb_matrix_is_enabled()) {
        rgb_matrix_control_config.is_underglow_rgb_enable ^= 1;
        eeconfig_update_rgb_matrix_control();
    }
}

void logo_rgb_toggle(void) {
    if (rgb_matrix_is_enabled()) {
        rgb_matrix_control_config.is_logo_rgb_enable ^= 1;
        eeconfig_update_rgb_matrix_control();
    }
}

void indicator_rgb_override_toggle(void) {
    rgb_matrix_control_config.is_indicator_override ^= 1;
    eeconfig_update_rgb_matrix_control();
}

void key_rgb_enable(bool update) {
    if (rgb_matrix_is_enabled()) {
        rgb_matrix_control_config.is_key_rgb_enable = 0;
        if (update)
            eeconfig_update_rgb_matrix_control();
    }
}

void key_rgb_disable(bool update) {
    if (rgb_matrix_is_enabled()) {
        rgb_matrix_control_config.is_key_rgb_enable = 1;
        if (update)
            eeconfig_update_rgb_matrix_control();
    }
}

void underglow_rgb_enable(bool update) {
    if (rgb_matrix_is_enabled()) {
        rgb_matrix_control_config.is_underglow_rgb_enable = 0;
        if (update)
            eeconfig_update_rgb_matrix_control();
    }
}

void underglow_rgb_disable(bool update) {
    if (rgb_matrix_is_enabled()) {
        rgb_matrix_control_config.is_underglow_rgb_enable = 1;
        if (update)
            eeconfig_update_rgb_matrix_control();
    }
}

void logo_rgb_enable(bool update) {
    if (rgb_matrix_is_enabled()) {
        rgb_matrix_control_config.is_logo_rgb_enable = 0;
        if (update)
            eeconfig_update_rgb_matrix_control();
    }
}

void logo_rgb_disable(bool update) {
    if (rgb_matrix_is_enabled()) {
        rgb_matrix_control_config.is_logo_rgb_enable = 1;
        if (update)
            eeconfig_update_rgb_matrix_control();
    }
}

void set_indicator_rgb_override(uint8_t enable, bool update) {
    rgb_matrix_control_config.is_indicator_override = enable;
    if (update)
        eeconfig_update_rgb_matrix_control();
}

#ifdef RGB_MATRIX_CONTROL_SWITCH_ENABLE
void rgb_matrix_control_switch(void) {
    if (rgb_matrix_is_enabled()) {
        uint8_t current_rgb_matrix_control_config = rgb_matrix_control_config.raw & 0x03;
        rgb_matrix_control_config.raw = rgb_matrix_control_lut[current_rgb_matrix_control_config];
        eeconfig_update_rgb_matrix_control();
    }
}
#endif

bool key_rgb_is_enabled(void) {
    return !(rgb_matrix_control_config.is_key_rgb_enable);
}

bool underglow_rgb_is_enabled(void) {
    return !(rgb_matrix_control_config.is_underglow_rgb_enable);
}

bool logo_rgb_is_enabled(void) {
    return !(rgb_matrix_control_config.is_logo_rgb_enable);
}

uint8_t indicator_rgb_is_override(void) {
    return rgb_matrix_control_config.is_indicator_override;
}

bool process_rgb_matrix_control(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case UG_RGB_TOG:
            if (record->event.pressed) {
                underglow_rgb_toggle();
            }
            return false;
        case K_RGB_TOG:
            if (record->event.pressed) {
                key_rgb_toggle();
            }
            return false;
        case L_RGB_TOG:
            if (record->event.pressed) {
                logo_rgb_toggle();
            }
            return false;
#ifdef RGB_MATRIX_CONTROL_SWITCH_ENABLE
        case RGB_CT_SW:
            if (record->event.pressed) {
                rgb_matrix_control_switch();
            }
            return false;
#endif
    }
    return true;
}

