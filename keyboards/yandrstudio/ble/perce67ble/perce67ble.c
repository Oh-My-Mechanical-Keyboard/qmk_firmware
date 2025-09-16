/* Copyright 2022 JasonRen(biu)
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
#include "perce67ble.h"

#ifdef BIU_BLE5_ENABLE
#    include "biu_ble_common.h"
#endif

#ifdef RGB_MATRIX_ENABLE

#   ifdef NO_UNDER_RGB

led_config_t g_led_config = {{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14},
                              {29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15},
                              {30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, NO_LED, 42, 43},
                              {57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, NO_LED, 46, 45, 44},
                              {58, 59, 60, NO_LED, NO_LED, 61, NO_LED, NO_LED, NO_LED, 62, 63, NO_LED, 64, 65, 66}},
                             {{0, 0},   {16, 0},  {32, 0},  {48, 0},   {64, 0},   {80, 0},   {96, 0},   {112, 0},  {128, 0},  {144, 0},  {160, 0},  {176, 0},  {192, 0},  {208, 0},  {224, 0},  {224, 16}, {208, 16}, {192, 16}, {176, 16}, {160, 16}, {144, 16}, {128, 16}, {112, 16}, {96, 16}, {80, 16}, {64, 16}, {48, 16}, {32, 16}, {16, 16},  {0, 16},   {0, 32},   {16, 32},  {32, 32}, {48, 32},
                              {64, 32}, {80, 32}, {96, 32}, {112, 32}, {128, 32}, {144, 32}, {160, 32}, {176, 32}, {208, 32}, {224, 32}, {224, 48}, {208, 48}, {192, 48}, {160, 48}, {144, 48}, {128, 48}, {112, 48}, {96, 48},  {80, 48},  {64, 48},  {48, 48},  {32, 48},  {16, 48},  {0, 48},  {0, 64},  {16, 64}, {32, 64}, {80, 64}, {144, 64}, {160, 64}, {192, 64}, {208, 64}, {224, 64}

                             },
                             {// LED Index to Flag
                              4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}};

#   else

led_config_t g_led_config = {{{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}, {29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15}, {30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, NO_LED, 42, 43}, {57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, NO_LED, 46, 45, 44}, {58, 59, 60, NO_LED, NO_LED, 61, NO_LED, NO_LED, NO_LED, 62, 63, NO_LED, 64, 65, 66}},
                             {{0, 0},    {16, 0},   {32, 0},   {48, 0},   {64, 0},   {80, 0},   {96, 0},   {112, 0},  {128, 0}, {144, 0}, {160, 0}, {176, 0}, {192, 0}, {208, 0}, {224, 0}, {224, 16}, {208, 16}, {192, 16}, {176, 16}, {160, 16}, {144, 16}, {128, 16}, {112, 16}, {96, 16},  {80, 16},  {64, 16},  {48, 16},  {32, 16},  {16, 16},  {0, 16},  {0, 32},  {16, 32}, {32, 32}, {48, 32}, {64, 32}, {80, 32}, {96, 32}, {112, 32}, {128, 32}, {144, 32}, {160, 32}, {176, 32}, {208, 32},
                              {224, 32}, {224, 48}, {208, 48}, {192, 48}, {160, 48}, {144, 48}, {128, 48}, {112, 48}, {96, 48}, {80, 48}, {64, 48}, {48, 48}, {32, 48}, {16, 48}, {0, 48},  {0, 64},   {16, 64},  {32, 64},  {80, 64},  {144, 64}, {160, 64}, {192, 64}, {208, 64}, {224, 64}, {224, 64}, {196, 64}, {168, 64}, {140, 64}, {112, 64}, {84, 64}, {56, 64}, {28, 64}, {0, 64},  {224, 0}, {196, 0}, {168, 0}, {140, 0}, {112, 0},  {84, 0},   {56, 0},   {28, 0},   {0, 0}

                             },
                             {// LED Index to Flag
                              4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}};
// globol
typedef union {
    uint32_t raw;
    uint8_t  underground_rgb_sw : 8;
} user_config_t;
user_config_t user_config;

void rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (rgb_matrix_is_enabled()) {
        if (user_config.underground_rgb_sw == 1) {
            for (uint8_t i = led_min; i < led_max; ++i) {
                if ((g_led_config.flags[i] == 4)) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
        } else if (user_config.underground_rgb_sw == 2) {
            for (uint8_t i = led_min; i < led_max; ++i) {
                if ((g_led_config.flags[i] == 2)) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
        }
    } else {
        rgb_matrix_set_color_all(0, 0, 0);
    }
}

void eeconfig_init_kb(void) {
    user_config.raw = 0;
    eeconfig_update_kb(user_config.raw);
}

extern const rgb_matrix_driver_t rgb_matrix_driver;
void keyboard_post_init_kb(void) {
    user_config.underground_rgb_sw = eeconfig_read_kb();
    rgb_matrix_reload_from_eeprom();
}
#   endif
#endif

#if defined(RGBLIGHT_ENABLE) && defined(BIU_BLE5_ENABLE)

const rgblight_segment_t PROGMEM bt_conn[]           = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_BLUE});   // 0
const rgblight_segment_t PROGMEM bt_pair[]           = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_BLUE});   // 1
const rgblight_segment_t PROGMEM usb_pair[]          = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_WHITE});  // 2
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_RED});    // 3
const rgblight_segment_t PROGMEM bat_10_layer[]      = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_GREEN});  // 4
const rgblight_segment_t PROGMEM bat_30_layer[]      = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_GREEN});  // 5
const rgblight_segment_t PROGMEM bat_50_layer[]      = RGBLIGHT_LAYER_SEGMENTS({0, 3, HSV_GREEN});  // 6
const rgblight_segment_t PROGMEM bat_70_layer[]      = RGBLIGHT_LAYER_SEGMENTS({0, 4, HSV_GREEN});  // 7
const rgblight_segment_t PROGMEM bat_80_layer[]      = RGBLIGHT_LAYER_SEGMENTS({0, 5, HSV_GREEN});  // 8
const rgblight_segment_t PROGMEM bat_90_layer[]      = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_GREEN});  // 9

const rgblight_segment_t* const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST(bt_conn, bt_pair, usb_pair, my_capslock_layer, bat_10_layer, bat_30_layer, bat_50_layer, bat_70_layer, bat_80_layer, bat_90_layer);

void keyboard_post_init_kb(void) {
    rgblight_layers = _rgb_layers;
    rgblight_reload_from_eeprom();
}

bool ble_led_update_kb(uint8_t channle, uint8_t state) {
    /*
    _ble_channle:
        BLE: 0-7
        USB: 0xa
        2G4: 0xb
    _ble_state:
        NRF_WORKING：1
        NRF_ADVING_NO_WL：8
        NRF_ADVING_WITH_WL：7

        USB_ACTIVE: 0xA0
        USB_DISCONNECTION：0xA1
    */
    if (channle == 0xa) {
        if (state != 0xa0) {
            rgblight_blink_layer_repeat(2, 500, 8);
        }
    } else if (channle <= 7) {
        if (state == 7) {
            rgblight_blink_layer_repeat(0, 500, 8);
        } else if (state == 8) {
            rgblight_blink_layer_repeat(1, 200, 20);
        }
    }
    return true;
}

bool led_update_kb(led_t led_state) {
    rgblight_set_layer_state(3, led_state.caps_lock);
    return true;
}

#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
#ifdef RGB_MATRIX_ENABLE
#   ifndef NO_UNDER_RGB
        case RGB_KG_T:
            if (rgb_matrix_config.enable && record->event.pressed) {
                user_config.underground_rgb_sw += 1;
                user_config.underground_rgb_sw %= 3;
                eeconfig_update_kb(user_config.raw);
            }
            return false;
#   else
        return true;
#   endif
#endif
        case KC_LG:
            if (record->event.pressed) {
                process_magic(GUI_TOG, record);
            }
            return false;
        case KC_MACOS:
            if (record->event.pressed) {
                process_magic(CG_TOGG, record);
            }
            return false;
        case KC_MCTL:
            if (record->event.pressed) {
                host_consumer_send(0x29F);
            } else {
                host_consumer_send(0);
            }
            return false;
        case KC_LPAD:
            if (record->event.pressed) {
                host_consumer_send(0x2A0);
            } else {
                host_consumer_send(0);
            }
            return false;
        default:
            return true;
    }
    return true;
}



#ifndef BIU_BLE5_ENABLE
void keyboard_pre_init_kb(void) {
    palSetLineMode(RGB_BLE_SW, PAL_MODE_OUTPUT_PUSHPULL);
    writePin(RGB_BLE_SW, 0);
}
#endif

// void housekeeping_task_kb(void) {
//     if (!rgb_matrix_is_enabled()) {
//         writePin(RGB_BLE_SW, RGB_EN_STATE ? 0 : 1);
//     } else {
//         writePin(RGB_BLE_SW, RGB_EN_STATE);
//     }
// }
