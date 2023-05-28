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

#pragma once

#include "quantum.h"

typedef struct __attribute__((packed)) {
    uint8_t enable;
    HSV hsv;
} rgb_sector_t;

#ifndef RGB_CONTROL_SECTOR_NUM
#define RGB_CONTROL_SECTOR_NUM 6
#endif

#define RGB_CONTROL_EEPROM_ADDR (EECONFIG_KB_DATABLOCK)

#define RGB_CONTROL_EEPROM_SIZE (sizeof(rgb_sector_t) * RGB_CONTROL_SECTOR_NUM)

void read_rgb_control(void);
void update_rgb_control(void);
void update_rgb_control_default(void);
void rgb_control_init(void);
void rgb_control_task(void);
void rgb_control_set_sector_enable(uint8_t sector, uint8_t enable, bool update);
uint8_t rgb_control_get_sector_enable(uint8_t sector);
void rgb_control_set_sector_hsv(uint8_t sector, HSV hsv, bool update);
void rgb_control_set_sector_hue(uint8_t sector, uint8_t hue, bool update);
void rgb_control_set_sector_sat(uint8_t sector, uint8_t sat, bool update);
void rgb_control_set_sector_val(uint8_t sector, uint8_t val, bool update);
HSV rgb_control_get_sector_hsv(uint8_t sector);
uint8_t rgb_control_get_sector_hue(uint8_t sector);
uint8_t rgb_control_get_sector_sat(uint8_t sector);
uint8_t rgb_control_get_sector_val(uint8_t sector);
