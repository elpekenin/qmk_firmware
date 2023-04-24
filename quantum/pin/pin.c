// Copyright 2023 Pablo Martinez (@elpekenin)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "pin.h"
#include "gpio.h"


bool get_mcu_pin(pin_t pin, mcu_pin_t *value) {
    pin_impl_t *impl = (pin_impl_t *)pin;

    if (impl->type == PIN_MCU) {
        *value = impl->mcu_pin;
        return true;
    }

    return false;
}

int8_t readPin(pin_t pin) {
    if (pin_vtables[pin->type]->read_pin == NULL) {
        return -1;
    }

    return pin_vtables[pin->type]->read_pin(pin);
}

// TODO: Add some actual functions here for debug purposses?
// i.e: dprint("Tried reading from NO_PIN\n");
const pin_vtable_t gpio_pin_vtable_none = {
    .set_pin_input      = NULL,
    .set_pin_input_high = NULL,
    .set_pin_input_low  = NULL,
    .set_pin_output     = NULL,
    .read_pin           = NULL,
    .write_pin          = NULL,
};

const pin_vtable_t *pin_vtables[] = {
    [PIN_MCU] = &gpio_pin_vtable_mcu, // platform(MCU) specific

    // (hopefully) MCU-agnostic
    [PIN_NONE] = &gpio_pin_vtable_none,
#ifdef USE_MCP23017
    [PIN_MCP23017] = &gpio_pin_vtable_mcp23017,
#endif // USE_MCP23017

#ifdef USE_MCP23S17
    [PIN_MCP23S17] = &gpio_pin_vtable_mcp23S17,
#endif // USE_MCP23S17
};
