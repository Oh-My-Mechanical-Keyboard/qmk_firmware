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
        uint8_t enable : 1;
        uint8_t mode : 7;
    };
} rgb_indicators_config_t;

typedef union {
    uint8_t raw;
    struct {
        uint8_t num_lock : 1;
        uint8_t caps_lock : 1;
        uint8_t scroll_lock : 1;
        uint8_t compose : 1;
        uint8_t kana : 1;
        uint8_t reserved : 3;
    };
} rgb_indicator_t;

void rgb_indicators_init(void);
void rgb_indicators_task(void);
void rgb_indicators_state_update(void);
void rgb_indicators_render(void);

void rgb_indicators_toggle(void);
void rgb_indicators_mode_step(void);
void rgb_indicators_mode_step_reverse(void);
bool process_rgb_indicators(uint16_t keycode, keyrecord_t *record);
void rgb_indicators_static(void);
#ifdef RGB_INDICATORS_BREATHING
void rgb_indicators_breathing(void);
#endif
#ifdef RGB_INDICATORS_CYCLEBREATHING
void rgb_indicators_cyclebreathing(void);
#endif
#ifdef RGB_INDICATORS_CYCLEALL
void rgb_indicators_cycleall(void);
#endif
