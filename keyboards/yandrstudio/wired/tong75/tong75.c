// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "tong75.h"

#ifdef RGBLIGHT_ENABLE

// Light LEDs 6 to 9 and 12 to 15 red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HSV_RED}
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
