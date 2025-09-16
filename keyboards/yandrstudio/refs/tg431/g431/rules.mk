# MCU name
MCU = STM32G431
BOARD = GENERIC_STM32_G431XB
BOOTLOADER = stm32-dfu
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
WS2812_DRIVER = pwm         # WS2812 RGB Driver
# WS2812_DRIVER = bitbang
EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = embedded_flash
# EEPROM_DRIVER = transient

# OPT_DEFS += -USTM32_FLASH_NUMBER_OF_BANKS
# lib/chibios/os/hal/ports/STM32/STM32G4xx/stm32_registry.h->Line:608
# undef STM32_FLASH_NUMBER_OF_BANKS
# define STM32_FLASH_NUMBER_OF_BANKS 1

