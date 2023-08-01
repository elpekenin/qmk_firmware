ifeq ($(strip $(BOOTLOADER)), tinyuf2)
    MCU_LDSCRIPT = STM32H750xB_qspi_tinyuf2
    UF2CONV_ARGS = --base 0x90000000
endif
