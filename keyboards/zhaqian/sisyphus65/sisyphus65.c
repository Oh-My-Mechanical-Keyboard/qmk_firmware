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
		{NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
		{NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
        {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
        {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
        {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
	}, {
        {0, 0}, {0, 0}, {112, 32},
	}, {
        4, 4, 4
	}
};

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) { 
        return false; 
    }

    HSV hsv = {HSV_WHITE};
    RGB rgb;
    if (host_keyboard_led_state().caps_lock) {
        hsv.v = rgb_matrix_get_val();
        rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(0, rgb.r, rgb.g, rgb.b);
    } else {
        rgb_matrix_set_color(0, 0x00, 0x00, 0x00);
    }
    
    switch(biton32(layer_state)) {
        case 1: {
            hsv = (HSV){HSV_RED};
            hsv.v = rgb_matrix_get_val();
            rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(1, rgb.r, rgb.g, rgb.b); 
            break;
        }
        case 2: {
            hsv = (HSV){HSV_BLUE};
            hsv.v = rgb_matrix_get_val();
            rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(1, rgb.r, rgb.g, rgb.b); 
            break;
        }
        case 3: {
            hsv = (HSV){HSV_PURPLE};
            hsv.v = rgb_matrix_get_val();
            rgb = hsv_to_rgb(hsv);
            rgb_matrix_set_color(1, rgb.r, rgb.g, rgb.b); 
            break;
        }
        default: {
            rgb_matrix_set_color(1, 0x00, 0x00, 0x00); 
            break;
        }
    }
    return true;
}

#endif

void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_TIM2_REMAP_PARTIALREMAP1;
}