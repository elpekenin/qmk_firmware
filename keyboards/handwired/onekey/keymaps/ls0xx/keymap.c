// Copyright 2020 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

#include "color.h"
#include "qp_surface.h"

#include "bw.qgf.h"
#include "fira_code.qff.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(KC_A)
};

static painter_device_t ls013b7dh03;
static painter_image_handle_t bw_gif;

uint32_t deferred_init(uint32_t trigger_time, void *cb_arg) {
    bw_gif = qp_load_image_mem(gfx_bw);
    qp_animate(ls013b7dh03, 0, 0, bw_gif);

    qp_flush(ls013b7dh03);

    return 0;
}

void keyboard_post_init_user(void) {
    ls013b7dh03 = qp_ls013b7dh03_make_spi_device(CS_PIN, SPI_DIV, 0);
    qp_init(ls013b7dh03, QP_ROTATION_180);

    qp_rect(ls013b7dh03, 0, 0, 127, 127, HSV_BLACK, true);

    debug_enable = true;
    defer_exec(3000, deferred_init, NULL);
}

void housekeeping_task_user(void) {
    if (timer_read() > 20000) {
        bootloader_jump();
    }
}
