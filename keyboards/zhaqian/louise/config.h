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

#ifdef RGB_MATRIX_ENABLE
#define RGB_MATRIX_LED_COUNT 30
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGB_MATRIX_ANIMATION
#endif

#ifdef VIA_ENABLE
#define DYNAMIC_KEYMAP_LAYER_COUNT 6
#define VIA_CUSTOM_RGB_INDICATORS_ENABLE // cheat for indicator control
#endif

#ifdef AUTO_SWITCH_LAYERS_ENABLE
#define DEFAULT_MACOS_LAYER 3
#endif

#ifdef RGB_MATRIX_CONTROL_ENABLE
#define LOGO_RGB_CONTROL_ENABLE
#endif

#ifdef UNDERGLOW_RGB_MATRIX_ENABLE
#define UG_RGB_MATRIX_ANIMATIONS
#endif

#ifdef DYNAMIC_TAP_DANCE_ENABLE
#define DYNAMIC_TAP_DANCE_ENTRIES 10
#endif

#ifdef DYNAMIC_COMBOS_ENABLE
#define DYNAMIC_COMBOS_ENTRIES 10
#endif
