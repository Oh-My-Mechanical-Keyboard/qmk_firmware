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

#ifndef NO_ACTION_ONESHOT
#ifndef ONESHOT_TAP_TOGGLE
#    define ONESHOT_TAP_TOGGLE 5
#endif

#ifndef ONESHOT_TIMEOUT
#    define ONESHOT_TIMEOUT 5000
#endif
#endif

#ifdef MAGIC_SETTINGS_ENABLE
typedef struct __attribute__((packed)) {
    // Debounce
    uint8_t debounce;                   
    // Mouse Key
    uint8_t mk_delay;                   
    uint8_t mk_interval;                
    uint8_t mk_move_delta;        
    uint8_t mk_max_speed;               
    uint8_t mk_time_to_max;             
    uint8_t mk_wheel_delay;             
    uint8_t mk_wheel_interval;          
    uint8_t mk_wheel_max_speed;         
    uint8_t mk_wheel_time_to_max;      
    // Grave Escape
    uint8_t grave_esc_override;
    // Tap-Hold Config
    uint8_t tap_hold_config;
    uint8_t tapping_toggle_times;
    uint16_t tapping_term;
    uint16_t quick_tap_term;
    uint16_t tap_code_delay;
    uint16_t tap_hold_caps_delay;
    // Auto Shift
    uint8_t auto_shift_config;
    uint16_t auto_shift_timeout;
    // One Shot Key
    uint8_t oneshot_tap_toggle;
    uint16_t oneshot_timeout;
    // combos
    uint8_t combo_config;
    uint16_t combo_term;
    uint16_t combo_hold_term;
} magic_settings_t;

extern magic_settings_t magic_settings_config;

#define MAGIC_SETTINGS_SET(var, val) magic_settings_config.var = val
#define MAGIC_SETTINGS_GET(var) magic_settings_config.var

void eeconfig_update_magic_settings(void);
void magic_settings_init(void);
void magic_settings_reset(void);

// Mouse Key Settings
#ifdef MOUSEKEY_ENABLE
void mousekey_maigc_settings_update(void);
void mousekey_maigc_settings_reset(void);
#endif

// Tapping Settings
#ifndef NO_ACTION_TAPPING
#ifndef TAP_CODE_DELAY
#    define TAP_CODE_DELAY 10
#endif

#ifndef TAP_HOLD_CAPS_DELAY
#    define TAP_HOLD_CAPS_DELAY 80
#endif

#ifndef TAPPING_TERM_PER_KEY
#    define TAPPING_TERM_PER_KEY
#endif

#ifndef QUICK_TAP_TERM_PER_KEY
#    define QUICK_TAP_TERM_PER_KEY
#endif

#ifndef PERMISSIVE_HOLD_PER_KEY
#    define PERMISSIVE_HOLD_PER_KEY
#endif

#ifndef HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#    define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#endif

#ifndef RETRO_TAPPING_PER_KEY
#    define RETRO_TAPPING_PER_KEY
#endif

void tap_hold_maigc_settings_reset(void);
#endif

// Auto Shift Settings
#ifdef AUTO_SHIFT_ENABLE
#ifndef AUTO_SHIFT_NO_SETUP
#    define AUTO_SHIFT_NO_SETUP
#endif

#ifndef AUTO_SHIFT_REPEAT_PER_KEY
#    define AUTO_SHIFT_REPEAT_PER_KEY
#endif

#ifndef AUTO_SHIFT_NO_AUTO_REPEAT_PER_KEY
#    define AUTO_SHIFT_NO_AUTO_REPEAT_PER_KEY
#endif

void auto_shift_maigc_settings_update(void);
void auto_shift_maigc_settings_reset(void);
#endif

// One Shot Keys Settings
#ifndef NO_ACTION_ONESHOT
void oneshot_maigc_settings_reset(void);
#endif

// Combo Settings
#ifdef COMBO_ENABLE
#ifndef COMBO_MUST_HOLD_PER_COMBO
#    define COMBO_MUST_HOLD_PER_COMBO
#endif

#ifndef COMBO_MUST_TAP_PER_COMBO
#    define COMBO_MUST_TAP_PER_COMBO
#endif

#ifndef COMBO_TERM_PER_COMBO
#    define COMBO_TERM_PER_COMBO
#endif

#ifndef COMBO_MUST_PRESS_IN_ORDER_PER_COMBO
#    define COMBO_MUST_PRESS_IN_ORDER_PER_COMBO
#endif

void combo_maigc_settings_update(void);
void combo_maigc_settings_reset(void);
#endif

// Custom Parameters for Debounce
#define CUSTOM_DEBOUNCE (magic_settings_config.debounce)

// Custom Parameters for Mouse Key
#define CUSTOM_MOUSEKEY_MOVE_DELTA (magic_settings_config.mk_move_delta)

// Custom Parameters for Grave Escape
#define CUSTOM_GRAVE_ESC_ALT_OVERRIDE (magic_settings_config.grave_esc_override & 0x01)
#define CUSTOM_GRAVE_ESC_CTRL_OVERRIDE (magic_settings_config.grave_esc_override & 0x02)
#define CUSTOM_GRAVE_ESC_GUI_OVERRIDE (magic_settings_config.grave_esc_override & 0x04)
#define CUSTOM_GRAVE_ESC_SHIFT_OVERRIDE (magic_settings_config.grave_esc_override & 0x08)

// Custom Parameters for Tap-Hold
#define CUSTOM_TAP_CODE_DELAY (magic_settings_config.tap_code_delay)
#define CUSTOM_TAP_HOLD_CAPS_DELAY (magic_settings_config.tap_hold_caps_delay)
#define CUSTOM_TAPPING_TOGGLE (magic_settings_config.tapping_toggle_times)

// Custom Parameters for Auto Shift
#define CUSTOM_AUTO_SHIFT_ENABLE (magic_settings_config.auto_shift_config & 0x01)
#define CUSTOM_AUTO_SHIFT_MODIFIERS (magic_settings_config.auto_shift_config & 0x02)

// Custom Parameters for One Shot Keys
#define CUSTOM_ONESHOT_TAP_TOGGLE (magic_settings_config.oneshot_tap_toggle)
#define CUSTOM_ONESHOT_TIMEOUT (magic_settings_config.oneshot_timeout)

// Custom Parameters for Combo
#define CUSTOM_COMBO_HOLD_TERM (magic_settings_config.combo_hold_term)

#else  
// Custom Parameters for Debounce
#define CUSTOM_DEBOUNCE DEBOUNCE

// Custom Parameters for Mouse Key
#define CUSTOM_MOUSEKEY_MOVE_DELTA MOUSEKEY_MOVE_DELTA

// Custom Parameters for Grave Escape
#ifdef GRAVE_ESC_ALT_OVERRIDE
#    define CUSTOM_GRAVE_ESC_ALT_OVERRIDE 1
#else
#    define CUSTOM_GRAVE_ESC_ALT_OVERRIDE 0
#endif

#ifdef GRAVE_ESC_CTRL_OVERRIDE
#    define CUSTOM_GRAVE_ESC_CTRL_OVERRIDE 1
#else
#    define CUSTOM_GRAVE_ESC_CTRL_OVERRIDE 0
#endif

#ifdef GRAVE_ESC_GUI_OVERRIDE
#    define CUSTOM_GRAVE_ESC_GUI_OVERRIDE 1
#else
#    define CUSTOM_GRAVE_ESC_GUI_OVERRIDE 0
#endif

#ifdef GRAVE_ESC_SHIFT_OVERRIDE
#    define CUSTOM_GRAVE_ESC_SHIFT_OVERRIDE 1
#else
#    define CUSTOM_GRAVE_ESC_SHIFT_OVERRIDE 0
#endif

// Custom Parameters for Tap-Hold
#define CUSTOM_TAP_CODE_DELAY TAP_CODE_DELAY
#define CUSTOM_TAP_HOLD_CAPS_DELAY TAP_HOLD_CAPS_DELAY
#define CUSTOM_TAPPING_TOGGLE TAPPING_TOGGLE

// Custom Parameters for Auto Shift
#ifdef AUTO_SHIFT_ENABLE
#    define CUSTOM_AUTO_SHIFT_ENABLE 1
#else 
#    define CUSTOM_AUTO_SHIFT_ENABLE 0
#endif

#ifdef AUTO_SHIFT_MODIFIERS
#    define CUSTOM_AUTO_SHIFT_MODIFIERS 1
#else
#    define CUSTOM_AUTO_SHIFT_MODIFIERS 0
#endif

// Custom Parameters for One Shot Keys
#define CUSTOM_ONESHOT_TAP_TOGGLE ONESHOT_TAP_TOGGLE
#define CUSTOM_ONESHOT_TIMEOUT ONESHOT_TIMEOUT

// Custom Parameters for Combo
#define CUSTOM_COMBO_HOLD_TERM COMBO_HOLD_TERM

#endif