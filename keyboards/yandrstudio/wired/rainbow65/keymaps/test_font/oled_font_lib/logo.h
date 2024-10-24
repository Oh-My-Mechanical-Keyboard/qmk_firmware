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
#include "progmem.h"

static const unsigned char logo_idobao[] PROGMEM = {
    0x00, 0x00, 0x00, 0x80, 0xC0, 0xC0, 0xE0, 0xE0,
    0xF0, 0xF0, 0x70, 0x60, 0x04, 0x0E, 0x0E, 0x1E,
    0x8E, 0x8E, 0xC4, 0xC0, 0xE0, 0xF0, 0xF0, 0xF0,
    0xE0, 0xE0, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x00,


    0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0x07, 0x03, 0x01,
    0xF0, 0xF8, 0xFC, 0xFC, 0x1E, 0x1E, 0x0F, 0x0F,
    0x07, 0x07, 0x03, 0x03, 0x01, 0x01, 0x00, 0x01,
    0x01, 0x03, 0x1F, 0xFF, 0xFF, 0xFF, 0xFE, 0x00,


    0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
    0xC0, 0xE0, 0xF8, 0xFF, 0xFF, 0xFF, 0x7F, 0x00,


    0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00,
    0x0F, 0x0F, 0x1F, 0x1F, 0x3E, 0x3C, 0x7C, 0x7C,
    0x7C, 0x7C, 0x3C, 0x3E, 0x1E, 0x1F, 0x0F, 0x0F,
    0x07, 0x07, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00
};

// {0x00,0x00,0x80,0xC0,0xC0,0xE0,0xE0,0xF0,0xF8,0xF0,0xF0,0xE4,0x6E,0x4E,0x1E,0x9F,0x9F,0xCE,0xCE,0xE6,0xF4,0xF0,0xF8,0xF8,0xF0,0xE0,0xE0,0xC0,0xC0,0x80,0x00,0x00},
// {0x00,0xFF,0xFF,0xFF,0xFF,0x07,0x03,0xFB,0xF9,0xFD,0xFC,0xFE,0x3E,0x1F,0x1F,0x0F,0x0F,0x07,0x07,0x03,0x03,0x01,0x01,0x01,0x03,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC},
// {0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xC0,0xC0,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F},
// {0x00,0x00,0x01,0x03,0x03,0x00,0x00,0x0F,0x0F,0x1F,0x1F,0x3F,0x3E,0x7E,0x7E,0x7C,0x7C,0x7E,0x7E,0x7E,0x3F,0x1F,0x1F,0x0F,0x0F,0x07,0x07,0x03,0x03,0x01,0x00,0x00},
