# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu
# Build Options
BOOTMAGIC_ENABLE = yes     # Enable Bootmagic Lite
EXTRAKEY_ENABLE = yes    # Audio control and System control
NKRO_ENABLE = yes       # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
RGBLIGHT_ENABLE = yes
