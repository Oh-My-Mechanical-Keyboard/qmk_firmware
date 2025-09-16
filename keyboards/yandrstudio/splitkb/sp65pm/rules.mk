# MCU name
MCU = atmega32u2
BOOTLOADER = atmel-dfu

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration
MOUSEKEY_ENABLE = no	# Mouse keys
EXTRAKEY_ENABLE = no	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = no   # Commands for debug and configuration
NKRO_ENABLE = no		# USB Nkey Rollover - not yet supported in LUFA

# LTO_ENABLE = yes

CUSTOM_MATRIX = yes    # Remote matrix from the wireless bridge
# # project specific file
SRC += matrix.c
