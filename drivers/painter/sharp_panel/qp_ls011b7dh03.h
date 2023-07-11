// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "gpio.h"
#include "qp_internal.h"
#include "qp_sharp_helper.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter LS011B7DH03 configurables (add to your keyboard's config.h)

#ifndef LS011B7DH03_NUM_DEVICES
#    define LS011B7DH03_NUM_DEVICES 1
#endif

// "translation" for compatibility with string'ified name
#define ls011b7dh03_NUM_DEVICES LS011B7DH03_NUM_DEVICES

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter LS011B7DH03 device factory
#if defined(QUANTUM_PAINTER_LS011B7DH03_SPI_ENABLE)
SHARP_PROTOTYPE(ls011b7dh03, 128, 128)
#endif // defined(QUANTUM_PAINTER_LS011B7DH03_SPI_ENABLE)
