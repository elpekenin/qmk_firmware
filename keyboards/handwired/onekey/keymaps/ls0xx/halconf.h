// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#undef  HAL_USE_SPI
#define HAL_USE_SPI TRUE

#undef  SPI_USE_WAIT
#define SPI_USE_WAIT TRUE

#undef  SPI_SELECT_MODE
#define SPI_SELECT_MODE SPI_SELECT_MODE_NONE

#include_next <halconf.h>
