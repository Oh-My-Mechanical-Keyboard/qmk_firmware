# MCU name
MCU = STM32F401

# Bootloader selection
# BOOTLOADER = stm32-dfu
BOOTLOADER = tinyuf2
MCU_LDSCRIPT = STM32F401xC_tinyuf2_lite

# # project specific file
CUSTOM_MATRIX = lite    # for using the A9 pin as matrix io
# QUANTUM_SRC += matrix.c
QUANTUM_SRC += matrix_io.c 74hc595_io.c
