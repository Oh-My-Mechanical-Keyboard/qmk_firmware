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
#include "magnum65v2.h"

#include "raw_hid.h"
bool yr_factory_test = false;
uint32_t rgb_t_itv = 1000;
uint32_t rgb_t_timer = 0;
uint8_t rgb_t_pos = 0;
uint8_t rgb_t_v = 10;

#if defined(RGBLIGHT_ENABLE)

// globol
kb_cstm_config_t kb_cstm_config;

rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_RED}
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

void setleds_custom(rgb_led_t *ledarray, uint16_t number_of_leds) {
    if (!yr_factory_test) {
        if (!host_keyboard_led_state().caps_lock) {
            ledarray[0].r = 0;
            ledarray[0].g = 0;
            ledarray[0].b = 0;
        }
    }
    ws2812_setleds(ledarray, number_of_leds);
}

const rgblight_driver_t rgblight_driver = {
    .init    = ws2812_init,
    .setleds = setleds_custom,
};

void eeconfig_init_kb_datablock(void) {
    kb_cstm_config.caps_brightness = RGBLIGHT_LIMIT_VAL;
    kb_cstm_config.caps_color_h = 0;
    kb_cstm_config.caps_color_s = 255;
    eeconfig_update_kb_datablock(&kb_cstm_config);
}

void keyboard_post_init_kb(void) {
    rgblight_reload_from_eeprom();
    eeconfig_read_kb_datablock(&kb_cstm_config);
    rgblight_layers = my_rgb_layers;
    keyboard_post_init_user();
}

void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_TIM2_REMAP_FULLREMAP;
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

#endif



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
