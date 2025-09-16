# MCU name
MCU = STM32F401

# Bootloader selection
# BOOTLOADER = stm32-dfu

# Bootloader selection
BOOTLOADER = tinyuf2

# # project specific file
CUSTOM_MATRIX = lite    # for using the A9 pin as matrix io
QUANTUM_SRC += matrix.c

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
