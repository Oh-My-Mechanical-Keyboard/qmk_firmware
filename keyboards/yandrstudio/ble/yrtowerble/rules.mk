# Build Options
BOOTMAGIC_ENABLE   = yes     # Virtual DIP switch configuration
KEYBOARD_SHARED_EP = no    # Free up some extra endpoints - needed if console+mouse+extra
MOUSEKEY_ENABLE    = no       # Mouse keys
EXTRAKEY_ENABLE    = yes       # Audio control and System control
COMMAND_ENABLE     = yes         # Commands for debug and configuration
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes           # USB Nkey Rollover

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
# RGBLIGHT_ENABLE = yes
# RGBLIGHT_DRIVER = WS2812
WS2812_DRIVER = pwm

CUSTOM_MATRIX = yes
QUANTUM_SRC += matrix_v2_io.c 74hc595_io.c
