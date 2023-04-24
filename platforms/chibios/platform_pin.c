// Copyright 2023 Pablo Martinez (@elpekenin)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "gpio.h"

void chibios_set_pin_input_impl(pin_t pin) {
    pin_impl_t *impl = (pin_impl_t *)pin;

    palSetLineMode(impl->mcu_pin, PAL_MODE_INPUT);
}

void chibios_set_pin_input_high_impl(pin_t pin) {
    pin_impl_t *impl = (pin_impl_t *)pin;

    palSetLineMode(impl->mcu_pin, PAL_MODE_INPUT_PULLUP);
}

void chibios_set_pin_input_low_impl(pin_t pin) {
    pin_impl_t *impl = (pin_impl_t *)pin;

    palSetLineMode(impl->mcu_pin, PAL_MODE_INPUT_PULLDOWN);
}

void chibios_set_pin_output_impl(pin_t pin) {
    pin_impl_t *impl = (pin_impl_t *)pin;

    palSetLineMode(impl->mcu_pin, PAL_MODE_OUTPUT_PUSHPULL);
}

bool chibios_read_pin_impl(pin_t pin) {
    pin_impl_t *impl = (pin_impl_t *)pin;

    return palReadLine(impl->mcu_pin);
}

void chibios_write_pin_impl(pin_t pin, bool value) {
    pin_impl_t *impl = (pin_impl_t *)pin;
    mcu_pin_t  _pin  = impl->mcu_pin;

    if (value) {
        palSetLine(_pin);
    } else {
        palClearLine(_pin);
    }
}

const pin_vtable_t gpio_pin_vtable_mcu = {
    .set_pin_input      = &chibios_set_pin_input_impl,
    .set_pin_input_high = &chibios_set_pin_input_high_impl,
    .set_pin_input_low  = &chibios_set_pin_input_low_impl,
    .set_pin_output     = &chibios_set_pin_output_impl,
    .read_pin           = &chibios_read_pin_impl,
    .write_pin          = &chibios_write_pin_impl,
};
