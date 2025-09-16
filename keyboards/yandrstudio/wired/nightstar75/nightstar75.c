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
#include "nightstar75.h"

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case LOCK_GUI:
            process_magic(GUI_TOG, record);
            return false;
        default:
            return true;
    }
    return true;
}

#ifdef RGBLIGHT_ENABLE

// Light LEDs 6 to 9 and 12 to 15 red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 4, HSV_RED}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer
);

void keyboard_post_init_kb(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
    rgblight_reload_from_eeprom();
}

bool led_update_kb(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}
#endif
