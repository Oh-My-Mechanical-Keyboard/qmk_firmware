// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "dmk87ble.h"

#ifdef BIU_BLE5_ENABLE
#    include "spi_master.h"
#    include "biu_ble_common.h"
#endif

#ifdef RGB_MATRIX_ENABLE

#    include "rgb_matrix_layer.h"

const aw_led PROGMEM g_aw_leds[RGB_MATRIX_LED_COUNT] = {
/* Each AW20216 channel is controlled by a register at some offset between 0x00
 * and 0xD7 inclusive.
 * See drivers/awinic/aw20216.h for the mapping between register offsets and
 * driver pin locations.
 *    driver
 *    |  R location
 *    |  |        G location
 *    |  |        |        B location
 *    |  |        |        | */
    /* Line 1*/
    { 0, CS3_SW8,   CS2_SW8,   CS1_SW8  },
    { 0, CS3_SW10,  CS2_SW10,  CS1_SW10 },
    { 0, CS3_SW6,   CS2_SW6,   CS1_SW6  },
    { 0, CS3_SW4,   CS2_SW4,   CS1_SW4  },
    { 0, CS3_SW2,   CS2_SW2,   CS1_SW2  },
    { 0, CS3_SW1,   CS2_SW1,   CS1_SW1  },
    { 0, CS3_SW3,   CS2_SW3,   CS1_SW3  },
    { 0, CS3_SW5,   CS2_SW5,   CS1_SW5  },
    { 0, CS3_SW7,   CS2_SW7,   CS1_SW7  },
    { 1, CS15_SW6,  CS14_SW6,  CS13_SW6 },
    { 1, CS15_SW8,  CS14_SW8,  CS13_SW8 },
    { 1, CS15_SW10, CS14_SW10, CS13_SW10},
    { 1, CS15_SW12, CS14_SW12, CS13_SW12},
    { 1, CS15_SW1,  CS14_SW1,  CS13_SW1 },
    { 1, CS15_SW3,  CS14_SW3,  CS13_SW3 },
    { 1, CS15_SW7,  CS14_SW7,  CS13_SW7 },
    /* Line2 */
    { 0, CS6_SW8,  CS5_SW8, CS4_SW8  },
    { 0, CS6_SW10, CS5_SW10, CS4_SW10},
    { 0, CS6_SW6,  CS5_SW6, CS4_SW6  },
    { 0, CS6_SW4,  CS5_SW4, CS4_SW4  },
    { 0, CS6_SW2,  CS5_SW2, CS4_SW2  },
    { 0, CS6_SW1,  CS5_SW1, CS4_SW1  },
    { 0, CS6_SW3,  CS5_SW3, CS4_SW3  },
    { 0, CS6_SW5,  CS5_SW5, CS4_SW5  },
    { 0, CS6_SW7,  CS5_SW7, CS4_SW7  },
    { 1, CS3_SW6,  CS2_SW6, CS1_SW6  },
    { 1, CS3_SW8,  CS2_SW8, CS1_SW8  },
    { 1, CS3_SW10, CS2_SW10, CS1_SW10},
    { 1, CS3_SW12, CS2_SW12, CS1_SW12},
    { 1, CS3_SW4,  CS2_SW4, CS1_SW4  },
    { 1, CS3_SW1,  CS2_SW1, CS1_SW1  },
    { 1, CS3_SW3,  CS2_SW3, CS1_SW3  },
    { 1, CS3_SW7,  CS2_SW7, CS1_SW7  },
    /* Line3 */
    { 0, CS9_SW8,   CS8_SW8,   CS7_SW8  },
    { 0, CS9_SW10,  CS8_SW10,  CS7_SW10 },
    { 0, CS9_SW6,   CS8_SW6,   CS7_SW6  },
    { 0, CS9_SW4,   CS8_SW4,   CS7_SW4  },
    { 0, CS9_SW2,   CS8_SW2,   CS7_SW2  },
    { 0, CS9_SW1,   CS8_SW1,   CS7_SW1  },
    { 0, CS9_SW3,   CS8_SW3,   CS7_SW3  },
    { 0, CS9_SW5,   CS8_SW5,   CS7_SW5  },
    { 0, CS9_SW7,   CS8_SW7,   CS7_SW7  },
    { 1, CS17_SW6,  CS16_SW6,  CS18_SW6 },
    { 1, CS17_SW8,  CS16_SW8,  CS18_SW8 },
    { 1, CS17_SW10, CS16_SW10, CS18_SW10},
    { 1, CS17_SW12, CS16_SW12, CS18_SW12},
    { 1, CS17_SW4,  CS16_SW4,  CS18_SW4 },
    { 1, CS17_SW1,  CS16_SW1,  CS18_SW1 },
    { 1, CS17_SW3,  CS16_SW3,  CS18_SW3 },
    { 1, CS17_SW7,  CS16_SW7,  CS18_SW7 },
    /* Line4 */
    { 0, CS12_SW8,  CS11_SW8,  CS10_SW8 },
    { 0, CS12_SW10, CS11_SW10, CS10_SW10},
    { 0, CS12_SW6,  CS11_SW6,  CS10_SW6 },
    { 0, CS12_SW4,  CS11_SW4,  CS10_SW4 },
    { 0, CS12_SW2,  CS11_SW2,  CS10_SW2 },
    { 0, CS12_SW1,  CS11_SW1,  CS10_SW1 },
    { 0, CS12_SW3,  CS11_SW3,  CS10_SW3 },
    { 0, CS12_SW5,  CS11_SW5,  CS10_SW5 },
    { 0, CS12_SW7,  CS11_SW7,  CS10_SW7 },
    { 1, CS6_SW6,   CS5_SW6,   CS4_SW6  },
    { 1, CS6_SW8,   CS5_SW8,   CS4_SW8  },
    { 1, CS6_SW10,  CS5_SW10,  CS4_SW10 },
    { 1, CS6_SW4,   CS5_SW4,   CS4_SW4  },
    /* Line5 */
    { 0, CS15_SW8, CS14_SW8, CS13_SW8},
    { 0, CS15_SW6, CS14_SW6, CS13_SW6},
    { 0, CS15_SW4, CS14_SW4, CS13_SW4},
    { 0, CS15_SW2, CS14_SW2, CS13_SW2},
    { 0, CS15_SW1, CS14_SW1, CS13_SW1},
    { 0, CS15_SW3, CS14_SW3, CS13_SW3},
    { 0, CS15_SW5, CS14_SW5, CS13_SW5},
    { 0, CS15_SW7, CS14_SW7, CS13_SW7},
    { 1, CS9_SW6,  CS8_SW6,  CS7_SW6 },
    { 1, CS9_SW8,  CS8_SW8,  CS7_SW8 },
    { 1, CS9_SW10, CS8_SW10, CS7_SW10},
    { 1, CS9_SW4,  CS8_SW4,  CS7_SW4 },
    { 1, CS9_SW3,  CS8_SW3,  CS7_SW3 },
    /* Line6 */
    { 0, CS18_SW8,  CS17_SW8,  CS16_SW8 },
    { 0, CS18_SW10, CS17_SW10, CS16_SW10},
    { 0, CS18_SW6,  CS17_SW6,  CS16_SW6 },
    { 0, CS18_SW1,  CS17_SW1,  CS16_SW1 },
    { 1, CS12_SW6,  CS11_SW6,  CS10_SW6 },
    { 1, CS12_SW8,  CS11_SW8,  CS10_SW8 },
    { 1, CS12_SW10, CS11_SW10, CS10_SW10},
    { 1, CS12_SW4,  CS11_SW4,  CS10_SW4 },
    { 1, CS12_SW1,  CS11_SW1,  CS10_SW1 },
    { 1, CS12_SW3,  CS11_SW3,  CS10_SW3 },
    { 1, CS12_SW7,  CS11_SW7,  CS10_SW7 },
    /* Indicator LED */
    { 1, CS15_SW5,  CS14_SW5,  CS13_SW5 },
    { 1, CS15_SW9,  CS14_SW9,  CS13_SW9 },
    { 1, CS15_SW11, CS14_SW11, CS13_SW11}
};


led_config_t g_led_config = {
    {
        {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  11,  12,   NO_LED,  13,  14,  15},
        {16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32},
        {33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49},
        {50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,   NO_LED,  62,   NO_LED,   NO_LED,   NO_LED},
        {63,   NO_LED,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,   NO_LED,  74,   NO_LED,  75,   NO_LED},
        {76,  77,  78,   NO_LED,   NO_LED,   NO_LED,  79,   NO_LED,   NO_LED,   NO_LED,  80,  81,  82,  83,  84,  85,  86}
    },
    {
        {0,0},{14,0},{28,0},{42,0},{56,0},{70,0},{84,0},{98,0},{112,0},{126,0},{140,0},{154,0},{168,0},       {196,0},{210,0},{224,0},
        {0,13},{14,13},{28,13},{42,13},{56,13},{70,13},{84,13},{98,13},{112,13},{126,13},{140,13},{154,13},{168,13},{182,13},{196,13},{210,13},{224,13},
        {0,26},{14,26},{28,26},{42,26},{56,26},{70,26},{84,26},{98,26},{112,26},{126,26},{140,26},{154,26},{168,26},{182,26},{196,26},{210,26},{224,26},
        {0,38},{14,38},{28,38},{42,38},{56,38},{70,38},{84,38},{98,38},{112,38},{126,38},{140,38},{154,38},       {182,38},
        {0,51},       {28,51},{42,51},{56,51},{70,51},{84,51},{98,51},{112,51},{126,51},{140,51},{154,51},       {182,51},       {210,51},
        {0,64},{14,64},{28,64},                     {84,64},                     {140,64},{154,64},{168,64},{182,64},{196,64},{210,64},{224,64},
        {196,0},{210,0},{224,0}

    },
    {
      // LED Index to Flag
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,2,2,2
    }
};

// rgb matrix layer
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn1_layer[] = RGB_MATRIX_LAYER_SEGMENTS({34, 1, HSV_GREEN});      // 0
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn2_layer[] = RGB_MATRIX_LAYER_SEGMENTS({35, 1, HSV_GREEN});      // 1
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn3_layer[] = RGB_MATRIX_LAYER_SEGMENTS({36, 1, HSV_GREEN});      // 2
const rgb_matrix_adv_layer_segment_t PROGMEM bt_conn4_layer[] = RGB_MATRIX_LAYER_SEGMENTS({37, 1, HSV_GREEN});      // 3
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair1_layer[] = RGB_MATRIX_LAYER_SEGMENTS({34, 1, HSV_BLUE});       // 4
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair2_layer[] = RGB_MATRIX_LAYER_SEGMENTS({35, 1, HSV_BLUE});       // 5
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair3_layer[] = RGB_MATRIX_LAYER_SEGMENTS({36, 1, HSV_BLUE});       // 6
const rgb_matrix_adv_layer_segment_t PROGMEM bt_pair4_layer[] = RGB_MATRIX_LAYER_SEGMENTS({37, 1, HSV_BLUE});       // 7
const rgb_matrix_adv_layer_segment_t PROGMEM usb_pair_layer[] = RGB_MATRIX_LAYER_SEGMENTS({52, 1, HSV_BLUE});       // 8
const rgb_matrix_adv_layer_segment_t PROGMEM usb_conn_layer[] = RGB_MATRIX_LAYER_SEGMENTS({52, 1, HSV_GREEN});      // 9
const rgb_matrix_adv_layer_segment_t PROGMEM capslock_layer[] = RGB_MATRIX_LAYER_SEGMENTS({50, 1, HSV_RED}, {88, 1, HSV_RED});        // 10
const rgb_matrix_adv_layer_segment_t PROGMEM scrolock_layer[] = RGB_MATRIX_LAYER_SEGMENTS({89, 1, HSV_RED});        // 11
const rgb_matrix_adv_layer_segment_t PROGMEM bat_10_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({87, 1, HSV_RED});        // 12
const rgb_matrix_adv_layer_segment_t PROGMEM bat_20_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 2, HSV_GREEN});       // 13
const rgb_matrix_adv_layer_segment_t PROGMEM bat_30_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 3, HSV_GREEN});       // 14
const rgb_matrix_adv_layer_segment_t PROGMEM bat_40_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 4, HSV_GREEN});       // 15
const rgb_matrix_adv_layer_segment_t PROGMEM bat_50_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 5, HSV_GREEN});       // 16
const rgb_matrix_adv_layer_segment_t PROGMEM bat_60_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 6, HSV_GREEN});       // 17
const rgb_matrix_adv_layer_segment_t PROGMEM bat_70_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 7, HSV_GREEN});       // 18
const rgb_matrix_adv_layer_segment_t PROGMEM bat_80_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 8, HSV_GREEN});       // 19
const rgb_matrix_adv_layer_segment_t PROGMEM bat_90_layer[]   = RGB_MATRIX_LAYER_SEGMENTS({1, 9, HSV_GREEN});       // 20
const rgb_matrix_adv_layer_segment_t PROGMEM bat_100_layer[]  = RGB_MATRIX_LAYER_SEGMENTS({1, 10, HSV_GREEN});      // 21

const rgb_matrix_adv_layer_segment_t* const PROGMEM my_rgb_matrix_layers[] = RGB_MATRIX_LAYERS_LIST(bt_conn1_layer, bt_conn2_layer, bt_conn3_layer, bt_conn4_layer, bt_pair1_layer, bt_pair2_layer, bt_pair3_layer, bt_pair4_layer, usb_pair_layer, usb_conn_layer, capslock_layer, bat_10_layer, bat_20_layer, bat_30_layer, bat_40_layer, bat_50_layer, bat_60_layer, bat_70_layer, bat_80_layer, bat_90_layer, bat_100_layer);

void rgb_matrix_adv_unblink_all_but_caps_bat_layer(void) {
    for (uint8_t i = 0; i < 11; i++) {
        rgb_matrix_adv_unblink_layer(i);
    }
}

void rgb_matrix_adv_unblink_all_batlayer_but_one_layer(uint8_t l) {
    for (uint8_t i = 12; i < 22; i++) {
        if (l == i) continue;
        rgb_matrix_adv_unblink_layer(i);
    }
}

void rgb_matrix_adv_unblink_all_but_layer(uint8_t l) {
    for (uint8_t i = 0; i < 22; i++) {
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
    rgb_matrix_set_color(87, 0, 0, 0);
    rgb_matrix_set_color(88, 0, 0, 0);
    rgb_matrix_set_color(89, 0, 0, 0);

    rgb_matrix_adv_blink_layer_repeat_helper();
    rgb_matrix_adv_set_layer_state(10, host_keyboard_led_state().caps_lock);
    rgb_matrix_adv_set_layer_state(11, host_keyboard_led_state().scroll_lock);
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

void keyboard_post_init_kb(void) {
    rgb_matrix_reload_from_eeprom();
    rgb_matrix_layers = my_rgb_matrix_layers;
#ifdef CONSOLE_ENABLE
    debug_enable = true;
#endif
}
#endif

// #ifndef BIU_BLE5_ENABLE
/* 对于通过供电控制关断的灯控，需要在初始化之前先供电 */
void keyboard_pre_init_kb(void) {
    palSetLineMode(RGB_BLE_SW, PAL_MODE_OUTPUT_PUSHPULL);
    writePin(RGB_BLE_SW, RGB_EN_STATE);
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
#ifdef BIU_BLE5_ENABLE
        case RGB_TOG:
            if (record->event.pressed) {
                if (!rgb_matrix_is_enabled()) {
                    writePin(RGB_BLE_SW, RGB_EN_STATE);
                    force_spi_init();
                    AW20216_init(DRIVER_1_CS, DRIVER_1_EN);
#           if defined(DRIVER_2_CS)
                    AW20216_init(DRIVER_2_CS, DRIVER_2_EN);
#           endif // DRIVER_2_CS
                }
            }
            return true;
#endif
        default:
            return true;
    }
    return true;
}
