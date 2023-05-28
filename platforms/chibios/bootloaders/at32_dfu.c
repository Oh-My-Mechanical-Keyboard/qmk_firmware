/* Copyright 2023 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include "bootloader.h"

#include <ch.h>
#include <hal.h>
#include "wait.h"

#define BOOTLOADER_MAGIC 0x5AA5
#if defined(AT32F415xx)
#define MAGIC_ADDR (__IO uint32_t *)(ERTC_BASE + 0x50)
#elif defined(AT32F413xx) || defined(AT32F40x)
#define MAGIC_ADDR (__IO uint32_t *)(BPR_BASE + 0x04)
#endif

__attribute__((weak)) void bootloader_jump(void) {
    *MAGIC_ADDR = (uint32_t)BOOTLOADER_MAGIC;
    NVIC_SystemReset();
}

__attribute__((weak)) void mcu_reset(void) {
    NVIC_SystemReset();
}

void enter_bootloader_mode_if_requested(void) {
    if (*MAGIC_ADDR == BOOTLOADER_MAGIC) {
        *MAGIC_ADDR = 0;
        __set_CONTROL(0);
        __set_MSP(*(__IO uint32_t *)AT32_BOOTLOADER_ADDRESS);
        __enable_irq();

        typedef void (*BootJump_t)(void);
        BootJump_t boot_jump = *(BootJump_t *)(AT32_BOOTLOADER_ADDRESS + 4);
        boot_jump();
        while (1);
    }
}

