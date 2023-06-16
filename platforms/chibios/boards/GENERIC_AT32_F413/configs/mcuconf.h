/*
    Copyright (C) Zhaqian

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef MCUCONF_H
#define MCUCONF_H

#define AT32F413xx_MCUCONF  TRUE

/*
 * AT32F413xx drivers configuration.
 * The following settings override the default settings present in
 * the various device driver implementation headers.
 * Note that the settings for each driver only have effect if the whole
 * driver is enabled in halconf.h.
 *
 * IRQ priorities:
 * 15...0       Lowest...Highest.
 *
 */

/*
 * HAL driver system settings.
 */
#define AT32_NO_INIT                       FALSE
#define AT32_HICK_ENABLED                  TRUE
#define AT32_LICK_ENABLED                  FALSE
#define AT32_HEXT_ENABLED                  TRUE
#define AT32_LEXT_ENABLED                  FALSE
#define AT32_PLL_ENABLED                   TRUE
#define AT32_SCLKSEL                       AT32_SCLKSEL_PLL
#define AT32_PLLRCS                        AT32_PLLRCS_HEXT
#define AT32_PLLHEXTDIV                    AT32_PLLHEXTDIV_DIV1
#define AT32_PLLMUL_VALUE                  24
#define AT32_AHBDIV                        AT32_AHBDIV_DIV1
#define AT32_APB1DIV                       AT32_APB1DIV_DIV2
#define AT32_APB2DIV                       AT32_APB2DIV_DIV2
#define AT32_ADCDIV                        AT32_ADCDIV_DIV4
#define AT32_USB_CLOCK_REQUIRED            TRUE
#define AT32_USBCLK_SRC                    AT32_USBCLK_SRC_PLL
#define AT32_USBDIV                        AT32_USBDIV_DIV4
#define AT32_CLKOUT_SEL                    AT32_CLKOUT_SEL_NOCLOCK
#define AT32_RTCSEL                        AT32_RTCSEL_LSI
#define AT32_PVM_ENABLE                    FALSE
#define AT32_PVM                           AT32_PVM_LEV0

/*
 * IRQ system settings.
 */
#define AT32_IRQ_EXTI0_PRIORITY            6
#define AT32_IRQ_EXTI1_PRIORITY            6
#define AT32_IRQ_EXTI2_PRIORITY            6
#define AT32_IRQ_EXTI3_PRIORITY            6
#define AT32_IRQ_EXTI4_PRIORITY            6
#define AT32_IRQ_EXTI5_9_PRIORITY          6
#define AT32_IRQ_EXTI10_15_PRIORITY        6
#define AT32_IRQ_EXTI16_PRIORITY           6
#define AT32_IRQ_EXTI17_PRIORITY           6
#define AT32_IRQ_EXTI18_PRIORITY           6

#define AT32_IRQ_TIM1_BRK_TIM9_PRIORITY    7
#define AT32_IRQ_TIM1_UP_TIM10_PRIORITY    7
#define AT32_IRQ_TIM1_TRGCO_TIM11_PRIORITY 7
#define AT32_IRQ_TIM1_CC_PRIORITY          7
#define AT32_IRQ_TIM2_PRIORITY             7
#define AT32_IRQ_TIM3_PRIORITY             7
#define AT32_IRQ_TIM4_PRIORITY             7
#define AT32_IRQ_TIM5_PRIORITY             7
#define AT32_IRQ_TIM8_BRK_TIM12_PRIORITY   7
#define AT32_IRQ_TIM8_UP_TIM13_PRIORITY    7
#define AT32_IRQ_TIM8_TRGCO_TIM14_PRIORITY 7
#define AT32_IRQ_TIM8_CC_PRIORITY          7

#define AT32_IRQ_USART1_PRIORITY           12
#define AT32_IRQ_USART2_PRIORITY           12
#define AT32_IRQ_USART3_PRIORITY           12
#define AT32_IRQ_UART4_PRIORITY            12
#define AT32_IRQ_UART5_PRIORITY            12

/*
 * ADC driver system settings.
 */
#define AT32_ADC_USE_ADC1                  FALSE
#define AT32_ADC_USE_ADC2                  FALSE
#define AT32_ADC_ADC1_DMA_STREAM           AT32_DMA_STREAM_ID(1, 1)
#define AT32_ADC_ADC2_DMA_STREAM           AT32_DMA_STREAM_ID(1, 1)
#define AT32_ADC_ADC1_DMA_PRIORITY         2
#define AT32_ADC_ADC2_DMA_PRIORITY         2
#define AT32_ADC_ADC1_IRQ_PRIORITY         6
#define AT32_ADC_ADC2_IRQ_PRIORITY         6

/*
 * CAN driver system settings.
 */
#define AT32_CAN_USE_CAN1                  FALSE
#define AT32_CAN_USE_CAN2                  FALSE
#define AT32_CAN_CAN1_IRQ_PRIORITY         11
#define AT32_CAN_CAN2_IRQ_PRIORITY         11

/*
 * GPT driver system settings.
 */
#define AT32_GPT_USE_TIM1                  FALSE
#define AT32_GPT_USE_TIM2                  FALSE
#define AT32_GPT_USE_TIM3                  FALSE
#define AT32_GPT_USE_TIM4                  FALSE
#define AT32_GPT_USE_TIM5                  FALSE
#define AT32_GPT_USE_TIM8                  FALSE
#define AT32_GPT_USE_TIM9                  FALSE
#define AT32_GPT_USE_TIM10                 FALSE
#define AT32_GPT_USE_TIM11                 FALSE

/*
 * I2C driver system settings.
 */
#define AT32_I2C_USE_I2C1                  FALSE
#define AT32_I2C_USE_I2C2                  FALSE
#define AT32_I2C_BUSY_TIMEOUT              50
#define AT32_I2C_I2C1_RX_DMA_STREAM        AT32_DMA_STREAM_ID(1, 7)
#define AT32_I2C_I2C1_TX_DMA_STREAM        AT32_DMA_STREAM_ID(1, 6)
#define AT32_I2C_I2C2_RX_DMA_STREAM        AT32_DMA_STREAM_ID(1, 5)
#define AT32_I2C_I2C2_TX_DMA_STREAM        AT32_DMA_STREAM_ID(1, 4)
#define AT32_I2C_I2C1_IRQ_PRIORITY         5
#define AT32_I2C_I2C2_IRQ_PRIORITY         5
#define AT32_I2C_I2C1_DMA_PRIORITY         3
#define AT32_I2C_I2C2_DMA_PRIORITY         3
#define AT32_I2C_DMA_ERROR_HOOK(i2cp)      osalSysHalt("DMA failure")

/*
 * ICU driver system settings.
 */
#define AT32_ICU_USE_TIM1                  FALSE
#define AT32_ICU_USE_TIM2                  FALSE
#define AT32_ICU_USE_TIM3                  FALSE
#define AT32_ICU_USE_TIM4                  FALSE
#define AT32_ICU_USE_TIM5                  FALSE
#define AT32_ICU_USE_TIM8                  FALSE
#define AT32_ICU_USE_TIM9                  FALSE
#define AT32_ICU_USE_TIM10                 FALSE
#define AT32_ICU_USE_TIM11                 FALSE

/*
 * PWM driver system settings.
 */
#define AT32_PWM_USE_TIM1                  FALSE
#define AT32_PWM_USE_TIM2                  FALSE
#define AT32_PWM_USE_TIM3                  FALSE
#define AT32_PWM_USE_TIM4                  FALSE
#define AT32_PWM_USE_TIM5                  FALSE
#define AT32_PWM_USE_TIM8                  FALSE
#define AT32_PWM_USE_TIM9                  FALSE
#define AT32_PWM_USE_TIM10                 FALSE
#define AT32_PWM_USE_TIM11                 FALSE

/*
 * RTC driver system settings.
 */
#define AT32_RTC_IRQ_PRIORITY              15

/*
 * SERIAL driver system settings.
 */
#define AT32_SERIAL_USE_USART1             FALSE
#define AT32_SERIAL_USE_USART2             FALSE
#define AT32_SERIAL_USE_USART3             FALSE
#define AT32_SERIAL_USE_UART4              FALSE
#define AT32_SERIAL_USE_UART5              FALSE

/*
 * SPI driver system settings.
 */
#define AT32_SPI_USE_SPI1                  FALSE
#define AT32_SPI_USE_SPI2                  FALSE
#define AT32_SPI_SPI1_RX_DMA_STREAM        AT32_DMA_STREAM_ID(1, 2)
#define AT32_SPI_SPI1_TX_DMA_STREAM        AT32_DMA_STREAM_ID(1, 3)
#define AT32_SPI_SPI2_RX_DMA_STREAM        AT32_DMA_STREAM_ID(1, 4)
#define AT32_SPI_SPI2_TX_DMA_STREAM        AT32_DMA_STREAM_ID(1, 5)
#define AT32_SPI_SPI1_DMA_PRIORITY         1
#define AT32_SPI_SPI2_DMA_PRIORITY         1
#define AT32_SPI_SPI1_IRQ_PRIORITY         10
#define AT32_SPI_SPI2_IRQ_PRIORITY         10
#define AT32_SPI_DMA_ERROR_HOOK(spip)      osalSysHalt("DMA failure")

/*
 * ST driver system settings.
 */
#define AT32_ST_IRQ_PRIORITY               8
#define AT32_ST_USE_TIMER                  2

/*
 * UART driver system settings.
 */
#define AT32_UART_USE_USART1               FALSE
#define AT32_UART_USE_USART2               FALSE
#define AT32_UART_USE_USART3               FALSE
#define AT32_UART_USE_UART4                FALSE
#define AT32_UART_USE_UART5                FALSE
#define AT32_UART_USART1_RX_DMA_STREAM     AT32_DMA_STREAM_ID(1, 5)
#define AT32_UART_USART1_TX_DMA_STREAM     AT32_DMA_STREAM_ID(1, 4)
#define AT32_UART_USART2_RX_DMA_STREAM     AT32_DMA_STREAM_ID(1, 6)
#define AT32_UART_USART2_TX_DMA_STREAM     AT32_DMA_STREAM_ID(1, 7)
#define AT32_UART_USART3_RX_DMA_STREAM     AT32_DMA_STREAM_ID(1, 3)
#define AT32_UART_USART3_TX_DMA_STREAM     AT32_DMA_STREAM_ID(1, 2)
#define AT32_UART_UART4_RX_DMA_STREAM      AT32_DMA_STREAM_ID(2, 3)
#define AT32_UART_UART4_TX_DMA_STREAM      AT32_DMA_STREAM_ID(2, 5)
// Only support if use dma mux
#define AT32_UART_UART5_RX_DMA_STREAM      AT32_DMA_STREAM_ID(1, 1)
#define AT32_UART_UART5_TX_DMA_STREAM      AT32_DMA_STREAM_ID(1, 2)
#define AT32_UART_USART1_DMA_PRIORITY      0
#define AT32_UART_USART2_DMA_PRIORITY      0
#define AT32_UART_USART3_DMA_PRIORITY      0
#define AT32_UART_UART4_DMA_PRIORITY       0
#define AT32_UART_UART5_DMA_PRIORITY       0
#define AT32_UART_DMA_ERROR_HOOK(uartp)    osalSysHalt("DMA failure")

/*
 * USB driver system settings.
 */
#define AT32_USB_USE_USB1                  TRUE
#define AT32_USB_LOW_POWER_ON_SUSPEND      FALSE
#define AT32_USB_USB1_HP_IRQ_PRIORITY      13
#define AT32_USB_USB1_LP_IRQ_PRIORITY      14
#define AT32_USBRAM_USE_EXTENDED_RAM       TRUE
#define AT32_USB_USB1_IRQ_REMAP            FALSE
#define AT32_USB_USB1_MAPHP_IRQ_PRIORITY   13
#define AT32_USB_USB1_MAPLP_IRQ_PRIORITY   14

/*
 * WDG driver system settings.
 */
#define AT32_WDG_USE_IWDG                  FALSE

/*
 * DMA driver system settings.
 */
#define AT32_DMA_USE_DMAMUX                FALSE

#endif /* MCUCONF_H */
