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

uint16_t mock_press(void) {
    static uint8_t i = 0;

    uint16_t mock_events[] = {
         // open file
        OPEN_EDITOR,

        // file
        KC_H, KC_O, KC_U, KC_S, KC_E,

        // .lua
        KC_DOT, KC_L, KC_U, KC_A,

        // confirm
        KC_ENT,

        // get to the line
        KC_DOWN, KC_DOWN, KC_DOWN, KC_DOWN, KC_DOWN, KC_DOWN, KC_DOWN, KC_DOWN, KC_DOWN, KC_DOWN, KC_DOWN,

        // indentation
        KC_RIGHT, KC_RIGHT, KC_RIGHT, KC_RIGHT, KC_RIGHT, KC_RIGHT, KC_RIGHT, KC_RIGHT,

        // "HSV_RED"
        KC_RIGHT, KC_RIGHT, KC_RIGHT, KC_RIGHT, KC_RIGHT, KC_RIGHT, KC_RIGHT,

        // remove RED
        KC_BSPC, KC_BSPC, KC_BSPC,

        // write BLUE
        KC_CAPS,
        KC_B, KC_L, KC_U, KC_E,

        // open menu
        KC_ESC,

        // save
        KC_W,

        // confirm
        KC_ENT
    };

    if (i >= ARRAY_SIZE(mock_events)) {
        printf("ERROR: Exhausted mock events for the test\n");
        return KC_NO;
    }

    return mock_events[i++];
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return false;
    }

    keycode = mock_press();
    if (keycode == KC_NO) {
        return false;
    }

    return process_input_mode(keycode, record);
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

    static uint16_t timer = 0;
    if (timer_elapsed(timer) < 5000) {
        return;
    }
    timer = timer_read();

    lua_exec("house.lua");
}
