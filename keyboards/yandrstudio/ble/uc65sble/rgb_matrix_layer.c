// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgb_matrix_layer.h"
#include "rgb_matrix.h"
#include "color.h"
#include <stdlib.h>

rgb_matrix_adv_layers_mask_t                 rgb_matrix_adv_enabled_layer_mask = 0;
rgb_matrix_adv_layer_segment_t const *const *rgb_matrix_layers                 = NULL;

#ifdef RGB_MATRIX_LAYERS_OVERRIDE_RGB_OFF
uint8_t layer_off2on_idx[RGB_MATRIX_MAX_LAYERS+2];
#endif

void rgb_matrix_adv_layers_write(void) {
    uint8_t i = 0;
#ifdef RGB_MATRIX_LAYERS_OVERRIDE_RGB_OFF
    uint8_t offi = 0, oni = RGB_MATRIX_MAX_LAYERS-1;
    for (i = 0; i < RGB_MATRIX_MAX_LAYERS; i++) {
        if ((rgb_matrix_adv_enabled_layer_mask & (1 << i)) == 0) {
            layer_off2on_idx[offi++] = i;
        } else {
            layer_off2on_idx[oni--] = i;
        }
    }
#endif
#ifdef RGB_MATRIX_LAYERS_OVERRIDE_RGB_OFF
    // For each layer
    for (i = 0; i < RGB_MATRIX_MAX_LAYERS; i++) {
        // if this led has been set color with layer on, not set it
        // so we should process off layer first to avoid overwrite the led of lower rgb matrix layer that is on
        bool off_flag = false;
        if ((rgb_matrix_adv_enabled_layer_mask & (1 << layer_off2on_idx[i])) == 0) {
            if (!rgb_matrix_is_enabled()) off_flag = true;
            else continue;
        }
        const rgb_matrix_adv_layer_segment_t *segment_ptr = pgm_read_ptr(rgb_matrix_layers+layer_off2on_idx[i]);
#else
    i = 0;
    // For each layer
    for (const rgb_matrix_adv_layer_segment_t *const *layer_ptr = rgb_matrix_layers; i < RGB_MATRIX_MAX_LAYERS; layer_ptr++, i++) {
        if ((rgb_matrix_adv_enabled_layer_mask & (1 << i)) == 0) {
                continue; // Layer is disabled
        }
        const rgb_matrix_adv_layer_segment_t *segment_ptr = pgm_read_ptr(layer_ptr);
#endif
        if (segment_ptr == NULL) {
            break; // No more layers
        }
        // For each segment
        while (1) {
            rgb_matrix_adv_layer_segment_t segment;
            memcpy_P(&segment, segment_ptr, sizeof(rgb_matrix_adv_layer_segment_t));
            if (segment.index == RGB_MATRIX_END_SEGMENT_INDEX) {
                break; // No more segments
            }
#ifdef RGB_MATRIX_LAYERS_RETAIN_VAL
            segment.val = rgb_matrix_get_val();
#endif
            RGB rgb = hsv_to_rgb((HSV){segment.hue, segment.sat, segment.val});
#ifdef RGB_MATRIX_LAYERS_OVERRIDE_RGB_OFF
            if (off_flag) rgb = (RGB){0, 0, 0};
#endif
            // Write segment.count LEDs
            for (uint8_t j = 0; j < segment.count; ++j) {
                rgb_matrix_set_color(segment.index + j, rgb.r, rgb.g, rgb.b);
            }
            segment_ptr++;
        }
    }
}

void rgb_matrix_adv_set_layer_state(uint8_t layer, bool enabled) {
    rgb_matrix_adv_layers_mask_t mask = 1 << layer;
    if (enabled) {
        rgb_matrix_adv_enabled_layer_mask |= mask;
    } else {
        rgb_matrix_adv_enabled_layer_mask &= ~mask;
    }
    rgb_matrix_adv_layers_write();
}

rgb_matrix_adv_layers_mask_t _blinking_layer_mask = 0;
static uint16_t              _repeat_timer;
static uint8_t               _times_remaining;
static uint16_t              _dur;

void rgb_matrix_adv_blink_layer_repeat(uint8_t layer, uint16_t duration_ms, uint8_t times) {
    if (times > UINT8_MAX / 2) {
        times = UINT8_MAX / 2;
    }

    _times_remaining = times * 2;
    _dur             = duration_ms;

    rgb_matrix_adv_set_layer_state(layer, true);
    _times_remaining--;
    _blinking_layer_mask |= (rgb_matrix_adv_layers_mask_t)1 << layer;
    _repeat_timer = sync_timer_read() + duration_ms;
}

void rgb_matrix_adv_unblink_layer(uint8_t layer) {
    rgb_matrix_adv_set_layer_state(layer, false);
    _blinking_layer_mask &= ~((rgb_matrix_adv_layers_mask_t)1 << layer);
}

void rgb_matrix_adv_blink_layer_repeat_helper(void) {
    if (_blinking_layer_mask != 0 && timer_expired(sync_timer_read(), _repeat_timer)) {
        for (uint8_t layer = 0; layer < RGB_MATRIX_MAX_LAYERS; layer++) {
            if ((_blinking_layer_mask & (rgb_matrix_adv_layers_mask_t)1 << layer) != 0) {
                if (_times_remaining % 2 == 1) {
                    rgb_matrix_adv_set_layer_state(layer, false);
                } else {
                    rgb_matrix_adv_set_layer_state(layer, true);
                }
            }
        }
        _times_remaining--;
        if (_times_remaining <= 0) {
            _blinking_layer_mask = 0;
        } else {
            _repeat_timer = sync_timer_read() + _dur;
        }
    }
}
