OLED_ENABLE = yes
CONSOLE_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += ili9486_spi

LUA_ENABLE = yes
FILESYSTEM_DRIVER = fatfs_spi_sd_card

VPATH += $(KEYMAP_PATH)/helpers
SRC += lua_helpers.c \
       fira_code.qff.c \
       fatfs_helpers.c \
       painter_helpers.c
