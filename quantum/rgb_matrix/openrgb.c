/* Copyright 2020 Kasper
 *           2022 ZhaQian
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


#include "version.h"
#include "quantum.h"
#include "openrgb.h"
#include "raw_hid.h"
#include "string.h"
#include <color.h>
#include "keymap_introspection.h"

#define OPENRGB_EPSIZE 64

#if !defined(OPENRGB_DIRECT_MODE_STARTUP_RED)
#    define OPENRGB_DIRECT_MODE_STARTUP_RED 0
#endif

#if !defined(OPENRGB_DIRECT_MODE_STARTUP_GREEN)
#    define OPENRGB_DIRECT_MODE_STARTUP_GREEN 0
#endif

#if !defined(OPENRGB_DIRECT_MODE_STARTUP_BLUE)
#    define OPENRGB_DIRECT_MODE_STARTUP_BLUE 200
#endif

RGB g_openrgb_direct_mode_colors[RGB_MATRIX_LED_COUNT] = {[0 ... RGB_MATRIX_LED_COUNT - 1] = {OPENRGB_DIRECT_MODE_STARTUP_GREEN, OPENRGB_DIRECT_MODE_STARTUP_RED, OPENRGB_DIRECT_MODE_STARTUP_BLUE}};
static const uint8_t openrgb_rgb_matrix_effects_indexes[]           = {
    1,  2,

#ifdef ENABLE_RGB_MATRIX_ALPHAS_MODS
    3,
#endif
#ifdef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
    4,
#endif
#ifdef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
    5,
#endif
#ifdef ENABLE_RGB_MATRIX_BREATHING
    6,
#endif
#ifdef ENABLE_RGB_MATRIX_BAND_SAT
    7,
#endif
#ifdef ENABLE_RGB_MATRIX_BAND_VAL
    8,
#endif
#ifdef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
    9,
#endif
#ifdef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
    10,
#endif
#ifdef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
    11,
#endif
#ifdef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
    12,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_ALL
    13,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
    14,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
    15,
#endif
#ifdef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
    16,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
    17,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
    18,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
    19,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
    20,
#endif
#ifdef ENABLE_RGB_MATRIX_DUAL_BEACON
    21,
#endif
#ifdef ENABLE_RGB_MATRIX_RAINBOW_BEACON
    22,
#endif
#ifdef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
    23,
#endif
#ifdef ENABLE_RGB_MATRIX_RAINDROPS
    24,
#endif
#ifdef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
    25,
#endif
#ifdef ENABLE_RGB_MATRIX_HUE_BREATHING
    26,
#endif
#ifdef ENABLE_RGB_MATRIX_HUE_PENDULUM
    27,
#endif
#ifdef ENABLE_RGB_MATRIX_HUE_WAVE
    28,
#endif
#ifdef ENABLE_RGB_MATRIX_PIXEL_RAIN
    29,
#endif
#ifdef ENABLE_RGB_MATRIX_PIXEL_FLOW
    30,
#endif
#ifdef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
    31,
#endif
#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && defined(ENABLE_RGB_MATRIX_TYPING_HEATMAP)
    32,
#endif
#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && defined(ENABLE_RGB_MATRIX_DIGITAL_RAIN)
    33,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && defined ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
    34,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && defined ENABLE_RGB_MATRIX_SOLID_REACTIVE
    35,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && defined ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
    36,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && defined ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
    37,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && defined ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
    38,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && defined ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
    39,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && defined ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
    40,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && defined ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
    41,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && defined ENABLE_RGB_MATRIX_SPLASH
    42,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && defined ENABLE_RGB_MATRIX_MULTISPLASH
    43,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && defined ENABLE_RGB_MATRIX_SOLID_SPLASH
    44,
#endif
#if defined RGB_MATRIX_KEYREACTIVE_ENABLED && defined ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
    45,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_BREATHING
    46,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_BANDVAL
    47,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_BAND_PINWHEEL_SAT
    48,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_BAND_PINWHEEL_VAL
    49,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_BAND_SPIRAL_SAT
    50,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_BAND_SPIRAL_VAL
    51,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_RIGHT_LEFT
    52,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_DOWN_UP
    53,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_IN_OUT
    54,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_IN_OUT_DUAL
    55,
#endif
#ifdef ENABLE_RGB_MATRIX_FRACTAL
    56,
#endif
#ifdef ENABLE_RGB_MATRIX_FRACTAL_RGB
    57,
#endif
#ifdef ENABLE_RGB_MATRIX_KITT_RGB
    58,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_SIN_WAVE
    59,
#endif
#ifdef ENABLE_RGB_MATRIX_RAINBOW_SIN_WAVE
    60,
#endif
#ifdef ENABLE_RGB_MATRIX_RAINBOW_SIN_WAVE_REVERSE
    61,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_ALTER
    62,
#endif
#ifdef ENABLE_RGB_MATRIX_RAINBOW_ALTER
    63,
#endif
#ifdef ENABLE_RGB_MATRIX_STATIC_BREATHING_CIRCLE
    64,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_BREATHING_CIRCLE
    65,
#endif
#ifdef ENABLE_RGB_MATRIX_BLOOM
    66,
#endif
#ifdef ENABLE_RGB_MATRIX_COMMET
    67,
#endif
#ifdef ENABLE_RGB_MATRIX_ROTATE_RAINBOW
    68,
#endif
#ifdef ENABLE_RGB_MATRIX_MOTION_POINT
    69,
#endif
#ifdef ENABLE_RGB_MATRIX_ROTATE_BEAM_PENDULUM
    70,
#endif
#ifdef ENABLE_RGB_MATRIX_ROTATE_BEAM_WIPERS
    71,
#endif
#ifdef ENABLE_RGB_MATRIX_H_STACK
    72,
#endif
#ifdef ENABLE_RGB_MATRIX_V_STACK
    73,
#endif
#ifdef ENABLE_RGB_MATRIX_SWAP
    74,
#endif
#ifdef ENABLE_RGB_MATRIX_STATIC_ZIGZAG
    75,
#endif
#ifdef ENABLE_RGB_MATRIX_RAINBOW_ZIGZAG
    76,
#endif
#ifdef ENABLE_RGB_MATRIX_CANDY_TAP
    77,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_REACTIVE_MULTIWIDE
    78,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_REACTIVE_MULTICROSS
    79,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_REACTIVE_MULTINEXUS
    80,
#endif
#ifdef ENABLE_RGB_MATRIX_CYCLE_MULTISPLASH
    81,
#endif
#ifdef ENABLE_RGB_MATRIX_REACTIVE_MULTIWIDE_RGB
    82,
#endif
#ifdef ENABLE_RGB_MATRIX_REACTIVE_MULTICROSS_RGB
    83,
#endif
#ifdef ENABLE_RGB_MATRIX_REACTIVE_MULTINEXUS_RGB
    84,
#endif

};

static uint8_t raw_hid_buffer[OPENRGB_EPSIZE];
const uint8_t size = sizeof openrgb_rgb_matrix_effects_indexes / sizeof openrgb_rgb_matrix_effects_indexes[0];
static uint8_t mode_index = 0;

bool openrgb_command_handler(uint8_t *data, uint8_t length) {
    switch (*data) {
        case OPENRGB_GET_PROTOCOL_VERSION:
            openrgb_get_protocol_version();
            break;
        case OPENRGB_GET_QMK_VERSION:
            openrgb_get_qmk_version();
            break;
        case OPENRGB_GET_DEVICE_INFO:
            openrgb_get_device_info();
            break;
        case OPENRGB_GET_MODE_INFO:
            openrgb_get_mode_info();
            break;
        case OPENRGB_GET_LED_INFO:
            openrgb_get_led_info(data);
            break;
        case OPENRGB_GET_ENABLED_MODES:
            openrgb_get_enabled_modes();
            break;
        case OPENRGB_SET_MODE:
            openrgb_set_mode(data);
            break;
        case OPENRGB_DIRECT_MODE_SET_SINGLE_LED:
            openrgb_direct_mode_set_single_led(data);
            break;
        case OPENRGB_DIRECT_MODE_SET_LEDS:
            openrgb_direct_mode_set_leds(data);
            break;
    }

    if (*data != OPENRGB_DIRECT_MODE_SET_LEDS) {
        raw_hid_buffer[OPENRGB_EPSIZE - 1] = OPENRGB_END_OF_MESSAGE;
        // openrgb_hid_send(raw_hid_buffer, OPENRGB_EPSIZE);
        memcpy(data, raw_hid_buffer, OPENRGB_EPSIZE);
        memset(raw_hid_buffer, 0x00, OPENRGB_EPSIZE);
        return true;
    }
    return false;
}

void openrgb_get_protocol_version(void) {
    raw_hid_buffer[0] = OPENRGB_GET_PROTOCOL_VERSION;
    raw_hid_buffer[1] = OPENRGB_PROTOCOL_VERSION;
}
void openrgb_get_qmk_version(void) {
    raw_hid_buffer[0]    = OPENRGB_GET_QMK_VERSION;
    uint8_t current_byte = 1;
    for (uint8_t i = 0; (current_byte < (OPENRGB_EPSIZE - 2)) && (QMK_VERSION[i] != 0); i++) {
        raw_hid_buffer[current_byte] = QMK_VERSION[i];
        current_byte++;
    }
}
void openrgb_get_device_info(void) {
    raw_hid_buffer[0] = OPENRGB_GET_DEVICE_INFO;
    raw_hid_buffer[1] = RGB_MATRIX_LED_COUNT;
    raw_hid_buffer[2] = MATRIX_COLS * MATRIX_ROWS;

#define MASSDROP_VID 0x04D8
#if VENDOR_ID == MASSDROP_VID
#    define PRODUCT_STRING PRODUCT
#    define MANUFACTURER_STRING MANUFACTURER
#else
#    define PRODUCT_STRING STR(PRODUCT)
#    define MANUFACTURER_STRING STR(MANUFACTURER)
#endif

    uint8_t current_byte = 3;
    for (uint8_t i = 0; (current_byte < ((OPENRGB_EPSIZE - 2) / 2)) && (PRODUCT_STRING[i] != 0); i++) {
        raw_hid_buffer[current_byte] = PRODUCT_STRING[i];
        current_byte++;
    }
    raw_hid_buffer[current_byte] = 0;
    current_byte++;

    for (uint8_t i = 0; (current_byte + 2 < OPENRGB_EPSIZE) && (MANUFACTURER_STRING[i] != 0); i++) {
        raw_hid_buffer[current_byte] = MANUFACTURER_STRING[i];
        current_byte++;
    }
}
void openrgb_get_mode_info(void) {
    const HSV hsv_color = rgb_matrix_get_hsv();

    raw_hid_buffer[0] = OPENRGB_GET_MODE_INFO;
    raw_hid_buffer[1] = rgb_matrix_get_mode();
    raw_hid_buffer[2] = rgb_matrix_get_speed();
    raw_hid_buffer[3] = hsv_color.h;
    raw_hid_buffer[4] = hsv_color.s;
    raw_hid_buffer[5] = hsv_color.v;
}
void openrgb_get_led_info(uint8_t *data) {
    const uint8_t first_led   = data[1];
    const uint8_t number_leds = data[2];

    raw_hid_buffer[0] = OPENRGB_GET_LED_INFO;

    for (uint8_t i = 0; i < number_leds; i++) {
        const uint8_t led_idx = first_led + i;
        const uint8_t data_idx  = i * 7;

        if (led_idx >= RGB_MATRIX_LED_COUNT) {
            raw_hid_buffer[data_idx + 3] = OPENRGB_FAILURE;
        } else {
            raw_hid_buffer[data_idx + 1] = g_led_config.point[led_idx].x;
            raw_hid_buffer[data_idx + 2] = g_led_config.point[led_idx].y;
            raw_hid_buffer[data_idx + 3] = g_led_config.flags[led_idx];
            raw_hid_buffer[data_idx + 4] = g_openrgb_direct_mode_colors[led_idx].r;
            raw_hid_buffer[data_idx + 5] = g_openrgb_direct_mode_colors[led_idx].g;
            raw_hid_buffer[data_idx + 6] = g_openrgb_direct_mode_colors[led_idx].b;
        }

        uint8_t row   = 0;
        uint8_t col   = 0;
        uint8_t found = 0;

        for (row = 0; row < MATRIX_ROWS; row++) {
            for (col = 0; col < MATRIX_COLS; col++) {
                if (g_led_config.matrix_co[row][col] == led_idx) {
                    found = 1;
                    break;
                }
            }

            if (found == 1) {
                break;
            }
        }

        if (col >= MATRIX_COLS || row >= MATRIX_ROWS) {
            raw_hid_buffer[data_idx + 7] = KC_NO;
        }
        else {
            uint16_t kc = keycode_at_keymap_location(0, row, col);
            if (kc >= QK_TO && kc <= QK_LAYER_TAP_TOGGLE_MAX) {
                raw_hid_buffer[data_idx + 7] = 0xFE;
            }
            else if (kc >= QK_BASIC && kc <= QK_BASIC_MAX) {
                raw_hid_buffer[data_idx + 7] = (kc & 0xFF);
            }
            else {
                raw_hid_buffer[data_idx + 7] = KC_NO;
            }
        }
    }
}

void openrgb_get_enabled_modes(void) {
    raw_hid_buffer[0] = OPENRGB_GET_ENABLED_MODES;
    raw_hid_buffer[1] = size;
    for (int i = 0; i < 61; i++) {
        raw_hid_buffer[i + 2] = openrgb_rgb_matrix_effects_indexes[mode_index];
        mode_index ++;
        if (mode_index >= size)
        {
            mode_index = 0;
            break;
        }
    }
}

void openrgb_set_mode(uint8_t *data) {
    const uint8_t h     = data[1];
    const uint8_t s     = data[2];
    const uint8_t v     = data[3];
    const uint8_t mode  = data[4];
    const uint8_t speed = data[5];
    const uint8_t save = data[6];

    raw_hid_buffer[0] = OPENRGB_SET_MODE;

    if (h > 255 || s > 255 || v > 255 || mode >= RGB_MATRIX_EFFECT_MAX || speed > 255) {
        raw_hid_buffer[OPENRGB_EPSIZE - 2] = OPENRGB_FAILURE;
        return;
    }

    if (save == 1) {
        rgb_matrix_mode(mode);
        rgb_matrix_set_speed(speed);
        rgb_matrix_sethsv(h, s, v);
    }
    else {
        rgb_matrix_mode_noeeprom(mode);
        rgb_matrix_set_speed_noeeprom(speed);
        rgb_matrix_sethsv_noeeprom(h, s, v);
    }

    raw_hid_buffer[OPENRGB_EPSIZE - 2] = OPENRGB_SUCCESS;
}
void openrgb_direct_mode_set_single_led(uint8_t *data) {
    const uint8_t led = data[1];
    const uint8_t r   = data[2];
    const uint8_t g   = data[3];
    const uint8_t b   = data[4];

    raw_hid_buffer[0] = OPENRGB_DIRECT_MODE_SET_SINGLE_LED;

    if (led >= RGB_MATRIX_LED_COUNT || r > 255 || g > 255 || b > 255) {
        raw_hid_buffer[OPENRGB_EPSIZE - 2] = OPENRGB_FAILURE;
        return;
    }

    g_openrgb_direct_mode_colors[led].r = r;
    g_openrgb_direct_mode_colors[led].g = g;
    g_openrgb_direct_mode_colors[led].b = b;

    raw_hid_buffer[OPENRGB_EPSIZE - 2] = OPENRGB_SUCCESS;
}
void openrgb_direct_mode_set_leds(uint8_t *data) {
    const uint8_t first_led   = data[1];
    const uint8_t number_leds = data[2];

    for (uint8_t i = 0; i < number_leds; i++) {
        const uint8_t color_idx = first_led + i;
        const uint8_t data_idx  = i * 3;

        g_openrgb_direct_mode_colors[color_idx].r = data[data_idx + 3];
        g_openrgb_direct_mode_colors[color_idx].g = data[data_idx + 4];
        g_openrgb_direct_mode_colors[color_idx].b = data[data_idx + 5];
    }
}
