// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

// ----------- XAP Mock -----------
extern "C" {
#include "xap.h"
}

// We wont be sending any data, so these can just be no-ops for now, we can later re-implement stuff here
// to confirm the outputs
extern "C" void xap_broadcast(uint8_t type, const void *data, size_t length) {}

extern "C" void xap_send(xap_token_t token, xap_response_flags_t response_flags, const void *data, size_t length) {}

// Various functions used on XAP, no-ops again
extern "C" void eeconfig_disable(void) {}

extern "C" void soft_reset_keyboard(void) {}

extern "C" typedef struct hardware_id_t {
    uint32_t data[4];
} hardware_id_t;
extern "C" hardware_id_t get_hardware_id(void) { return hardware_id_t { .data = { 0, 0, 0, 0 } }; }

extern "C" uint8_t keymap_layer_count(void) { return 1; }

extern "C" uint16_t keycode_at_keymap_location(uint8_t layer_num, uint8_t row, uint8_t column) { return 0; }
