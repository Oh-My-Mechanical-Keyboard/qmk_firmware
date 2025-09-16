MCU_LDSCRIPT = STM32F103x8_uf2boot

# Wildcard to allow APM32 MCU
DFU_SUFFIX_ARGS = -p FFFF -v FFFF

QUANTUM_SRC += rgb_matrix_layer.c
SRC += my_sym_eager_pk.c
