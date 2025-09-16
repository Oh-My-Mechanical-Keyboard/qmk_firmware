// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "buff67v3.h"

#ifdef RGBLIGHT_ENABLE

#   ifndef FACTORY_TEST

#if PRODUCT_YR_ID == 3
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 4, HSV_RED});
#else
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_RED});
#endif

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(my_capslock_layer);

bool led_update_kb(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

void keyboard_post_init_kb(void) {
    rgblight_reload_from_eeprom();
    rgblight_layers = my_rgb_layers;
}

#   endif

#endif
