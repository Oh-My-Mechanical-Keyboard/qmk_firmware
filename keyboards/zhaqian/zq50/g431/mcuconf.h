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

#undef STM32_PWM_USE_TIM1
#define STM32_PWM_USE_TIM1 TRUE

#undef STM32_HSI16_ENABLED 
#undef STM32_HSI48_ENABLED 
#undef STM32_HSE_ENABLED 
#undef STM32_PLLSRC
#undef STM32_PLLM_VALUE
#undef STM32_PLLN_VALUE
#undef STM32_PLLP_VALUE
#undef STM32_PLLQ_VALUE
#undef STM32_PLLR_VALUE
#undef STM32_CLK48SEL
// #undef STM32_FLASH_SECTORS_PER_BANK

// Only use HSE 8MHz
#define STM32_HSI16_ENABLED                 FALSE
#define STM32_HSI48_ENABLED                 FALSE
#define STM32_HSE_ENABLED                   TRUE
#define STM32_PLLSRC                        STM32_PLLSRC_HSE
#define STM32_PLLM_VALUE                    1
#define STM32_PLLN_VALUE                    36
#define STM32_PLLP_VALUE                    7
#define STM32_PLLQ_VALUE                    6
#define STM32_PLLR_VALUE                    2
#define STM32_CLK48SEL                      STM32_CLK48SEL_PLLQCLK 
// #define STM32_FLASH_SECTORS_PER_BANK        32  // for stm32g431xb