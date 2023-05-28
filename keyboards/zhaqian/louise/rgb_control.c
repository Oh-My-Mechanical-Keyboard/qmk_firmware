/* Copyright 2022 ZhaQian
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

#include "rgb_control.h"
#include "eeprom.h"

static rgb_sector_t rgb_sectors[RGB_CONTROL_SECTOR_NUM];

void read_rgb_control(void) {
    eeprom_read_block(rgb_sectors, (void*)RGB_CONTROL_EEPROM_ADDR, RGB_CONTROL_EEPROM_SIZE);
}

void update_rgb_control(void) {
    eeprom_update_block(rgb_sectors, (void*)RGB_CONTROL_EEPROM_ADDR, RGB_CONTROL_EEPROM_SIZE);
}

void update_rgb_control_default(void) {
    for (uint8_t i = 0; i < RGB_CONTROL_SECTOR_NUM; i++) {
        rgb_sectors[i].enable = 0;
        rgb_sectors[i].hsv = rgb_matrix_get_hsv();
    }
    update_rgb_control();
}

void rgb_control_init(void) {
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
        update_rgb_control_default();
    }
    read_rgb_control();
    if (rgb_sectors[0].hsv.v == 0) {
        update_rgb_control_default();
    }
}

// need to be improved
static void rgb_sector_set_color(uint8_t sector, HSV hsv) {
    RGB rgb = hsv_to_rgb(hsv);
    switch(sector) {
        case 0: {
            rgb_matrix_set_color(0, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(13, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(14, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(15, rgb.r, rgb.g, rgb.b);
            break;
        }
        case 1: {
            rgb_matrix_set_color(1, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(2, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(11, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(12, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(16, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(17, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(18, rgb.r, rgb.g, rgb.b);
            break;
        }
        case 2: {
            rgb_matrix_set_color(3, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(10, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(19, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(20, rgb.r, rgb.g, rgb.b);
            break;
        }
        case 3: {
            rgb_matrix_set_color(4, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(5, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(8, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(9, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(21, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(22, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(23, rgb.r, rgb.g, rgb.b);
            break;
        }
        case 4: {
            rgb_matrix_set_color(6, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(7, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(24, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(25, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(26, rgb.r, rgb.g, rgb.b);
            break;
        }
        case 5: {
            rgb_matrix_set_color(27, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(28, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(29, rgb.r, rgb.g, rgb.b);
            break;
        }
        default : {
            break;
        }
    }
}

void rgb_control_task(void) {
    for (uint8_t i = 0; i < RGB_CONTROL_SECTOR_NUM; i ++) {
        if (rgb_sectors[i].enable) {
            rgb_sector_set_color(i, rgb_sectors[i].hsv);
        }
    }
}

void rgb_control_set_sector_enable(uint8_t sector, uint8_t enable, bool update) {
    rgb_sectors[sector].enable = enable;
    if (update)
        update_rgb_control();
}

uint8_t rgb_control_get_sector_enable(uint8_t sector) {
    return rgb_sectors[sector].enable;
}


void rgb_control_set_sector_hsv(uint8_t sector, HSV hsv, bool update) {
    rgb_sectors[sector].hsv = hsv;
    if (update)
        update_rgb_control();
}

void rgb_control_set_sector_hue(uint8_t sector, uint8_t hue, bool update) {
    rgb_sectors[sector].hsv.h = hue;
    if (update)
        update_rgb_control();
}

void rgb_control_set_sector_sat(uint8_t sector, uint8_t sat, bool update) {
    rgb_sectors[sector].hsv.s = sat;
    if (update)
        update_rgb_control();
}

void rgb_control_set_sector_val(uint8_t sector, uint8_t val, bool update) {
    rgb_sectors[sector].hsv.v = val;
    if (update)
        update_rgb_control();
}

HSV rgb_control_get_sector_hsv(uint8_t sector) {
    return rgb_sectors[sector].hsv;
}

uint8_t rgb_control_get_sector_hue(uint8_t sector) {
    return rgb_sectors[sector].hsv.h;
}

uint8_t rgb_control_get_sector_sat(uint8_t sector) {
    return rgb_sectors[sector].hsv.s;
}

uint8_t rgb_control_get_sector_val(uint8_t sector) {
    return rgb_sectors[sector].hsv.v;
}


