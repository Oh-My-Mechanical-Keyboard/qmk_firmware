// Copyright 2024 HackStone-HAL9000 (@Jason)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgbm_layer.h"
#include "rgb_matrix.h"
#include "color.h"
#include <stdlib.h>
#include <string.h>

rgb_matrix_adv_layer_segment_t  **rgb_matrix_layers = NULL;

struct rgbm_blink_state_t
{
    /* data */
    bool     enable;
    bool     blink_enable;
    uint32_t duration_ms;
    uint32_t times;
    uint32_t last_time;
} rgbm_blink_state[RGB_MATRIX_MAX_LAYERS];


void rgb_matrix_adv_layers_init(rgb_matrix_adv_layer_segment_t **user_rgbm_layer) {
    rgb_matrix_layers = user_rgbm_layer;
    for (uint8_t i = 0; i < RGB_MATRIX_MAX_LAYERS; ++i) {
        rgbm_blink_state[i].enable = false;
        rgbm_blink_state[i].blink_enable = false;
        rgbm_blink_state[i].duration_ms = 0;
        rgbm_blink_state[i].times = 0;
        rgbm_blink_state[i].last_time = 0;
    }
}

void rgb_matrix_adv_static_layer_enable(uint8_t layer) {
    rgbm_blink_state[layer].enable = true;
    rgbm_blink_state[layer].blink_enable = false;
}

void rgb_matrix_adv_blink_layer_repeat(uint8_t layer, uint16_t duration_ms, uint8_t times) {
    if (times > UINT8_MAX / 2) {
        times = UINT8_MAX / 2;
    }
    rgbm_blink_state[layer].enable = true;
    rgbm_blink_state[layer].blink_enable = true;
    rgbm_blink_state[layer].times = times*2+1; // 奇数
    rgbm_blink_state[layer].duration_ms = duration_ms;
    rgbm_blink_state[layer].last_time = 0;
}

void rgb_matrix_adv_disable_layer(uint8_t layer) {
    rgbm_blink_state[layer].enable = false;
    rgbm_blink_state[layer].blink_enable = false;
}

static void rgb_matrix_adv_static_layer_task(uint8_t layer) {
    rgb_matrix_adv_layer_segment_t *segment_ptr = rgb_matrix_layers[layer];
    if (segment_ptr == NULL) {
        return; // No more layers
    }
    // For each segment
    while (1) {
        rgb_matrix_adv_layer_segment_t segment;
        memcpy(&segment, segment_ptr, sizeof(rgb_matrix_adv_layer_segment_t));
        if (segment.index == RGB_MATRIX_END_SEGMENT_INDEX) {
            break; // No more segments
        }
#ifdef RGB_MATRIX_LAYERS_RETAIN_VAL
        segment.val = rgb_matrix_get_val();
#endif
        RGB rgb = hsv_to_rgb((HSV){segment.hue, segment.sat, segment.val});
        // Write segment.count LEDs
        for (uint8_t j = 0; j < segment.count; ++j) {
            rgb_matrix_set_color(segment.index + j, rgb.r, rgb.g, rgb.b);
        }
        segment_ptr++;
    }
}

static void rgb_matrix_adv_blink_layer_task(uint8_t layer) {
    if (rgbm_blink_state[layer].times == 0) {
        rgb_matrix_adv_disable_layer(layer);
        return;
    }
    if (rgbm_blink_state[layer].last_time == 0 || timer_elapsed32(rgbm_blink_state[layer].last_time) >= rgbm_blink_state[layer].duration_ms) {
        rgbm_blink_state[layer].last_time = timer_read32();
        if (rgbm_blink_state[layer].times > 0) rgbm_blink_state[layer].times--;
    }

    rgb_matrix_adv_layer_segment_t *segment_ptr =rgb_matrix_layers[layer];
    if (segment_ptr == NULL) {
        return; // No more layers
    }
    // For each segment
    while (1) {
        rgb_matrix_adv_layer_segment_t segment;
        memcpy(&segment, segment_ptr, sizeof(rgb_matrix_adv_layer_segment_t));
        if (segment.index == RGB_MATRIX_END_SEGMENT_INDEX) {
            break; // No more segments
        }
#ifdef RGB_MATRIX_LAYERS_RETAIN_VAL
        segment.val = rgb_matrix_get_val();
#endif
        RGB rgb = hsv_to_rgb((HSV){segment.hue, segment.sat, segment.val});
        // Write segment.count LEDs
        for (uint8_t j = 0; j < segment.count; ++j) {
            if (rgbm_blink_state[layer].times % 2 == 1) {
                rgb_matrix_set_color(segment.index + j, 0, 0, 0);
            } else {
                rgb_matrix_set_color(segment.index + j, rgb.r, rgb.g, rgb.b);
            }
        }
        segment_ptr++;
    }
}

void rgb_matrix_adv_layer_task(void) {
    for (uint8_t layer = 0; layer < RGB_MATRIX_MAX_LAYERS; layer++) {
        if (rgbm_blink_state[layer].enable == false) continue;
        if (rgbm_blink_state[layer].blink_enable) {
            rgb_matrix_adv_blink_layer_task(layer);
        } else {
            rgb_matrix_adv_static_layer_task(layer);
        }
    }
}

bool rgb_matrix_adv_layer_is_enable(uint8_t layer) {
    if (layer >= RGB_MATRIX_MAX_LAYERS) return false;
    return rgbm_blink_state[layer].enable;
}
