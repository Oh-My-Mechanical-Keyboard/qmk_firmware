# List of all the board related files.
BOARDSRC = $(BOARD_PATH)/board/board.c

# Required include directories
BOARDINC = $(BOARD_PATH)/board

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)

ifeq ($(strip $(AIR32F10x_USE_UNLOCKED_SRAM)), yes)
	ADEF += -DCRT0_UNLOCK_SRAM=1
endif
