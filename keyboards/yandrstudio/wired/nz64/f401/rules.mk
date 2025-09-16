# MCU name
MCU = STM32F401

# Bootloader selection
BOOTLOADER = tinyuf2
# BOOTLOADER = stm32-dfu

# # project specific file
CUSTOM_MATRIX = lite    # for using the A9 pin as matrix io
QUANTUM_SRC += matrix.c

WS2812_DRIVER = pwm
