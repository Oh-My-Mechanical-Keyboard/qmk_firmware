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
        uint8_t positive_x : 1;
        uint8_t negative_x : 1;
        uint8_t positive_y : 1;
        uint8_t negative_y : 1;
    };
} joystick_axes_trigger_t;

typedef struct {
    joystick_axes_trigger_t joystick_axes_trigger_state;
    int16_t joystick_axes_x_value;
    int16_t joystick_axes_y_value;
    int16_t joystick_axes_x_calbration;
    int16_t joystick_axes_y_calbration;
} joystick_axes_state_t;

void joystick_trigger(uint8_t index, joystick_axes_trigger_t axes_state, uint8_t changed_axes);
bool joystick_update_user(uint8_t index, joystick_axes_trigger_t axes_state, uint8_t changed_axes);
bool joystick_update_kb(uint8_t index, joystick_axes_trigger_t axes_state, uint8_t changed_axes);

void joystick_trigger_init(void);
bool joystick_trigger_task(void);

