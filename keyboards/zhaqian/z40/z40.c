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
		{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
		{12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, NO_LED},
		{23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, NO_LED},
		{34, 35, 36, 37, NO_LED, 38, NO_LED, 39, 40, 41, 42, NO_LED},
	}, {
		{9, 12}, {28, 12}, {47, 12}, {65, 12}, {84, 12}, {103, 12}, {121, 12}, {140, 12}, {159, 12}, {177, 12}, {196, 12}, {215, 12}, 
		{12, 28}, {33, 28}, {51, 28}, {70, 28}, {89, 28}, {107, 28}, {126, 28}, {145, 28}, {163, 28}, {182, 28}, {208, 28}, 
		{16, 44}, {42, 44}, {61, 44}, {79, 44}, {98, 44}, {117, 44}, {135, 44}, {154, 44}, {173, 44}, {191, 44}, {212, 44}, 
		{12, 60}, {33, 60}, {54, 60}, {84, 60}, {121, 60}, {149, 60}, {170, 60}, {191, 60}, {212, 60}, 
	}, {
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
		4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
		4, 4, 4, 4, 4, 4, 4, 4, 4, 
	}
};

#endif
