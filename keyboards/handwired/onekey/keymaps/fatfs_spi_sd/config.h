// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP14
#define SPI_MOSI_PIN GP15
#define SPI_MISO_PIN GP12
#define SD_CS_PIN GP13
#define ILI9486_CS_PIN GP18
#define DC_PIN GP19
#define RST_PIN GP20

#define SPI_MODE 0
#define SPI_DIV  8

#undef DEBUG_MATRIX_SCAN_RATE

#define READ_BUFFER_SIZE 1024

#define TEXT_BUFFER_LEN 1000
#define TEMP_BUFF_LEN 50
#define INPUT_BUF_LEN 20

#define OPEN_EDITOR QK_USER
