# MCU name
MCU = STM32F401

# Address of the bootloader in system memory
STM32_BOOTLOADER_ADDRESS = 0x1FFF0000
# Bootloader selection
# BOOTLOADER = stm32-dfu
# Bootloader selection
MCU_LDSCRIPT = STM32F401xC_tinyuf2
BOOTLOADER = tinyuf2
FIRMWARE_FORMAT = uf2

# # project specific file
CUSTOM_MATRIX = lite    # for using the A9 pin as matrix io
# QUANTUM_SRC += matrix.c
QUANTUM_SRC += matrix_inv.c


RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
# RGBLIGHT_ENABLE = yes
# RGBLIGHT_DRIVER = WS2812
WS2812_DRIVER = pwm

EEPROM_DRIVER = custom
SRC += eep/eeprom_stm32.c
SRC += eep/flash_stm32.c
OPT_DEFS += -DEEPROM_EMU_STM32F401xC


# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
