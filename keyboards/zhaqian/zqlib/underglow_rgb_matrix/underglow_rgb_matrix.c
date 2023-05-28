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

#include <math.h>
#include <lib/lib8tion/lib8tion.h>
#include <stdint.h>
#include "underglow_rgb_matrix.h"
#include "eeprom.h"

#ifndef RGB_MATRIX_CENTER
static const led_point_t ug_rgb_matrix_center = {112, 32};
#else
static const led_point_t ug_rgb_matrix_center = RGB_MATRIX_CENTER;
#endif

#if !defined(UNDERGLOW_RGB_MATRIX_HUE_STEP)
#define UNDERGLOW_RGB_MATRIX_HUE_STEP 8
#endif

#if !defined(UNDERGLOW_RGB_MATRIX_SAT_STEP)
#define UNDERGLOW_RGB_MATRIX_SAT_STEP 16
#endif

#if !defined(UNDERGLOW_RGB_MATRIX_VAL_STEP)
#define UNDERGLOW_RGB_MATRIX_VAL_STEP 16
#endif

#if !defined(UNDERGLOW_RGB_MATRIX_SPD_STEP)
#define UNDERGLOW_RGB_MATRIX_SPD_STEP 16
#endif

#if !defined(UNDERGLOW_RGB_MATRIX_STARTUP_MODE)
#define UNDERGLOW_RGB_MATRIX_STARTUP_MODE UG_RGB_MATRIX_SYNC
#endif

#if !defined(UNDERGLOW_RGB_MATRIX_STARTUP_HUE)
#define UNDERGLOW_RGB_MATRIX_STARTUP_HUE 0
#endif

#if !defined(UNDERGLOW_RGB_MATRIX_STARTUP_SAT)
#define UNDERGLOW_RGB_MATRIX_STARTUP_SAT UINT8_MAX
#endif

#if !defined(UNDERGLOW_RGB_MATRIX_STARTUP_VAL)
#define UNDERGLOW_RGB_MATRIX_STARTUP_VAL UNDERGLOW_RGB_MATRIX_MAXIMUM_BRIGHTNESS
#endif

#if !defined(UNDERGLOW_RGB_MATRIX_STARTUP_SPD)
#define UNDERGLOW_RGB_MATRIX_STARTUP_SPD (UINT8_MAX / 2)
#endif

static const uint8_t ug_rgb_matrix_effect_index[] = {
// to enable mode step reverse (uint8_t >= 0)
    0,
// default effect synchronize with qmk rgb matrix effects
    1,
#ifdef UG_RGB_MATRIX_BREATHING
    2,
#endif

#ifdef UG_RGB_MATRIX_CYCLEBREATHING
    3,
#endif

#ifdef UG_RGB_MATRIX_CYCLEBANDVAL
    4,
#endif

#ifdef UG_RGB_MATRIX_CYCLEBANDPINWHEELVAL
    5,
#endif

#ifdef UG_RGB_MATRIX_CYCLEALL
    6,
#endif

#ifdef UG_RGB_MATRIX_CYCLELEFTRIGHT
    7,
#endif

#ifdef UG_RGB_MATRIX_CYCLEUPDOWN
    8,
#endif

#ifdef UG_RGB_MATRIX_CYCLEOUTIN
    9,
#endif

#ifdef UG_RGB_MATRIX_CYCLEINOUT
    10,
#endif

#ifdef UG_RGB_MATRIX_RAINBOWPINWHEEL
    11,
#endif

#ifdef UG_RGB_MATRIX_CYCLESPIRAL
    12,
#endif

#if defined UG_RGB_MATRIX_WPMCYCLELEFTRIGHT && defined WPM_ENABLE
    13,
#endif

#if defined UG_RGB_MATRIX_WPMRAINBOWPINWHEEL && defined WPM_ENABLE
    14,
#endif

#if defined UG_RGB_MATRIX_WPMCYCLEBREATHING && defined WPM_ENABLE
    15,
#endif

#if defined UG_RGB_MATRIX_WPMCYCLESPIRAL && defined WPM_ENABLE
    16,
#endif

#if defined UG_RGB_MATRIX_WPMCYCLEINOUT && defined WPM_ENABLE
    17,
#endif

};

static const uint8_t ug_rgb_matrix_effect_num = sizeof(ug_rgb_matrix_effect_index)/sizeof(uint8_t);

static underglow_rgb_matrix_config_t underglow_rgb_matrix_config;

EECONFIG_DEBOUNCE_HELPER(underglow_rgb_matrix, EECONFIG_UNDERGLOW_RGB_MATRIX, underglow_rgb_matrix_config);

void eeconfig_update_underglow_rgb_matrix(void) {
    eeconfig_flush_underglow_rgb_matrix(true);
}

void eeconfig_update_underglow_rgb_matrix_default(void) {
    underglow_rgb_matrix_config.mode = UNDERGLOW_RGB_MATRIX_STARTUP_MODE;
    underglow_rgb_matrix_config.hsv = (HSV){UNDERGLOW_RGB_MATRIX_STARTUP_HUE, UNDERGLOW_RGB_MATRIX_STARTUP_SAT, UNDERGLOW_RGB_MATRIX_STARTUP_VAL};
    underglow_rgb_matrix_config.speed = UNDERGLOW_RGB_MATRIX_STARTUP_SPD;
    eeconfig_update_underglow_rgb_matrix();
}

void underglow_rgb_matrix_init(void) {
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
        eeconfig_update_underglow_rgb_matrix_default();
    }
    eeconfig_init_underglow_rgb_matrix();
    if (underglow_rgb_matrix_config.mode == 0) {
        eeconfig_update_underglow_rgb_matrix_default();
    }
}

void underglow_rgb_matrix_task(void) {
#ifdef UNDERGLOW_RGB_MATRIX_API_DISABLE
    underglow_rgb_matrix_config.hsv = rgb_matrix_config.hsv;
    underglow_rgb_matrix_config.speed = rgb_matrix_config.speed;
#endif

    switch (ug_rgb_matrix_effect_index[underglow_rgb_matrix_config.mode]) {
        case 0:
        case 1: break;
#ifdef UG_RGB_MATRIX_BREATHING
        case 2: Breathing(); break;
#endif
#ifdef UG_RGB_MATRIX_CYCLEBREATHING
        case 3: CycleBreathing();  break;
#endif
#ifdef UG_RGB_MATRIX_CYCLEBANDVAL
        case 4: CycleBandVal(); break;
#endif
#ifdef UG_RGB_MATRIX_CYCLEBANDPINWHEELVAL
        case 5: CycleBandPinwheelVal(); break;
#endif
#ifdef UG_RGB_MATRIX_CYCLEALL
        case 6: CycleAll(); break;
#endif
#ifdef UG_RGB_MATRIX_CYCLELEFTRIGHT
        case 7: CycleLeftRight(); break;
#endif
#ifdef UG_RGB_MATRIX_CYCLEUPDOWN
        case 8: CycleUpDown(); break;
#endif
#ifdef UG_RGB_MATRIX_CYCLEOUTIN
        case 9: CycleOutIn(); break;
#endif
#ifdef UG_RGB_MATRIX_CYCLEINOUT
        case 10: CycleInOut(); break;
#endif
#ifdef UG_RGB_MATRIX_RAINBOWPINWHEEL
        case 11: RainbowPinwheel(); break;
#endif
#ifdef UG_RGB_MATRIX_CYCLESPIRAL
        case 12: CycleSpiral(); break;
#endif
#if defined UG_RGB_MATRIX_WPMCYCLELEFTRIGHT && defined WPM_ENABLE
        case 13: WpmCycleLeftRight(); break;
#endif
#if defined UG_RGB_MATRIX_WPMRAINBOWPINWHEEL && defined WPM_ENABLE
        case 14: WpmRainbowPinwheel(); break;
#endif
#if defined UG_RGB_MATRIX_WPMCYCLEBREATHING && defined WPM_ENABLE
        case 15: WpmCycleBreathing(); break;
#endif
#if defined UG_RGB_MATRIX_WPMCYCLESPIRAL && defined WPM_ENABLE
        case 16: WpmCycleSpiral(); break;
#endif
#if defined UG_RGB_MATRIX_WPMCYCLEINOUT && defined WPM_ENABLE
        case 17: WpmCycleInOut(); break;
#endif
        default: break;
    }
}

void underglow_rgb_mode_sync(void) {
    if (rgb_matrix_is_enabled()) {
        underglow_rgb_matrix_config.mode = 1;
        eeconfig_update_underglow_rgb_matrix();
    }
}

void underglow_rgb_mode_step(void) {
    if (rgb_matrix_is_enabled()) {
        uint8_t mod = underglow_rgb_matrix_config.mode + 1;
        underglow_rgb_matrix_config.mode = mod < ug_rgb_matrix_effect_num ? mod : 1;
        eeconfig_update_underglow_rgb_matrix();
    }
}

void underglow_rgb_mode_step_reverse(void) {
    if (rgb_matrix_is_enabled()) {
        uint8_t mod = underglow_rgb_matrix_config.mode - 1;
        underglow_rgb_matrix_config.mode = mod < 1 ? ug_rgb_matrix_effect_num - 1 : mod;
        eeconfig_update_underglow_rgb_matrix();
    }
}

#ifndef UNDERGLOW_RGB_MATRIX_API_DISABLE

uint8_t underglow_rgb_matrix_get_mode_num(void) {
    return ug_rgb_matrix_effect_num;
}

uint8_t underglow_rgb_matrix_get_mode(void) {
    return underglow_rgb_matrix_config.mode;
}

HSV underglow_rgb_matrix_get_hsv(void) {
    return underglow_rgb_matrix_config.hsv;
}

uint8_t underglow_rgb_matrix_get_hue(void) {
    return underglow_rgb_matrix_config.hsv.h;
}

uint8_t underglow_rgb_matrix_get_sat(void) {
    return underglow_rgb_matrix_config.hsv.s;
}

uint8_t underglow_rgb_matrix_get_val(void) {
    return underglow_rgb_matrix_config.hsv.v;
}

uint8_t underglow_rgb_matrix_get_speed(void) {
    return underglow_rgb_matrix_config.speed;
}

void underglow_rgb_matrix_set_mode(uint8_t mode, bool update) {
    underglow_rgb_matrix_config.mode = mode;
    if (update)
        eeconfig_update_underglow_rgb_matrix();
}

void underglow_rgb_matrix_set_hsv(uint8_t hue, uint8_t sat, uint8_t val, bool update) {
    underglow_rgb_matrix_config.hsv.h = hue;
    underglow_rgb_matrix_config.hsv.s = sat;
    underglow_rgb_matrix_config.hsv.v = val;
    if (update)
        eeconfig_update_underglow_rgb_matrix();
}

void underglow_rgb_matrix_set_hue(uint8_t hue, bool update) {
    underglow_rgb_matrix_config.hsv.h = hue;
    if (update)
        eeconfig_update_underglow_rgb_matrix();
}

void underglow_rgb_matrix_set_sat(uint8_t sat, bool update) {
    underglow_rgb_matrix_config.hsv.s = sat;
    if (update)
        eeconfig_update_underglow_rgb_matrix();
}

void underglow_rgb_matrix_set_val(uint8_t val, bool update) {
    underglow_rgb_matrix_config.hsv.v = val;
    if (update)
        eeconfig_update_underglow_rgb_matrix();
}

void underglow_rgb_matrix_set_speed(uint8_t speed, bool update) {
    underglow_rgb_matrix_config.speed = speed;
    if (update)
        eeconfig_update_underglow_rgb_matrix();
}

void underglow_rgb_matrix_increase_hue(void) {
    underglow_rgb_matrix_set_hue(underglow_rgb_matrix_config.hsv.h + UNDERGLOW_RGB_MATRIX_HUE_STEP, true);
}

void underglow_rgb_matrix_decrease_hue(void) {
    underglow_rgb_matrix_set_hue(underglow_rgb_matrix_config.hsv.h - UNDERGLOW_RGB_MATRIX_HUE_STEP, true);
}

void underglow_rgb_matrix_increase_sat(void) {
    underglow_rgb_matrix_set_sat(qadd8(underglow_rgb_matrix_config.hsv.s, UNDERGLOW_RGB_MATRIX_SAT_STEP), true);
}

void underglow_rgb_matrix_decrease_sat(void) {
    underglow_rgb_matrix_set_sat(qsub8(underglow_rgb_matrix_config.hsv.s, UNDERGLOW_RGB_MATRIX_SAT_STEP), true);
}

void underglow_rgb_matrix_increase_val(void) {
    underglow_rgb_matrix_set_val(qadd8(underglow_rgb_matrix_config.hsv.v, UNDERGLOW_RGB_MATRIX_VAL_STEP), true);
}

void underglow_rgb_matrix_decrease_val(void) {
    underglow_rgb_matrix_set_val(qsub8(underglow_rgb_matrix_config.hsv.v, UNDERGLOW_RGB_MATRIX_VAL_STEP), true);
}

void underglow_rgb_matrix_increase_speed(void) {
    underglow_rgb_matrix_set_speed(qadd8(underglow_rgb_matrix_config.speed, UNDERGLOW_RGB_MATRIX_SPD_STEP), true);
}

void underglow_rgb_matrix_decrease_speed(void) {
    underglow_rgb_matrix_set_speed(qsub8(underglow_rgb_matrix_config.speed, UNDERGLOW_RGB_MATRIX_SPD_STEP), true);
}

#endif

bool process_underglow_rgb_matrix(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case UG_RGB_MS:
            if (record->event.pressed) {
                underglow_rgb_mode_sync();
            }
            return false;
        case UG_RGB_MF:
            if (record->event.pressed) {
                underglow_rgb_mode_step();
            }
            return false;
        case UG_RGB_MR:
            if (record->event.pressed) {
                underglow_rgb_mode_step_reverse();
            }
            return false;
#ifndef UNDERGLOW_RGB_MATRIX_API_DISABLE
        case UG_RGB_HI:
            if (record->event.pressed) {
                underglow_rgb_matrix_increase_hue();
            }
            return false;
        case UG_RGB_HD:
            if (record->event.pressed) {
                underglow_rgb_matrix_decrease_hue();
            }
            return false;
        case UG_RGB_SI:
            if (record->event.pressed) {
                underglow_rgb_matrix_increase_sat();
            }
            return false;
        case UG_RGB_SD:
            if (record->event.pressed) {
                underglow_rgb_matrix_decrease_sat();
            }
            return false;
        case UG_RGB_VI:
            if (record->event.pressed) {
                underglow_rgb_matrix_increase_val();
            }
            return false;
        case UG_RGB_VD:
            if (record->event.pressed) {
                underglow_rgb_matrix_decrease_val();
            }
            return false;
        case UG_RGB_SPI:
            if (record->event.pressed) {
                underglow_rgb_matrix_increase_speed();
            }
            return false;
        case UG_RGB_SPD:
            if (record->event.pressed) {
                underglow_rgb_matrix_decrease_speed();
            }
            return false;
#endif
    }
    return true;
}


#if defined UG_RGB_MATRIX_CYCLEBANDVAL \
    || defined UG_RGB_MATRIX_CYCLEALL \
    || defined UG_RGB_MATRIX_CYCLELEFTRIGHT \
    || defined UG_RGB_MATRIX_CYCLEUPDOWN \
    || (defined UG_RGB_MATRIX_WPMCYCLELEFTRIGHT && defined WPM_ENABLE)
void CycleIMath(uint8_t time, uint8_t mode) {
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW) || HAS_FLAGS(g_led_config.flags[i], LED_FLAG_INDICATOR)) {
            HSV hsv = underglow_rgb_matrix_config.hsv;
            switch (mode) {
#if defined UG_RGB_MATRIX_CYCLEBANDVAL
                case 0: {
                    int16_t v = hsv.v - abs(scale8(g_led_config.point[i].x, 228) + 28 - time) * 8;
                    hsv.v     = scale8(v < 0 ? 0 : v, hsv.v);
                    hsv.h = time;
                    break;
                }
#endif
#if defined UG_RGB_MATRIX_CYCLEALL
                case 1: hsv.h = time; break;
#endif
#if defined UG_RGB_MATRIX_CYCLELEFTRIGHT || (defined UG_RGB_MATRIX_WPMCYCLELEFTRIGHT && defined WPM_ENABLE)
                case 2: hsv.h = g_led_config.point[i].x - time; break;
#endif
#if defined UG_RGB_MATRIX_CYCLEUPDOWN
                case 3: hsv.h = g_led_config.point[i].y - time; break;
#endif
            }
            RGB rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}
#endif

#if defined UG_RGB_MATRIX_CYCLEBREATHING || (defined UG_RGB_MATRIX_WPMCYCLEBREATHING && defined WPM_ENABLE)
static uint8_t is_breathing_highest = 1;
static uint8_t is_breathing_lowest = 1;
static uint8_t hue_index = 0;
static uint8_t val_index = 0;
static uint8_t hue_stepper = 0;
void CycleBreathingMath(uint16_t time) {
    HSV hsv = underglow_rgb_matrix_config.hsv;
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
    RGB rgb       = hsv_to_rgb(hsv);
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW) || HAS_FLAGS(g_led_config.flags[i], LED_FLAG_INDICATOR))
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
}
#endif

#if defined UG_RGB_MATRIX_CYCLEBANDPINWHEELVAL \
    || defined UG_RGB_MATRIX_CYCLEOUTIN \
    || defined UG_RGB_MATRIX_CYCLEINOUT \
    || defined UG_RGB_MATRIX_CYCLESPIRAL \
    || (defined UG_RGB_MATRIX_WPMCYCLESPIRAL && defined WPM_ENABLE) \
    || (defined UG_RGB_MATRIX_WPMCYCLEINOUT && defined WPM_ENABLE)
void CycleDxDyDistMath(uint8_t time, uint8_t mode) {
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW) || HAS_FLAGS(g_led_config.flags[i], LED_FLAG_INDICATOR)) {
            int16_t dx = g_led_config.point[i].x - ug_rgb_matrix_center.x;
            int16_t dy = g_led_config.point[i].y - ug_rgb_matrix_center.y;
            uint8_t dist = sqrt16(dx * dx + dy * dy);
            HSV hsv = underglow_rgb_matrix_config.hsv;
            switch (mode){
#if defined UG_RGB_MATRIX_CYCLEOUTIN
                case 0: hsv.h = 3 * dist / 2 + time; break;
#endif
#if defined UG_RGB_MATRIX_CYCLEINOUT || (defined UG_RGB_MATRIX_WPMCYCLEINOUT && defined WPM_ENABLE)
                case 1: hsv.h = 3 * dist / 2 - time; break;
#endif
#if defined UG_RGB_MATRIX_CYCLESPIRAL || (defined UG_RGB_MATRIX_WPMCYCLESPIRAL && defined WPM_ENABLE)
                case 2: hsv.h = dist - time - atan2_8(dy, dx); break;
#endif
#if defined UG_RGB_MATRIX_CYCLEBANDPINWHEELVAL
                case 3: hsv.h = time; hsv.v = scale8(hsv.v - time - atan2_8(dy, dx) * 3, hsv.v); break;
#endif
            }
            RGB rgb  = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}
#endif

#if defined UG_RGB_MATRIX_RAINBOWPINWHEEL || (defined UG_RGB_MATRIX_WPMRAINBOWPINWHEEL && defined WPM_ENABLE)
void CycleCosSinMath(uint16_t time) {
    int8_t cos1 = cos8(time) - 128;
    int8_t sin1 = sin8(time) - 128;
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW) || HAS_FLAGS(g_led_config.flags[i], LED_FLAG_INDICATOR)) {
            HSV hsv = underglow_rgb_matrix_config.hsv;
            hsv.h += ((g_led_config.point[i].y - ug_rgb_matrix_center.y) * 3 * cos1 + (56 - abs8(g_led_config.point[i].x - ug_rgb_matrix_center.x)) * 3 * sin1) / 128;
            RGB rgb  = hsv_to_rgb(hsv);
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}
#endif

#if (defined UG_RGB_MATRIX_WPMCYCLELEFTRIGHT \
    || defined UG_RGB_MATRIX_WPMRAINBOWPINWHEEL \
    || defined UG_RGB_MATRIX_WPMCYCLEBREATHING  \
    || defined UG_RGB_MATRIX_WPMCYCLESPIRAL \
    || defined UG_RGB_MATRIX_WPMCYCLEINOUT) \
    && defined WPM_ENABLE
uint8_t WpmMath(void) {
    return get_current_wpm() / 50 + 1;
}
#endif

/*
 *  the functions of rgb matrix effects
 */

#ifdef UG_RGB_MATRIX_BREATHING
void Breathing(void) {
    HSV      hsv  = underglow_rgb_matrix_config.hsv;
    uint16_t time = g_rgb_timer * (underglow_rgb_matrix_config.speed / 8) / 256;
    hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
    RGB rgb       = hsv_to_rgb(hsv);
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW) || HAS_FLAGS(g_led_config.flags[i], LED_FLAG_INDICATOR))
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
}
#endif

#ifdef UG_RGB_MATRIX_CYCLEBREATHING
void CycleBreathing() {
    uint16_t time = g_rgb_timer * (underglow_rgb_matrix_config.speed / 8) / 256;
    CycleBreathingMath(time);
}
#endif

#ifdef UG_RGB_MATRIX_CYCLEBANDVAL
void CycleBandVal(void) {
    uint8_t time = g_rgb_timer * qadd8(underglow_rgb_matrix_config.speed / 4, 1) / 256;
    CycleIMath(time, 0);
}
#endif

#ifdef UG_RGB_MATRIX_CYCLEBANDPINWHEELVAL
void CycleBandPinwheelVal(void) {
    uint8_t time = g_rgb_timer * (underglow_rgb_matrix_config.speed / 2) / 256;
    CycleDxDyDistMath(time, 3);
}
#endif

#ifdef UG_RGB_MATRIX_CYCLEALL
void CycleAll(void) {
    uint8_t time = g_rgb_timer * qadd8(underglow_rgb_matrix_config.speed / 4, 1) / 256;
    CycleIMath(time, 1);
}
#endif

#ifdef UG_RGB_MATRIX_CYCLELEFTRIGHT
void CycleLeftRight(void) {
    uint8_t time = g_rgb_timer * qadd8(underglow_rgb_matrix_config.speed / 4, 1) / 256;
    CycleIMath(time, 2);
}
#endif

#ifdef UG_RGB_MATRIX_CYCLEUPDOWN
void CycleUpDown(void) {
    uint8_t time = g_rgb_timer * qadd8(underglow_rgb_matrix_config.speed / 4, 1) / 256;
    CycleIMath(time, 3);
}
#endif

#ifdef UG_RGB_MATRIX_CYCLEOUTIN
void CycleOutIn(void) {
    uint8_t time = g_rgb_timer * (underglow_rgb_matrix_config.speed / 2) / 256;
    CycleDxDyDistMath(time, 0);
}
#endif

#ifdef UG_RGB_MATRIX_CYCLEINOUT
void CycleInOut() {
    uint8_t time = g_rgb_timer * (underglow_rgb_matrix_config.speed / 2) / 256;
    CycleDxDyDistMath(time, 1);
}
#endif

#ifdef UG_RGB_MATRIX_RAINBOWPINWHEEL
void RainbowPinwheel(void) {
    uint16_t time =  g_rgb_timer * (underglow_rgb_matrix_config.speed / 4) / 256;
    CycleCosSinMath(time);
}
#endif

#ifdef UG_RGB_MATRIX_CYCLESPIRAL
void CycleSpiral(void) {
    uint8_t time = g_rgb_timer * (underglow_rgb_matrix_config.speed / 2) / 256;
    CycleDxDyDistMath(time, 2);
}
#endif

#if defined UG_RGB_MATRIX_WPMCYCLELEFTRIGHT && defined WPM_ENABLE
void WpmCycleLeftRight(void) {
    uint8_t time = scale16by8(g_rgb_timer, qadd8(underglow_rgb_matrix_config.speed * WpmMath() / 12 , 1));
    CycleIMath(time, 2);
}
#endif

#if defined UG_RGB_MATRIX_WPMRAINBOWPINWHEEL && defined WPM_ENABLE
void WpmRainbowPinwheel() {
    uint16_t time =  g_rgb_timer * (underglow_rgb_matrix_config.speed * WpmMath() / 12) / 256;
    CycleCosSinMath(time);
}
#endif

#if defined UG_RGB_MATRIX_WPMCYCLEBREATHING && defined WPM_ENABLE
void WpmCycleBreathing() {
    uint8_t wpm = WpmMath();
    if (wpm < 3) {
        wpm = g_rgb_timer * (underglow_rgb_matrix_config.speed * WpmMath() / 8) / 256;
    } else {
        wpm = g_rgb_timer * (underglow_rgb_matrix_config.speed * 3 / 8) / 256;
    }
    CycleBreathingMath(wpm);
}
#endif

#if defined UG_RGB_MATRIX_WPMCYCLESPIRAL && defined WPM_ENABLE
void WpmCycleSpiral() {
    uint8_t time = g_rgb_timer * (underglow_rgb_matrix_config.speed * WpmMath() / 6) / 256;
    CycleDxDyDistMath(time, 2);
}
#endif

#if defined UG_RGB_MATRIX_WPMCYCLEINOUT && defined WPM_ENABLE
void WpmCycleInOut() {
    uint8_t time = g_rgb_timer * (underglow_rgb_matrix_config.speed * WpmMath() / 6) / 256;
    CycleDxDyDistMath(time, 1);
}
#endif
