/* 
Copyright 2021 OwLab

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "quantum.h"
#include "spring_alt.h"
#include "process_magic.h"

#include "raw_hid.h"
bool yr_factory_test = false;
uint32_t rgb_t_itv = 1000;
uint32_t rgb_t_timer = 0;
uint8_t rgb_t_pos = 0;
uint8_t rgb_t_v = 10;

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 5, HSV_WHITE}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer
);

bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        rgblight_set_layer_state(0, led_state.caps_lock);
    }
    return true;
}

/* globol var store in eeprom for key and underground rgb switch */
kb_cstm_config_t kb_cstm_config;

/* 只会调用一次 */
void eeconfig_init_kb_datablock(void) {
    kb_cstm_config.gap_rgb_sw  = 0;
    eeconfig_update_kb_datablock(&kb_cstm_config);
}

void keyboard_post_init_kb(void) {
    eeconfig_read_kb_datablock(&kb_cstm_config);
    rgblight_reload_from_eeprom();
    rgblight_set();
    rgblight_layers = my_rgb_layers;
    keyboard_post_init_user();
#ifdef CONSOLE_ENABLE
    debug_enable = true;
#endif
}
void keyboard_pre_init_kb(void) { }

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



bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) { return false; }
    switch(keycode) {
        case KC_F13:
            if (rgblight_is_enabled() && record->event.pressed) {
                kb_cstm_config.gap_rgb_sw += 1;
                kb_cstm_config.gap_rgb_sw %= 3;
                eeconfig_update_kb_datablock(&kb_cstm_config);
            }
            return false;
        case KC_F14:
            if (rgblight_is_enabled() && record->event.pressed) {
                process_magic(GUI_TOG, record);
            }
            return false;
        default:
            break;
    }
    return true;
}


void rgblight_call_driver(LED_TYPE *start_led, uint8_t num_leds) {
    uint8_t i = 0;
    if(!yr_factory_test) {
        if (kb_cstm_config.gap_rgb_sw == 1) {
            for (i = 5; i < 29; i++) {
                start_led[i].r = 0;
                start_led[i].g = 0;
                start_led[i].b = 0;
            }
        } else if (kb_cstm_config.gap_rgb_sw == 2 && !rgblight_get_layer_state(0)) {
            for (i = 0; i < 5; i++) {
                start_led[i].r = 0;
                start_led[i].g = 0;
                start_led[i].b = 0;
            }
        }
    }
    ws2812_setleds(start_led, num_leds);
}

extern keymap_config_t keymap_config;
void housekeeping_task_kb(void) {
    if (yr_factory_test) {
        if (rgblight_get_mode() != RGBLIGHT_MODE_STATIC_LIGHT) {
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        } else {
            if (rgb_t_timer == 0) rgb_t_timer = timer_read32();
            if (timer_elapsed32(rgb_t_timer) > rgb_t_itv) {
                rgb_t_timer = timer_read32();
                rgb_t_pos = (rgb_t_pos + 1) % 3;
            }
            switch (rgb_t_pos) {
                case 0:
                    rgblight_setrgb(rgb_t_v, 0, 0);
                    break;
                case 1:
                    rgblight_setrgb(0, rgb_t_v, 0);
                    break;
                case 2:
                    rgblight_setrgb(0, 0, rgb_t_v);
                default:
                    break;
            }
        }
    }
}
