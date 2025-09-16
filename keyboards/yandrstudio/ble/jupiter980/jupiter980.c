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
#include "jupiter980.h"

#ifdef RGBLIGHT_ENABLE

const rgblight_segment_t PROGMEM bt_conn[] = RGBLIGHT_LAYER_SEGMENTS( {0, 6, HSV_GREEN} );
const rgblight_segment_t PROGMEM bt_pair[] = RGBLIGHT_LAYER_SEGMENTS( {0, 6, HSV_BLUE} );
const rgblight_segment_t PROGMEM usb_pair[] = RGBLIGHT_LAYER_SEGMENTS( {0, 6, HSV_WHITE} );

const rgblight_segment_t* const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST( bt_conn, bt_pair, usb_pair );

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
        rgblight_blink_layer_repeat(2, 500, 6);
    } else {
        rgblight_unblink_layer(2);
    }
   } else if (channle <= 7) {
        if (state == 7) {
            rgblight_blink_layer_repeat(0, 500, 6);
        } else if (state == 8) {
            rgblight_blink_layer_repeat(1, 500, 6);
        } else {
            rgblight_unblink_layer(0);
            rgblight_unblink_layer(1);
        }
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

