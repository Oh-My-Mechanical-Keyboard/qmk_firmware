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

#include "radial_controller.h"
#include "report.h"
#include "host.h"

// support encoder and switches
#ifndef RADIAL_CONTROLLER_RESOLUTION
#define RADIAL_CONTROLLER_RESOLUTION 100
#endif

#ifndef RADIAL_CONTROLLER_ROTATION_STEP
#define RADIAL_CONTROLLER_ROTATION_STEP 10
#endif

#ifndef RADIAL_CONTROLLER_TIMER_DELAY
#define RADIAL_CONTROLLER_TIMER_DELAY 15
#endif

#ifndef RADIAL_CONTROLLER_ROTATION_CONTINUE_STEP
#define RADIAL_CONTROLLER_ROTATION_CONTINUE_STEP RADIAL_CONTROLLER_RESOLUTION
#endif

static report_radial_controller_t radial_controller_report;

static int16_t radial_controller_rotation = 0;
static bool is_radial_controller_rotate_finished = true;
static bool is_clockwise = true;
static uint16_t radial_controller_timer = 0;

void radial_controller_task(void) {
	if (!is_radial_controller_rotate_finished) {
        if (timer_elapsed(radial_controller_timer) > RADIAL_CONTROLLER_TIMER_DELAY) {
            if (is_clockwise) {
                radial_controller_rotation = radial_controller_rotation > (3600 - RADIAL_CONTROLLER_ROTATION_STEP) ? \
                                        3600 : radial_controller_rotation + RADIAL_CONTROLLER_ROTATION_STEP;
            } else {
                radial_controller_rotation = radial_controller_rotation < (-(3600 - RADIAL_CONTROLLER_ROTATION_STEP)) ? \
                                        -3600 : radial_controller_rotation - RADIAL_CONTROLLER_ROTATION_STEP;
            }
            radial_controller_timer = timer_read();
#ifdef RADIAL_CONTROLLER_ROTATION_CONTINUE_BUTTON_ENABLE
            if (radial_controller_rotation >= RADIAL_CONTROLLER_ROTATION_CONTINUE_STEP \
                || radial_controller_rotation <= -RADIAL_CONTROLLER_ROTATION_CONTINUE_STEP) {
                radial_controller_dial_finished();
                is_radial_controller_rotate_finished = false;
            }
#endif
        }
    }
}

void radial_controller_event_finished(void) {
    radial_controller_report.raw = 0;
    host_radial_send(radial_controller_report.raw);
}

void radial_controller_button_update(bool pressed) {
    if (pressed) {
        radial_controller_report.button = 1;
    } else {
        radial_controller_report.raw = 0;
    }
    host_radial_send(radial_controller_report.raw);
}

void radial_controller_dial_update(bool clockwise, bool continued) {
    if (!continued) {
        if (clockwise) {
            radial_controller_report.dial = RADIAL_CONTROLLER_RESOLUTION;
        } else {
            radial_controller_report.dial = -RADIAL_CONTROLLER_RESOLUTION;
        }
        host_radial_send(radial_controller_report.raw);
        radial_controller_report.dial = 0;
    } else {
        is_clockwise = clockwise;
        is_radial_controller_rotate_finished = false;
        radial_controller_timer = timer_read();
    }
}

void radial_controller_dial_finished(void) {
    is_radial_controller_rotate_finished = true;
    radial_controller_report.dial = radial_controller_rotation;
    host_radial_send(radial_controller_report.raw);
    radial_controller_report.dial = 0;
    radial_controller_rotation = 0;
    radial_controller_timer = 0;
}

bool process_radial_controller(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DIAL_BUT:
            if (record->event.pressed) {
                radial_controller_button_update(true);
            } else {
                radial_controller_button_update(false);
            }
            return false;
        case DIAL_L:
            if (record->event.pressed) {
                radial_controller_dial_update(false, false);
            }
            return false;
        case DIAL_R:
            if (record->event.pressed) {
                radial_controller_dial_update(true, false);
            }
            return false;
        case DIAL_LC:
            if (record->event.pressed) {
                radial_controller_dial_update(false, true);
            } else {
                radial_controller_dial_finished();
            }
            return false;
        case DIAL_RC:
            if (record->event.pressed) {
                radial_controller_dial_update(true, true);
            } else {
                radial_controller_dial_finished();
            }
            return false;
    }
    return true;
}
