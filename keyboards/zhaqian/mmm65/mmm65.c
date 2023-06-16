/* Copyright 2023 ZhaQian
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
		{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16},
		{17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33},
		{34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, NO_LED, 48, 49},
		{50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, NO_LED, 64, 65},
		{NO_LED, NO_LED, 66, 67, 68, NO_LED, NO_LED, 69, NO_LED, NO_LED, NO_LED, 70, 71, NO_LED, 72, 73, 74},
    }, {
       	{6, 10}, {18, 10}, {36, 10}, {48, 10}, {61, 10}, {73, 10}, {85, 10}, {97, 10}, {109, 10}, {121, 10}, {133, 10}, {145, 10}, {157, 10}, {170, 10}, {182, 10}, {200, 10}, {218, 10}, 
		{6, 23}, {18, 23}, {39, 23}, {54, 23}, {67, 23}, {79, 23}, {91, 23}, {103, 23}, {115, 23}, {127, 23}, {139, 23}, {151, 23}, {163, 23}, {176, 23}, {188, 23}, {203, 23}, {218, 23}, 
		{6, 35}, {18, 35}, {41, 35}, {58, 35}, {70, 35}, {82, 35}, {94, 35}, {106, 35}, {118, 35}, {130, 35}, {142, 35}, {154, 35}, {166, 35}, {179, 35}, {198, 35}, {218, 35}, 
		{6, 48}, {18, 48}, {44, 48}, {64, 48}, {76, 48}, {88, 48}, {100, 48}, {112, 48}, {124, 48}, {136, 48}, {148, 48}, {160, 48}, {173, 48}, {189, 48}, {206, 48}, {218, 48}, 
		{38, 61}, {53, 61}, {68, 61}, {114, 61}, {159, 61}, {174, 61}, {194, 61}, {206, 61}, {218, 61}, 
        {37, 20}, {74, 20}, {111, 20}, {148, 20}, {185, 20},
    },{
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
        4, 4, 4, 4, 4, 4, 4, 4, 4,
        2, 2, 2, 2, 2,
    }
};

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) { 
        return false; 
    }

    HSV hsv = {0, 0, rgb_matrix_get_val()};
    RGB rgb;
    if (host_keyboard_led_state().caps_lock) {
        rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(75, rgb.r, rgb.g, rgb.b);
        rgb_matrix_set_color(77, rgb.r, rgb.g, rgb.b);
        rgb_matrix_set_color(79, rgb.r, rgb.g, rgb.b);
    }

    switch(biton32(layer_state)) {
        case 1: {
            hsv = (HSV){0, 255, rgb_matrix_get_val()};
            rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(76, rgb.r, rgb.g, rgb.b); 
            rgb_matrix_set_color(78, rgb.r, rgb.g, rgb.b);
            break;
        }
        case 2: {
            hsv = (HSV){170, 255, rgb_matrix_get_val()};
            rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(76, rgb.r, rgb.g, rgb.b); 
            rgb_matrix_set_color(78, rgb.r, rgb.g, rgb.b);
            break;
        }
        case 3: {
            hsv = (HSV){48, 255, rgb_matrix_get_val()};
            rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(76, rgb.r, rgb.g, rgb.b); 
            rgb_matrix_set_color(78, rgb.r, rgb.g, rgb.b);
            break;
        }
        default: break;
    }
    return true;
}

#endif

void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_TIM3_REMAP_PARTIALREMAP;
}