/* Copyright 2021 JasonRen(biu)
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
 * along with this program.  If not, see <http: //www.gnu.org/licenses/>.
 */
#include "m93ble.h"

#ifdef BIU_BLE5_ENABLE
#include "biu_ble_common.h"
#endif

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {
    {
        { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10,  11,  12,  13,  14,  15,  16 },
        { 17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33 },
        { 34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50 },
        { 51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,   NO_LED,  63,  64,  65,  66 },
        { 67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,   NO_LED,  78,  79,  80,  81,  82 },
        { 83,  84,  85,   NO_LED,   NO_LED,  86,   NO_LED,   NO_LED,   NO_LED,  87,  88,   NO_LED,  89,  90,  91,  92,  93 }
    },
    {
        {0,0},{14,0},{28,0},{42,0},{56,0},{70,0},{84,0},{98,0},{112,0},{126,0},{140,0},{154,0},{168,0},{182,0},{196,0},{210,0},{224,0},
        {0,13},{14,13},{28,13},{42,13},{56,13},{70,13},{84,13},{98,13},{112,13},{126,13},{140,13},{154,13},{168,13},{182,13},{196,13},{210,13},{224,13},
        {0,26},{14,26},{28,26},{42,26},{56,26},{70,26},{84,26},{98,26},{112,26},{126,26},{140,26},{154,26},{168,26},{182,26},{196,26},{210,26},{224,26},
        {0,38},{14,38},{28,38},{42,38},{56,38},{70,38},{84,38},{98,38},{112,38},{126,38},{140,38},{154,38},       {182,38},{196,38},{210,38},{224,38},
        {0,51},{14,51},{28,51},{42,51},{56,51},{70,51},{84,51},{98,51},{112,51},{126,51},{140,51},       {168,51},{182,51},{196,51},{210,51},{224,51},
        {0,64},{14,64},{28,64},              {70,64},                     {126,64},{140,64},       {168,64},{182,64},{196,64},{210,64},{224,64}

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
      4,4,4,4,4, 4,4,4,4,4,
      4,4,4,4
    }
};
#endif

void keyboard_pre_init_kb(void) {
#ifdef LED_BAT_LOW_PIN
    setPinOutput(LED_BAT_LOW_PIN);
    writePin(LED_BAT_LOW_PIN, 0);
#endif
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
#if defined(LED_NUM_LOCK_PIN) || defined(LED_CAPS_LOCK_PIN) || defined(LED_SCROLL_LOCK_PIN) || defined(LED_COMPOSE_PIN) || defined(LED_KANA_PIN)
#    if LED_PIN_ON_STATE == 0
        // invert the whole thing to avoid having to conditionally !led_state.x later
        led_state.raw = ~led_state.raw;
#    endif

#    ifdef LED_NUM_LOCK_PIN
        writePin(LED_NUM_LOCK_PIN, led_state.num_lock);
#    endif
#    ifdef LED_CAPS_LOCK_PIN
        writePin(LED_CAPS_LOCK_PIN, led_state.caps_lock);
#    endif
#   if defined(LED_BAT_LOW_PIN) && defined(BIU_BLE5_ENABLE)
        if (get_bat_level() < 10) {
            writePin(LED_BAT_LOW_PIN, 1);
        } else {
            writePin(LED_BAT_LOW_PIN, 0);
        }

#   endif
#endif
    }
    return res;
}
