# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes  # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes   # Mouse keys
EXTRAKEY_ENABLE = yes   # Audio control and System control
COMMAND_ENABLE = no     # Commands for debug and configuration
NKRO_ENABLE = yes       # Enable N-Key Rollover	
BACKLIGHT_ENABLE = no   # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes   # Enable keyboard RGB underglow
AUDIO_ENABLE = no       # Audio output

MCU_LDSCRIPT = R4M31G
BOOTLOADER = custom

OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE

# CONSOLE_ENABLE = yes
