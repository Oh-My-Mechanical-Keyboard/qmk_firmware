AUDIO_DRIVER = pwm_software
WS2812_DRIVER = pwm

OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE
SRC += ../rgb_control.c
