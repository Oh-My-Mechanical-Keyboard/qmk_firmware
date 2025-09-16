# MCU name
MCU = STM32F103

# Bootloader selection
# BOOTLOADER = stm32duino

MCU_LDSCRIPT = STM32F103xB_uf2
BOARD = STM32_F103_STM32DUINO
BOOTLOADER = tinyuf2
FIRMWARE_FORMAT = uf2
MCU_STARTUP ?= stm32f1xx

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
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
ENCODER_ENABLE = no         # Rotary encoder support
RGB_MATRIX_ENABLE = no      # Enable keyboard RGB matrix functionality
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
RGB_MATRIX_DRIVER = WS2812  # RGB matrix driver support
WS2812_DRIVER = pwm         # WS2812 RGB Driver
