/* Copyright 2021 JasonRen(biu)
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

#include "cums_spi_master.h"

#include "timer.h"

static SPIConfig spiConfig       = {false, NULL, 0, 0};

void spi_init(bool force) {
    static bool is_initialised = false;
    if (force || !is_initialised) {
        is_initialised = true;

        // Try releasing special pins for a short time
        palSetPadMode(PAL_PORT(SPI_SCK_PIN_OF_595), PAL_PAD(SPI_SCK_PIN_OF_595), PAL_MODE_INPUT);
        palSetPadMode(PAL_PORT(SPI_MOSI_PIN_OF_595), PAL_PAD(SPI_MOSI_PIN_OF_595), PAL_MODE_INPUT);
        palSetPadMode(PAL_PORT(SPI_MISO_PIN_OF_595), PAL_PAD(SPI_MISO_PIN_OF_595), PAL_MODE_INPUT);

        chThdSleepMilliseconds(10);
#if defined(USE_GPIOV1)
        palSetPadMode(PAL_PORT(SPI_SCK_PIN_OF_595), PAL_PAD(SPI_SCK_PIN_OF_595), PAL_MODE_STM32_ALTERNATE_PUSHPULL);
        palSetPadMode(PAL_PORT(SPI_MOSI_PIN_OF_595), PAL_PAD(SPI_MOSI_PIN_OF_595), PAL_MODE_STM32_ALTERNATE_PUSHPULL);
        palSetPadMode(PAL_PORT(SPI_MISO_PIN_OF_595), PAL_PAD(SPI_MISO_PIN_OF_595), PAL_MODE_STM32_ALTERNATE_PUSHPULL);

#else
        palSetPadMode(PAL_PORT(SPI_SCK_PIN_OF_595), PAL_PAD(SPI_SCK_PIN_OF_595), PAL_MODE_ALTERNATE(SPI_SCK_PAL_MODE_OF_595) | PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
        palSetPadMode(PAL_PORT(SPI_MOSI_PIN_OF_595), PAL_PAD(SPI_MOSI_PIN_OF_595), PAL_MODE_ALTERNATE(SPI_MOSI_PAL_MODE_OF_595) | PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
        palSetPadMode(PAL_PORT(SPI_MISO_PIN_OF_595), PAL_PAD(SPI_MISO_PIN_OF_595), PAL_MODE_ALTERNATE(SPI_MISO_PAL_MODE_OF_595) | PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);

#endif
    }
}
bool spi_start(bool lsbFirst, uint8_t mode, uint16_t divisor) {
    uint16_t roundedDivisor = 2;
    while (roundedDivisor < divisor) {
        roundedDivisor <<= 1;
    }

    if (roundedDivisor < 2 || roundedDivisor > 256) {
        return false;
    }

    spiConfig.cr1 = 0;

    if (lsbFirst) {
        spiConfig.cr1 |= SPI_CR1_LSBFIRST;
    }
    switch (mode) {
        case 0:
            break;
        case 1:
            spiConfig.cr1 |= SPI_CR1_CPHA;
            break;
        case 2:
            spiConfig.cr1 |= SPI_CR1_CPOL;
            break;
        case 3:
            spiConfig.cr1 |= SPI_CR1_CPHA | SPI_CR1_CPOL;
            break;
    }

    switch (roundedDivisor) {
        case 2:
            break;
        case 4:
            spiConfig.cr1 |= SPI_CR1_BR_0;
            break;
        case 8:
            spiConfig.cr1 |= SPI_CR1_BR_1;
            break;
        case 16:
            spiConfig.cr1 |= SPI_CR1_BR_1 | SPI_CR1_BR_0;
            break;
        case 32:
            spiConfig.cr1 |= SPI_CR1_BR_2;
            break;
        case 64:
            spiConfig.cr1 |= SPI_CR1_BR_2 | SPI_CR1_BR_0;
            break;
        case 128:
            spiConfig.cr1 |= SPI_CR1_BR_2 | SPI_CR1_BR_1;
            break;
        case 256:
            spiConfig.cr1 |= SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0;
            break;
    }


    spiStart(&SPI_DRIVER, &spiConfig);
    spiSelect(&SPI_DRIVER);

    return true;
}

spi_status_t spi_write(uint8_t data) {
    uint8_t rxData;
    spiExchange(&SPI_DRIVER, 1, &data, &rxData);

    return rxData;
}

spi_status_t spi_read(void) {
    uint8_t data = 0;
    spiReceive(&SPI_DRIVER, 1, &data);

    return data;
}

spi_status_t spi_transmit(const uint8_t *data, uint16_t length) {
    spiSend(&SPI_DRIVER, length, data);
    return SPI_STATUS_SUCCESS;
}

spi_status_t spi_receive(uint8_t *data, uint16_t length) {
    spiReceive(&SPI_DRIVER, length, data);
    return SPI_STATUS_SUCCESS;
}

void spi_stop(void) {
    spiUnselect(&SPI_DRIVER);
    spiStop(&SPI_DRIVER);
}
