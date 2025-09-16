# Build Options
BOOTMAGIC_ENABLE = yes     # Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
COMMAND_ENABLE = yes         # Commands for debug and configuration
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = yes           # USB Nkey Rollover

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = ws2812
# QUANTUM_SRC += rgb_matrix_layer.c
WS2812_DRIVER = pwm

CUSTOM_MATRIX = lite
QUANTUM_SRC += matrix_sp.c

SPLIT_KEYBOARD = yes
SERIAL_DRIVER = usart

# NO_USB_STARTUP_CHECK = yes
# CONSOLE_ENABLE = yes         # Console for debug
# KEYBOARD_SHARED_EP = yes        # Free up some extra endpoints - needed if console+mouse+extra
# QUANTUM_SRC += SEGGER_RTT_printf.c SEGGER_RTT.c
# ALLOW_WARNINGS = yes

# RGBLIGHT_ENABLE = yes
# RGBLIGHT_DRIVER = WS2812
# OPT_DEFS += -DFACTORY_TEST
