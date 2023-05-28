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

#include "joystick_trigger.h"
#include "analog.h"

#ifndef JOYSTICK_LPF_PROPORTION 
#define JOYSTICK_LPF_PROPORTION (0.2)
#endif

// Low Pass Filter Calculate
#ifdef JOYSTICK_USE_LPF
#define JOYSTICK_LPF_CAL(in, out)                    \
do {                                                 \
    out += (in - out) * JOYSTICK_LPF_PROPORTION;     \
} while (0)
#else
#define JOYSTICK_LPF_CAL(in, out)                    \
do {                                                 \
    out = in;                                        \
} while (0)
#endif

#ifndef JOYSTICK_ADC_RESOLUTION
#define JOYSTICK_ADC_RESOLUTION 10
#elif JOYSTICK_ADC_RESOLUTION < 8 || JOYSTICK_ADC_RESOLUTION > 16
#error "JOYSTICK_ADC_RESOLUTION must be between 8 and 16"
#endif

#define JOYSTICK_RESOLUTION ((1L << (JOYSTICK_ADC_RESOLUTION - 1)) - 1)

#ifndef JOYSTICK_THRESHOLD
#define JOYSTICK_THRESHOLD (JOYSTICK_RESOLUTION / 2)
#endif

#if !defined(JOYSTICK_AXES_X_PIN) || !defined(JOYSTICK_AXES_Y_PIN)
#error "No joystick axes pins defined"
#endif

#ifndef JOYSTICK_AXES_PX_KEY_POS
#define JOYSTICK_AXES_PX_KEY_POS {0, 0}
#endif

#ifndef JOYSTICK_AXES_NX_KEY_POS
#define JOYSTICK_AXES_NX_KEY_POS {0, 1}
#endif

#ifndef JOYSTICK_AXES_PY_KEY_POS
#define JOYSTICK_AXES_PY_KEY_POS {1, 0}
#endif

#ifndef JOYSTICK_AXES_NY_KEY_POS
#define JOYSTICK_AXES_NY_KEY_POS {1, 1}
#endif

static pin_t joystick_axes_x_pin[] = JOYSTICK_AXES_X_PIN;
static pin_t joystick_axes_y_pin[] = JOYSTICK_AXES_Y_PIN;

static keypos_t joystick_axes_key_pos[] = {JOYSTICK_AXES_PX_KEY_POS, JOYSTICK_AXES_NX_KEY_POS, \
                                            JOYSTICK_AXES_PY_KEY_POS, JOYSTICK_AXES_NY_KEY_POS};

#define NUMBER_OF_JOYSTICKS (sizeof(joystick_axes_x_pin) / sizeof(pin_t))
static joystick_axes_state_t joystick_axes_state[NUMBER_OF_JOYSTICKS];

void joystick_trigger(uint8_t index, joystick_axes_trigger_t axes_state, uint8_t changed_axes) {
    keyevent_t current_key_event;
    uint8_t axes_mask = 1;
    for (uint8_t i = 0; i < 4; i ++, axes_mask <<= 1) {
        if ((changed_axes & axes_mask )== axes_mask) {
            current_key_event.key = joystick_axes_key_pos[index + i * NUMBER_OF_JOYSTICKS];
            current_key_event.pressed = (axes_state.raw & axes_mask) == axes_mask ? 1 : 0;
            current_key_event.time = (timer_read() | 1);
            action_exec(current_key_event);
        }
    }
}

__attribute__((weak)) bool joystick_update_user(uint8_t index, joystick_axes_trigger_t axes_state, uint8_t changed_axes) {
    return true;
}

__attribute__((weak)) bool joystick_update_kb(uint8_t index, joystick_axes_trigger_t axes_state, uint8_t changed_axes) {
    joystick_trigger(index, axes_state, changed_axes);
    return joystick_update_user(index, axes_state, changed_axes);
}

void joystick_trigger_init(void) {
    int16_t check_buffer = 0;
    for (uint8_t i = 0; i < NUMBER_OF_JOYSTICKS; i ++) {
        joystick_axes_state[i].joystick_axes_x_value = analogReadPin(joystick_axes_x_pin[i]);
        joystick_axes_state[i].joystick_axes_y_value = analogReadPin(joystick_axes_y_pin[i]);
        check_buffer = joystick_axes_state[i].joystick_axes_x_value - JOYSTICK_RESOLUTION;
        if ((check_buffer > JOYSTICK_THRESHOLD) || (check_buffer < -JOYSTICK_THRESHOLD)) {
            joystick_axes_state[i].joystick_axes_x_calbration = JOYSTICK_RESOLUTION;
        } else {
            joystick_axes_state[i].joystick_axes_x_calbration = joystick_axes_state[i].joystick_axes_x_value;
        }
        check_buffer = joystick_axes_state[i].joystick_axes_y_value - JOYSTICK_RESOLUTION;
        if ((check_buffer > JOYSTICK_THRESHOLD) || (check_buffer < -JOYSTICK_THRESHOLD)) {
            joystick_axes_state[i].joystick_axes_y_calbration = JOYSTICK_RESOLUTION;
        } else {
            joystick_axes_state[i].joystick_axes_y_calbration = joystick_axes_state[i].joystick_axes_y_value;
        }
    }
}

static bool joystick_update(uint8_t index) {
    bool changed = false;
    joystick_axes_trigger_t current_state;
    int16_t axes_x_buf = joystick_axes_state[index].joystick_axes_x_value - joystick_axes_state[index].joystick_axes_x_calbration;
    int16_t axes_y_buf = joystick_axes_state[index].joystick_axes_y_value - joystick_axes_state[index].joystick_axes_y_calbration;
    current_state.positive_x = axes_x_buf > JOYSTICK_THRESHOLD ? 1 : 0;
    current_state.negative_x = axes_x_buf < -JOYSTICK_THRESHOLD ? 1 : 0;
    current_state.positive_y = axes_y_buf > JOYSTICK_THRESHOLD ? 1 : 0;
    current_state.negative_y = axes_y_buf < -JOYSTICK_THRESHOLD ? 1 : 0;
    if (current_state.raw != joystick_axes_state[index].joystick_axes_trigger_state.raw) {
        uint8_t changed_axes = current_state.raw ^ joystick_axes_state[index].joystick_axes_trigger_state.raw;
        changed |= joystick_update_kb(index, current_state, changed_axes);
        joystick_axes_state[index].joystick_axes_trigger_state = current_state;
    }
    return changed;
}

bool joystick_trigger_task(void) {
    bool changed = false;
    for (uint8_t i = 0; i < NUMBER_OF_JOYSTICKS; i++) {
        JOYSTICK_LPF_CAL(analogReadPin(joystick_axes_x_pin[i]), joystick_axes_state[i].joystick_axes_x_value);
        JOYSTICK_LPF_CAL(analogReadPin(joystick_axes_y_pin[i]), joystick_axes_state[i].joystick_axes_y_value);
        changed |= joystick_update(i);
    }
    return changed;
}
