// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "gpio.h"
#include "qp_internal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter LS013B7DH03 configurables (add to your keyboard's config.h)

#ifndef LS013B7DH03_NUM_DEVICES
/**
 * @def This controls the maximum number of LS013B7DH03 devices that Quantum Painter can communicate with at any one time.
 *      Increasing this number allows for multiple displays to be used.
 */
#    define LS013B7DH03_NUM_DEVICES 1
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter LS013B7DH03 device factories

#ifdef QUANTUM_PAINTER_LS013B7DH03_SPI_ENABLE
/**
 * Factory method for a generic LS013B7DH03(128x128) SPI MIP device.
 *
 * @param chip_select_pin[in] the GPIO pin used for SPI chip select
 * @param spi_divisor[in] the SPI divisor to use when communicating with the display
 * @param spi_mode[in] the SPI mode to use when communicating with the display
 * @return the device handle used with all drawing routines in Quantum Painter
 */
painter_device_t qp_ls013b7dh03_make_spi_device(pin_t chip_select_pin, uint16_t spi_divisor, int spi_mode);
#endif // QUANTUM_PAINTER_LS013B7DH03_SPI_ENABLE

