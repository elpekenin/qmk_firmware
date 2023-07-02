CONSOLE_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes
QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += ili9486_spi

LUA_ENABLE = yes
FILESYSTEM_DRIVER = fatfs_spi_sd_card

VPATH += $(KEYMAP_PATH)/code
SRC += input.c \
       editor.c \
       lua_bindings.c \
       fatfs_helpers.c \

VPATH += $(KEYMAP_PATH)/assets
SRC +=
       fira_code.qff.c \
