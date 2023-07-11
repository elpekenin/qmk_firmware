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

static painter_device_t       ls013b7dh03;
static painter_font_handle_t  fira_code;
static painter_image_handle_t bw_gif;

uint32_t deferred_init(uint32_t trigger_time, void *cb_arg) {
    // qp_animate(ls013b7dh03, 0, 0, bw_gif);

    for (uint8_t rotation = 0; rotation < 4; ++rotation) {
        qp_init(ls013b7dh03, rotation);
        qp_drawtext(ls013b7dh03, 0, 0, fira_code, "Rotation :)");
        qp_flush(ls013b7dh03);
        wait_ms(500);
    }

    return 0;
}

void keyboard_post_init_user(void) {
    debug_enable = true;

    ls013b7dh03 = qp_ls013b7dh03_make_spi_device(CS_PIN, SPI_DIV, 0);

    bw_gif = qp_load_image_mem(gfx_bw);
    fira_code = qp_load_font_mem(font_fira_code);

    defer_exec(3000, deferred_init, NULL);
}

void housekeeping_task_user(void) {
    if (timer_read() > 20000) {
        bootloader_jump();
    }
}
