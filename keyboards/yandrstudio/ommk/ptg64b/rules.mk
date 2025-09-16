# Build Options
MCU_LDSCRIPT = R4M31G
BOOTLOADER = custom

QUANTUM_SRC += rgb_matrix_layer.c

OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

DEBOUNCE_TYPE = sym_eager_pk
