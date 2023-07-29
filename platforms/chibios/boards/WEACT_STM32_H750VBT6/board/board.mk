# List of all the board related files.
BOARDSRC = $(BOARD_PATH)/board/board.c

# Required include directories
BOARDINC = $(CHIBIOS)/os/hal/boards/WEACT_STM32H750VBT6_MINI

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
