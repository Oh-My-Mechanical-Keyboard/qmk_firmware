// Copyright 2023 Y&R-studio (@superYoungMonk)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "korea80.h"

#include "raw_hid.h"
bool yr_factory_test = false;
uint32_t rgb_t_itv = 1000;
uint32_t rgb_t_timer = 0;
uint8_t rgb_t_pos = 0;
uint8_t rgb_t_v = 10;

// globol
kb_cstm_config_t kb_cstm_config;


#ifdef RGB_MATRIX_ENABLE

#include "rgb_matrix_layer.h"

extern rgb_task_states rgb_task_state;

led_config_t g_led_config = {
    {
        {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  11,  12,  13,  14,  15,  16},
        {33,  32,  31,  30,  29,  28,  27,  26,  25,  24,  23,  22,  21,  20,  19,  18,  17},
        {34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50},
        {63,  62,  61,  60,  59,  58,  57,  56,  55,  54,  53,  52,   NO_LED,  51,   NO_LED,   NO_LED,   NO_LED},
        {64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,   NO_LED,  75,   NO_LED,   NO_LED,  76,   NO_LED},
        #ifdef LAYOUT_RGB_87
        {90,  89,  88,  85,  NO_LED,   NO_LED,   NO_LED,  82,   NO_LED,   NO_LED,   NO_LED,  81,  NO_LED,  80,  79,  78,  77}
        #else
        {91,  90,  89,  86,  NO_LED,   NO_LED,   NO_LED,  83,   NO_LED,   NO_LED,   NO_LED,  82,   81,      80,  79,  78,  77}
        #endif
    },
    {
        // LED Index to Physical Position
       {0,0},{14,0},{28,0},{42,0},{56,0},{70,0},{84,0},{98,0},{112,0},{126,0},{140,0},{154,0},{168,0},{182,0},{196,0},{210,0},{224,0},
        {224,13},{210,13},{196,13},{182,13},{168,13},{154,13},{140,13},{126,13},{112,13},{98,13},{84,13},{70,13},{56,13},{42,13},{28,13},{14,13},{0,13},
        {0,26},{14,26},{28,26},{42,26},{56,26},{70,26},{84,26},{98,26},{112,26},{126,26},{140,26},{154,26},{168,26},{182,26},{196,26},{210,26},{224,26},
                            {182,38},       {154,38},{140,38},{126,38},{112,38},{98,38},{84,38},{70,38},{56,38},{42,38},{28,38},{14,38},{0,38},
        {0,51},{14,51},{28,51},{42,51},{56,51},{70,51},{84,51},{98,51},{112,51},{126,51},{140,51},       {168,51},              {210,51},
        {224,64},{210,64},{196,64},{182,64},{168,64},{154,64},       {126,64},{112,64},{98,64},{84,64},{70,64},       {42,64},{28,64},{14,64},{0,64},

        {0,0},{16,0},{32,0},{48,0},{64,0},{80,0},{96,0},{112,0},{128,0},{144,0},{160,0},{176,0},{192,0},{208,0},{224,0},
        #ifdef LAYOUT_RGB_87
        {224,64},{208,64},{192,64},{176,64},{160,64},{144,64},{128,64},{112,64},{96,64},{80,64},{48,64},{32,64},{16,64},{0,64}
        #else
        {224,64},{208,64},{192,64},{176,64},{160,64},{144,64},{128,64},{112,64},{96,64},{80,64},{64,64},{48,64},{32,64},{16,64},{0,64}
        #endif
    },
    {
      // LED Index to Flag
      4,4,4,4,4, 4,4,4,4,4, // 0
      4,4,4,4,4, 4,4,4,4,4, // 1
      4,4,4,4,4, 4,4,4,4,4, // 2
      4,4,4,4,4, 4,4,4,4,4, // 3
      4,4,4,4,4, 4,4,4,4,4, // 4
      4,4,4,4,4, 4,4,4,4,4, // 5
      4,4,4,4,4, 4,4,4,4,4, // 6
      4,4,4,4,4, 4,4,4,4,4, // 7
      4,4,4,4,4, 4,4,4,4,4, // 8
    #ifdef LAYOUT_RGB_87
      4,
    #else
      4,4,
    #endif
      2,2,2,2,2, 2,2,2,2,2,
      2,2,2,2,2, 2,2,2,2,2,
      2,2,2,2,2, 2,2,2,2,2
    }
};


const rgb_matrix_adv_layer_segment_t PROGMEM my_capslock_layer[] = RGB_MATRIX_LAYER_SEGMENTS(
    {63, 1, HSV_RED}
);

const rgb_matrix_adv_layer_segment_t* const PROGMEM my_rgb_matrix_layers[] = RGB_MATRIX_LAYERS_LIST(
    my_capslock_layer
);

extern rgb_led_t rgb_matrix_ws2812_array[RGB_MATRIX_LED_COUNT];

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }

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

    if (rgb_matrix_is_enabled()) {
        if (kb_cstm_config.underground_rgb_sw == 1) {
            for (uint8_t i = led_min; i < led_max; ++i) {
                if ((g_led_config.flags[i] == 4)) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
        }
        if (kb_cstm_config.underground_rgb_sw == 2) {
            for (uint8_t i = led_min; i < led_max; ++i) {
                if ((g_led_config.flags[i] == 2)) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
        }
    }

    rgb_matrix_adv_blink_layer_repeat_helper();
    rgb_matrix_adv_set_layer_state(0, host_keyboard_led_state().caps_lock);

    // If not enabled, then nothing else will actually set the LEDs...
    if (!rgb_matrix_is_enabled()) {
        rgb_task_state = FLUSHING;
    }
#ifdef LAYOUT_RGB_87
    uint8_t cent_num = 85;
#else
    uint8_t cent_num = 86;
#endif
    rgb_matrix_ws2812_array[cent_num-1].r = rgb_matrix_ws2812_array[cent_num].r;
    rgb_matrix_ws2812_array[cent_num-1].g = rgb_matrix_ws2812_array[cent_num].g;
    rgb_matrix_ws2812_array[cent_num-1].b = rgb_matrix_ws2812_array[cent_num].b;
    rgb_matrix_ws2812_array[cent_num-2].r = rgb_matrix_ws2812_array[cent_num].r;
    rgb_matrix_ws2812_array[cent_num-2].g = rgb_matrix_ws2812_array[cent_num].g;
    rgb_matrix_ws2812_array[cent_num-2].b = rgb_matrix_ws2812_array[cent_num].b;
    rgb_matrix_ws2812_array[cent_num+1].r = rgb_matrix_ws2812_array[cent_num].r;
    rgb_matrix_ws2812_array[cent_num+1].g = rgb_matrix_ws2812_array[cent_num].g;
    rgb_matrix_ws2812_array[cent_num+1].b = rgb_matrix_ws2812_array[cent_num].b;
    rgb_matrix_ws2812_array[cent_num+2].r = rgb_matrix_ws2812_array[cent_num].r;
    rgb_matrix_ws2812_array[cent_num+2].g = rgb_matrix_ws2812_array[cent_num].g;
    rgb_matrix_ws2812_array[cent_num+2].b = rgb_matrix_ws2812_array[cent_num].b;
    return true;
}

void eeconfig_init_kb_datablock(void) {
    kb_cstm_config.underground_rgb_sw = 0;
    eeconfig_update_kb_datablock(&kb_cstm_config);
}


void keyboard_post_init_kb(void) {
    rgb_matrix_reload_from_eeprom();
    rgb_matrix_layers = my_rgb_matrix_layers;
#ifdef CONSOLE_ENABLE
    debug_enable = true;
    debug_matrix = true;
#endif
    eeconfig_read_kb_datablock(&kb_cstm_config);
}

void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_TIM2_REMAP_PARTIALREMAP1;
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

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) { return false; }
    switch(keycode) {
        case KC_F13:
            if (rgb_matrix_config.enable && record->event.pressed) {
                kb_cstm_config.underground_rgb_sw += 1;
                kb_cstm_config.underground_rgb_sw %= 3;
                eeconfig_update_kb_datablock(&kb_cstm_config);
            }
            return false;
        default:
            break;
    }
    return true;
}

// void bootmagic_lite(void) {
//     // We need multiple scans because debouncing can't be turned off.
//     setPinInputHigh(A15); // col0 pin
//     setPinOutput(B9); // row0 pin
//     writePin(B9, 0);
//     uint16_t toggle_times = 0;
//     bool into_boot = false;
//     while (1) {
//         wait_ms(5);
//         if (readPin(A15) == 0) {
//             toggle_times++;
//         } else {
//             break;
//         }
//         if (toggle_times >= 1000) {
//             into_boot = true;
//             break;
//         }
//     }

//     // If the configured key (commonly Esc) is held down on power up,
//     // reset the EEPROM valid state and jump to bootloader.
//     // This isn't very generalized, but we need something that doesn't
//     // rely on user's keymaps in firmware or EEPROM.

//     if (into_boot) {
//         eeconfig_disable();
//         // Jump to bootloader.
//         bootloader_jump();
//     }
// }
