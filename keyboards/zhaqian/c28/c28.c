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
		{0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
		{10, 11, 12, 13, 14, 15, 16, 17, 18, 19},
		{NO_LED, 20, 21, 22, 23, 24, NO_LED, 25, 26, 27},
	}, {
		{11, 5}, {34, 5}, {56, 5}, {78, 5}, {101, 5}, {123, 5}, {146, 5}, {168, 5}, {190, 5}, {213, 5}, 
		{11, 26}, {34, 26}, {56, 26}, {78, 26}, {101, 26}, {123, 26}, {146, 26}, {168, 26}, {190, 26}, {213, 26}, 
		{22, 48}, {45, 48}, {67, 48}, {90, 48}, {123, 48}, {157, 48}, {179, 48}, {202, 48}, 
	}, {
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
		4, 4, 4, 4, 4, 4, 4, 4, 
	}
};

#endif
