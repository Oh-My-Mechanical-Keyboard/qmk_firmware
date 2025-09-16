// Copyright 2023 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef STM32_SPI_USE_SPI2
#define STM32_SPI_USE_SPI2 TRUE

#undef STM32_SERIAL_USE_USART1
#define STM32_SERIAL_USE_USART1 TRUE

#undef  STM32_ADC_USE_ADC2
#define STM32_ADC_USE_ADC2 TRUE

#undef STM32_HSE_ENABLED
#undef STM32_PLLSRC
#undef STM32_PLLM_VALUE
#undef STM32_PLLN_VALUE
#undef STM32_PLLQ_VALUE
#undef STM32_PLLR_VALUE
#undef STM32_ADC12SEL
#undef STM32_ADC_ADC12_CLOCK_MODE
#undef STM32_ADC_ADC12_PRESC



#define STM32_HSE_ENABLED                   TRUE
#define STM32_PLLSRC                        STM32_PLLSRC_HSE
#define STM32_PLLM_VALUE                    4
// #define STM32_PLLN_VALUE                    85 // SYSCK 170M
#define STM32_PLLN_VALUE                    80 // SYSCK 160M
// #define STM32_PLLN_VALUE                    60 // SYSCK 120M
// #define STM32_PLLN_VALUE                    50 // SYSCK 100M
// #define STM32_PLLN_VALUE                    40 // SYSCK 80M
// #define STM32_PLLN_VALUE                    30 // SYSCK 60M
// #define STM32_PLLN_VALUE                    20 // SYSCK 40M
#define STM32_PLLQ_VALUE                    2
#define STM32_PLLR_VALUE                    2

#define STM32_ADC12SEL                      STM32_ADC12SEL_SYSCLK
#define STM32_ADC_ADC12_CLOCK_MODE          ADC_CCR_CKMODE_ADCCK
#define STM32_ADC_ADC12_PRESC               ADC_CCR_PRESC_DIV4

//  dual bank organization: 2*32*2k
#undef STM32_FLASH_SECTORS_PER_BANK
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
