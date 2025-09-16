/* Copyright 2021 JasonRen(biu)
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
#include "zpadble.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
        {0,  1,  3,  4,  6,  7,  9,  10,  12,  13,  15,  16},
    },
    {
      // LED Index to Physical Position
    },
    {
      // LED Index to Flag
      2,2,2,2,2, 2,2,2,2,2,
      2,2,2,2,2, 2,2,2,2,2
    }
};


#endif

void keyboard_post_init_kb(void) {
    debug_enable = true;
}
