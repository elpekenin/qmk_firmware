# List of all the board related files.
BOARDSRC = $(CHIBIOS)/os/hal/boards/ST_STM32H750XB_DISCOVERY/board.c

# Extra files
BOARDSRC += $(BOARD_PATH)/board/extra.c

# Required include directories
BOARDINC = $(CHIBIOS)/os/hal/boards/ST_STM32H750XB_DISCOVERY

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
