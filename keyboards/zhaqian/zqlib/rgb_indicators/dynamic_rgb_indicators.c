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

#include "dynamic_rgb_indicators.h"
#include <lib/lib8tion/lib8tion.h>
#include "color.h"
#include <stdlib.h>
#include "eeprom.h"

#ifdef DEFAULT_NUM_LOCK_ENABLE 
#define DEFAULT_NUM_LOCK_ENABLE_VAL 1
#else
#define DEFAULT_NUM_LOCK_ENABLE_VAL 0
#endif

#ifdef DEFAULT_NUM_LOCK_ALL_LED
#define DEFAULT_NUM_LOCK_ALL_LED_VAL 1
#else
#define DEFAULT_NUM_LOCK_ALL_LED_VAL 0
#endif

#ifdef DEFAULT_NUM_LOCK_KEY_LED
#define DEFAULT_NUM_LOCK_KEY_LED_VAL 1
#else
#define DEFAULT_NUM_LOCK_KEY_LED_VAL 0
#endif

#ifdef DEFAULT_NUM_LOCK_UNDERGLOW_LED
#define DEFAULT_NUM_LOCK_UNDERGLOW_LED_VAL 1
#else
#define DEFAULT_NUM_LOCK_UNDERGLOW_LED_VAL 0
#endif

#ifndef DEFAULT_NUM_LOCK_MODE
#define DEFAULT_NUM_LOCK_MODE 1
#endif

#ifdef DEFAULT_NUM_LOCK_LOGO_LED
#define DEFAULT_NUM_LOCK_LOGO_LED_VAL 1
#else
#define DEFAULT_NUM_LOCK_LOGO_LED_VAL 0
#endif

#ifndef DEFAULT_NUM_LOCK_LED
#define DEFAULT_NUM_LOCK_LED 0
#endif

#ifndef DEFAULT_NUM_LOCK_HSV
#define DEFAULT_NUM_LOCK_HSV {240, 255, 200}
#endif

#ifdef DEFAULT_CAPS_LOCK_ENABLE 
#define DEFAULT_CAPS_LOCK_ENABLE_VAL 1
#else
#define DEFAULT_CAPS_LOCK_ENABLE_VAL 0
#endif

#ifdef DEFAULT_CAPS_LOCK_ALL_LED
#define DEFAULT_CAPS_LOCK_ALL_LED_VAL 1
#else
#define DEFAULT_CAPS_LOCK_ALL_LED_VAL 0
#endif

#ifdef DEFAULT_CAPS_LOCK_KEY_LED
#define DEFAULT_CAPS_LOCK_KEY_LED_VAL 1
#else
#define DEFAULT_CAPS_LOCK_KEY_LED_VAL 0
#endif

#ifdef DEFAULT_CAPS_LOCK_UNDERGLOW_LED
#define DEFAULT_CAPS_LOCK_UNDERGLOW_LED_VAL 1
#else
#define DEFAULT_CAPS_LOCK_UNDERGLOW_LED_VAL 0
#endif

#ifndef DEFAULT_CAPS_LOCK_MODE
#define DEFAULT_CAPS_LOCK_MODE 1
#endif

#ifdef DEFAULT_CAPS_LOCK_LOGO_LED
#define DEFAULT_CAPS_LOCK_LOGO_LED_VAL 1
#else
#define DEFAULT_CAPS_LOCK_LOGO_LED_VAL 0
#endif

#ifndef DEFAULT_CAPS_LOCK_LED
#define DEFAULT_CAPS_LOCK_LED 1
#endif

#ifndef DEFAULT_CAPS_LOCK_HSV
#define DEFAULT_CAPS_LOCK_HSV {0, 255, 200}
#endif

#ifdef DEFAULT_SCROLL_LOCK_ENABLE 
#define DEFAULT_SCROLL_LOCK_ENABLE_VAL 1
#else
#define DEFAULT_SCROLL_LOCK_ENABLE_VAL 0
#endif

#ifdef DEFAULT_SCROLL_LOCK_ALL_LED
#define DEFAULT_SCROLL_LOCK_ALL_LED_VAL 1
#else
#define DEFAULT_SCROLL_LOCK_ALL_LED_VAL 0
#endif

#ifdef DEFAULT_SCROLL_LOCK_KEY_LED
#define DEFAULT_SCROLL_LOCK_KEY_LED_VAL 1
#else
#define DEFAULT_SCROLL_LOCK_KEY_LED_VAL 0
#endif

#ifdef DEFAULT_SCROLL_LOCK_UNDERGLOW_LED
#define DEFAULT_SCROLL_LOCK_UNDERGLOW_LED_VAL 1
#else
#define DEFAULT_SCROLL_LOCK_UNDERGLOW_LED_VAL 0
#endif

#ifndef DEFAULT_SCROLL_LOCK_MODE
#define DEFAULT_SCROLL_LOCK_MODE 1
#endif

#ifdef DEFAULT_SCROLL_LOCK_LOGO_LED
#define DEFAULT_SCROLL_LOCK_LOGO_LED_VAL 1
#else
#define DEFAULT_SCROLL_LOCK_LOGO_LED_VAL 0
#endif

#ifndef DEFAULT_SCROLL_LOCK_LED
#define DEFAULT_SCROLL_LOCK_LED 2
#endif

#ifndef DEFAULT_SCROLL_LOCK_HSV
#define DEFAULT_SCROLL_LOCK_HSV {120, 255, 200}
#endif


static const uint8_t rgb_indicators_effect_index[] = {
// to enable mode step reverse (uint8_t >= 0)
    0,
// default effect static mode
    1,
#ifdef ENABLE_RGB_INDICATORS_BREATHING
    2,
#endif

#ifdef ENABLE_RGB_INDICATORS_CYCLEBREATHING
    3,
#endif

#ifdef ENABLE_RGB_INDICATORS_CYCLEALL
    4,
#endif

#ifdef ENABLE_RGB_INDICATORS_RANDOM
    5,
#endif

#ifdef ENABLE_RGB_INDICATORS_RANDOM_ONCE
    6,
#endif

};

static const uint8_t rgb_indicators_effect_num = sizeof(rgb_indicators_effect_index) / sizeof(uint8_t);
static all_rgb_indicators_config_t rgb_indicators_config = {{0}, {0}, {0}};
static rgb_indicator_t rgb_indicators_state;

#ifdef ENABLE_RGB_INDICATORS_RANDOM_ONCE
static uint8_t changed[3] = {0};
#endif

EECONFIG_DEBOUNCE_HELPER(dynamic_rgb_indicators, EECONFIG_RGB_INDICATORS, rgb_indicators_config);

void update_dynamic_rgb_indicators(void) {
    eeconfig_flush_dynamic_rgb_indicators(true);
}

static void update_dynamic_rgb_indicators_default(void) {
    HSV tmp_hsv[3] = {DEFAULT_NUM_LOCK_HSV, DEFAULT_CAPS_LOCK_HSV, DEFAULT_SCROLL_LOCK_HSV};
    rgb_indicators_config.num_lock_config.enable = DEFAULT_NUM_LOCK_ENABLE_VAL;
    rgb_indicators_config.num_lock_config.all_led = DEFAULT_NUM_LOCK_ALL_LED_VAL;
    rgb_indicators_config.num_lock_config.key_led = DEFAULT_NUM_LOCK_KEY_LED_VAL;
    rgb_indicators_config.num_lock_config.underglow_led = DEFAULT_NUM_LOCK_UNDERGLOW_LED_VAL;
    rgb_indicators_config.num_lock_config.logo_led = DEFAULT_NUM_LOCK_LOGO_LED_VAL;
    rgb_indicators_config.num_lock_config.mode = DEFAULT_NUM_LOCK_MODE;
    rgb_indicators_config.num_lock_config.led = DEFAULT_NUM_LOCK_LED;
    rgb_indicators_config.num_lock_config.hsv = tmp_hsv[0];

    rgb_indicators_config.caps_lock_config.enable = DEFAULT_CAPS_LOCK_ENABLE_VAL;
    rgb_indicators_config.caps_lock_config.all_led = DEFAULT_CAPS_LOCK_ALL_LED_VAL;
    rgb_indicators_config.caps_lock_config.key_led = DEFAULT_CAPS_LOCK_KEY_LED_VAL;
    rgb_indicators_config.caps_lock_config.underglow_led = DEFAULT_CAPS_LOCK_UNDERGLOW_LED_VAL;
    rgb_indicators_config.caps_lock_config.logo_led = DEFAULT_CAPS_LOCK_LOGO_LED_VAL;
    rgb_indicators_config.caps_lock_config.mode = DEFAULT_CAPS_LOCK_MODE;
    rgb_indicators_config.caps_lock_config.led = DEFAULT_CAPS_LOCK_LED;
    rgb_indicators_config.caps_lock_config.hsv = tmp_hsv[1];

    rgb_indicators_config.scroll_lock_config.enable = DEFAULT_SCROLL_LOCK_ENABLE_VAL;
    rgb_indicators_config.scroll_lock_config.all_led = DEFAULT_SCROLL_LOCK_ALL_LED_VAL;
    rgb_indicators_config.scroll_lock_config.key_led = DEFAULT_SCROLL_LOCK_KEY_LED_VAL;
    rgb_indicators_config.scroll_lock_config.underglow_led = DEFAULT_SCROLL_LOCK_UNDERGLOW_LED_VAL;
    rgb_indicators_config.scroll_lock_config.logo_led = DEFAULT_SCROLL_LOCK_LOGO_LED_VAL;
    rgb_indicators_config.scroll_lock_config.mode = DEFAULT_SCROLL_LOCK_MODE;
    rgb_indicators_config.scroll_lock_config.led = DEFAULT_SCROLL_LOCK_LED;
    rgb_indicators_config.scroll_lock_config.hsv = tmp_hsv[2];

    update_dynamic_rgb_indicators();
}

void rgb_indicators_init(void) {
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
        update_dynamic_rgb_indicators_default();
    }
    eeconfig_init_dynamic_rgb_indicators();
    if (rgb_indicators_config.num_lock_config.mode == 0) {
        update_dynamic_rgb_indicators_default();
    }
    rgb_indicators_state_update();
}

void rgb_indicators_state_update(void) {
    rgb_indicators_state.num_lock = host_keyboard_led_state().num_lock;
    rgb_indicators_state.caps_lock = host_keyboard_led_state().caps_lock;
    rgb_indicators_state.scroll_lock = host_keyboard_led_state().scroll_lock;
}

uint8_t is_rgb_indicators_enabled(void) {
    return (rgb_indicators_config.num_lock_config.enable || rgb_indicators_config.caps_lock_config.enable || rgb_indicators_config.scroll_lock_config.enable);
}

uint8_t is_rgb_indicator_enabled(uint8_t indicator) {
    switch (indicator) {
        case 0: return (rgb_indicators_config.num_lock_config.enable);
        case 1: return (rgb_indicators_config.caps_lock_config.enable);
        case 2: return (rgb_indicators_config.scroll_lock_config.enable);
        default: break;
    }
    return 0;
}

uint8_t is_num_lock_enabled(void) {
    return (rgb_indicators_config.num_lock_config.enable);
}

uint8_t is_caps_lock_enabled(void) {
    return (rgb_indicators_config.caps_lock_config.enable);
}

uint8_t is_scroll_lock_enabled(void) {
    return (rgb_indicators_config.scroll_lock_config.enable);
}

static void rgb_indicator_render(uint8_t mode, uint8_t indicator) {
    switch (rgb_indicators_effect_index[mode]) {
#ifdef ENABLE_RGB_INDICATORS_BREATHING
        case 2: rgb_indicators_breathing(indicator); break;
#endif
#ifdef ENABLE_RGB_INDICATORS_CYCLEBREATHING
        case 3: rgb_indicators_cyclebreathing(indicator); break;
#endif
#ifdef ENABLE_RGB_INDICATORS_CYCLEALL
        case 4: rgb_indicators_cycleall(indicator); break;
#endif
#ifdef ENABLE_RGB_INDICATORS_RANDOM
        case 5: rgb_indicators_random(indicator); break;
#endif
#ifdef ENABLE_RGB_INDICATORS_RANDOM_ONCE
        case 6: rgb_indicators_random_once(indicator); break;
#endif
        default: rgb_indicators_static(indicator); break;
    }
}

static void rgb_indicators_render(void) {
    if (is_num_lock_enabled())
        rgb_indicator_render(rgb_indicators_config.num_lock_config.mode, 0);
    if (is_caps_lock_enabled())
        rgb_indicator_render(rgb_indicators_config.caps_lock_config.mode, 1);
    if (is_scroll_lock_enabled())
        rgb_indicator_render(rgb_indicators_config.scroll_lock_config.mode, 2);
}

void rgb_indicators_task(void) {
    if (is_rgb_indicators_enabled()) {
        rgb_indicators_state_update();
        rgb_indicators_render();
    }
}

void num_lock_indicator_toggle(void) {
    if (rgb_matrix_is_enabled()) {
        rgb_indicators_config.num_lock_config.enable ^= 1;
        update_dynamic_rgb_indicators();
    }
}

void num_lock_indicator_mode_step(void) {
    if (rgb_matrix_is_enabled() && is_num_lock_enabled()) {
        uint8_t mod = rgb_indicators_config.num_lock_config.mode + 1;
        rgb_indicators_config.num_lock_config.mode = mod < rgb_indicators_effect_num ? mod : 1;
        update_dynamic_rgb_indicators();
    }
}

void num_lock_indicator_mode_step_reverse(void) {
    if (rgb_matrix_is_enabled() && is_num_lock_enabled()) {
        uint8_t mod = rgb_indicators_config.num_lock_config.mode - 1;
        rgb_indicators_config.num_lock_config.mode = mod < 1 ? rgb_indicators_effect_num - 1 : mod;;
        update_dynamic_rgb_indicators();
    }
}

void caps_lock_indicator_toggle(void) {
    if (rgb_matrix_is_enabled()) {
        rgb_indicators_config.caps_lock_config.enable ^= 1;
        update_dynamic_rgb_indicators();
    }
}

void caps_lock_indicator_mode_step(void) {
    if (rgb_matrix_is_enabled() && is_caps_lock_enabled()) {
        uint8_t mod = rgb_indicators_config.caps_lock_config.mode + 1;
        rgb_indicators_config.caps_lock_config.mode = mod < rgb_indicators_effect_num ? mod : 1;
        update_dynamic_rgb_indicators();
    }
}

void caps_lock_indicator_mode_step_reverse(void) {
    if (rgb_matrix_is_enabled() && is_caps_lock_enabled()) {
        uint8_t mod = rgb_indicators_config.caps_lock_config.mode - 1;
        rgb_indicators_config.caps_lock_config.mode = mod < 1 ? rgb_indicators_effect_num  - 1 : mod;;
        update_dynamic_rgb_indicators();
    }
}


void scroll_lock_indicator_toggle(void) {
    if (rgb_matrix_is_enabled()) {
        rgb_indicators_config.scroll_lock_config.enable ^= 1;
        update_dynamic_rgb_indicators();
    }
}

void scroll_lock_indicator_mode_step(void) {
    if (rgb_matrix_is_enabled() && is_scroll_lock_enabled()) {
        uint8_t mod = rgb_indicators_config.scroll_lock_config.mode + 1;
        rgb_indicators_config.scroll_lock_config.mode = mod < rgb_indicators_effect_num ? mod : 1;
        update_dynamic_rgb_indicators();
    }
}

void scroll_lock_indicator_mode_step_reverse(void) {
    if (rgb_matrix_is_enabled() && is_scroll_lock_enabled()) {
        uint8_t mod = rgb_indicators_config.scroll_lock_config.mode - 1;
        rgb_indicators_config.scroll_lock_config.mode = mod < 1 ? rgb_indicators_effect_num  - 1 : mod;
        update_dynamic_rgb_indicators();
    }
}

void rgb_indicators_enable(uint8_t indicator, bool update) {
    switch (indicator) {
        case 0: rgb_indicators_config.num_lock_config.enable = 1; break;
        case 1: rgb_indicators_config.caps_lock_config.enable = 1; break;
        case 2: rgb_indicators_config.scroll_lock_config.enable = 1; break;
        default: break;
    }
    if (update)
        update_dynamic_rgb_indicators();
}

void rgb_indicators_disable(uint8_t indicator, bool update) {
    switch (indicator) {
        case 0: rgb_indicators_config.num_lock_config.enable = 0; break;
        case 1: rgb_indicators_config.caps_lock_config.enable = 0; break;
        case 2: rgb_indicators_config.scroll_lock_config.enable = 0; break;
        default: break;
    }
    if (update)
        update_dynamic_rgb_indicators();
}

void rgb_indicators_enable_all_led(uint8_t indicator, uint8_t enable, bool update) {
    switch (indicator) {
        case 0: rgb_indicators_config.num_lock_config.all_led = enable; break;
        case 1: rgb_indicators_config.caps_lock_config.all_led = enable; break;
        case 2: rgb_indicators_config.scroll_lock_config.all_led = enable; break;
        default: break;
    }
    if (update)
        update_dynamic_rgb_indicators();
}

void rgb_indicators_enable_key_led(uint8_t indicator, uint8_t enable, bool update) {
    switch (indicator) {
        case 0: rgb_indicators_config.num_lock_config.key_led = enable; break;
        case 1: rgb_indicators_config.caps_lock_config.key_led = enable; break;
        case 2: rgb_indicators_config.scroll_lock_config.key_led = enable; break;
        default: break;
    }
    if (update)
        update_dynamic_rgb_indicators();
}

void rgb_indicators_enable_underglow_led(uint8_t indicator, uint8_t enable, bool update) {
    switch (indicator) {
        case 0: rgb_indicators_config.num_lock_config.underglow_led = enable; break;
        case 1: rgb_indicators_config.caps_lock_config.underglow_led = enable; break;
        case 2: rgb_indicators_config.scroll_lock_config.underglow_led = enable; break;
        default: break;
    }
    if (update)
        update_dynamic_rgb_indicators();
}

void rgb_indicators_enable_logo_led(uint8_t indicator, uint8_t enable, bool update) {
    switch (indicator) {
        case 0: rgb_indicators_config.num_lock_config.logo_led = enable; break;
        case 1: rgb_indicators_config.caps_lock_config.logo_led = enable; break;
        case 2: rgb_indicators_config.scroll_lock_config.logo_led = enable; break;
        default: break;
    }
    if (update)
        update_dynamic_rgb_indicators();
}

void rgb_indicators_set_mode(uint8_t indicator, uint8_t mod, bool update) {
    switch (indicator) {
        case 0: rgb_indicators_config.num_lock_config.mode = mod; break;
        case 1: rgb_indicators_config.caps_lock_config.mode = mod; break;
        case 2: rgb_indicators_config.scroll_lock_config.mode = mod; break;
        default: break;
    }
    if (update)
        update_dynamic_rgb_indicators();
}

void rgb_indicators_set_led(uint8_t indicator, uint8_t led, bool update) {
    switch (indicator) {
        case 0: rgb_indicators_config.num_lock_config.led = led; break;
        case 1: rgb_indicators_config.caps_lock_config.led = led; break;
        case 2: rgb_indicators_config.scroll_lock_config.led = led; break;
        default: break;
    }
    if (update)
        update_dynamic_rgb_indicators();
}

void rgb_indicators_set_hsv(uint8_t indicator, uint8_t hue, uint8_t sat, uint8_t val, bool update) {
    switch (indicator) {
        case 0: {
            rgb_indicators_config.num_lock_config.hsv.h = hue;
            rgb_indicators_config.num_lock_config.hsv.s = sat;
            rgb_indicators_config.num_lock_config.hsv.v = val;
            break;
        }
        case 1: {
            rgb_indicators_config.caps_lock_config.hsv.h = hue;
            rgb_indicators_config.caps_lock_config.hsv.s = sat;
            rgb_indicators_config.caps_lock_config.hsv.v = val;
            break;
        }
        case 2: {
            rgb_indicators_config.scroll_lock_config.hsv.h = hue;
            rgb_indicators_config.scroll_lock_config.hsv.s = sat;
            rgb_indicators_config.scroll_lock_config.hsv.v = val;
            break;
        }
        default: break;
    }
    if (update)
        update_dynamic_rgb_indicators();
}

void rgb_indicators_set_val(uint8_t indicator, uint8_t val, bool update) {
    switch (indicator) {
        case 0: {
            rgb_indicators_config.num_lock_config.hsv.v = val;
            break;
        }
        case 1: {
            rgb_indicators_config.caps_lock_config.hsv.v = val;
            break;
        }
        case 2: {
            rgb_indicators_config.scroll_lock_config.hsv.v = val;
            break;
        }
        default: break;
    }
    if (update)
        update_dynamic_rgb_indicators();
}

uint8_t rgb_indicators_get_multiple_led(uint8_t indicator) {
    return rgb_indicators_get_all_led(indicator) || rgb_indicators_get_key_led(indicator) || \
            rgb_indicators_get_underglow_led(indicator) || rgb_indicators_get_logo_led(indicator);
}

uint8_t rgb_indicators_get_all_led(uint8_t indicator) {
    switch (indicator) {
        case 0: return rgb_indicators_config.num_lock_config.all_led;
        case 1: return rgb_indicators_config.caps_lock_config.all_led;
        case 2: return rgb_indicators_config.scroll_lock_config.all_led;
        default: return 0;
    }
}

uint8_t rgb_indicators_get_key_led(uint8_t indicator) {
    switch (indicator) {
        case 0: return rgb_indicators_config.num_lock_config.key_led;
        case 1: return rgb_indicators_config.caps_lock_config.key_led;
        case 2: return rgb_indicators_config.scroll_lock_config.key_led;
        default: return 0;
    }
}

uint8_t rgb_indicators_get_underglow_led(uint8_t indicator) {
    switch (indicator) {
        case 0: return rgb_indicators_config.num_lock_config.underglow_led;
        case 1: return rgb_indicators_config.caps_lock_config.underglow_led;
        case 2: return rgb_indicators_config.scroll_lock_config.underglow_led;
        default: return 0;
    }
}

uint8_t rgb_indicators_get_logo_led(uint8_t indicator) {
    switch (indicator) {
        case 0: return rgb_indicators_config.num_lock_config.logo_led;
        case 1: return rgb_indicators_config.caps_lock_config.logo_led;
        case 2: return rgb_indicators_config.scroll_lock_config.logo_led;
        default: return 0;
    }
}

uint8_t rgb_indicators_get_led(uint8_t indicator) {
    switch (indicator) {
        case 0: return rgb_indicators_config.num_lock_config.led;
        case 1: return rgb_indicators_config.caps_lock_config.led;
        case 2: return rgb_indicators_config.scroll_lock_config.led;
        default: return 0;
    }
}

uint8_t rgb_indicators_get_mode(uint8_t indicator) {
    switch (indicator) {
        case 0: return rgb_indicators_config.num_lock_config.mode;
        case 1: return rgb_indicators_config.caps_lock_config.mode;
        case 2: return rgb_indicators_config.scroll_lock_config.mode;
        default: return 0;
    }
}

uint8_t rgb_indicators_get_hue(uint8_t indicator) {
    switch (indicator) {
        case 0: return rgb_indicators_config.num_lock_config.hsv.h;
        case 1: return rgb_indicators_config.caps_lock_config.hsv.h;
        case 2: return rgb_indicators_config.scroll_lock_config.hsv.h;
        default: return 0;
    }
}

uint8_t rgb_indicators_get_sat(uint8_t indicator) {
    switch (indicator) {
        case 0: return rgb_indicators_config.num_lock_config.hsv.s;
        case 1: return rgb_indicators_config.caps_lock_config.hsv.s;
        case 2: return rgb_indicators_config.scroll_lock_config.hsv.s;
        default: return 0;
    }
}

uint8_t rgb_indicators_get_val(uint8_t indicator) {
    switch (indicator) {
        case 0: return rgb_indicators_config.num_lock_config.hsv.v;
        case 1: return rgb_indicators_config.caps_lock_config.hsv.v;
        case 2: return rgb_indicators_config.scroll_lock_config.hsv.v;
        default: return 0;
    }
}

HSV rgb_indicators_get_hsv(uint8_t indicator) {
    switch (indicator) {
        case 0: return rgb_indicators_config.num_lock_config.hsv;
        case 1: return rgb_indicators_config.caps_lock_config.hsv;
        case 2: return rgb_indicators_config.scroll_lock_config.hsv;
        default: return rgb_indicators_config.scroll_lock_config.hsv;
    }
}

static void rgb_indicators_set_color_multiple(uint8_t indicator, RGB rgb) {
    if (rgb_indicators_get_all_led(indicator) == 1) {
        rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
    } else {
        for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
            if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
                if (rgb_indicators_get_underglow_led(indicator) == 1) {
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                }
#ifdef LOGO_RGB_CONTROL_ENABLE
            } else if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_INDICATOR)) {
                if (rgb_indicators_get_logo_led(indicator) == 1) {
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                }
#endif
            } else {
                if (rgb_indicators_get_key_led(indicator) == 1) {
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                }
            }
        }
    }
}

static void rgb_indicators_set_color(uint8_t indicator, HSV hsv) {
    switch (indicator) {
        case 0: {
            if (rgb_indicators_state.num_lock == 1) {
                RGB rgb = hsv_to_rgb(hsv);
                if (rgb_indicators_get_multiple_led(indicator) == 1)
                    rgb_indicators_set_color_multiple(indicator, rgb);
                else
                    rgb_matrix_set_color(rgb_indicators_config.num_lock_config.led, rgb.r, rgb.g, rgb.b);
            }
#ifdef ENABLE_RGB_INDICATORS_RANDOM_ONCE
            else
                changed[0] = 0;
#endif
            break;
        }
        case 1: {
            if (rgb_indicators_state.caps_lock == 1) {
                RGB rgb = hsv_to_rgb(hsv);
                if (rgb_indicators_get_multiple_led(indicator) == 1)
                    rgb_indicators_set_color_multiple(indicator, rgb);
                else
                    rgb_matrix_set_color(rgb_indicators_config.caps_lock_config.led, rgb.r, rgb.g, rgb.b);
            }
#ifdef ENABLE_RGB_INDICATORS_RANDOM_ONCE
            else
                changed[1] = 0;
#endif
            break;
        }
        case 2: {
            if (rgb_indicators_state.scroll_lock == 1) {
                RGB rgb = hsv_to_rgb(hsv);
                if (rgb_indicators_get_multiple_led(indicator) == 1)
                    rgb_indicators_set_color_multiple(indicator, rgb);
                else
                    rgb_matrix_set_color(rgb_indicators_config.scroll_lock_config.led, rgb.r, rgb.g, rgb.b);
            }
#ifdef ENABLE_RGB_INDICATORS_RANDOM_ONCE
            else
                changed[2] = 0;
#endif
            break;
        }
        default: break;
    }
}

void rgb_indicators_static(uint8_t indicator) {
    HSV hsv = rgb_indicators_get_hsv(indicator);
    rgb_indicators_set_color(indicator, hsv);
}

#ifdef ENABLE_RGB_INDICATORS_BREATHING
void rgb_indicators_breathing(uint8_t indicator) {
    HSV hsv = rgb_indicators_get_hsv(indicator);
    uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
    hsv.v = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
    rgb_indicators_set_color(indicator, hsv);
}
#endif

#ifdef ENABLE_RGB_INDICATORS_CYCLEBREATHING
static uint8_t is_breathing_highest[3] = {1};
static uint8_t is_breathing_lowest[3] = {1};
static uint8_t hue_index[3] = {0};
static uint8_t val_index[3] = {0};
static uint8_t hue_stepper[3] = {0};

void rgb_indicators_cyclebreathing(uint8_t indicator) {
    HSV hsv = rgb_indicators_get_hsv(indicator);
    uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
    hsv.v = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
    if (is_breathing_lowest[indicator]){
        val_index[indicator] = hsv.v;
        hue_index[indicator] = hue_stepper[indicator];
        hue_stepper[indicator] += 8;
        is_breathing_lowest[indicator] ^= 1;
    } else {
        if (hsv.v >= val_index[indicator] && is_breathing_highest[indicator]) {
            is_breathing_highest[indicator] ^= 1;
        } else {
            if (hsv.v <= 0 && !is_breathing_highest[indicator]) {
                is_breathing_highest[indicator] ^= 1;
                is_breathing_lowest[indicator] ^= 1;
            }
        }
    }
    hsv.h = hue_index[indicator];
    rgb_indicators_set_color(indicator, hsv);
}
#endif

#ifdef ENABLE_RGB_INDICATORS_CYCLEALL
void rgb_indicators_cycleall(uint8_t indicator) {
    uint8_t time = scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed / 4, 1));
    HSV hsv = rgb_indicators_get_hsv(indicator);
    hsv.h = time;
    rgb_indicators_set_color(indicator, hsv);
}
#endif

#ifdef ENABLE_RGB_INDICATORS_RANDOM
static uint8_t timer[3] = {0};
static uint8_t hue[3] = {0};
void rgb_indicators_random(uint8_t indicator) {
    HSV hsv = rgb_indicators_get_hsv(indicator);
    if (timer[indicator] > 50) {
        srand(timer_read());
        hue[indicator] = rand() % 256;
        timer[indicator] = 0;
    } else {
        timer[indicator] ++;
    }
    hsv.h = hue[indicator];
    rgb_indicators_set_color(indicator, hsv);
}
#endif

#ifdef ENABLE_RGB_INDICATORS_RANDOM_ONCE
static uint8_t hue_once[3] = {0};
void rgb_indicators_random_once(uint8_t indicator) {
    HSV hsv = rgb_indicators_get_hsv(indicator);
    if (changed[indicator] == 0) {
        changed[indicator] = 1;
        srand(timer_read());
        hue_once[indicator] = rand() % 256;
    }
    hsv.h = hue_once[indicator];
    rgb_indicators_set_color(indicator, hsv);
}
#endif

bool process_rgb_indicators(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_IND_NUM_LOCK_TOG:
            if (record->event.pressed) {
                num_lock_indicator_toggle();
            }
            return false;
        case RGB_IND_NUM_LOCK_MF:
            if (record->event.pressed) {
                num_lock_indicator_mode_step();
            }
            return false;
        case RGB_IND_NUM_LOCK_MR:
            if (record->event.pressed) {
                num_lock_indicator_mode_step_reverse();
            }
            return false;
        case RGB_IND_CAPS_LOCK_TOG:
            if (record->event.pressed) {
                caps_lock_indicator_toggle();
            }
            return false;
        case RGB_IND_CAPS_LOCK_MF:
            if (record->event.pressed) {
                caps_lock_indicator_mode_step();
            }
            return false;
        case RGB_IND_CAPS_LOCK_MR:
            if (record->event.pressed) {
                caps_lock_indicator_mode_step_reverse();
            }
            return false;
        case RGB_IND_SCROLL_LOCK_TOG:
            if (record->event.pressed) {
                scroll_lock_indicator_toggle();
            }
            return false;
        case RGB_IND_SCROLL_LOCK_MF:
            if (record->event.pressed) {
                scroll_lock_indicator_mode_step();
            }
            return false;
        case RGB_IND_SCROLL_LOCK_MR:
            if (record->event.pressed) {
                scroll_lock_indicator_mode_step_reverse();
            }
            return false;
    }
    return true;
}
