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

#pragma once

#include "quantum.h"

#ifndef DYNAMIC_COMBOS_ENTRIES
#    define DYNAMIC_COMBOS_ENTRIES 4
#endif

typedef struct __attribute__((packed)) {
    uint16_t keys[4];
    uint16_t keycode;
    uint16_t combo_term;
} combo_entry_t;

void dynamic_combos_update(uint8_t index);
void dynamic_combos_init(void);