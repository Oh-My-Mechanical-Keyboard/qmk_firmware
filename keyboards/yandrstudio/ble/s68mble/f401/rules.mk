# MCU name
MCU = STM32F401

# Bootloader selection
# BOOTLOADER = stm32-dfu

# Bootloader selection
BOOTLOADER = tinyuf2

CUSTOM_MATRIX = lite    # for using the A9 pin as matrix io
# QUANTUM_SRC += matrix_io.c 74hc595_io.c
QUANTUM_SRC += matrix_io_inv.c 74hc595_io_inv.c
