# MCU name
MCU = WB32FQ95
# Bootloader selection
BOOTLOADER = wb32-dfu

BOOTMAGIC_ENABLE = yes         # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes          # Mouse keys
EXTRAKEY_ENABLE = yes          # Audio control and System control
NKRO_ENABLE = yes              # Enable N-Key Rollover

# KEYBOARD_SHARED_EP = yes
# CONSOLE_ENABLE = yes            # Console for debug

EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = spi_flash

RGB_MATRIX_ENABLE = yes        # RGB matrix
RGB_MATRIX_DRIVER = ws2812
WS2812_DRIVER = spi

# Wireless
include keyboards/hackstone/wireless_wb32_hs/wireless.mk

SRC += wls_port.c

