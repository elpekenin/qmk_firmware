// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "qp.h"
#include "color.h"
#include "fira_code.qff.h"

#include "code/input.h"
#include "code/editor.h"
#include "code/lua_bindings.h"
#include "code/fatfs_helpers.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(KC_A)
};


static painter_device_t device = NULL;
static painter_font_handle_t font = NULL;


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return false;
    }

    keycode = mock_press();
    if (keycode == KC_NO) {
        return false;
    }

    if (!process_input_mode(keycode, record)) {
        return false;
    }

    return true;
}

uint32_t deferred_init(uint32_t t, void* cb_arg) {
    // FatFS
    mount();

    // Lua
    lua_setup();

    // Quantum Painter
    device = qp_ili9486_make_spi_waveshare_device(320, 480, ILI9486_CS_PIN, DC_PIN, RST_PIN, SPI_DIV, SPI_MODE);
    qp_init(device, QP_ROTATION_180);

    font = qp_load_font_mem(font_fira_code);

    return 0;
}

void keyboard_post_init_user(void) {
    debug_enable   = true;
    debug_matrix   = false;
    debug_keyboard = false;

    defer_exec(3000, deferred_init, NULL);
}

void housekeeping_task_user(void) {
    if (!device || !font) {
        return;
    }

    editor_flush(device, font);
}
