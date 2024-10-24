/* Copyright 2020 QMK
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

#include_next <mcuconf.h>

#undef AIR32_PWM_USE_TIM4
#define AIR32_PWM_USE_TIM4 TRUE

#undef AIR32_PLLMUL_VALUE
#undef AIR32_ADCPRE
#undef AIR32_USBPRE
#undef AIR32_PLLXTPRE

// PLLCLKOUT = 216MHz
#define AIR32_PLLXTPRE                      AIR32_PLLXTPRE_DIV2
#define AIR32_PLLMUL_VALUE                  27
#define AIR32_ADCPRE                        AIR32_ADCPRE_DIV32
#define AIR32_USBPRE                        AIR32_USBPRE_DIV4P5