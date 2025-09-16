# MCU name
MCU = STM32F401

# Bootloader selection
# BOOTLOADER = stm32-dfu
BOOTLOADER = tinyuf2

# Build Options
BOOTMAGIC_ENABLE = yes     # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes           # USB Nkey Rollover

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
WS2812_DRIVER = pwm         # WS2812 RGB Driver

SPLIT_KEYBOARD = yes
SERIAL_DRIVER = usart

# Revert to legacy wear-leveling driver until ChibiOS's EFL driver is fixed with 128kB and 384kB variants.
EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = legacy
