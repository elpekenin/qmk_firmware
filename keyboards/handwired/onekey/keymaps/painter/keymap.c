// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "color.h"
#include "qp.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(KC_A)
};

painter_device_t lcd;

uint32_t deferred_init(uint32_t trigger_time, void *cb_arg) {
    setPinOutput(LCD_BL_PIN);
    writePinLow(LCD_BL_PIN);

    dprintf("Hello world!\n");
    lcd = qp_st7735_make_spi_device(80, 160, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 256, 0);
    qp_init(lcd, QP_ROTATION_0);
    qp_rect(lcd, 0, 0, 79, 159, HSV_RED, true);

    return 0;
}

void keyboard_post_init_user(void) {
    defer_exec(3000, deferred_init, NULL);
}
