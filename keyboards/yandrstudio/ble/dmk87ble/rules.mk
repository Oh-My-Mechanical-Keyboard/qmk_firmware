# Build Options
BOOTMAGIC_ENABLE = yes     # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
COMMAND_ENABLE = yes         # Commands for debug and configuration
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes           # USB Nkey Rollover

CUSTOM_MATRIX = lite
QUANTUM_SRC += matrix_io_inv.c 74hc595_io_inv.c
QUANTUM_SRC += rgb_matrix_layer.c

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = AW20216

CONSOLE_ENABLE = yes         # Console for debug
KEYBOARD_SHARED_EP = yes    # Free up some extra endpoints - needed if console+mouse+extra
