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

#undef STM32_PWM_USE_TIM4
#define STM32_PWM_USE_TIM4 TRUE

#undef  STM32_ADC_USE_ADC1
#define STM32_ADC_USE_ADC1 TRUE

#undef STM32_HSE_ENABLED
#undef STM32_PLLSRC
#undef STM32_PLLM_VALUE
#undef STM32_PLLN_VALUE
#undef STM32_PLLQ_VALUE
#undef STM32_PLLR_VALUE
#undef STM32_ADC12SEL
#undef STM32_ADC_ADC12_CLOCK_MODE
#undef STM32_ADC_ADC12_PRESC

#undef STM32_FLASH_SECTORS_PER_BANK


#define STM32_HSE_ENABLED                   TRUE
#define STM32_PLLSRC                        STM32_PLLSRC_HSE
#define STM32_PLLM_VALUE                    6
#define STM32_PLLN_VALUE                    85
#define STM32_PLLQ_VALUE                    2
#define STM32_PLLR_VALUE                    2

#define STM32_ADC12SEL                      STM32_ADC12SEL_SYSCLK
#define STM32_ADC_ADC12_CLOCK_MODE          ADC_CCR_CKMODE_ADCCK
#define STM32_ADC_ADC12_PRESC               ADC_CCR_PRESC_DIV4

//  dual bank organization: 2*32*2k
#define STM32_FLASH_SECTORS_PER_BANK        32

// for avoid compiling error of STM32_FLASH_NUMBER_OF_BANKS
#define FLASH_OPTR_DBANK_Pos              (22U)
#define FLASH_OPTR_DBANK_Msk              (0x1UL << FLASH_OPTR_DBANK_Pos)      /*!< 0x00400000 */
#define FLASH_OPTR_DBANK                  FLASH_OPTR_DBANK_Msk

// setup dual bank for g431

#define FLASH_CR_MER2_Pos                 (15U)
#define FLASH_CR_MER2_Msk                 (0x1UL << FLASH_CR_MER2_Pos)         /*!< 0x00008000 */
#define FLASH_CR_MER2                     FLASH_CR_MER2_Msk

#define FLASH_CR_MER2_Pos                 (15U)
#define FLASH_CR_MER2_Msk                 (0x1UL << FLASH_CR_MER2_Pos)         /*!< 0x00008000 */
#define FLASH_CR_MER2                     FLASH_CR_MER2_Msk
