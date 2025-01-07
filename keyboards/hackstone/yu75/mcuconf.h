// Copyright 2024 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#define WB32_EXTI_REQUIRED

#undef WB32_USB_HOST_WAKEUP_DURATION
#define WB32_USB_HOST_WAKEUP_DURATION 2

#undef WB32_SERIAL_USE_UART1
#define WB32_SERIAL_USE_UART1 TRUE

// The interrupt priority of the WS2812 driver must be higher than that of other SPI devices.
#undef WB32_SPI_QSPI_IRQ_PRIORITY
#define WB32_SPI_QSPI_IRQ_PRIORITY 9

#undef WB32_SPI_SPIM2_IRQ_PRIORITY
#define WB32_SPI_SPIM2_IRQ_PRIORITY 10

#undef WB32_SPI_USE_SPIM2
#define WB32_SPI_USE_SPIM2 TRUE

/* system clock set to 96Mhz */
// #undef WB32_PLLDIV_VALUE
// #define WB32_PLLDIV_VALUE 2

// #undef WB32_PLLMUL_VALUE
// #define WB32_PLLMUL_VALUE 16

// #undef WB32_USBPRE
// #define WB32_USBPRE WB32_USBPRE_DIV2
