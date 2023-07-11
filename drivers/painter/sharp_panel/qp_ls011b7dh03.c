// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_sharp_panel.h"
#include "qp_sharp_helper.h"

// AKA: nice!view
#if defined(QUANTUM_PAINTER_LS011B7DH03_SPI_ENABLE)
SHARP_SPI_IMPL(ls011b7dh03, 160, 68)
#endif // defined(QUANTUM_PAINTER_LS011B7DH03_SPI_ENABLE)
