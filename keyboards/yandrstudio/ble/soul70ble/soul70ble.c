/* Copyright 2021 JasonRen(biu)
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
 * along with this program.  If not, see <http: //www.gnu.org/licenses/>.
 */
#include "soul70ble.h"
#ifdef BIU_BLE5_ENABLE
#include "biu_ble_common.h"
#endif

#if defined(RGBLIGHT_ENABLE) && defined(BIU_BLE5_ENABLE)

const rgblight_segment_t PROGMEM bt_conn[] = RGBLIGHT_LAYER_SEGMENTS( {0, 6, HSV_GREEN} );          // 0
const rgblight_segment_t PROGMEM bt_pair[] = RGBLIGHT_LAYER_SEGMENTS( {0, 6, HSV_BLUE} );          // 1
const rgblight_segment_t PROGMEM usb_pair[] = RGBLIGHT_LAYER_SEGMENTS( {0, 6, HSV_WHITE} );        // 2
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_RED});   // 3
const rgblight_segment_t PROGMEM bat_10_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_GREEN});      // 4
const rgblight_segment_t PROGMEM bat_30_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_GREEN});      // 5
const rgblight_segment_t PROGMEM bat_50_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 3, HSV_GREEN});      // 6
const rgblight_segment_t PROGMEM bat_70_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 4, HSV_GREEN});      // 7
const rgblight_segment_t PROGMEM bat_80_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 5, HSV_GREEN});      // 8
const rgblight_segment_t PROGMEM bat_90_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_GREEN});      // 9

const rgblight_segment_t* const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST( bt_conn,
                                                                              bt_pair,
                                                                              usb_pair,
                                                                              my_capslock_layer,
                                                                              bat_10_layer,
                                                                              bat_30_layer,
                                                                              bat_50_layer,
                                                                              bat_70_layer,
                                                                              bat_80_layer,
                                                                              bat_90_layer);

void keyboard_post_init_kb(void) {
    rgblight_layers = _rgb_layers;
    rgblight_reload_from_eeprom();
    keyboard_post_init_user();
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


bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case BAT_SHOW: {
            if (record->event.pressed) {
                uint8_t bat_l_t =  get_bat_level();
                if (bat_l_t <= 10) {
                    rgblight_blink_layer_repeat(4, 500, 4);
                } else if (bat_l_t <= 30) {
                    rgblight_blink_layer_repeat(5, 500, 4);
                } else if (bat_l_t <= 50) {
                    rgblight_blink_layer_repeat(6, 500, 4);
                } else if (bat_l_t <= 70) {
                    rgblight_blink_layer_repeat(7, 500, 4);
                } else if (bat_l_t <= 80) {
                    rgblight_blink_layer_repeat(8, 500, 4);
                } else {
                    rgblight_blink_layer_repeat(9, 500, 4);
                }
            }
        }
            return false;
        default:
            return true;
    }
    return true;
}
#endif


#ifndef BIU_BLE5_ENABLE
void keyboard_pre_init_kb(void) {
    palSetLineMode(RGB_BLE_SW, PAL_MODE_OUTPUT_PUSHPULL);
    writePin(RGB_BLE_SW, 0);
}
#endif
