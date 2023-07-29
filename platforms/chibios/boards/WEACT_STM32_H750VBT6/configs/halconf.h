// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <halconf.h>

#undef HAL_USE_WSPI
#define HAL_USE_WSPI                        TRUE

#undef WSPI_USE_WAIT
#define WSPI_USE_WAIT                       TRUE

#undef WSPI_USE_MUTUAL_EXCLUSION
#define WSPI_USE_MUTUAL_EXCLUSION           TRUE
