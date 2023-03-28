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
    uint16_t raw;
    struct __attribute__ ((packed)) {
        uint16_t button : 1;
        int16_t dial : 15;
    };
} report_radial_controller_t;

void radial_controller_task(void);
void radial_controller_event_finished(void);
void radial_controller_button_update(bool pressed);
void radial_controller_dial_update(bool clockwise, bool continued);
void radial_controller_dial_finished(void);
bool process_radial_controller(uint16_t keycode, keyrecord_t *record);
