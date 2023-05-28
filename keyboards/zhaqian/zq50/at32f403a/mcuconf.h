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

#undef AT32_PWM_USE_TIM1
#define AT32_PWM_USE_TIM1 TRUE

#undef AT32_PLLMUL_VALUE
#undef AT32_ADCDIV
#undef AT32_USBCLK_SRC

#define AT32_PLLMUL_VALUE                  30
#define AT32_ADCDIV                        AT32_ADCDIV_DIV6
#define AT32_USBCLK_SRC                    AT32_USBCLK_SRC_HSI48