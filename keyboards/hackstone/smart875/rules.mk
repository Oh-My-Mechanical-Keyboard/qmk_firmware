# MCU name
MCU = WB32FQ95
# Bootloader selection
BOOTLOADER = wb32-dfu

BOOTMAGIC_ENABLE = yes         # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes          # Mouse keys
EXTRAKEY_ENABLE = yes          # Audio control and System control
NKRO_ENABLE = yes              # Enable N-Key Rollover

KEYBOARD_SHARED_EP = yes
CONSOLE_ENABLE = yes            # Console for debug

EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = spi_flash

RGB_MATRIX_ENABLE = yes        # RGB matrix
RGB_MATRIX_DRIVER = ws2812
WS2812_DRIVER = spi

OPT_DEFS += -DSMT875_SPP

SRC += keyboards/hackstone/smart875/logo_rgb.o

# DEBOUNCE_TYPE = sym_eager_pk

# Wireless
include keyboards/hackstone/wireless_wb32_hs/wireless.mk
DEFERRED_EXEC_ENABLE = yes

SRC += wls_port.c

# SRC += iprint.c
# OPT_DEFS += -DGPIO_UART_ENABLE
