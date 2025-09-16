# MCU name
MCU = STM32F103

# Bootloader selection
# BOOTLOADER = stm32duino

MCU_LDSCRIPT = STM32F103xB_uf2boot
BOARD = STM32_F103_STM32DUINO
BOOTLOADER = uf2boot
FIRMWARE_FORMAT = uf2

# Wildcard to allow APM32 MCU
DFU_SUFFIX_ARGS = -p FFFF -v FFFF

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
RGBLIGHT_DRIVER = ws2812
WS2812_DRIVER = pwm

CUSTOM_MATRIX = lite
SRC += matrix.c
