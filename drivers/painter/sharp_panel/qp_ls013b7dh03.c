// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_sharp_panel.h"

#define PANEL_WIDTH  128
#define PANEL_HEIGHT 128

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver storage
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct ls013b7dh03_panel_painter_device_t {
    mip_panel_painter_device_t mip;

    uint8_t framebuffer[SURFACE_REQUIRED_BUFFER_BYTE_SIZE(PANEL_WIDTH, PANEL_HEIGHT, 1)];
} ls013b7dh03_panel_painter_device_t;

ls013b7dh03_panel_painter_device_t ls013b7dh03_drivers[LS013B7DH03_NUM_DEVICES] = {0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SPI

#ifdef QUANTUM_PAINTER_LS013B7DH03_SPI_ENABLE

painter_device_t qp_ls013b7dh03_make_spi_device(pin_t chip_select_pin, uint16_t spi_divisor, int spi_mode) {
    for (uint32_t i = 0; i < LS013B7DH03_NUM_DEVICES; ++i) {
        ls013b7dh03_panel_painter_device_t *driver = &ls013b7dh03_drivers[i];
        if (!driver->mip.base.driver_vtable) {
            painter_device_t surface = qp_make_mono1bpp_surface_advanced(&driver->mip.surface, 1, PANEL_WIDTH, PANEL_HEIGHT, driver->framebuffer);
            if (!surface) {
                return NULL;
            }

            driver->mip.base.driver_vtable         = (const painter_driver_vtable_t *)&ls0xx_driver_vtable;
            driver->mip.base.comms_vtable          = (const painter_comms_vtable_t *)&spi_comms_vtable;
            driver->mip.base.native_bits_per_pixel = 1;
            driver->mip.base.panel_width           = PANEL_WIDTH;
            driver->mip.base.panel_height          = PANEL_HEIGHT;
            driver->mip.base.rotation              = QP_ROTATION_0;
            driver->mip.base.offset_x              = 0;
            driver->mip.base.offset_y              = 0;

            driver->mip.base.comms_config          = &driver->mip.spi_config;
            driver->mip.spi_config.chip_select_pin = chip_select_pin;
            driver->mip.spi_config.lsb_first       = false;
            driver->mip.spi_config.divisor         = spi_divisor;
            driver->mip.spi_config.mode            = spi_mode;

            // append pixels in inverted order
            driver->mip.surface.invert_order = true;

            if (!qp_internal_register_device((painter_device_t)driver)) {
                memset(driver, 0, sizeof(ls013b7dh03_panel_painter_device_t));
                return NULL;
            }

            return (painter_device_t)driver;
        }
    }

    return NULL;
}

#endif // QUANTUM_PAINTER_LS013B7DH03_SPI_ENABLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
