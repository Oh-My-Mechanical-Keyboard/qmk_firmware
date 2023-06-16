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

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#ifdef RGB_MATRIX_ENABLE
#define RGB_MATRIX_LED_COUNT 66
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#define RGB_DISABLE_WHEN_USB_SUSPENDED

#define RGB_MATRIX_ANIMATION
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

#ifdef RGB_MATRIX_CUSTOM_KB
#define RGB_MATRIX_CUSTOM_ANIMATION
#endif
#endif

#ifdef UNDERGLOW_RGB_MATRIX_ENABLE
#define UG_RGB_MATRIX_ANIMATIONS
#endif

#ifdef DYNAMIC_RGB_INDICATORS_ENABLE
#define ENABLE_RGB_INDICATORS_ANIMATIONS
#endif

#ifdef VIA_ENABLE
#define DYNAMIC_KEYMAP_LAYER_COUNT 6
#endif

#ifdef OPENRGB_ENABLE
#define OPENRGB_DIRECT_MODE_USE_UNIVERSAL_BRIGHTNESS
#endif

#ifdef DYNAMIC_TAP_DANCE_ENABLE
#define DYNAMIC_TAP_DANCE_ENTRIES 10
#endif

#ifdef DYNAMIC_COMBOS_ENABLE
#define DYNAMIC_COMBOS_ENTRIES 10
#endif
