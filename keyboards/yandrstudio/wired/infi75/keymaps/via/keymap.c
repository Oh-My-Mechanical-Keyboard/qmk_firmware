// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum keyboard_keycodes {
    LOCK_GUI = QK_USER,
    TOG_MACOS_KEYMAP_MAC,
    KC_MISSION_CONTROL_MAC,
    KC_LAUNCHPAD_MAC,
#ifdef RGB_MATRIX_ENABLE
    TRGB_KEY,
    TRGB_ENC,
    TRGB_LIT
#endif
};

#define MKC_LG     LOCK_GUI
#define MKC_MACOS  TOG_MACOS_KEYMAP_MAC
#define MKC_MCTL   KC_MISSION_CONTROL_MAC
#define MKC_LPAD   KC_LAUNCHPAD_MAC

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3, KC_F4,        KC_F5, KC_F6, KC_F7,   KC_F8,            KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_GRV,  KC_1,    KC_2,    KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
        KC_CAPS, KC_A,    KC_S,    KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_MUTE,
        KC_LSFT, KC_Z,    KC_X,    KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,               KC_SPC,                       KC_RALT, MO(1),            KC_LEFT, KC_DOWN, KC_RIGHT),
    [1] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,          KC_TRNS, TRGB_KEY,TRGB_ENC,TRGB_LIT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
        KC_TRNS, RGB_TOG, RGB_MOD, RGB_RMOD,RGB_VAI, RGB_VAD, KC_TRNS, MKC_MACOS,KC_TRNS,  KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
        KC_TRNS, MKC_LG,  KC_TRNS,                   KC_TRNS,                              KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS),
    [2] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                              KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS),
    [3] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                              KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS)
};

#if defined(ENCODER_MAP_ENABLE) && defined(ENCODER_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1]  = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [2]  = {ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
    [3]  = {ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)}
};
#endif

#ifdef RGB_MATRIX_ENABLE
typedef union {
    uint32_t raw;
    bool  key_rgb_sw : 1;
    bool  enc_rgb_sw : 1;
    bool  light_rgb_sw : 1;
} my_user_config_t;
my_user_config_t my_user_config;

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (rgb_matrix_is_enabled()) {
        for (uint8_t i = led_min; i < led_max; ++i) {
            if (g_led_config.flags[i] == 4 && !my_user_config.key_rgb_sw) {
                rgb_matrix_set_color(i, 0, 0, 0);
            }
            if (g_led_config.flags[i] == 2 && !my_user_config.enc_rgb_sw) {
                rgb_matrix_set_color(i, 0, 0, 0);
            }
            if (g_led_config.flags[i] == 8 && !my_user_config.light_rgb_sw) {
                rgb_matrix_set_color(i, 0, 0, 0);
            }
        }
    }
    return true;
}

void eeconfig_init_user(void) {
    my_user_config.raw = 0;
    my_user_config.key_rgb_sw = true;
    my_user_config.enc_rgb_sw = true;
    my_user_config.light_rgb_sw = true;
    eeconfig_update_user(my_user_config.raw);
}

extern const rgb_matrix_driver_t rgb_matrix_driver;
void keyboard_post_init_user(void) {
    my_user_config.raw = eeconfig_read_user();
    rgb_matrix_reload_from_eeprom();
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef RGB_MATRIX_ENABLE
        case TRGB_KEY:
            if (rgb_matrix_is_enabled() && record->event.pressed) {
                my_user_config.key_rgb_sw ^= 1;
                eeconfig_update_user(my_user_config.raw);
            }
            return false;
        case TRGB_ENC:
            if (rgb_matrix_is_enabled() && record->event.pressed) {
                my_user_config.enc_rgb_sw ^= 1;
                eeconfig_update_user(my_user_config.raw);
            }
            return false;
        case TRGB_LIT:
            if (rgb_matrix_is_enabled() && record->event.pressed) {
                my_user_config.light_rgb_sw ^= 1;
                eeconfig_update_user(my_user_config.raw);
            }
            return false;
#endif
        case MKC_LG:
            if (record->event.pressed) {
                process_magic(GUI_TOG, record);
            }
            return false;
        case MKC_MACOS:
            if (record->event.pressed) {
                process_magic(CG_TOGG, record);
            }
            return false;
        case MKC_MCTL:
            if (record->event.pressed) {
                host_consumer_send(KC_MCTL);
            } else {
                host_consumer_send(0);
            }
            return false;
        case MKC_LPAD:
            if (record->event.pressed) {
                host_consumer_send(KC_LPAD);
            } else {
                host_consumer_send(0);
            }
            return false;
        default:
            return true;
    }
    return true;
}
