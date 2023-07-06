// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

/* Code adapted from Zephyr's driver
 *
 * Should support several LS0xx because they are pretty much
 * the same, with different sizes.
 *
 * Driver was developed on a LS013B7DH03, cant grant anything else will work as is.
 *
 * Note: xx does not mean 2 chars, names are pretty long
 */

#include "qp_internal.h"
#include "qp_comms.h"
#include "qp_surface.h"
#include "qp_surface_internal.h"
#include "qp_ls0xx_opcodes.h"

#ifdef QUANTUM_PAINTER_LS0XX_SPI_ENABLE
#    include "qp_comms_spi.h"
#endif // QUANTUM_PAINTER_LS0XX_SPI_ENABLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common MIP panel implementation for Sharp displays, using 3-wire SPI.
typedef struct mip_panel_painter_driver_vtable_t {
    painter_driver_vtable_t base; // must be first, so it can be cast to/from the painter_driver_vtable_t* type
} mip_panel_painter_driver_vtable_t;

// Device definition
typedef struct mip_panel_painter_device_t {
    painter_driver_t base; // must be first, so it can be cast to/from the painter_device_t* type

    // 1bpp-surface holding the data
    painter_device_t framebuffer;

    union {
#ifdef QUANTUM_PAINTER_SPI_ENABLE
        // SPI-based configurables
        qp_comms_spi_config_t spi_config;
#endif // QUANTUM_PAINTER_SPI_ENABLE

        // TODO: I2C/parallel etc.
    };
} mip_panel_painter_device_t;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common

// Driver storage
mip_panel_painter_device_t ls0xx_drivers[LS0XX_NUM_DEVICES] = {0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter API implementations

__attribute__((weak)) bool qp_ls0xx_init(painter_device_t device, painter_rotation_t rotation) {
    mip_panel_painter_device_t *mip_dev = (mip_panel_painter_device_t *)mip_dev;
    painter_driver_t *          surface = (painter_driver_t *)mip_dev->framebuffer;

    const uint8_t ls0xx_init_sequence[] = { LS0XX_CLEAR, 0 };
    qp_comms_send(device, ls0xx_init_sequence, sizeof(ls0xx_init_sequence));

    mip_dev->base.rotation = rotation;
    surface->driver_vtable->init(surface, rotation);

    return true;
}

bool qp_ls0xx_power(painter_device_t device, bool power_on) {
    // No-op
    return true;
}

bool qp_ls0xx_clear(painter_device_t device) {
    // Just re-init the display
    painter_driver_t *driver = (painter_driver_t *)device;
    return qp_ls0xx_init(device, driver->rotation);
}

bool qp_ls0xx_flush(painter_device_t device) {
    mip_panel_painter_device_t *mip_dev = (mip_panel_painter_device_t *)mip_dev;
    surface_painter_device_t *  surface = (surface_painter_device_t *)mip_dev->framebuffer;
    surface_dirty_data_t        dirty   = surface->dirty;

    if (!dirty.is_dirty) {
        // nothing to be sent
        return true;
    }

    /* NOTE
     * ----
     * Display has to be written in full lines (width)
     * Counting starts at 1, need to add to y
     *
     * TODO: Rotation support
     * FIXME: This works up to y == 255
     */
    uint8_t top    = (uint8_t)surface->dirty.t + 1;
    uint8_t bottom = (uint8_t)surface->dirty.b + 1;

    uint8_t  bytes_per_line = (mip_dev->base.panel_width / 8) * mip_dev->base.native_bits_per_pixel;
    uint16_t buffer_offset  = top * bytes_per_line;

    // start sending
    uint8_t cmd = LS0XX_WRITE;
    qp_comms_spi_send_data(device, &cmd, 1);

    // iterate over the lines
    for (uint8_t i = 0; i < bottom - top; ++i) {
        // set y-pos
        cmd = i + top;
        qp_comms_spi_send_data(device, &cmd, 1);

        // send data
        qp_comms_spi_send_data(device, surface->u8buffer + buffer_offset, bytes_per_line);
        buffer_offset += bytes_per_line;

        // dummy data
        cmd = 27;
        qp_comms_spi_send_data(device, &cmd, 1);
    }

    // extra trailing bits, the value doesnt matter
    qp_comms_spi_send_data(device, &cmd, 1);

    // clear surface's dirty area, no API to prevent extra prints
    surface->base.driver_vtable->flush(surface);

    return true;
}

bool qp_ls0xx_viewport(painter_device_t device, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
    mip_panel_painter_device_t *mip_dev = (mip_panel_painter_device_t *)mip_dev;
    painter_driver_t *  surface = (painter_driver_t *)mip_dev->framebuffer;

    return surface->driver_vtable->viewport(surface, left, top, right, bottom);
}

bool qp_ls0xx_pixdata(painter_device_t device, const void *pixel_data, uint32_t native_pixel_count) {
    mip_panel_painter_device_t *mip_dev = (mip_panel_painter_device_t *)mip_dev;
    painter_driver_t *          surface = (painter_driver_t *)mip_dev->framebuffer;

    return surface->driver_vtable->pixdata(surface, pixel_data, native_pixel_count);
}

bool qp_ls0xx_palette_convert(painter_device_t device, int16_t palette_size, qp_pixel_t *palette) {
    mip_panel_painter_device_t *mip_dev = (mip_panel_painter_device_t *)mip_dev;
    painter_driver_t *          surface = (painter_driver_t *)mip_dev->framebuffer;

    return surface->driver_vtable->palette_convert(surface, palette_size, palette);
}

bool qp_ls0xx_append_pixels(painter_device_t device, uint8_t *target_buffer, qp_pixel_t *palette, uint32_t pixel_offset, uint32_t pixel_count, uint8_t *palette_indices) {
    mip_panel_painter_device_t *mip_dev = (mip_panel_painter_device_t *)mip_dev;
    painter_driver_t *          surface = (painter_driver_t *)mip_dev->framebuffer;

    return surface->driver_vtable->append_pixels(surface, target_buffer, palette, pixel_offset, pixel_count, palette_indices);
}

bool qp_ls0xx_append_pixdata(painter_device_t device, uint8_t *target_buffer, uint32_t pixdata_offset, uint8_t pixdata_byte) {
    mip_panel_painter_device_t *mip_dev = (mip_panel_painter_device_t *)mip_dev;
    painter_driver_t *          surface = (painter_driver_t *)mip_dev->framebuffer;

    return surface->driver_vtable->append_pixdata(surface, target_buffer, pixdata_offset, pixdata_byte);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Driver vtable

const mip_panel_painter_driver_vtable_t ls0xx_driver_vtable = {
    .base =
        {
            .init            = qp_ls0xx_init,
            .power           = qp_ls0xx_power,
            .clear           = qp_ls0xx_clear,
            .flush           = qp_ls0xx_flush,
            .pixdata         = qp_ls0xx_pixdata,
            .viewport        = qp_ls0xx_viewport,
            .palette_convert = qp_ls0xx_palette_convert,
            .append_pixels   = qp_ls0xx_append_pixels,
            .append_pixdata  = qp_ls0xx_append_pixdata,
        },
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SPI

#ifdef QUANTUM_PAINTER_LS0XX_SPI_ENABLE

// Factory function for creating a handle to the ILI9163 device
painter_device_t qp_ls0xx_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, uint16_t spi_divisor, int spi_mode, void *buffer) {
    for (uint32_t i = 0; i < LS0XX_NUM_DEVICES; ++i) {
        mip_panel_painter_device_t *driver = &ls0xx_drivers[i];
        if (!driver->base.driver_vtable) {
            driver->base.driver_vtable         = (const painter_driver_vtable_t *)&ls0xx_driver_vtable;
            driver->base.comms_vtable          = (const painter_comms_vtable_t *)&spi_comms_vtable;
            driver->base.panel_width           = panel_width;
            driver->base.panel_height          = panel_height;
            driver->base.rotation              = QP_ROTATION_0;
            driver->base.offset_x              = 0;
            driver->base.offset_y              = 0;
            driver->base.native_bits_per_pixel = 1;

            // SPI and other pin configuration
            driver->base.comms_config          = &driver->spi_config;
            driver->spi_config.chip_select_pin = chip_select_pin;
            driver->spi_config.cs_active_high  = true;
            driver->spi_config.divisor         = spi_divisor;
            driver->spi_config.lsb_first       = false;
            driver->spi_config.mode            = spi_mode;

            driver->framebuffer = qp_make_mono1bpp_surface(panel_width, panel_height, buffer);

            if (!qp_internal_register_device((painter_device_t)driver)) {
                memset(driver, 0, sizeof(mip_panel_painter_device_t));
                return NULL;
            }

            return (painter_device_t)driver;
        }
    }
    return NULL;
}

#endif // QUANTUM_PAINTER_LS0XX_SPI_ENABLE

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
