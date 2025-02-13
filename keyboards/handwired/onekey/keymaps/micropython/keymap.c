// Copyright 2020 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

#include "port/micropython_embed.h"

static char micropy_heap[8 * 1024];

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(KC_A)
};

void housekeeping_task_user(void) {
    int stack_top;

    // wait for USB to be ready for printing
    static bool done = false;
    if (timer_read() > 5000 && !done) {
        done = true;

        mp_embed_init(&micropy_heap[0], sizeof(micropy_heap), &stack_top);
        mp_embed_exec_str("print('hello from micropython!', [x for x in range(5)])");
        mp_embed_deinit();
    }
}
