# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes     # Virtual DIP switch configuration
MAGIC_ENABLE = yes
KEYBOARD_SHARED_EP = no    # Free up some extra endpoints - needed if console+mouse+extra
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
COMMAND_ENABLE = no         # Commands for debug and configuration
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes           # USB Nkey Rollover

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = ws2812
WS2812_DRIVER = pwm
QUANTUM_SRC += rgb_matrix_layer.c

LTO_ENABLE = yes

CONSOLE_ENABLE = yes         # Console for debug
KEYBOARD_SHARED_EP = yes     # Free up some extra endpoints - needed if console+mouse+extra
