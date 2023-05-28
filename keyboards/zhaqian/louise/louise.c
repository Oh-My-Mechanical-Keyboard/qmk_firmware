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
#ifdef VIA_ENABLE
#include "rgb_control.h"

enum via_custom_rgb_control_value {
    id_rgb_control_enable                = 1,
	id_rgb_control_brightness            = 2,      
	id_rgb_control_color                 = 3, 
};
#endif

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {
	{
		{NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
		{NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
		{NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
		{NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
	}, {
		{20, 50}, {50, 51}, {80, 52}, {105, 55}, {130, 52}, {160, 51}, {190, 50}, 
		{200, 20}, {164, 20}, {134, 18}, {104, 16}, {76, 18}, {46, 20}, {12, 20},
		{0, 2}, {18, 2}, {36, 2}, {54, 2}, {72, 2}, {90, 2}, {108, 2}, {126, 2}, {144, 2}, {162, 2}, {180, 2}, {198, 2}, {216, 2},
		{112, 2}, {112, 32}, {112, 62},
	}, {
		2, 2, 2, 2, 2, 2, 2, 
		2, 2, 2, 2, 2, 2, 2,
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		8, 8, 8,
	}
};

const static HSV hsv[] = {{HSV_RED}, {HSV_BLUE}, {HSV_YELLOW}, {HSV_GREEN}};

#define LOUISE_RGB_INDICATOR_SET_COLOR(r, g, b) 	\
do {										  		\
	rgb_matrix_set_color(27, r, g, b);				\
	rgb_matrix_set_color(28, r, g, b);				\
	rgb_matrix_set_color(29, r, g, b);				\
} while (0)									  

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) { 
        return false; 
    }
#ifdef VIA_ENABLE
	rgb_control_task();
#endif
	uint8_t layer_now = biton32(layer_state);
	// Layer Indicator
	if (layer_now != 0)
	{
		RGB rgb = hsv_to_rgb(hsv[layer_now]);
		LOUISE_RGB_INDICATOR_SET_COLOR(rgb.r, rgb.g, rgb.b);
	}
	// Caps Lock Indicator
	if (host_keyboard_led_state().caps_lock) {
		RGB rgb = hsv_to_rgb(hsv[0]);
		LOUISE_RGB_INDICATOR_SET_COLOR(rgb.r, rgb.g, rgb.b);
    }
    return true;
}
#endif

#ifdef VIA_ENABLE
void keyboard_post_init_kb(void) {
    rgb_control_init();
}
void via_custom_rgb_control_command(uint8_t *data, uint8_t length);
void via_custom_rgb_control_set_value(uint8_t *data);
void via_custom_rgb_control_get_value(uint8_t *data);
void via_custom_rgb_control_save(void);

// via custom control
bool via_custom_value_command_user(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id = &(data[0]);
    uint8_t *channel_id = &(data[1]);
    if (*channel_id == 66) {
        via_custom_rgb_control_command(data, length);
        return true;
    }
    *command_id = id_unhandled;
    *channel_id = *channel_id;  // force use of variable
    return false;
}

void via_custom_rgb_control_command(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *value_id_and_data = &(data[2]);

    switch (*command_id) {
        case id_custom_set_value: {
            via_custom_rgb_control_set_value(value_id_and_data);
            break;
        }
        case id_custom_get_value: {
            via_custom_rgb_control_get_value(value_id_and_data);
            break;
        }
        case id_custom_save: {
            via_custom_rgb_control_save();
            break;
        }
        default: {
            *command_id = id_unhandled;
            break;
        }
    }
}

void via_custom_rgb_control_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case id_rgb_control_enable: {
            rgb_control_set_sector_enable(value_data[0], value_data[1], false);
            break;
        }
        case id_rgb_control_brightness: {
            rgb_control_set_sector_val(value_data[0], value_data[1], false);
            break;
        }
        case id_rgb_control_color: {
            rgb_control_set_sector_hue(value_data[0], value_data[1], false);
            rgb_control_set_sector_sat(value_data[0], value_data[2], false);
            break;
        }
    }
}

void via_custom_rgb_control_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch (*value_id) {
        case id_rgb_control_enable: {
            value_data[1] = rgb_control_get_sector_enable(value_data[0]);
            break;
        }
        case id_rgb_control_brightness: {
            value_data[1] = rgb_control_get_sector_val(value_data[0]);
            break;
        }
        case id_rgb_control_color: {
            value_data[1] = rgb_control_get_sector_hue(value_data[0]);
            value_data[2] = rgb_control_get_sector_sat(value_data[0]);
            break;
        }
    }
}

void via_custom_rgb_control_save(void) {
	update_rgb_control();
}
#endif

void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_TIM3_REMAP_PARTIALREMAP;
}