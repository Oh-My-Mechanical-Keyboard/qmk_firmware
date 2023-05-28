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

#ifndef DYNAMIC_TAP_DANCE_ENTRIES
#    define DYNAMIC_TAP_DANCE_ENTRIES 4
#endif

typedef struct __attribute__((packed)) {
    uint16_t on_tap;
    uint16_t on_hold;
    uint16_t on_double_tap;
    uint16_t on_tap_hold;
    uint16_t tapping_term;
} td_entry_t;

typedef enum {
    TD_NONE              = 0,
    TD_UNKNOWN           = 1,
    TD_SINGLE_TAP        = 2,
    TD_SINGLE_HOLD       = 3,
    TD_DOUBLE_TAP        = 4,
    TD_DOUBLE_HOLD       = 5,
    TD_DOUBLE_SINGLE_TAP = 6
} td_state_t;

typedef struct {
    uint8_t entry;
    td_state_t state;
} td_info_t;

void dynamic_tap_dance_init(void);
