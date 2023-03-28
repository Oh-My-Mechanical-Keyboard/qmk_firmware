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
		{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
		{14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, NO_LED, 26},
		{27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, NO_LED, 39},
		{40, 41, 42, NO_LED, 43, NO_LED, 44, NO_LED, 45, 46, 47, 48, NO_LED, 49},
	}, {
		{8, 17}, {23, 17}, {39, 17}, {54, 17}, {70, 17}, {85, 17}, {100, 17}, {116, 17}, {131, 17}, {147, 17}, {162, 17}, {178, 17}, {193, 17}, {216, 17},
		{10, 30}, {27, 30}, {42, 30}, {58, 30}, {73, 30}, {89, 30}, {104, 30}, {120, 30}, {135, 30}, {151, 30}, {166, 30}, {187, 30}, {216, 30},
		{14, 44}, {35, 44}, {50, 44}, {66, 44}, {81, 44}, {97, 44}, {112, 44}, {127, 44}, {143, 44}, {158, 44}, {176, 44}, {197, 47}, {216, 44},
		{10, 57}, {27, 57}, {44, 57}, {75, 57}, {114, 57}, {141, 57}, {160, 57}, {182, 61}, {197, 61}, {212, 61},
        {204, 64}, {175, 64}, {156, 64}, {131, 64}, {98, 64}, {58, 64}, {39, 64}, {13, 64},
        {10, 3}, {35, 3}, {63, 3}, {95, 3}, {127, 3}, {154, 3}, {172, 3}, {210, 3},
	}, {
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2,
	}
};

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) { 
        return false; 
    }

    HSV hsv = {0, 255, rgb_matrix_get_val()};
    RGB rgb = hsv_to_rgb(hsv);
    switch(biton32(layer_state)) {
        case 1: rgb_matrix_set_color(1, rgb.r, rgb.g, rgb.b); break;
        case 2: rgb_matrix_set_color(2, rgb.r, rgb.g, rgb.b); break;
        case 3: rgb_matrix_set_color(3, rgb.r, rgb.g, rgb.b); break;
        case 4: rgb_matrix_set_color(4, rgb.r, rgb.g, rgb.b); break;
        case 5: rgb_matrix_set_color(5, rgb.r, rgb.g, rgb.b); break;
        case 6: rgb_matrix_set_color(6, rgb.r, rgb.g, rgb.b); break;
        default: break;
    }
    return true;
}

#endif
