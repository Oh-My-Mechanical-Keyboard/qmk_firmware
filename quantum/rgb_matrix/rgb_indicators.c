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

#include "rgb_indicators.h"
#include <lib/lib8tion/lib8tion.h>
#include "color.h"

#ifdef RGB_INDICATOR_NUM_LOCK_LED
static uint8_t num_lock_leds[] = RGB_INDICATOR_NUM_LOCK_LED;
static uint8_t num_lock_leds_num = sizeof(num_lock_leds) / sizeof(uint8_t);
#ifndef NUM_LOCK_STATIC_HSV
#define NUM_LOCK_STATIC_HSV {0, 255, 200}
#endif
#endif

#ifdef RGB_INDICATOR_CAPS_LOCK_LED
static uint8_t caps_lock_leds[] = RGB_INDICATOR_CAPS_LOCK_LED;
static uint8_t caps_lock_leds_num = sizeof(caps_lock_leds) / sizeof(uint8_t);
#ifndef CAPS_LOCK_STATIC_HSV
#define CAPS_LOCK_STATIC_HSV {0, 255, 200}
#endif
#endif

#ifdef RGB_INDICATOR_SCROLL_LOCK_LED
static uint8_t scroll_lock_leds[] = RGB_INDICATOR_SCROLL_LOCK_LED;
static uint8_t scroll_lock_leds_num = sizeof(scroll_lock_leds) / sizeof(uint8_t);
#ifndef SCROLL_LOCK_STATIC_HSV
#define SCROLL_LOCK_STATIC_HSV {0, 255, 200}
#endif
#endif

#ifdef RGB_INDICATOR_COMPOSE_LED
static uint8_t compose_leds[] = RGB_INDICATOR_COMPOSE_LED;
static uint8_t compose_leds_num = sizeof(compose_leds) / sizeof(uint8_t);
#ifndef COMPOSE_STATIC_HSV
#define COMPOSE_STATIC_HSV {0, 255, 200}
#endif
#endif

#ifdef RGB_INDICATOR_KANA_LED
static uint8_t kana_leds[] = RGB_INDICATOR_KANA_LED;
static uint8_t kana_leds_num = sizeof(kana_leds) / sizeof(uint8_t);
#ifndef KANA_STATIC_HSV
#define KANA_STATIC_HSV {0, 255, 200}
#endif
#endif

static HSV rgb_indicators_led_hsv[5] = {0};

static const uint8_t rgb_indicators_effect_index[] = {
// to enable mode step reverse (uint8_t >= 0)
    0,
// default effect static mode
    1,
#ifdef RGB_INDICATORS_BREATHING
    2,
#endif

#ifdef RGB_INDICATORS_CYCLEBREATHING
    3,
#endif

#ifdef RGB_INDICATORS_CYCLEALL
    4,
#endif

};

static const uint8_t rgb_indicators_effect_num = sizeof(rgb_indicators_effect_index) / sizeof(uint8_t);

static rgb_indicators_config_t rgb_indicators_config = {1};
static rgb_indicator_t rgb_indicators_state;

EECONFIG_DEBOUNCE_HELPER(rgb_indicators, EECONFIG_RGB_INDICATORS, rgb_indicators_config);

static void eeconfig_update_rgb_indicators(void) {
    eeprom_update_byte(EECONFIG_RGB_INDICATORS, rgb_indicators_config.raw);
}

static void eeconfig_update_rgb_indicators_default(void) {
    rgb_indicators_config.enable = 1;
    rgb_indicators_config.mode = 1;
    eeconfig_update_rgb_indicators();
}

void rgb_indicators_init(void) {
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
        eeconfig_update_rgb_indicators_default();
    }
    eeconfig_init_rgb_indicators();
    if (rgb_indicators_config.mode == 0) {
        eeconfig_update_rgb_indicators_default();
    }
    rgb_indicators_state.raw = 0;
#ifdef  NUM_LOCK_STATIC_HSV
    HSV hsv_num = NUM_LOCK_STATIC_HSV;
    rgb_indicators_led_hsv[0] = hsv_num;
#endif
#ifdef CAPS_LOCK_STATIC_HSV
    HSV hsv_caps = CAPS_LOCK_STATIC_HSV;
    rgb_indicators_led_hsv[1] = hsv_caps;
#endif
#ifdef SCROLL_LOCK_STATIC_HSV
    HSV hsv_scroll = SCROLL_LOCK_STATIC_HSV;
    rgb_indicators_led_hsv[2] = hsv_scroll;
#endif
#ifdef COMPOSE_STATIC_HSV
    HSV hsv_compose = COMPOSE_STATIC_HSV;
    rgb_indicators_led_hsv[3] = hsv_compose;
#endif
#ifdef KANA_STATIC_HSV
    HSV hsv_kana = KANA_STATIC_HSV;
    rgb_indicators_led_hsv[4] = hsv_kana;
#endif
    rgb_indicators_state_update();
}

void rgb_indicators_state_update(void) {
    rgb_indicators_state.num_lock = host_keyboard_led_state().num_lock;
    rgb_indicators_state.caps_lock = host_keyboard_led_state().caps_lock;
    rgb_indicators_state.scroll_lock = host_keyboard_led_state().scroll_lock;
    rgb_indicators_state.compose = host_keyboard_led_state().compose;
    rgb_indicators_state.kana = host_keyboard_led_state().kana;
}

void rgb_indicators_task(void) {
    if (rgb_indicators_config.enable == 1) {
        rgb_indicators_state_update();
        rgb_indicators_render();
    }
}

void rgb_indicators_render(void) {
#if defined RGB_INDICATOR_NUM_LOCK_LED || defined RGB_INDICATOR_CAPS_LOCK_LED || \
    defined RGB_INDICATOR_SCROLL_LOCK_LED || defined RGB_INDICATOR_COMPOSE_LED || \
    defined RGB_INDICATOR_KANA_LED

    switch (rgb_indicators_effect_index[rgb_indicators_config.mode]) {
#ifdef RGB_INDICATORS_BREATHING
        case 2: rgb_indicators_breathing(); break;
#endif
#ifdef RGB_INDICATORS_CYCLEBREATHING
        case 3: rgb_indicators_cyclebreathing(); break;
#endif
#ifdef RGB_INDICATORS_CYCLEALL
        case 4: rgb_indicators_cycleall(); break;
#endif
        default: rgb_indicators_static(); break;
    }

#endif
}

void rgb_indicators_toggle(void) {
    if (rgb_matrix_is_enabled()) {
        rgb_indicators_config.enable ^= 1;
        eeconfig_update_rgb_indicators();
    }
}

void rgb_indicators_mode_step(void) {
    if (rgb_matrix_is_enabled() && rgb_indicators_config.enable == 1) {
        uint8_t mod = rgb_indicators_config.mode + 1;
        rgb_indicators_config.mode = mod < rgb_indicators_effect_num ? mod : 1;
        eeconfig_update_rgb_indicators();
    }
}

void rgb_indicators_mode_step_reverse(void) {
    if (rgb_matrix_is_enabled() && rgb_indicators_config.enable == 1) {
        uint8_t mod = rgb_indicators_config.mode - 1;
        rgb_indicators_config.mode = mod < 1 ? rgb_indicators_effect_num - 1 : mod;
        eeconfig_update_rgb_indicators();
    }
}

static HSV rgb_indicators_get_static_hsv(uint8_t index) {
    HSV hsv = rgb_indicators_led_hsv[index];
#ifdef RGB_INDICATORS_BRIGHTNESS_SYNC_WITH_MATRIX
    hsv.v = rgb_matrix_get_val();
#endif
#if defined RGB_INDICATORS_BREATHING
    if (rgb_indicators_effect_index[rgb_indicators_config.mode] == 2) {
        uint16_t time = g_rgb_timer * (rgb_matrix_config.speed / 8) / 256;
        hsv.v = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
    }
#endif
    return hsv;
}

static void rgb_indicators_set_color(HSV *hsv) {
#ifdef RGB_INDICATOR_NUM_LOCK_LED
    if (rgb_indicators_state.num_lock == 1) {
        RGB rgb = hsv_to_rgb(hsv[0]);
        for (uint8_t i = 0; i < num_lock_leds_num; i++) {
            rgb_matrix_set_color(num_lock_leds[i], rgb.r, rgb.g, rgb.b);
        }
    }
#endif

#ifdef RGB_INDICATOR_CAPS_LOCK_LED
    if (rgb_indicators_state.caps_lock == 1) {
        RGB rgb = hsv_to_rgb(hsv[1]);
        for (uint8_t i = 0; i < caps_lock_leds_num; i++) {
            rgb_matrix_set_color(caps_lock_leds[i], rgb.r, rgb.g, rgb.b);
        }
    }
#endif

#ifdef RGB_INDICATOR_SCROLL_LOCK_LED
    if (rgb_indicators_state.scroll_lock == 1) {
        RGB rgb = hsv_to_rgb(hsv[2]);
        for (uint8_t i = 0; i < scroll_lock_leds_num; i++) {
            rgb_matrix_set_color(scroll_lock_leds[i], rgb.r, rgb.g, rgb.b);
        }
    }
#endif

#ifdef RGB_INDICATOR_COMPOSE_LED
    if (rgb_indicators_state.compose == 1) {
        RGB rgb = hsv_to_rgb(hsv[3]);
        for (uint8_t i = 0; i < compose_leds_num; i++) {
            rgb_matrix_set_color(compose_leds[i], rgb.r, rgb.g, rgb.b);
        }
    }
#endif

#ifdef RGB_INDICATOR_KANA_LED
    if (rgb_indicators_state.kana == 1) {
        RGB rgb = hsv_to_rgb(hsv[4]);
        for (uint8_t i = 0; i < kana_leds_num; i++) {
            rgb_matrix_set_color(kana_leds[i], rgb.r, rgb.g, rgb.b);
        }
    }
#endif
}

void rgb_indicators_static(void) {
    HSV hsv[5] = {0};
#ifdef RGB_INDICATOR_NUM_LOCK_LED
    hsv[0] = rgb_indicators_get_static_hsv(0);
#endif

#ifdef RGB_INDICATOR_CAPS_LOCK_LED
    hsv[1] = rgb_indicators_get_static_hsv(1);
#endif

#ifdef RGB_INDICATOR_SCROLL_LOCK_LED
    hsv[2] = rgb_indicators_get_static_hsv(2);
#endif

#ifdef RGB_INDICATOR_COMPOSE_LED
    hsv[3] = rgb_indicators_get_static_hsv(3);
#endif

#ifdef RGB_INDICATOR_KANA_LED
    hsv[4] = rgb_indicators_get_static_hsv(4);
#endif
    rgb_indicators_set_color(hsv);
}

#ifdef RGB_INDICATORS_BREATHING
void rgb_indicators_breathing(void) {
    rgb_indicators_static();
}
#endif

#ifdef RGB_INDICATORS_CYCLEBREATHING
static uint8_t is_breathing_highest = 1;
static uint8_t is_breathing_lowest = 1;
static uint8_t hue_index = 0;
static uint8_t val_index = 0;
static uint8_t hue_stepper = 0;
void rgb_indicators_cyclebreathing(void) {
    HSV hsv = rgb_matrix_config.hsv;
    uint16_t time = g_rgb_timer * (rgb_matrix_config.speed / 8) / 256;
    hsv.v = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
    if (is_breathing_lowest){
        val_index = hsv.v;
        hue_index = hue_stepper;
        hue_stepper += 8;
        is_breathing_lowest ^= 1;
    } else {
        if (hsv.v >= val_index && is_breathing_highest) {
            is_breathing_highest ^= 1;
        } else {
            if (hsv.v <= 0 && !is_breathing_highest) {
                is_breathing_highest ^= 1;
                is_breathing_lowest  ^= 1;
            }
        }
    }
    hsv.h = hue_index;
    HSV hsv_buf[5] = {hsv, hsv, hsv, hsv, hsv};
    rgb_indicators_set_color(hsv_buf);
}
#endif

#ifdef RGB_INDICATORS_CYCLEALL
void rgb_indicators_cycleall(void) {
    uint8_t time = scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed / 4, 1));
    HSV hsv = rgb_matrix_config.hsv;
    hsv.h = time;
    HSV hsv_buf[5] = {hsv, hsv, hsv, hsv, hsv};
    rgb_indicators_set_color(hsv_buf);
}
#endif

bool process_rgb_indicators(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_INDTOG:
            if (record->event.pressed) {
                rgb_indicators_toggle();
            }
            return false;
        case RGB_INDMF:
            if (record->event.pressed) {
                rgb_indicators_mode_step();
            }
            return false;
        case RGB_INDMR:
            if (record->event.pressed) {
                rgb_indicators_mode_step_reverse();
            }
            return false;
    }
    return true;
}
