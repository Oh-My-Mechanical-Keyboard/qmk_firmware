// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "cupid65ble.h"
#include "raw_hid.h"
bool yr_factory_test = false;
uint32_t rgb_t_itv = 1000;
uint32_t rgb_t_timer = 0;
uint8_t rgb_t_pos = 0;
uint8_t rgb_t_v = 10;

#ifdef BIU_BLE5_ENABLE
#    include "biu_ble_common.h"
#endif

#ifdef RGB_MATRIX_ENABLE

#    include "rgb_matrix_layer.h"


led_config_t g_led_config = {{{0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  11,  12,  13,  14},
                              {15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29},
                              {30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,   NO_LED,  42,   NO_LED},
                              {43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,   NO_LED,  54,  55,   NO_LED},
                              {56,  57,  58,  59,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,  60,  61,   NO_LED,  62,  63,  64}},
                             {{0,0},{16,0},{32,0},{48,0},{64,0},{80,0},{96,0},{112,0},{128,0},{144,0},{160,0},{176,0},{192,0},{208,0},{224,0},
                              {0,16},{16,16},{32,16},{48,16},{64,16},{80,16},{96,16},{112,16},{128,16},{144,16},{160,16},{176,16},{192,16},{208,16},{224,16},
                              {0,32},{16,32},{32,32},{48,32},{64,32},{80,32},{96,32},{112,32},{128,32},{144,32},{160,32},{176,32},       {208,32},
                              {0,48},{16,48},{32,48},{48,48},{64,48},{80,48},{96,48},{112,48},{128,48},{144,48},{160,48},       {192,48},{208,48},
                              {0,64},{16,64},{32,64},{48,64},                                   {144,64},{160,64},       {192,64},{208,64},{224,64},
                              {224,64},{224,56},{224,48},{224,40},{224,32},{224,24},{224,16},{224,8},{224,0},
                              {0,0},{0,8},{0,16},{0,24},{0,32},{0,40},{0,48},{0,56},{0,64}
                              },
                             {// LED Index to Flag
                              4,4,4,4,4, 4,4,4,4,4,
                              4,4,4,4,4, 4,4,4,4,4,
                              4,4,4,4,4, 4,4,4,4,4,
                              4,4,4,4,4, 4,4,4,4,4,
                              4,4,4,4,4, 4,4,4,4,4,
                              4,4,4,4,4, 4,4,4,4,4,
                              4,4,4,4,4, 2,2,2,2,2,
                              2,2,2,2,2, 2,2,2,2,2,
                              2,2,2}};

// globol
kb_cstm_config_t kb_cstm_config;

// rgb matrix layer
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn1_layer[] = RGB_MATRIX_LAYER_SEGMENTS({16, 1, HSV_GREEN});      // 0
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn2_layer[] = RGB_MATRIX_LAYER_SEGMENTS({17, 1, HSV_GREEN});      // 1
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn3_layer[] = RGB_MATRIX_LAYER_SEGMENTS({18, 1, HSV_GREEN});      // 2
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn4_layer[] = RGB_MATRIX_LAYER_SEGMENTS({19, 1, HSV_GREEN});      // 3
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair1_layer[] = RGB_MATRIX_LAYER_SEGMENTS({16, 1, HSV_BLUE});       // 4
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair2_layer[] = RGB_MATRIX_LAYER_SEGMENTS({17, 1, HSV_BLUE});       // 5
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair3_layer[] = RGB_MATRIX_LAYER_SEGMENTS({18, 1, HSV_BLUE});       // 6
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair4_layer[] = RGB_MATRIX_LAYER_SEGMENTS({19, 1, HSV_BLUE});       // 7
const rgb_matrix_adv_layer_segment_t PROGMEM usb_pair_layer[] = RGB_MATRIX_LAYER_SEGMENTS({32, 1, HSV_BLUE});       // 8
const rgb_matrix_adv_layer_segment_t PROGMEM usb_conn_layer[] = RGB_MATRIX_LAYER_SEGMENTS({32, 1, HSV_GREEN});      // 9
const rgb_matrix_adv_layer_segment_t PROGMEM capslock_layer[] = RGB_MATRIX_LAYER_SEGMENTS({30, 1, HSV_RED});        // 10
const rgb_matrix_adv_layer_segment_t PROGMEM bat_10_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 1, HSV_RED});        // 11
const rgb_matrix_adv_layer_segment_t PROGMEM bat_20_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 2, HSV_GREEN});       // 12
const rgb_matrix_adv_layer_segment_t PROGMEM bat_30_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 3, HSV_GREEN});       // 13
const rgb_matrix_adv_layer_segment_t PROGMEM bat_40_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 4, HSV_GREEN});       // 14
const rgb_matrix_adv_layer_segment_t PROGMEM bat_50_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 5, HSV_GREEN});       // 15
const rgb_matrix_adv_layer_segment_t PROGMEM bat_60_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 6, HSV_GREEN});       // 16
const rgb_matrix_adv_layer_segment_t PROGMEM bat_70_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 7, HSV_GREEN});       // 17
const rgb_matrix_adv_layer_segment_t PROGMEM bat_80_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 8, HSV_GREEN});       // 18
const rgb_matrix_adv_layer_segment_t PROGMEM bat_90_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 9, HSV_GREEN});       // 19
const rgb_matrix_adv_layer_segment_t PROGMEM bat_100_layer[]  = RGB_MATRIX_LAYER_SEGMENTS({1, 10, HSV_GREEN});      // 20

const rgb_matrix_adv_layer_segment_t* const PROGMEM my_rgb_matrix_layers[] = RGB_MATRIX_LAYERS_LIST(bt_conn1_layer, bt_conn2_layer, bt_conn3_layer, bt_conn4_layer, bt_pair1_layer, bt_pair2_layer, bt_pair3_layer, bt_pair4_layer, usb_pair_layer, usb_conn_layer, capslock_layer, bat_10_layer, bat_20_layer, bat_30_layer, bat_40_layer, bat_50_layer, bat_60_layer, bat_70_layer, bat_80_layer, bat_90_layer, bat_100_layer);

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

extern rgb_task_states              rgb_task_state;
extern rgb_matrix_adv_layers_mask_t rgb_matrix_adv_enabled_layer_mask;
extern rgb_matrix_adv_layers_mask_t _blinking_layer_mask;

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    if (rgb_matrix_is_enabled()) {
        if (kb_cstm_config.side_eff == 1) {
            HSV hsv_ud_color = {kb_cstm_config.side_color_h, kb_cstm_config.side_color_s, kb_cstm_config.side_brightness};
            RGB rgb_ud_color = hsv_to_rgb(hsv_ud_color);
            for (uint8_t i = led_min; i < led_max; ++i) {
                if ((g_led_config.flags[i] == 2)) {
                    rgb_matrix_set_color(i, rgb_ud_color.r, rgb_ud_color.g, rgb_ud_color.b);
                }
            }
        }
        if (kb_cstm_config.side_rgb_sw == 1) {
            for (uint8_t i = led_min; i < led_max; ++i) {
                if ((g_led_config.flags[i] == 4)) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
        }
        if (kb_cstm_config.side_rgb_sw == 2 || kb_cstm_config.side_eff == 2) {
            for (uint8_t i = led_min; i < led_max; ++i) {
                if ((g_led_config.flags[i] == 2)) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
        }
    }
    rgb_matrix_adv_blink_layer_repeat_helper();
    rgb_matrix_adv_set_layer_state(10, host_keyboard_led_state().caps_lock);

    if (yr_factory_test) {
        if (rgb_t_timer == 0) rgb_t_timer = timer_read32();
        if (timer_elapsed32(rgb_t_timer) > rgb_t_itv) {
            rgb_t_timer = timer_read32();
            rgb_t_pos = (rgb_t_pos + 1) % 3;
        }
        switch (rgb_t_pos) {
            case 0:
                rgb_matrix_set_color_all(rgb_t_v, 0, 0);
                break;
            case 1:
                rgb_matrix_set_color_all(0, rgb_t_v, 0);
                break;
            case 2:
                rgb_matrix_set_color_all(0, 0, rgb_t_v);
            default:
                break;

        }
    }

    // If not enabled, then nothing else will actually set the LEDs...
    if (!rgb_matrix_is_enabled()) {
        rgb_task_state = FLUSHING;
    }
    return true;
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
            rgb_matrix_adv_unblink_all_but_layer(channle % 4);
            rgb_matrix_adv_blink_layer_repeat(channle % 4, 500, 8);
        } else if (state == 8) {
            rgb_matrix_adv_unblink_all_but_layer(channle % 4 + 4);
            rgb_matrix_adv_blink_layer_repeat(channle % 4 + 4, 200, 20);
        } else if (state == 1) {
            rgb_matrix_adv_unblink_all_but_layer(channle % 4);
            rgb_matrix_adv_blink_layer_repeat(channle % 4, 3000, 1);
        } else {
            rgb_matrix_adv_unblink_all_but_caps_bat_layer();
        }
    }
    if (!rgb_matrix_is_enabled()) {
        rgb_task_state = FLUSHING;
    }
    return true;
}

void eeconfig_init_kb_datablock(void) {
    kb_cstm_config.side_rgb_sw = 0;
    kb_cstm_config.side_eff = 0;
    kb_cstm_config.side_brightness = RGB_MATRIX_DEFAULT_VAL;
    kb_cstm_config.side_color_h = 0;
    kb_cstm_config.side_color_s = 255;
    eeconfig_update_kb_datablock(&kb_cstm_config);
}

void keyboard_post_init_kb(void) {
    rgb_matrix_reload_from_eeprom();
    rgb_matrix_layers = my_rgb_matrix_layers;
    eeconfig_read_kb_datablock(&kb_cstm_config);
#ifdef CONSOLE_ENABLE
    debug_enable = true;
#endif
}

void side_config_set_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch ( *value_id )
    {
        case via_side_brightness:
            kb_cstm_config.side_brightness = *value_data;
            break;
        case via_side_effect:
            kb_cstm_config.side_eff = *value_data;
            break;
        case via_side_color:
            kb_cstm_config.side_color_h = value_data[0];
            kb_cstm_config.side_color_s = value_data[1];
            break;
    }
}
void side_config_get_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);
    switch ( *value_id )
    {
        case via_side_brightness:
            *value_data = kb_cstm_config.side_brightness;
            break;
        case via_side_effect:
            *value_data = kb_cstm_config.side_eff;
            break;
        case via_side_color:
            value_data[0] = kb_cstm_config.side_color_h;
            value_data[1] = kb_cstm_config.side_color_s;
            break;
    }
}
void side_config_save(void) {
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
                side_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value:
            {
                side_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save:
            {
                side_config_save();
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

#endif


#ifndef BIU_BLE5_ENABLE
void keyboard_pre_init_kb(void) {
    palSetLineMode(RGB_BLE_SW, PAL_MODE_OUTPUT_PUSHPULL);
    writePin(RGB_BLE_SW, 0);
}
#endif

bool via_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id = &(data[0]);
    uint8_t *command_data = &(data[1]);
    if (*command_id == 0x03 && command_data[0] == 0x96) {
        dprintf(">>Recv a pkg with cmd_data1: [%d]!!\n", command_data[1]);
        if (command_data[1] == 0x96) { // Factory test
            if (!yr_factory_test) {
                yr_factory_test = true;
            }
            raw_hid_send(data, length);
        }
        return true;
    }
    return false;
}
