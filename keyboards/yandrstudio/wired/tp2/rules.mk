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
BOOTMAGIC_ENABLE = yes     # Virtual DIP switch configuration
KEYBOARD_SHARED_EP = no   # Free up some extra endpoints - needed if console+mouse+extra
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes           # USB Nkey Rollover
ENCODER_ENABLE = yes

RGBLIGHT_ENABLE = yes
RGBLIGHT_DRIVER = ws2812
WS2812_DRIVER = pwm

AUDIO_ENABLE = yes
AUDIO_DRIVER = pwm_hardware

HAPTIC_ENABLE = yes
HAPTIC_DRIVER = solenoid

CUSTOM_MATRIX = lite    # for using the A9 pin as matrix io
QUANTUM_SRC += matrix_io_tp2.c
# QUANTUM_SRC += matrix_spi_tp2.c spi_master.c
