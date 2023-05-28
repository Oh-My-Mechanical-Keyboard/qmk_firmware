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
        {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED}, 
        {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED}, 
        {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED} 
    },{
        {0, 0}, {14, 0}, {28, 0}, {42, 0}, {56, 0}, {70, 0}, {84, 0}, {98, 0}, {112, 0}, {126, 0}, {140, 0}, {154, 0}, {168, 0}, {182, 0}, {196, 0}, {210, 0},
        {0, 9}, {14, 9}, {28, 9}, {42, 9}, {56, 9}, {70, 9}, {84, 9}, {98, 9}, {112, 9}, {126, 9}, {140, 9}, {154, 9}, {168, 9}, {182, 9}, {196, 9}, {210, 9},
        {0, 18}, {14, 18}, {28, 18}, {42, 18}, {56, 18}, {70, 18}, {84, 18}, {98, 18}, {112, 18}, {126, 18}, {140, 18}, {154, 18}, {168, 18}, {182, 18}, {196, 18}, {210, 18},
        {0, 27}, {14, 27}, {28, 27}, {42, 27}, {56, 27}, {70, 27}, {84, 27}, {98, 27}, {112, 27}, {126, 27}, {140, 27}, {154, 27}, {168, 27}, {182, 27}, {196, 27}, {210, 27},
        {0, 36}, {14, 36}, {28, 36}, {42, 36}, {56, 36}, {70, 36}, {84, 36}, {98, 36}, {112, 36}, {126, 36}, {140, 36}, {154, 36}, {168, 36}, {182, 36}, {196, 36}, {210, 36},
        {0, 45}, {14, 45}, {28, 45}, {42, 45}, {56, 45}, {70, 45}, {84, 45}, {98, 45}, {112, 45}, {126, 45}, {140, 45}, {154, 45}, {168, 45}, {182, 45}, {196, 45}, {210, 45},
        {0, 54}, {14, 54}, {28, 54}, {42, 54}, {56, 54}, {70, 54}, {84, 54}, {98, 54}, {112, 54}, {126, 54}, {140, 54}, {154, 54}, {168, 54}, {182, 54}, {196, 54}, {210, 54},
        {0, 63}, {14, 63}, {28, 63}, {42, 63}, {56, 63}, {70, 63}, {84, 63}, {98, 63}, {112, 63}, {126, 63}, {140, 63}, {154, 63}, {168, 63}, {182, 63}, {196, 63}, {210, 63}
    },{
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
    }
};

#endif

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  // debug_enable=true;
  // debug_matrix=true;
  // debug_keyboard=true;
  // debug_mouse=true;
}



