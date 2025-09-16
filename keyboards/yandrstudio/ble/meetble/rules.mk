# Build Options
BOOTMAGIC_ENABLE = yes     # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
COMMAND_ENABLE = yes         # Commands for debug and configuration
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes           # USB Nkey Rollover

CUSTOM_MATRIX = lite
QUANTUM_SRC += matrix_io.c 74hc595_io.c

RGBLIGHT_ENABLE = yes
RGBLIGHT_DRIVER = WS2812
