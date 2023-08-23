// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* SPI pins */
#define SPI_DRIVER SPID4
#define SPI_SCK_PIN E12
#define SPI_MOSI_PIN E14
#define SPI_MISO_PIN NO_PIN

/* LCD Configuration */
#define LCD_RST_PIN NO_PIN
#define LCD_DC_PIN E13
#define LCD_CS_PIN E11
#define LCD_BL_PIN E10

#define QUANTUM_PAINTER_DEBUG
#define DEBUG_MATRIX_SCAN_RATE
