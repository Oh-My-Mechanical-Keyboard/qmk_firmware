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
#include "wn68ble_v2.h"

#ifdef BIU_BLE5_ENABLE
#    include "biu_ble_common.h"
#endif

#ifdef RGB_MATRIX_ENABLE

#include "rgb_matrix_layer.h"


led_config_t g_led_config = {
    {
        {0,  1,  2,  3,  4,      5,      6,      7,      8,      9,  10, 11,     12,     13, 14, 15}, 
        {31, 30, 29, 28, 27,     26,     25,     24,     23,     22, 21, 20,     19,     18, 17, 16}, 
        {32, 34, 35, 36, 37,     38,     39,     40,     41,     42, 43, 44,     NO_LED, 45, 46, 48}, 
        {70, 68, 66, 65, 63,     62,     60,     59,     57,     56, 54, NO_LED, NO_LED, 53, 51, 49}, 
        {71, 72, 73, 74, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, 75, 76, 77,     NO_LED, 80, 81, 82}
    },
    {
        {0,0},{15,0},{30,0},{45,0},{60,0},{75,0},{90,0},{105,0},{119,0},{134,0},{149,0},{164,0},{179,0},{194,0},{209,0},{224,0},
        {224,16},{209,16},{194,16},{179,16},{164,16},{149,16},{134,16},{119,16},{105,16},{90,16},{75,16},{60,16},{45,16},{30,16},{15,16},{0,16},
        {0,32},{0,32},    {15,32},{30,32},{45,32},{60,32},{75,32},{90,32},{105,32},{119,32},{134,32},{149,32},{164,32},       {194,32},{209,32},   {224,32},    {224,32},
        {224,48},{224,48},{209,48},{209,48},{194,48},              {149,48},{149,48},{134,48},{119,48},{119,48},{105,48},{90,48},{90,48},{75,48},{60,48},{60,48}, {45,48},{30,48},{30,48},{15,48},{15,48},{0,48},
        {0,64},{15,64},{30,64},{45,64},                                   {134,64},{149,64},{164,64},       {194,64},{194,64}, {194,64},{209,64},{224,64},
        {224,64},{194,64},{164,64},{134,64},{105,64},{75,64},{45,64},{0,64}
    },
    {
      // LED Index to Flag
      4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
      4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
      4,2,4,4,4,4,4,4,4,4,4,4,4,4,4,2,4,
      4,2,4,2,4,4,2,4,4,2,4,4,2,4,4,2,4,4,2,4,2,4,
      4,4,4,4,4,4,4,4,4,4,4,4,
      2,2,2,2,2,2,2,2
    }
};

// globol
typedef union {
    uint32_t raw;
    uint8_t  underground_rgb_sw : 8;
} kb_cstm_config_t;
kb_cstm_config_t kb_cstm_config;


// rgb matrix layer

const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn1_layer[] = RGB_MATRIX_LAYER_SEGMENTS({30, 1, HSV_GREEN});  // 0
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn2_layer[] = RGB_MATRIX_LAYER_SEGMENTS({29, 1, HSV_GREEN});  // 1
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn3_layer[] = RGB_MATRIX_LAYER_SEGMENTS({28, 1, HSV_GREEN});  // 2
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn4_layer[] = RGB_MATRIX_LAYER_SEGMENTS({27, 1, HSV_GREEN});  // 3
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair1_layer[] = RGB_MATRIX_LAYER_SEGMENTS({30, 1, HSV_BLUE});   // 4
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair2_layer[] = RGB_MATRIX_LAYER_SEGMENTS({29, 1, HSV_BLUE});   // 5
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair3_layer[] = RGB_MATRIX_LAYER_SEGMENTS({28, 1, HSV_BLUE});   // 6
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair4_layer[] = RGB_MATRIX_LAYER_SEGMENTS({27, 1, HSV_BLUE});   // 7
const rgb_matrix_adv_layer_segment_t PROGMEM usb_pair_layer[] = RGB_MATRIX_LAYER_SEGMENTS({35, 1, HSV_BLUE});   // 8
const rgb_matrix_adv_layer_segment_t PROGMEM usb_conn_layer[] = RGB_MATRIX_LAYER_SEGMENTS({35, 1, HSV_GREEN});  // 9
const rgb_matrix_adv_layer_segment_t PROGMEM capslock_layer[] = RGB_MATRIX_LAYER_SEGMENTS({32, 1, HSV_RED}, {78, 1, HSV_RED});    // 10
const rgb_matrix_adv_layer_segment_t PROGMEM bat_10_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 1, HSV_RED}, {79, 1, HSV_RED});     // 11
const rgb_matrix_adv_layer_segment_t PROGMEM bat_20_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 2, HSV_GREEN});   // 12
const rgb_matrix_adv_layer_segment_t PROGMEM bat_30_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 3, HSV_GREEN});   // 13
const rgb_matrix_adv_layer_segment_t PROGMEM bat_40_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 4, HSV_GREEN});   // 14
const rgb_matrix_adv_layer_segment_t PROGMEM bat_50_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 5, HSV_GREEN});   // 15
const rgb_matrix_adv_layer_segment_t PROGMEM bat_60_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 6, HSV_GREEN});   // 16
const rgb_matrix_adv_layer_segment_t PROGMEM bat_70_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 7, HSV_GREEN});   // 17
const rgb_matrix_adv_layer_segment_t PROGMEM bat_80_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 8, HSV_GREEN});   // 18
const rgb_matrix_adv_layer_segment_t PROGMEM bat_90_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 9, HSV_GREEN});   // 19
const rgb_matrix_adv_layer_segment_t PROGMEM bat_100_layer[]  = RGB_MATRIX_LAYER_SEGMENTS({1, 10, HSV_GREEN});  // 20

const rgb_matrix_adv_layer_segment_t* const PROGMEM my_rgb_matrix_layers[] =
                                                    RGB_MATRIX_LAYERS_LIST(bt_conn1_layer, bt_conn2_layer, bt_conn3_layer, bt_conn4_layer,
                                                                           bt_pair1_layer, bt_pair2_layer, bt_pair3_layer, bt_pair4_layer,
                                                                           usb_pair_layer, usb_conn_layer,
                                                                           capslock_layer,
                                                                           bat_10_layer, bat_20_layer, bat_30_layer, bat_40_layer, bat_50_layer,
                                                                           bat_60_layer, bat_70_layer, bat_80_layer, bat_90_layer, bat_100_layer);



void rgb_matrix_adv_unblink_all_but_caps_bat_layer(void) {
    for (uint8_t i = 0; i < 10; i++) {
        rgb_matrix_adv_unblink_layer(i);
    }
}

void rgb_matrix_adv_unblink_all_batlayer_but_one_layer(uint8_t l) {
    for (uint8_t i = 11; i < 21; i++) {
        if (l == i) continue;
        rgb_matrix_adv_unblink_layer(i);
    }
}

void rgb_matrix_adv_unblink_all_but_layer(uint8_t l) {
    for (uint8_t i = 0; i < 21; i++) {
        if (l == i) continue;
        rgb_matrix_adv_unblink_layer(i);
    }
}

extern rgb_task_states rgb_task_state;
extern rgb_matrix_adv_layers_mask_t rgb_matrix_adv_enabled_layer_mask;
extern rgb_matrix_adv_layers_mask_t _blinking_layer_mask;

void rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    rgb_matrix_set_color(78, 0, 0, 0);
    rgb_matrix_set_color(79, 0, 0, 0);
    if (rgb_matrix_is_enabled()) {
        if (kb_cstm_config.underground_rgb_sw == 1) {
            for (uint8_t i = led_min; i < led_max; ++i) {
                if ((g_led_config.flags[i] == 4)) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
        } else if (kb_cstm_config.underground_rgb_sw == 2) {
            for (uint8_t i = led_min; i < led_max; ++i) {
                if ((g_led_config.flags[i] == 2)) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
        }
    }
    rgb_matrix_adv_blink_layer_repeat_helper();
    rgb_matrix_adv_set_layer_state(10, host_keyboard_led_state().caps_lock);
    // If not enabled, then nothing else will actually set the LEDs...
    if (!rgb_matrix_is_enabled()) {
        rgb_task_state = FLUSHING;
    }
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
            rgb_matrix_adv_unblink_all_but_caps_bat_layer();
            rgb_matrix_adv_blink_layer_repeat(8, 500, 8);
        } else {
            rgb_matrix_adv_unblink_all_but_caps_bat_layer();
            rgb_matrix_adv_blink_layer_repeat(9, 1000, 1);
        }
    } else if (channle <= 7) {
        if (state == 7) {
            rgb_matrix_adv_unblink_all_but_layer(channle%4);
            rgb_matrix_adv_blink_layer_repeat(channle%4, 500, 8);
        } else if (state == 8) {
            rgb_matrix_adv_unblink_all_but_layer(channle%4+4);
            rgb_matrix_adv_blink_layer_repeat(channle%4+4, 200, 20);
        } else if (state == 1) {
            rgb_matrix_adv_unblink_all_but_layer(channle%4);
            rgb_matrix_adv_blink_layer_repeat(channle%4, 3000, 1);
        } else {
            rgb_matrix_adv_unblink_all_but_caps_bat_layer();
        }
    }
    if (!rgb_matrix_is_enabled()) {
        rgb_task_state = FLUSHING;
    }
    return true;
}


void eeconfig_init_kb(void) {
    kb_cstm_config.raw = 0;
    eeconfig_update_kb(kb_cstm_config.raw);
}

void keyboard_post_init_kb(void) {
    kb_cstm_config.underground_rgb_sw = eeconfig_read_kb();
    rgb_matrix_reload_from_eeprom();
    rgb_matrix_layers = my_rgb_matrix_layers;
}
#endif


bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
#ifdef RGB_MATRIX_ENABLE
        case KC_KEY_UNDER_RGBSW:
            if (rgb_matrix_config.enable && record->event.pressed) {
                kb_cstm_config.underground_rgb_sw += 1;
                kb_cstm_config.underground_rgb_sw %= 3;
                eeconfig_update_kb(kb_cstm_config.raw);
            }
            return false;
        case BAT_SHOW: {
            if (record->event.pressed) {
                uint8_t bat_l_t = get_bat_level();
                if (bat_l_t <= 10) {
                    rgb_matrix_adv_unblink_all_batlayer_but_one_layer(11);
                    rgb_matrix_adv_blink_layer_repeat(11, 1500, 1);
                } else {
                    rgb_matrix_adv_unblink_all_batlayer_but_one_layer((bat_l_t % 101) / 10 + 10);
                    rgb_matrix_adv_blink_layer_repeat((bat_l_t % 101) / 10 + 10, 1500, 1);
                }
                if (!rgb_matrix_is_enabled()) {
                    rgb_task_state = FLUSHING;
                }
            }
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
