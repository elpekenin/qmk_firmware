// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define SPI_DRIVER   SPID0
#define SPI_SCK_PIN  GP2
#define SPI_MOSI_PIN GP3
#define SPI_MISO_PIN NO_PIN
#define CS_PIN       GP4

#define SPI_DIV 16

// #define QUANTUM_PAINTER_DEBUG
/* just enough for the whole display */
#define QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE 2048
