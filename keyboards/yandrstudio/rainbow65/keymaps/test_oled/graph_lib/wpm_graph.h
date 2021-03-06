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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "../dev_oled/oled_driver.h"
#include "time.h"
#include "wpm.h"



void draw_y_grad(uint8_t x, uint8_t y, bool inside);
void render_countdown(void);
void render_wpm_graph(uint16_t);
void render_yandr_logo(void);
void render_r65_logo(void);


static const char my_font_lib_etc_countdown[10][48] PROGMEM = {
    {// 0
    0x00, 0x00, 0x00, 0xF8, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0xF8, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x1F, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x1F, 0x00, 0x00, 0x00,
    },
    { // 1
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00,
    },
    { // 2
    0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0xF8, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0xF0, 0x10, 0x10, 0x10, 0x10,
    0x08, 0x08, 0x08, 0x08, 0x0F, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x1F, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00,
    },
    { // 3
    0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0xF8, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x08, 0x08, 0x08, 0x08, 0xFF, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x1F, 0x00, 0x00, 0x00,
    },
    { // 4
    0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x1F, 0x10, 0x10, 0x10, 0x10,
    0x08, 0x08, 0x08, 0x08, 0xFF, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00,
    },
    { // 5
    0x00, 0x00, 0x00, 0xF8, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x1F, 0x10, 0x10, 0x10, 0x10,
    0x08, 0x08, 0x08, 0x08, 0xF8, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x1F, 0x00, 0x00, 0x00,
    },
    { // 6
    0x00, 0x00, 0x00, 0xF8, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0xFF, 0x10, 0x10, 0x10, 0x10,
    0x08, 0x08, 0x08, 0x08, 0xF8, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x1F, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x1F, 0x00, 0x00, 0x00,
    },
    { // 7
    0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0xF8, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00,
    },
    { // 8
    0x00, 0x00, 0x00, 0xF8, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0xF8, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0xFF, 0x10, 0x10, 0x10, 0x10,
    0x08, 0x08, 0x08, 0x08, 0xFF, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x1F, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x1F, 0x00, 0x00, 0x00,
    },
    { // 9
    0x00, 0x00, 0x00, 0xF8, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0xF8, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x1F, 0x10, 0x10, 0x10, 0x10,
    0x08, 0x08, 0x08, 0x08, 0xFF, 0x00, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x1F, 0x00, 0x00, 0x00,
    }
};

static const char my_font_lib_etc_logo[] PROGMEM = {
    0x00, 0x00, 0x18, 0x30, 0x60, 0xC0, 0x80, 0x00,
    0x00, 0x80, 0xC0, 0x60, 0x30, 0x18, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF8,
    0x18, 0x18, 0x18, 0x30, 0x60, 0xC0, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF,
    0xFF, 0x01, 0x00, 0x00, 0x00, 0xDC, 0x22, 0x22,
    0xDC, 0x80, 0x40, 0x00, 0x00, 0x00, 0xFF, 0xFF,
    0x7C, 0xCC, 0x8C, 0x06, 0x03, 0x01, 0x00, 0x00,

    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F,
    0x1F, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02,
    0x01, 0x01, 0x02, 0x00, 0x00, 0x00, 0x1F, 0x1F,
    0x00, 0x00, 0x01, 0x03, 0x06, 0x0C, 0x18, 0x00,
};

static const char my_font_lib_etc_r65_logo[] PROGMEM = {
    0x00, 0x00, 0xF8, 0xF8, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x30, 0x60, 0xC0, 0x00, 0xF8, 0xF8, 0x18,
    0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0xF8, 0xF8,
    0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00,

    0x00, 0x00, 0xFF, 0xFF, 0x3C, 0x6C, 0xCC, 0x8C,
    0x0C, 0x06, 0x03, 0x01, 0x00, 0xFF, 0xFF, 0x18,
    0x18, 0x18, 0x18, 0xF8, 0xF8, 0x00, 0x1F, 0x1F,
    0x18, 0x18, 0x18, 0x18, 0xF8, 0xF8, 0x00, 0x00,

    0x00, 0x00, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x01,
    0x03, 0x06, 0x0C, 0x18, 0x00, 0x1F, 0x1F, 0x18,
    0x18, 0x18, 0x18, 0x1F, 0x1F, 0x00, 0x18, 0x18,
    0x18, 0x18, 0x18, 0x18, 0x1F, 0x1F, 0x00, 0x00,
};
