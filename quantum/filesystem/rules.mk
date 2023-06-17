# Filesystem Configurables
VALID_FILESYSTEM_DRIVERS := lfs_spi_flash fatfs_spi_sd_card

ifeq ($(filter $(FILESYSTEM_DRIVER),$(VALID_FILESYSTEM_DRIVERS)),)
  $(call CATASTROPHIC_ERROR,Invalid FILESYSTEM_DRIVER,FILESYSTEM_DRIVER="$(FILESYSTEM_DRIVER)" is not a valid filesystem driver)
else
	OPT_DEFS += -DFILESYSTEM_ENABLE
	COMMON_VPATH += \
		$(QUANTUM_DIR)/filesystem

	ifeq ($(strip $(FILESYSTEM_DRIVER)),lfs_spi_flash)
		FLASH_DRIVER = spi
		QUANTUM_LIB_SRC += spi_master.c
		COMMON_VPATH += \
			$(LIB_PATH)/littlefs
		SRC += \
			lfs.c \
			lfs_util.c \
			fs_lfs_common.c \
			fs_lfs_spi_flash.c
	endif
	ifeq ($(strip $(FILESYSTEM_DRIVER)),fatfs_spi_sd_card)
		QUANTUM_LIB_SRC += spi_master.c
		COMMON_VPATH += \
			$(LIB_PATH)/fatfs/source \
			$(QUANTUM_DIR)/filesystem/fatfs
		SRC += \
			ff.c \
			sdmm.c
	endif
endif
