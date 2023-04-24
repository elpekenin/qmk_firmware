// Copyright 2023 Pablo Martinez (@elpekenin)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "gpio.h"

void arm_atsam_set_pin_input_impl(pin_t pin) {
    pin_impl_t *impl = (pin_impl_t *)pin;
    mcu_pin_t  _pin  = impl->mcu_pin;

    PORT->Group[SAMD_PORT(_pin)].PINCFG[SAMD_PIN(_pin)].bit.INEN = 1;
    PORT->Group[SAMD_PORT(_pin)].DIRCLR.reg                      = SAMD_PIN_MASK(_pin);
}

void arm_atsam_set_pin_input_high_impl(pin_t pin) {
    pin_impl_t *impl = (pin_impl_t *)pin;
    mcu_pin_t  _pin  = impl->mcu_pin;

    PORT->Group[SAMD_PORT(_pin)].DIRCLR.reg                        = SAMD_PIN_MASK(_pin);
    PORT->Group[SAMD_PORT(_pin)].OUTSET.reg                        = SAMD_PIN_MASK(_pin);
    PORT->Group[SAMD_PORT(_pin)].PINCFG[SAMD_PIN(_pin)].bit.INEN   = 1;
    PORT->Group[SAMD_PORT(_pin)].PINCFG[SAMD_PIN(_pin)].bit.PULLEN = 1;
}

void arm_atsam_set_pin_input_low_impl(pin_t pin) {
    pin_impl_t *impl = (pin_impl_t *)pin;
    mcu_pin_t  _pin  = impl->mcu_pin;

    PORT->Group[SAMD_PORT(_pin)].DIRCLR.reg                        = SAMD_PIN_MASK(_pin);
    PORT->Group[SAMD_PORT(_pin)].OUTCLR.reg                        = SAMD_PIN_MASK(_pin);
    PORT->Group[SAMD_PORT(_pin)].PINCFG[SAMD_PIN(_pin)].bit.INEN   = 1;
    PORT->Group[SAMD_PORT(_pin)].PINCFG[SAMD_PIN(_pin)].bit.PULLEN = 1;
}

void arm_atsam_set_pin_output_impl(pin_t pin) {
    pin_impl_t *impl = (pin_impl_t *)pin;
    mcu_pin_t  _pin  = impl->mcu_pin;

    PORT->Group[SAMD_PORT(_pin)].DIRSET.reg = SAMD_PIN_MASK(_pin);
    PORT->Group[SAMD_PORT(_pin)].OUTCLR.reg = SAMD_PIN_MASK(_pin);
}

bool arm_atsam_read_pin_impl(pin_t pin) {
    pin_impl_t *impl = (pin_impl_t *)pin;
    mcu_pin_t  _pin  = impl->mcu_pin;

    return (PORT->Group[SAMD_PORT(_pin)].IN.reg & SAMD_PIN_MASK(_pin)) != 0;
}

void arm_atsam_write_pin_impl(pin_t pin, bool value) {
    pin_impl_t *impl = (pin_impl_t *)pin;
    mcu_pin_t  _pin  = impl->mcu_pin;

    if (value) {
        PORT->Group[SAMD_PORT(_pin)].OUTSET.reg = SAMD_PIN_MASK(_pin);
    } else {
        PORT->Group[SAMD_PORT(_pin)].OUTCLR.reg = SAMD_PIN_MASK(_pin);
    }
}

const pin_vtable_t gpio_pin_vtable_mcu = {
    .set_pin_input      = &arm_atsam_set_pin_input_impl,
    .set_pin_input_high = &arm_atsam_set_pin_input_high_impl,
    .set_pin_input_low  = &arm_atsam_set_pin_input_low_impl,
    .set_pin_output     = &arm_atsam_set_pin_output_impl,
    .read_pin           = &arm_atsam_read_pin_impl,
    .write_pin          = &arm_atsam_write_pin_impl,
};
