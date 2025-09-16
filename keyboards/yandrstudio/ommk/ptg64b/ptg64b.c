// Copyright 2024 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ptg64b.h"
#include "process_magic.h"
#include "rgb_matrix_layer.h"

#include "raw_hid.h"
bool yr_factory_test = false;
uint32_t rgb_t_itv = 1000;
uint32_t rgb_t_timer = 0;
uint8_t rgb_t_pos = 0;
uint8_t rgb_t_v = 5;

/* globol var store in eeprom for key and underground rgb switch */
kb_cstm_config_t kb_cstm_config;
extern rgb_task_states rgb_task_state;

led_config_t g_led_config = {
    {
        {13,  12,  11,  10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0}, 
        {14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27}, 
        {40,  39,  38,  37,  36,  35,  34,  33,  32,  31,  30,  29,   NO_LED,  28}, 
        {41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,  52,  53,  54}, 
        {63,  62,  61,   NO_LED,   NO_LED,  60,   NO_LED,   NO_LED,   NO_LED,  59,  58,  57,  56,  55}
    },
    {
        /* LED Index to Physical Position */
        {224,0},{207,0},{190,0},{172,0},{155,0},{138,0},{121,0},{103,0},{86,0},{69,0},{52,0},{34,0},{17,0},{0,0},
        {0,16},{17,16},{34,16},{52,16},{69,16},{86,16},{103,16},{121,16},{138,16},{155,16},{172,16},{190,16},{207,16},{224,16},
        {224,32},       {190,32},{172,32},{155,32},{138,32},{121,32},{103,32},{86,32},{69,32},{52,32},{34,32},{17,32},{0,32},
        {0,48},{17,48},{34,48},{52,48},{69,48},{86,48},{103,48},{121,48},{138,48},{155,48},{172,48},{190,48},{207,48},{224,48},
        {224,64},{207,64},{190,64},{172,64},{155,64},                     {86,64},              {34,64},{17,64},{0,64},

        {0,64},{0,42},{0,21},{0,0},
        {22,0},{44,0},{66,0},{88,0},{110,0},{132,0},{154,0},{176,0},{200,0},
        {224,0},{224,21},{224,42},{224,64},
        {200,64},{176,64},{154,64},{132,64},{110,64},{88,64},{66,64},{44,64},{22,64}
    },
    {
      /* LED Index to Flag */
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4,
      2,2,2,2,2, 2,2,2,2,2,
      2,2,2,2,2, 2,2,2,2,2,
      2,2,2,2,2, 2
    }
};

const rgb_matrix_adv_layer_segment_t PROGMEM my_capslock_layer[] = RGB_MATRIX_LAYER_SEGMENTS(
    {40, 1, HSV_RED}
);

const rgb_matrix_adv_layer_segment_t* const PROGMEM my_rgb_matrix_layers[] = RGB_MATRIX_LAYERS_LIST(
    my_capslock_layer
);

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    if (rgb_matrix_is_enabled()) {
        if (kb_cstm_config.top_rgb_sw == 2) {
            for (uint8_t i = led_min; i < led_max; ++i) {
                if ((g_led_config.flags[i] == 4)) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
        } else if (kb_cstm_config.top_rgb_sw == 1) {
            for (uint8_t i = led_min; i < led_max; ++i) {
                if ((g_led_config.flags[i] == 2)) {
                    rgb_matrix_set_color(i, 0, 0, 0);
                }
            }
        }
    }

    rgb_matrix_adv_blink_layer_repeat_helper();
    rgb_matrix_adv_set_layer_state(0, host_keyboard_led_state().caps_lock);

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


/* 只会调用一次 */
void eeconfig_init_kb_datablock(void) {
    kb_cstm_config.top_rgb_sw  = 0;
    eeconfig_update_kb_datablock(&kb_cstm_config);
}

void keyboard_post_init_kb(void) {
    eeconfig_read_kb_datablock(&kb_cstm_config);
    keyboard_post_init_user();
    rgb_matrix_reload_from_eeprom();
    rgb_matrix_layers = my_rgb_matrix_layers;
#ifdef CONSOLE_ENABLE
    debug_enable = true;
#endif
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_F24:
            if (rgb_matrix_config.enable && record->event.pressed) {
                kb_cstm_config.top_rgb_sw += 1;
                kb_cstm_config.top_rgb_sw %= 3;
            }
            eeconfig_update_kb_datablock(&kb_cstm_config);
            return false;
        case KC_F23:
            if (record->event.pressed) {
                process_magic(CG_TOGG, record);
            }
            return false;
        default:
            return true;
    }
    return true;
}

bool via_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id = &(data[0]);
    uint8_t *command_data = &(data[1]);
    if (*command_id == 0x96 && command_data[0] == 0x96) {
        if (command_data[1] == 0x96) {
            eeconfig_disable();
        }
        if (command_data[2] == 0x96) {
            bootloader_jump();
        } else if (command_data[2] == 0x97) {
            NVIC_SystemReset();
        }
        return true;
    }
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

void mcu_reset(void) {
    NVIC_SystemReset();
}

void bootloader_jump(void) {}
void bootmagic_lite(void) {}