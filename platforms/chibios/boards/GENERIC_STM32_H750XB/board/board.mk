# List of all the board related files.
BOARDSRC = $(BOARD_PATH)/board/board.c \
        #    $(BOARD_PATH)/board/extra.c

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
