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

#ifdef ENCODER_ENABLE
#define ENCODERS 1
#define ENCODERS_CCW_KEY { { 13, 0 } }
#define ENCODERS_CW_KEY  { { 15, 0 } }
#endif

#ifdef RGB_MATRIX_ENABLE
#define WS2812_PWM_DRIVER PWMD4
#define WS2812_PWM_CHANNEL 3
#define WS2812_DMA_STREAM STM32_DMA1_STREAM7

#define RGB_MATRIX_LED_COUNT 111
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#define RGB_DISABLE_WHEN_USB_SUSPENDED

#define RGB_MATRIX_ANIMATION
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
#endif

#ifdef OPENRGB_ENABLE
#define OPENRGB_DIRECT_MODE_USE_UNIVERSAL_BRIGHTNESS
#endif

