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
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = yes     # Virtual DIP switch configuration
KEYBOARD_SHARED_EP = no    # Free up some extra endpoints - needed if console+mouse+extra
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
COMMAND_ENABLE = no         # Commands for debug and configuration
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes           # USB Nkey Rollover
# CONSOLE_ENABLE = yes         # Console for debug
SPLIT_KEYBOARD = yes
SERIAL_DRIVER = usart

CUSTOM_MATRIX = lite
QUANTUM_SRC += matrix_io_sp.c
