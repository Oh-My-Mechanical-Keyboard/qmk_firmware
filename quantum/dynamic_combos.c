/* Copyright 2023 zhaqian
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

#include "dynamic_combos.h"
#include "dynamic_keymap.h"

static combo_t key_combos[DYNAMIC_COMBOS_ENTRIES];
static uint16_t keys_buf[DYNAMIC_COMBOS_ENTRIES][4];

void dynamic_combos_update(uint8_t entry) {
    if (entry >= DYNAMIC_COMBOS_ENTRIES) {
        return;
    }
    combo_entry_t combo;
    dynamic_get_combos(entry, &combo);
    memcpy(keys_buf[entry], combo.keys, sizeof(combo.keys));
    key_combos[entry].keys = keys_buf[entry];
    key_combos[entry].keycode = combo.keycode;
}

void dynamic_combos_init(void) {
    for (uint8_t i = 0; i < DYNAMIC_COMBOS_ENTRIES; i++) {
        dynamic_combos_update(i);
    }
}

uint16_t combo_count(void) {
    return DYNAMIC_COMBOS_ENTRIES;
}

combo_t* combo_get(uint16_t combo_idx) {
    return &key_combos[combo_idx];
}