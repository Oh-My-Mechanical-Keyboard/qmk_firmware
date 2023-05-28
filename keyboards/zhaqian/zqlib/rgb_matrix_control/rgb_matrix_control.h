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

typedef union {
    uint8_t raw;
    struct __attribute__((packed)) {
        uint8_t is_key_rgb_enable : 1;
        uint8_t is_underglow_rgb_enable : 1;
        uint8_t is_logo_rgb_enable : 1;
        uint8_t is_indicator_override: 1;
        uint8_t reverse : 4;
    };
} rgb_matrix_control_config_t;

void eeconfig_read_rgb_matrix_control(void);
void eeconfig_update_rgb_matrix_control(void);

void rgb_matrix_control_init(void);
void rgb_matrix_control_task(void);

void key_rgb_toggle(void);
void underglow_rgb_toggle(void);
void logo_rgb_toggle(void);
void indicator_rgb_override_toggle(void);
void underglow_rgb_enable(bool update);
void underglow_rgb_disable(bool update);
void key_rgb_enable(bool update);
void key_rgb_disable(bool update);
void logo_rgb_enable(bool update);
void logo_rgb_disable(bool update);
void set_indicator_rgb_override(uint8_t enable, bool update);
#ifdef RGB_MATRIX_CONTROL_SWITCH_ENABLE
void rgb_matrix_control_switch(void);
#endif

bool key_rgb_is_enabled(void);
bool underglow_rgb_is_enabled(void);
bool logo_rgb_is_enabled(void);
uint8_t indicator_rgb_is_override(void);
bool process_rgb_matrix_control(uint16_t keycode, keyrecord_t *record);
