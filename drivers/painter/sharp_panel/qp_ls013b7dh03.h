// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "gpio.h"
#include "qp_internal.h"
#include "qp_sharp_helper.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter LS013B7DH03 configurables (add to your keyboard's config.h)

#ifndef LS013B7DH03_NUM_DEVICES
#    define LS013B7DH03_NUM_DEVICES 1
     // "translation" for compatibility with string'ified name
#    define ls013b7dh03_NUM_DEVICES LS013B7DH03_NUM_DEVICES
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter LS013B7DH03 device factory
SHARP_PROTOTYPE(ls013b7dh03, 128, 128)

