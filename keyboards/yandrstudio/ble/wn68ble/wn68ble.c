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
#include "wn68ble.h"

#ifdef BIU_BLE5_ENABLE
#    include "biu_ble_common.h"
#endif

#ifdef RGB_MATRIX_ENABLE



led_config_t g_led_config = {
    {
        {72,  71,  70,  69,  68,  67,  66,  65,  64,  63,  62,  61,  60,  59,  58,  57},
        {41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56},
        {40,  39,  38,  37,  36,  35,  34,  33,  32,  31,  30,  29,  28,   NO_LED,  27,  26},
        {12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,   NO_LED,  23,   NO_LED,  24,  25},
        {11,  10,  9,   NO_LED,   NO_LED,  8,   NO_LED,   NO_LED,  7,  NO_LED,  6,  NO_LED,  5,  2,  1,  0}
    },
    {
        {224,64},{209,64},{194,64},{186,64},{186,64},{179,64},       {149,64},       {119,64},              {75,64},              {30,64},{15,64},{0,64},
        {0,48},{15,48},{30,48},{45,48},{60,48},{75,48},{90,48},{105,48},{119,48},{134,48},{149,48},       {179,48},       {209,48},{224,48},
        {224,32},{209,32},       {179,32},{164,32},{149,32},{134,32},{119,32},{105,32},{90,32},{75,32},{60,32},{45,32},{30,32},{15,32},{0,32},
        {0,16},{15,16},{30,16},{45,16},{60,16},{75,16},{90,16},{105,16},{119,16},{134,16},{149,16},{164,16},{179,16},{194,16},{209,16},{224,16},
        {224,0},{209,0},{194,0},{179,0},{164,0},{149,0},{134,0},{119,0},{105,0},{90,0},{75,0},{60,0},{45,0},{30,0},{15,0},{0,0},
        {0,64},{28,64},{56,64},{84,64},{112,64},{140,64},{168,64},{196,64},{224,64},
        {224,0},{196,0},{168,0},{140,0},{112,0},{84,0},{56,0},{28,0},{0,0}
    },
    {
      // LED Index to Flag
      4,4,4,2,2, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,
      2,2,2,2,2, 2,2,2,2,2,
      2,2,2,2,2, 2,2,2

    }
};

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

extern rgb_config_t rgb_matrix_config;
void keyboard_post_init_kb(void) {
    user_config.underground_rgb_sw = eeconfig_read_kb();
    rgb_matrix_config.enable = 0;
    rgb_matrix_reload_from_eeprom();
}

#endif

#if defined(RGBLIGHT_ENABLE) && defined(BIU_BLE5_ENABLE)

const rgblight_segment_t PROGMEM bt_conn[] = RGBLIGHT_LAYER_SEGMENTS( {3, 1, HSV_BLUE} );         // 0
const rgblight_segment_t PROGMEM bt_pair[] = RGBLIGHT_LAYER_SEGMENTS( {3, 1, HSV_RED} );          // 1
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({4, 1, HSV_RED});  // 2
const rgblight_segment_t PROGMEM bat_20_layer[] = RGBLIGHT_LAYER_SEGMENTS({3, 1, HSV_YELLOW});    // 3


const rgblight_segment_t* const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST( bt_conn,
                                                                              bt_pair,
                                                                              my_capslock_layer,
                                                                              bat_20_layer);

extern rgblight_config_t rgblight_config;
void keyboard_post_init_kb(void) {
    rgblight_layers = _rgb_layers;
    rgblight_reload_from_eeprom();
    rgblight_config.enable = 0;
    eeconfig_update_rgblight(rgblight_config.raw);
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
   if (channle <= 7) {
        if (state == 7) {
            rgblight_blink_layer_repeat(0, 500, 8);
        } else if (state == 8) {
            rgblight_blink_layer_repeat(1, 200, 20);
        }
   }
   return true;
}


bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        rgblight_set_layer_state(2, led_state.caps_lock);
        if (get_bat_level() <= 20) {
            rgblight_blink_layer_repeat(3, 400, 10);
        }
    }
    return res;
}

#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
#ifdef RGB_MATRIX_ENABLE
        case RGB_KG_T:
            if (rgb_matrix_config.enable && record->event.pressed) {
                user_config.underground_rgb_sw += 1;
                user_config.underground_rgb_sw %= 3;
                eeconfig_update_kb(user_config.raw);
            }
            return false;
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
