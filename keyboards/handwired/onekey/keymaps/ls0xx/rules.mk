CONSOLE_ENABLE = yes

QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += ls0xx_spi

VPATH += \
    $(KEYMAP_PATH)/painter/fonts \
    $(KEYMAP_PATH)/painter/images

SRC += \
    bw.qgf.c \
    fira_code.qff.c
