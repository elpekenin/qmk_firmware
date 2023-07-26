// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <board.h>

#undef STM32_HSECLK
#define STM32_HSECLK 25000000U

#undef STM32_HSE_BYPASS
