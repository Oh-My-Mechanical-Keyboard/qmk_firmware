// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "magnum65.h"

#ifdef BIU_BLE5_ENABLE
#    include "biu_ble_common.h"
#    include "usb_main.h"
#endif

#if defined(RGBLIGHT_ENABLE)

// globol
kb_cstm_config_t kb_cstm_config;

const rgblight_segment_t PROGMEM bt1_conn[] = RGBLIGHT_LAYER_SEGMENTS( {1, 1, HSV_GREEN} ); // 0
const rgblight_segment_t PROGMEM bt2_conn[] = RGBLIGHT_LAYER_SEGMENTS( {2, 1, HSV_GREEN} ); // 1
const rgblight_segment_t PROGMEM bt3_conn[] = RGBLIGHT_LAYER_SEGMENTS( {3, 1, HSV_GREEN} ); // 2
const rgblight_segment_t PROGMEM bt4_conn[] = RGBLIGHT_LAYER_SEGMENTS( {4, 1, HSV_GREEN} ); // 3
const rgblight_segment_t PROGMEM bt1_pair[] = RGBLIGHT_LAYER_SEGMENTS( {1, 1, HSV_BLUE} );  // 4
const rgblight_segment_t PROGMEM bt2_pair[] = RGBLIGHT_LAYER_SEGMENTS( {2, 1, HSV_BLUE} );  // 5
const rgblight_segment_t PROGMEM bt3_pair[] = RGBLIGHT_LAYER_SEGMENTS( {3, 1, HSV_BLUE} );  // 6
const rgblight_segment_t PROGMEM bt4_pair[] = RGBLIGHT_LAYER_SEGMENTS( {4, 1, HSV_BLUE} );  // 7
const rgblight_segment_t PROGMEM usb_conn[] = RGBLIGHT_LAYER_SEGMENTS( {1, 4, HSV_GREEN} ); // 8
const rgblight_segment_t PROGMEM usb_pair[] = RGBLIGHT_LAYER_SEGMENTS( {1, 4, HSV_BLUE} );  // 9
rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, 0, 255, RGBLIGHT_LIMIT_VAL}); // 10
const rgblight_segment_t PROGMEM bat_10_layer[] = RGBLIGHT_LAYER_SEGMENTS({1, 1, HSV_RED}); // 11
const rgblight_segment_t PROGMEM bat_40_layer[] = RGBLIGHT_LAYER_SEGMENTS({1, 2, HSV_GREEN}); // 12
const rgblight_segment_t PROGMEM bat_70_layer[] = RGBLIGHT_LAYER_SEGMENTS({1, 3, HSV_GREEN}); // 13
const rgblight_segment_t PROGMEM bat_100_layer[] = RGBLIGHT_LAYER_SEGMENTS({1, 4, HSV_GREEN}); // 14
const rgblight_segment_t PROGMEM bat_ch1_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_RED}); // 15
const rgblight_segment_t PROGMEM bat_ch2_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_GREEN}); // 16
const rgblight_segment_t PROGMEM bat_ch3_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_BLUE}); // 17
const rgblight_segment_t PROGMEM bat_ch4_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_YELLOW}); // 18


const rgblight_segment_t* const PROGMEM _rgb_layers[] = RGBLIGHT_LAYERS_LIST(bt1_conn, bt2_conn, bt3_conn, bt4_conn,
                                                                             bt1_pair, bt2_pair, bt3_pair, bt4_pair,
                                                                             usb_conn, usb_pair,
                                                                             my_capslock_layer,
                                                                             bat_10_layer, bat_40_layer, bat_70_layer, bat_100_layer,
                                                                             bat_ch1_layer, bat_ch2_layer, bat_ch3_layer, bat_ch4_layer);

void eeconfig_init_kb_datablock(void) {
    kb_cstm_config.caps_brightness = RGBLIGHT_LIMIT_VAL;
    kb_cstm_config.caps_color_h = 0;
    kb_cstm_config.caps_color_s = 255;
    eeconfig_update_kb_datablock(&kb_cstm_config);
}

void keyboard_post_init_kb(void) {
    rgblight_layers = _rgb_layers;
    rgblight_reload_from_eeprom();
    eeconfig_read_kb_datablock(&kb_cstm_config);
    keyboard_post_init_user();
    palSetLineMode(A1, PAL_MODE_INPUT_PULLUP);
    palSetLineMode(A2, PAL_MODE_INPUT_PULLUP);
#ifdef CONSOLE_ENABLE
    debug_enable = true;
#endif
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
        rgblight_blink_layer_repeat(9, 500, 8);
    } else {
        rgblight_blink_layer_repeat(8, 2000, 1);
    }
   } else if (channle <= 7) {
        if (state == 7) {
            rgblight_unblink_all_but_layer(channle%4);
            rgblight_blink_layer_repeat(channle%4, 500, 8);
        } else if (state == 8) {
            rgblight_unblink_all_but_layer(channle%4+4);
            rgblight_blink_layer_repeat(channle%4+4, 200, 20);
        } else if (state == 1) {
            rgblight_unblink_all_but_layer(channle%4);
            rgblight_blink_layer_repeat(channle%4, 3000, 1);
        }
   }
    return true;
}


bool led_update_kb(led_t led_state) {
    rgblight_set_layer_state(10, led_state.caps_lock);
    return true;
}

void caps_config_set_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch ( *value_id )
    {
        case via_caps_brightness:
            kb_cstm_config.caps_brightness = *value_data;
            break;
        case via_caps_color:
            kb_cstm_config.caps_color_h = value_data[0];
            kb_cstm_config.caps_color_s = value_data[1];
            break;
    }
    rgblight_segment_t temp_stt = {0, 1, kb_cstm_config.caps_color_h, kb_cstm_config.caps_color_s, kb_cstm_config.caps_brightness};
    my_capslock_layer[0] = temp_stt;
}

void caps_config_get_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch ( *value_id )
    {
        case via_caps_brightness:
            *value_data = kb_cstm_config.caps_brightness;
            break;
        case via_caps_color:
            value_data[0] = kb_cstm_config.caps_color_h;
            value_data[1] = kb_cstm_config.caps_color_s;
            break;
    }
}
void caps_config_save(void) {
    eeconfig_update_kb_datablock(&kb_cstm_config);
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if ( *channel_id == id_custom_channel ) {
        switch ( *command_id )
        {
            case id_custom_set_value:
            {
                caps_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value:
            {
                caps_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save:
            {
                caps_config_save();
                break;
            }
            default:
            {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }

    // Return the unhandled state
    *command_id = id_unhandled;

    // DO NOT call raw_hid_send(data,length) here, let caller do this
}
#include "analog.h"
void housekeeping_task_kb(void) {
    static uint8_t rgb_charge_state = 0;
    static uint32_t rgb_charge_timer = 0;
    if (palReadLine(A2) == 0 && analogReadPin(BATTERY_LEVEL_PIN)>=480) {
        rgblight_set_layer_state(18, true);
        rgb_charge_state = 0;
    } else if (palReadLine(A1) == 0) {
        if (timer_elapsed32(rgb_charge_timer) >= 500) {
            rgb_charge_timer = timer_read32();
        } else {
            return;
        }

        if (rgb_charge_state == 0) {
            rgb_charge_state += 1;
            rgblight_unblink_all_but_layer(15);
            rgblight_blink_layer_repeat(15, 500, 1);
        } else if (rgb_charge_state == 1) {
            rgb_charge_state += 1;
            rgblight_unblink_all_but_layer(16);
            rgblight_blink_layer_repeat(16, 500, 1);
        } else if (rgb_charge_state == 2) {
            rgb_charge_state += 1;
            rgblight_unblink_all_but_layer(17);
            rgblight_blink_layer_repeat(17, 500, 1);
        } else {
            rgb_charge_state = 0;
            rgblight_unblink_all_but_layer(18);
            rgblight_blink_layer_repeat(18, 500, 1);
        }
    } else {
        // if (rgb_charge_state != 5) {
            // rgblight_unblink_all_but_layer(18);
            // rgblight_unblink_layer(18);
        // }
        rgblight_set_layer_state(18, false);
        rgb_charge_state = 5;
    }
}

#endif
