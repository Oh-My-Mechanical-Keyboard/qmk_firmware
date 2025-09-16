// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ps64ble.h"

#ifdef BIU_BLE5_ENABLE
#    include "biu_ble_common.h"
#endif

#ifdef RGB_MATRIX_ENABLE

#include "rgb_matrix_layer.h"

led_config_t g_led_config = {
    {
    //    0     1   2     3   4    5      6      7    8    9      10   11   12   13
        { 13,  12,  11,  10,  9,   8,     7,     6,   5,   4,     3,   2,   1,   0},
        { 43,  41,  40,  39,  38,  37,    36,    35,  34,  33,    32,  31,  30,  28},
        { 45,  51,  50,  49,  48,  47,    46,    52,  53,  54,    55,  56,  57,  KC_NO},
        { 72,  69,  68,  67,  66,  70,    71,    62,  63,  65,    64,  61,  60,  59},
        { 98,  97,  96,  95,  94,  KC_NO, KC_NO, 90,  91,  KC_NO, 92,  89,  88,  87}
    },
    {
        {224,0},{206,0},{189,0},{172,0},{155,0},{137,0},{120,0},{103,0},{86,0},{68,0},{51,0},{34,0},{17,0},{0,0},
        {0,0},{17,0},{34,0},{51,0},{68,0},{86,0},{103,0},{120,0},{137,0},{155,0},{172,0},{189,0},{206,0},{224,0},
        {224,16},{224,16},{206,16},{189,16},{172,16},{155,16},{137,16},{120,16},{103,16},{86,16},{68,16},{51,16},{34,16},{17,16},{0,16},{0,16},
        {0,32},{0,32},{17,32},{34,32},{51,32},{68,32},{86,32},{103,32},{120,32},{137,32},{155,32},{172,32},{189,32},{206,32},{224,32},
        {224,48},{206,48},{189,48},{172,48},{155,48},{137,48},{120,48},{103,48},{86,48},{68,48},{51,48},{34,48},{17,48},{0,48},
        {0,48},{17,48},{34,48},{51,48},{68,48},{86,48},{103,48},{120,48},{137,48},{155,48},{172,48},{189,48},{206,48},{224,48},
        {224,64},{206,64},{189,64},{172,64},{155,64},{137,64},{68,64},{68,64},{51,64},{34,64},{17,64},{0,64}
    },
    {
        // LED Index to Flag
        4,4,4,4,4, 4,4,4,4,4, 4,4,4,4,
        2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,
        4,2,4,4,4, 4,4,4,4,4, 4,4,4,4, 2,4,
        2,4,4,4,4, 4,4,4,4,4, 4,4,4,4, 2,
        4,4,4,4,4, 4,4,4,4,4, 4,4,4,4,
        2,2,2,2,2, 2,2,2,2,2, 2,2,2,2,
        4,4,4,4,4, 4,4,4,4,4, 4,4
    }
};

// globol
typedef union {
    uint32_t raw;
    uint8_t  underground_rgb_sw : 8;
} kb_cstm_config_t;
kb_cstm_config_t kb_cstm_config;


// rgb matrix layer

const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn1_layer[] = RGB_MATRIX_LAYER_SEGMENTS({41, 1, HSV_GREEN});  // 0
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn2_layer[] = RGB_MATRIX_LAYER_SEGMENTS({40, 1, HSV_GREEN});  // 1
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn3_layer[] = RGB_MATRIX_LAYER_SEGMENTS({39, 1, HSV_GREEN});  // 2
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn4_layer[] = RGB_MATRIX_LAYER_SEGMENTS({38, 1, HSV_GREEN});  // 3
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair1_layer[] = RGB_MATRIX_LAYER_SEGMENTS({41, 1, HSV_BLUE});   // 4
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair2_layer[] = RGB_MATRIX_LAYER_SEGMENTS({40, 1, HSV_BLUE});   // 5
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair3_layer[] = RGB_MATRIX_LAYER_SEGMENTS({39, 1, HSV_BLUE});   // 6
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair4_layer[] = RGB_MATRIX_LAYER_SEGMENTS({38, 1, HSV_BLUE});   // 7
const rgb_matrix_adv_layer_segment_t PROGMEM usb_pair_layer[] = RGB_MATRIX_LAYER_SEGMENTS({37, 1, HSV_BLUE});   // 8 // nlg:37 ble:47
const rgb_matrix_adv_layer_segment_t PROGMEM usb_conn_layer[] = RGB_MATRIX_LAYER_SEGMENTS({37, 1, HSV_GREEN});  // 9 // nlg:37 ble:47
const rgb_matrix_adv_layer_segment_t PROGMEM capslock_layer[] = RGB_MATRIX_LAYER_SEGMENTS({45, 1, HSV_RED});    // 10
const rgb_matrix_adv_layer_segment_t PROGMEM bat_10_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({12, 1, HSV_RED});     // 11
const rgb_matrix_adv_layer_segment_t PROGMEM bat_20_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({11, 2, HSV_GREEN});   // 12
const rgb_matrix_adv_layer_segment_t PROGMEM bat_30_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({10, 3, HSV_GREEN});   // 13
const rgb_matrix_adv_layer_segment_t PROGMEM bat_40_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({9, 4, HSV_GREEN});   // 14
const rgb_matrix_adv_layer_segment_t PROGMEM bat_50_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({8, 5, HSV_GREEN});   // 15
const rgb_matrix_adv_layer_segment_t PROGMEM bat_60_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({7, 6, HSV_GREEN});   // 16
const rgb_matrix_adv_layer_segment_t PROGMEM bat_70_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({6, 7, HSV_GREEN});   // 17
const rgb_matrix_adv_layer_segment_t PROGMEM bat_80_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({5, 8, HSV_GREEN});   // 18
const rgb_matrix_adv_layer_segment_t PROGMEM bat_90_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({4, 9, HSV_GREEN});   // 19
const rgb_matrix_adv_layer_segment_t PROGMEM bat_100_layer[]  = RGB_MATRIX_LAYER_SEGMENTS({3, 10, HSV_GREEN});  // 20

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

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
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
#ifdef CONSOLE_ENABLE
    debug_enable = true;
#endif
}

// void housekeeping_task_kb(void) {
//     static uint8_t rgb_charge_state = 0;
//     static uint32_t rgb_charge_timer = 0;
//     if (palReadLine(USB_PWR_READ_PIN)) {

//         if (timer_elapsed32(rgb_charge_timer) >= 500) {
//             rgb_charge_timer = timer_read32();
//         } else {
//             return;
//         }

//         if (rgb_charge_state == 0) {
//             rgb_charge_state += 1;
//             rgb_matrix_adv_unblink_all_batlayer_but_one_layer(15);
//             rgb_matrix_adv_blink_layer_repeat(15, 500, 1);
//         } else if (rgb_charge_state == 1) {
//             rgb_charge_state += 1;
//             rgb_matrix_adv_unblink_all_batlayer_but_one_layer(16);
//             rgb_matrix_adv_blink_layer_repeat(16, 500, 1);
//         } else if (rgb_charge_state == 2) {
//             rgb_charge_state += 1;
//             rgb_matrix_adv_unblink_all_batlayer_but_one_layer(17);
//             rgb_matrix_adv_blink_layer_repeat(17, 500, 1);
//         } else {
//             rgb_charge_state = 0;
//             rgb_matrix_adv_unblink_all_batlayer_but_one_layer(18);
//             rgb_matrix_adv_blink_layer_repeat(18, 500, 1);
//         }
//     } else {
//         rgb_charge_state = 0;
//     }
// }
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

        case MKC_LG:
            if (record->event.pressed) {
                process_magic(GUI_TOG, record);
            }
            return false;
        case MKC_TCG:
            if (record->event.pressed) {
                process_magic(CG_TOGG, record);
            }
            return false;
        case MKC_MACOS:
            if (record->event.pressed) {
                process_magic(AG_TOGG, record);
            }
            return false;
        case MKC_MCTL:
            if (record->event.pressed) {
                host_consumer_send(0x29F);
            } else {
                host_consumer_send(0);
            }
            return false;
        case MKC_LPAD:
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
