// Copyright 2023 Pablo Martinez (@elpekenin)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "debug.h"
#include "gpio.h"

void avr_set_pin_input_impl(pin_t pin) {
    pin_impl_t *impl = (pin_impl_t *)pin;
    mcu_pin_t  _pin  = impl->mcu_pin;

    DDRx_ADDRESS(_pin)  &= ~_BV((_pin)&0xF);
    PORTx_ADDRESS(_pin) &= ~_BV((_pin)&0xF);
}

void avr_set_pin_input_high_impl(pin_t pin) {
    pin_impl_t *impl = (pin_impl_t *)pin;
    mcu_pin_t  _pin  = impl->mcu_pin;

    DDRx_ADDRESS(_pin) &= ~_BV((_pin)&0xF);
    PORTx_ADDRESS(_pin) |= _BV((_pin)&0xF);
}

void avr_set_pin_input_low_impl(pin_t pin) {
    dprintln("ERROR: AVR processors cannot implement an input as pull low");
}

void avr_set_pin_output_impl(pin_t pin) {
    pin_impl_t *impl = (pin_impl_t *)pin;
    mcu_pin_t  _pin  = impl->mcu_pin;

    DDRx_ADDRESS(_pin) |= _BV((_pin)&0xF);
}

bool avr_read_pin_impl(pin_t pin) {
    pin_impl_t *impl = (pin_impl_t *)pin;
    mcu_pin_t  _pin  = impl->mcu_pin;

    return PINx_ADDRESS(_pin) & _BV((_pin)&0xF);
}

void avr_write_pin_impl(pin_t pin, bool value) {
    pin_impl_t *impl = (pin_impl_t *)pin;
    mcu_pin_t  _pin  = impl->mcu_pin;

    if (value) {
        PORTx_ADDRESS(_pin) |= _BV((_pin)&0xF);
    } else {
        PORTx_ADDRESS(_pin) &= ~_BV((_pin)&0xF);
    }
}

const pin_vtable_t gpio_pin_vtable_mcu = {
    .set_pin_input      = &avr_set_pin_input_impl,
    .set_pin_input_high = &avr_set_pin_input_high_impl,
    .set_pin_input_low  = &avr_set_pin_input_low_impl,
    .set_pin_output     = &avr_set_pin_output_impl,
    .read_pin           = &avr_read_pin_impl,
    .write_pin          = &avr_write_pin_impl,
};
