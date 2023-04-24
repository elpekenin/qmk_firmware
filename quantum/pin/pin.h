// Copyright 2023 Pablo Martinez (@elpekenin)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "stdbool.h"
#include "stddef.h" // for NULL
#include "stdint.h"

typedef enum pintype_t {
    PIN_MCU,             // Real GPIO
    PIN_NONE,            // Used for NO_PIN

#ifdef USE_MCP23017      /* 16-bit IO Expander */
    PIN_MCP23017,        // |- I2C
#endif // USE_MCP23017   // |
#ifdef USE_MCP2SS17      // |
    PIN_MCP23S17,        // |- SPI
#endif // USE_MCP23S17
} pintype_t;

// TODO: Platform-specific declaration
typedef uint32_t mcu_pin_t;

typedef struct pin_impl_t {
    pintype_t type;
    union {
        mcu_pin_t mcu_pin;

#ifdef USE_MCP23017
        struct {
            uint8_t i2c_bus_idx;
            uint8_t i2c_addr;
            uint8_t pin_num;
        } mcp23017;
#endif // USE_MCP23017

#ifdef USE_MCP23S17
        struct {
            uint8_t spi_bus_idx;
            pin_t * cs_pin;
            uint8_t pin_num;
        } mcp23S17;
#endif // USE_MCP23S17
    };
} pin_impl_t;

typedef const pin_impl_t *pin_t;

// Determine the base set of APIs required
typedef struct pin_vtable_t {
    // Perhaps consolidate these with another "pin_pull_t" parameter?
    void (*set_pin_input)(pin_t pin);
    void (*set_pin_input_low)(pin_t pin);
    void (*set_pin_input_high)(pin_t pin);

    void (*set_pin_output)(pin_t pin);

    bool (*read_pin)(pin_t pin);
    void (*write_pin)(pin_t pin, bool value);

    // ...
} pin_vtable_t;

extern const pin_vtable_t *pin_vtables[];

/**
   @brief   Check if a "pin" is real (MCU GPIO) or virtual
   @param   pin Pointer to the struct with the pin's information
   @param   value Pointer to a mcu_pin_t where the value will be copied
   @return  true if GPIO, false otherwise
*/
bool get_mcu_pin(pin_t pin, mcu_pin_t *value);

#define setPinInput(pin)                                     \
    do {                                                     \
        if (pin_vtables[pin->type]->set_pin_input != NULL) { \
            pin_vtables[pin->type]->set_pin_input(pin);      \
        }                                                    \
    } while (0)

#define setPinInputLow(pin)                                      \
    do {                                                         \
        if (pin_vtables[pin->type]->set_pin_input_low != NULL) { \
            pin_vtables[pin->type]->set_pin_input_low(pin);      \
        }                                                        \
    } while (0)

#define setPinInputHigh(pin)                                      \
    do {                                                          \
        if (pin_vtables[pin->type]->set_pin_input_high != NULL) { \
            pin_vtables[pin->type]->set_pin_input_high(pin);      \
        }                                                         \
    } while (0)

#define setPinOutput(pin)                                     \
    do {                                                      \
        if (pin_vtables[pin->type]->set_pin_output != NULL) { \
            pin_vtables[pin->type]->set_pin_output(pin);      \
        }                                                     \
    } while (0)

int8_t readPin(pin_t pin);

#define writePin(pin, value)                               \
    do {                                                   \
        if (pin_vtables[pin->type]->write_pin != NULL) {   \
            pin_vtables[pin->type]->write_pin(pin, value); \
        }                                                  \
    } while (0)

#define writePinHigh(pin) writePin(pin, true)
#define writePinLow(pin) writePin(pin, false)
