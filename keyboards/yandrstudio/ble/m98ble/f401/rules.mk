# MCU name
MCU = STM32F401

# Bootloader selection
# BOOTLOADER = stm32-dfu

# Bootloader selection
BOOTLOADER = tinyuf2

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
# RGBLIGHT_ENABLE = yes
# RGBLIGHT_DRIVER = WS2812
WS2812_DRIVER = pwm

CUSTOM_MATRIX = lite    # for using the A9 pin as matrix io
QUANTUM_SRC += matrix_io.c 74hc595_io.c
