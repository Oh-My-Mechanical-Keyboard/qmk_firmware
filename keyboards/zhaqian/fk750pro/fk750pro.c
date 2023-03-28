/* Copyright 2022 ZhaQian
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

#include QMK_KEYBOARD_H

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {
    {
        {68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, NO_LED, NO_LED, NO_LED},
        {53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, NO_LED},
        {38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, NO_LED},
        {24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, NO_LED, 36, 37, NO_LED},
        {11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, NO_LED, 22, 23, NO_LED, NO_LED},
        {0, 1, 2, NO_LED, NO_LED, 4, NO_LED, NO_LED, NO_LED, 6, 7, NO_LED, 8, 9, 10, NO_LED},
    }, {
        {8, 62},   {26, 62},  {43, 62},  {71, 62},  {95, 62},  {119, 62}, {147, 62}, {164, 62}, {186, 62}, {200, 62}, {214, 62},
        {15, 51},  {38, 51},  {52, 51},  {65, 51},  {79, 51},  {93, 51},  {107, 51}, {121, 51}, {135, 51}, {148, 51}, {162, 51}, {181, 51}, {200, 51},
        {12, 41},  {31, 41},  {45, 41},  {59, 41},  {72, 41},  {86, 41},  {100, 41}, {114, 41}, {128, 41}, {141, 41}, {155, 41}, {169, 41}, {191, 41}, {217, 41},
        {10, 31},  {27, 31},  {41, 31},  {55, 31},  {69, 31},  {83, 31},  {97, 31},  {110, 31}, {124, 31}, {138, 31}, {152, 31}, {166, 31}, {179, 31}, {196, 31}, {217, 31},
        {8, 21},   {21, 21},  {35, 21},  {48, 21},  {62, 21},  {76, 21},  {90, 21},  {103, 21}, {117, 21}, {131, 21}, {145, 21}, {159, 21}, {172, 21}, {193, 21}, {217, 21},
        {8, 8},    {34, 8},   {48, 8},   {62, 8},   {76, 8},   {97, 8},   {110, 8},  {124, 8},  {138, 8},  {159, 8},  {173, 8},  {186, 8},  {200, 8},
        {223, 12}, {223, 22}, {223, 32}, {223, 42}, {223, 52},
        {209, 63}, {191, 63}, {174, 63}, {157, 63}, {140, 63}, {122, 63}, {105, 63}, {88, 63},  {71, 63},  {53, 63},  {36, 63},  {17, 63},
        {2, 54},   {2, 44},   {2, 33},   {2, 23},   {2, 12},
        {26, 12},  {50, 12},  {74, 12},  {98, 12},  {122, 12}, {146, 12}, {171, 12}, {197, 12},
    }, {
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2,
    }
};

uint8_t rgb_matrix_map_row_column_to_led_kb(uint8_t row, uint8_t column, uint8_t *led_i) {
    if (row == 5 && column == 5) {
        led_i[0] = 3;
        led_i[1] = 5;
        return 2;
    }
    return 0;
}

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) { 
        return false; 
    }

    HSV hsv = {128, 255, rgb_matrix_get_val()};
    RGB rgb = hsv_to_rgb(hsv);
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(24, rgb.r, rgb.g, rgb.b);
    }
    return true;
}
#endif

#ifdef ENCODER_ENABLE
static uint8_t encoder_state[ENCODERS] = {0};
static keypos_t encoder_cw[ENCODERS] = ENCODERS_CW_KEY;
static keypos_t encoder_ccw[ENCODERS] = ENCODERS_CCW_KEY;

void encoder_action_unregister(void) {
    for (int index = 0; index < ENCODERS; ++index) {
        if (encoder_state[index]) {
            keyevent_t encoder_event = (keyevent_t) {
                .key = encoder_state[index] >> 1 ? encoder_cw[index] : encoder_ccw[index],
                .pressed = false,
                .time = (timer_read() | 1)
            };
            encoder_state[index] = 0;
            action_exec(encoder_event);
        }
    }
}

void encoder_action_register(uint8_t index, bool clockwise) {
    keyevent_t encoder_event = (keyevent_t) {
        .key = clockwise ? encoder_cw[index] : encoder_ccw[index],
        .pressed = true,
        .time = (timer_read() | 1)
    };
    encoder_state[index] = (clockwise ^ 1) | (clockwise << 1);
    action_exec(encoder_event);
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    encoder_action_register(index, clockwise);
    return true;
};
#endif

void matrix_scan_kb(void) {
#ifdef ENCODER_ENABLE
    encoder_action_unregister();
#endif
    matrix_scan_user();
}