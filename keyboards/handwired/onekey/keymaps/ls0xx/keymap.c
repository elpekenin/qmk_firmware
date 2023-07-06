// Copyright 2020 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

#include "color.h"
#include "qp_surface.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(KC_A)
};

uint8_t framebuffer[SURFACE_REQUIRED_BUFFER_BYTE_SIZE(128, 128, 1)];

uint32_t deferred_init(uint32_t trigger_time, void *cb_arg) {
    painter_device_t ls013b7dh03 = qp_ls013b7dh03_make_spi_device(CS_PIN, 64, 0, framebuffer);
    qp_init(ls013b7dh03, 0);
    qp_rect(ls013b7dh03, 0, 0, 15, 15, HSV_BLACK, true);
    qp_line(ls013b7dh03, 0, 0, 50, 50, HSV_WHITE);

    return 0;
}

void keyboard_post_init_user(void) {
    debug_enable = true;
    defer_exec(5000, deferred_init, NULL);
}
