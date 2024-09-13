# MCU name
MCU = STM32F103

# Bootloader selection
# BOOTLOADER = stm32duino

MCU_LDSCRIPT = STM32F103xB_uf2boot
BOARD = STM32_F103_STM32DUINO
BOOTLOADER = uf2boot
FIRMWARE_FORMAT = uf2

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes     # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
COMMAND_ENABLE = no         # Commands for debug and configuration
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes           # USB Nkey Rollover

CUSTOM_MATRIX = lite    # for using the A9 pin as matrix io
QUANTUM_SRC += matrix_ec.c


# KEYBOARD_SHARED_EP = yes
# CONSOLE_ENABLE = yes

SRC += analog.c
