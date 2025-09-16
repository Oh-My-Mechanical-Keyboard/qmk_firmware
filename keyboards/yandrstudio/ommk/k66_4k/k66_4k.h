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
#pragma once

#include "quantum.h"

#define LAYOUT( \
          K000, \
    K003, K002, K001 \
) { \
    { K000 }, \
    { K001 }, \
    { K002 }, \
    { K003 }  \
}
enum keyboard_keycodes {
    LOCK_GUI = QK_KB,
    TOG_MACOS_KEYMAP_MAC,
    KC_MISSION_CONTROL_MAC,
    KC_LAUNCHPAD_MAC
};

#define MKC_LG    LOCK_GUI
#define MKC_MACOS TOG_MACOS_KEYMAP_MAC
#define MKC_MCTL  KC_MISSION_CONTROL_MAC
#define MKC_LPAD  KC_LAUNCHPAD_MAC

extern bool yr_factory_test;
