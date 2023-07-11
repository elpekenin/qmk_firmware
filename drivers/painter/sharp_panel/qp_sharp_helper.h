// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

// As these displays dont (apparently) have any device-specific config, let's use a helper macro for them

#pragma once

#define __TYPE_NAME(name)    name##_device_t
#define __STORAGE_NAME(name) name##_drivers
#define __NUM_DEVICES(name)  name##_NUM_DEVICES
#define __FUNC_NAME(name)    qp_##name##_make_spi_device

#define __BUFFER_SIZE(width, height) (SURFACE_REQUIRED_BUFFER_BYTE_SIZE(width, height, 1))


#define _SHARP_TYPE(name, width, height)                   \
    typedef struct __TYPE_NAME(name) {                     \
        mip_panel_painter_device_t mip;                    \
        uint8_t framebuffer[__BUFFER_SIZE(width, height)]; \
    } __TYPE_NAME(name);


#define _SHARP_STORAGE(name) \
    __TYPE_NAME(name) __STORAGE_NAME(name)[__NUM_DEVICES(name)] = {0};


#define _SHARP_CONSTRUCTOR(name, width, height)                                                                                        \
    painter_device_t __FUNC_NAME(name) (pin_t chip_select_pin, uint16_t spi_divisor, int spi_mode) {                                   \
    for (uint32_t i = 0; i < __NUM_DEVICES(name); ++i) {                                                                               \
        __TYPE_NAME(name) *driver = &__STORAGE_NAME(name)[i];                                                                          \
        if (!driver->mip.base.driver_vtable) {                                                                                         \
            painter_device_t surface = qp_make_mono1bpp_surface_advanced(&driver->mip.surface, 1, width, height, driver->framebuffer); \
            if (!surface) {                                                                                                            \
                return NULL;                                                                                                           \
            }                                                                                                                          \
            driver->mip.base.driver_vtable         = (const painter_driver_vtable_t *)&ls0xx_driver_vtable;                            \
            driver->mip.base.comms_vtable          = (const painter_comms_vtable_t *)&spi_comms_vtable;                                \
            driver->mip.base.native_bits_per_pixel = 1;                                                                                \
            driver->mip.base.panel_width           = width;                                                                            \
            driver->mip.base.panel_height          = height;                                                                           \
            driver->mip.base.rotation              = QP_ROTATION_0;                                                                    \
            driver->mip.base.offset_x              = 0;                                                                                \
            driver->mip.base.offset_y              = 0;                                                                                \
            driver->mip.base.comms_config          = &driver->mip.spi_config;                                                          \
            driver->mip.spi_config.chip_select_pin = chip_select_pin;                                                                  \
            driver->mip.spi_config.lsb_first       = false;                                                                            \
            driver->mip.spi_config.divisor         = spi_divisor;                                                                      \
            driver->mip.spi_config.mode            = spi_mode;                                                                         \
            driver->mip.surface.invert_order       = true;                                                                             \
            if (!qp_internal_register_device((painter_device_t)driver)) {                                                              \
                memset(driver, 0, sizeof(__TYPE_NAME(name)));                                                                          \
                return NULL;                                                                                                           \
            }                                                                                                                          \
            return (painter_device_t)driver;                                                                                           \
        }                                                                                                                              \
    }                                                                                                                                  \
    return NULL;                                                                                                                       \
}


#define SHARP_IMPL(name, width, height) \
    _SHARP_TYPE(name, width, height)    \
    _SHARP_STORAGE(name)                \
    _SHARP_CONSTRUCTOR(name, width, height)

#define SHARP_PROTOTYPE(name, width, height) \
    painter_device_t __FUNC_NAME(name) (pin_t chip_select_pin, uint16_t spi_divisor, int spi_mode);
