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
#include "via.h"

typedef struct __attribute__((packed)) {
        uint8_t enable : 1;
        uint8_t all_led: 1;
        uint8_t key_led: 1;
        uint8_t underglow_led : 1;
        uint8_t logo_led : 1;
        uint8_t mode : 3;
        uint8_t led;
        HSV hsv;
} rgb_indicators_config_t;

typedef struct {
    rgb_indicators_config_t num_lock_config;
    rgb_indicators_config_t caps_lock_config;
    rgb_indicators_config_t scroll_lock_config;
} all_rgb_indicators_config_t;

typedef union {
    uint8_t raw;
    struct {
        uint8_t num_lock : 1;
        uint8_t caps_lock : 1;
        uint8_t scroll_lock : 1;
        uint8_t reserved : 5;
    };
} rgb_indicator_t;

#ifdef ENABLE_RGB_INDICATORS_ANIMATIONS
#define ENABLE_RGB_INDICATORS_BREATHING
#define ENABLE_RGB_INDICATORS_CYCLEBREATHING
#define ENABLE_RGB_INDICATORS_CYCLEALL
#define ENABLE_RGB_INDICATORS_RANDOM
#define ENABLE_RGB_INDICATORS_RANDOM_ONCE
#endif

void update_dynamic_rgb_indicators(void);
void rgb_indicators_init(void);
void rgb_indicators_task(void);
void rgb_indicators_state_update(void);
uint8_t is_rgb_indicators_enabled(void);
uint8_t is_rgb_indicator_enabled(uint8_t indicator);
uint8_t is_num_lock_enabled(void);
uint8_t is_caps_lock_enabled(void);
uint8_t is_scroll_lock_enabled(void);
void num_lock_indicator_toggle(void);
void num_lock_indicator_mode_step(void);
void num_lock_indicator_mode_step_reverse(void);
void caps_lock_indicator_toggle(void);
void caps_lock_indicator_mode_step(void);
void caps_lock_indicator_mode_step_reverse(void);
void scroll_lock_indicator_toggle(void);
void scroll_lock_indicator_mode_step(void);
void scroll_lock_indicator_mode_step_reverse(void);
void rgb_indicators_enable(uint8_t indicator, bool update);
void rgb_indicators_disable(uint8_t indicator, bool update);
void rgb_indicators_enable_all_led(uint8_t indicator, uint8_t enable, bool update);
void rgb_indicators_enable_key_led(uint8_t indicator, uint8_t enable, bool update);
void rgb_indicators_enable_underglow_led(uint8_t indicator, uint8_t enable, bool update);
void rgb_indicators_enable_logo_led(uint8_t indicator, uint8_t enable, bool update);
void rgb_indicators_set_mode(uint8_t indicator, uint8_t mod, bool update);
void rgb_indicators_set_led(uint8_t indicator, uint8_t led, bool update);
void rgb_indicators_set_hsv(uint8_t indicator, uint8_t hue, uint8_t sat, uint8_t val, bool update);
void rgb_indicators_set_val(uint8_t indicator, uint8_t val, bool update);
uint8_t rgb_indicators_get_all_led(uint8_t indicator);
uint8_t rgb_indicators_get_key_led(uint8_t indicator);
uint8_t rgb_indicators_get_underglow_led(uint8_t indicator);
uint8_t rgb_indicators_get_logo_led(uint8_t indicator);
uint8_t rgb_indicators_get_led(uint8_t indicator);
uint8_t rgb_indicators_get_mode(uint8_t indicator);
uint8_t rgb_indicators_get_hue(uint8_t indicator);
uint8_t rgb_indicators_get_sat(uint8_t indicator);
uint8_t rgb_indicators_get_val(uint8_t indicator);
HSV rgb_indicators_get_hsv(uint8_t indicator);
void rgb_indicators_static(uint8_t indicator);

#ifdef ENABLE_RGB_INDICATORS_BREATHING
void rgb_indicators_breathing(uint8_t indicator);
#endif

#ifdef ENABLE_RGB_INDICATORS_CYCLEBREATHING
void rgb_indicators_cyclebreathing(uint8_t indicator);
#endif

#ifdef ENABLE_RGB_INDICATORS_CYCLEALL
void rgb_indicators_cycleall(uint8_t indicator);
#endif

#ifdef ENABLE_RGB_INDICATORS_RANDOM
void rgb_indicators_random(uint8_t indicator);
#endif

#ifdef ENABLE_RGB_INDICATORS_RANDOM_ONCE
void rgb_indicators_random_once(uint8_t indicator);
#endif

bool process_rgb_indicators(uint16_t keycode, keyrecord_t *record);
