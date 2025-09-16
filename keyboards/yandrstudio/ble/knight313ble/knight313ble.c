// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "knight313ble.h"

#if defined(RGBLIGHT_ENABLE)

#   ifndef FACTORY_TEST

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_RED});


const rgblight_segment_t* const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST(my_capslock_layer);

void keyboard_post_init_kb(void) {
    rgblight_layers = _rgb_layers;
    rgblight_reload_from_eeprom();
    keyboard_post_init_user();
}

bool led_update_kb(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}
#   endif
#endif
