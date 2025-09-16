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
#include "waves60.h"
#include "process_magic.h"

#include "rgb_matrix_layer.h"

#include "raw_hid.h"
bool yr_factory_test = false;
uint32_t rgb_t_itv = 1000;
uint32_t rgb_t_timer = 0;
uint8_t rgb_t_pos = 0;
uint8_t rgb_t_v = 5;


#ifdef RGB_MATRIX_ENABLE

extern rgb_task_states rgb_task_state;

led_config_t g_led_config = {
    {
        {61, 60,  59,  58,  57,  56,  55,  54,  53,  52,  51,  50,  49,  47},
        {33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46},
        {32,  31,  30,  29,  28,  27,  26,  25,  24,  23,  22,  21,   NO_LED,  20},
        {7,  8,  9,  10,  11,  12,  13,  14,  15,  16,  17,   NO_LED,  18,  19},
        { NO_LED,  6,  5,   NO_LED,  NO_LED,   NO_LED,  3,  NO_LED,   NO_LED,   NO_LED,  1,   NO_LED,  0,   48}
    },
    {
        // LED Index to Physical Position
        {207,64},       {172,64},              {121,64},{103,64},       {69,64},       {34,64},{17,64},       
        {0,48},{17,48},{34,48},{52,48},{69,48},{86,48},{103,48},{121,48},{138,48},{155,48},{172,48},       {207,48},{224,48},
        {224,32},       {190,32},{172,32},{155,32},{138,32},{121,32},{103,32},{86,32},{69,32},{52,32},{34,32},{17,32},{0,32},
        {0,16},{17,16},{34,16},{52,16},{69,16},{86,16},{103,16},{121,16},{138,16},{155,16},{172,16},{190,16},{207,16},{224,16},
        {224,0},{208,0},{192,0},{176,0},{160,0},{144,0},{128,0},{112,0},{96,0},{80,0},{64,0},{48,0},{32,0},{16,0},{0,0}
    },
    {
      // LED Index to Flag
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4,
    }
};

const rgb_matrix_adv_layer_segment_t PROGMEM my_capslock_layer[] = RGB_MATRIX_LAYER_SEGMENTS(
    {32, 1, HSV_RED}
);

const rgb_matrix_adv_layer_segment_t* const PROGMEM my_rgb_matrix_layers[] = RGB_MATRIX_LAYERS_LIST(
    my_capslock_layer
);

extern LED_TYPE rgb_matrix_ws2812_array[RGB_MATRIX_LED_COUNT];

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

    rgb_matrix_adv_blink_layer_repeat_helper();
    rgb_matrix_adv_set_layer_state(0, host_keyboard_led_state().caps_lock);

    uint8_t cent_num = 3;
    rgb_matrix_ws2812_array[cent_num-1].r = rgb_matrix_ws2812_array[cent_num].r;
    rgb_matrix_ws2812_array[cent_num-1].g = rgb_matrix_ws2812_array[cent_num].g;
    rgb_matrix_ws2812_array[cent_num-1].b = rgb_matrix_ws2812_array[cent_num].b;
    rgb_matrix_ws2812_array[cent_num+1].r = rgb_matrix_ws2812_array[cent_num].r;
    rgb_matrix_ws2812_array[cent_num+1].g = rgb_matrix_ws2812_array[cent_num].g;
    rgb_matrix_ws2812_array[cent_num+1].b = rgb_matrix_ws2812_array[cent_num].b;

    // If not enabled, then nothing else will actually set the LEDs...
    if (!rgb_matrix_is_enabled()) {
        rgb_task_state = FLUSHING;
    }
    return true;
}

void keyboard_post_init_kb(void) {
    rgb_matrix_reload_from_eeprom();
    rgb_matrix_layers = my_rgb_matrix_layers;
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
        case MKC_LG:
            if (record->event.pressed) {
                process_magic(GUI_TOG, record);
            }
            return false;
        case MKC_MACOS:
            if (record->event.pressed) {
                process_magic(CG_TOGG, record);
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
