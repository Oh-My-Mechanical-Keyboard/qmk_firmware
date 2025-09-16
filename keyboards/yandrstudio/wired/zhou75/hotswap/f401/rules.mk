# MCU name
MCU = STM32F401

# Bootloader selection
# BOOTLOADER = stm32-dfu
BOOTLOADER = tinyuf2

# # project specific file
CUSTOM_MATRIX = lite    # for using the A9 pin as matrix io
QUANTUM_SRC += matrix.c

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
# RGBLIGHT_ENABLE = yes
# RGBLIGHT_DRIVER = WS2812
WS2812_DRIVER = pwm

ENCODER_ENABLE = yes
