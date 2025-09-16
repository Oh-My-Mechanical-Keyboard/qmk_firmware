// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t index;  // The first LED to light
    uint8_t count;  // The number of LEDs to light
    uint8_t hue;
    uint8_t sat;
    uint8_t val;
} rgb_matrix_adv_layer_segment_t;

typedef uint32_t rgb_matrix_adv_layers_mask_t;

extern rgb_matrix_adv_layer_segment_t const *const *rgb_matrix_layers;

#define RGB_MATRIX_END_SEGMENT_INDEX (255)
#define RGB_MATRIX_END_SEGMENT \
    { RGB_MATRIX_END_SEGMENT_INDEX, 0, 0, 0, 0 }
#define RGB_MATRIX_LAYER_SEGMENTS(...) \
    { __VA_ARGS__, RGB_MATRIX_END_SEGMENT }
#define RGB_MATRIX_LAYERS_LIST(...) \
    { __VA_ARGS__, NULL }

#ifndef RGB_MATRIX_LAYERS_OVERRIDE_RGB_OFF
#    define RGB_MATRIX_LAYERS_OVERRIDE_RGB_OFF
#endif

#ifndef RGB_MATRIX_LAYERS_RETAIN_VAL
#    define RGB_MATRIX_LAYERS_RETAIN_VAL
#endif

#ifndef RGB_MATRIX_MAX_LAYERS
#    define RGB_MATRIX_MAX_LAYERS 8
#endif

void rgb_matrix_adv_set_layer_state(uint8_t layer, bool enabled);
void rgb_matrix_adv_blink_layer_repeat(uint8_t layer, uint16_t duration_ms, uint8_t times);
void rgb_matrix_adv_unblink_layer(uint8_t layer);
void rgb_matrix_adv_blink_layer_repeat_helper(void);
