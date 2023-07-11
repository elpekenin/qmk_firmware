// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_sharp_panel.h"
#include "qp_sharp_helper.h"

#if defined(QUANTUM_PAINTER_LS013B7DH03_SPI_ENABLE)
SHARP_SPI_IMPL(ls013b7dh03, 128, 128)
#endif // defined(QUANTUM_PAINTER_LS013B7DH03_SPI_ENABLE)
