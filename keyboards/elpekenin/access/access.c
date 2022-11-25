// Copyright 2022 Pablo Martinez (@elpekenin)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "access.h"

#if defined(QUANTUM_PAINTER_ENABLE)
#    include "color.h"
#    include "graphics.h"
#    include "qp.h"
painter_device_t lcd;
#endif // QUANTUM_PAINTER_ENABLE

#if defined(RGB_MATRIX_ENABLE)
uint8_t key_selector_mode_last_key;
key_selector_direction_t key_selector_direction;
#endif // RGB_MATRIX_ENABLE

#if defined (TOUCH_SCREEN)
#    include "touch_driver.h"
touch_device_t touch_device;
#endif // TOUCH_SCREEN


void keyboard_post_init_kb(void) {
    debug_enable = true;

#if defined(DEFERRED_EXEC_ENABLE)
    // Define function so `defer_exec` doesn't crash the compiling
    uint32_t deferred_init(uint32_t trigger_time, void *cb_arg);

    // Defer init code so USB has started and we can receive console messages
    defer_exec(INIT_DELAY, deferred_init, NULL);
}

uint32_t deferred_init(uint32_t trigger_time, void *cb_arg) {
#endif // DEFERRED_EXEC_ENABLE

    dprint("---------- Init phase ----------\n");

    // =======
    // Power indicator
    setPinOutput(POWER_LED_PIN);
    writePinHigh(POWER_LED_PIN);

    // ==========
    // Peripherals
#if defined(QUANTUM_PAINTER_ENABLE)
    setPinOutput(LCD_BL_PIN);
    writePinHigh(LCD_BL_PIN);
    wait_ms(150); //Let it draw some power
    lcd = qp_ili9486_shiftreg_make_spi_device(_SCREEN_WIDTH, _SCREEN_HEIGHT, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, SPI_DIV, SPI_MODE);
    qp_init(lcd, _SCREEN_ROTATION);
    qp_rect(lcd, 0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1, HSV_BLACK, true);
    load_qp_resources();
    dprint("Display initialized\n");
#endif // QUANTUM_PAINTER_ENABLE

#if defined (TOUCH_SCREEN)
    static touch_driver_t touch_driver = {
        .width = _SCREEN_WIDTH,
        .height = _SCREEN_HEIGHT,
        .measurements = 1,
        .offset = 430,
        .scale = 3270,
        .rotation = (_SCREEN_ROTATION+2)%4,
        .upside_down = false,
        .spi_config = {
            .chip_select_pin = TOUCH_CS_PIN,
            .divisor = SPI_DIV,
            .lsb_first = false,
            .mode = SPI_MODE,
            .irq_pin = TOUCH_IRQ_PIN,
            .x_cmd = 0xD0,
            .y_cmd = 0x90
        },
    };

    touch_device = &touch_driver;
    touch_spi_init(touch_device);
    dprint("Touch initialized\n");
#endif // TOUCH_SCREEN

    dprint("\n---------- User code ----------\n");

    // =======
    // Call user code
    keyboard_post_init_user();

#if defined(DEFERRED_EXEC_ENABLE)
    return 0; //don't repeat the function
#endif // DEFERRED_EXEC_ENABLE
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

    return true;
}

#if defined(ONE_HAND_MODE)
#    if defined(POINTING_DEVICE_ENABLE)
report_mouse_t empty_mouse_report() {
    return report_mouse_t {
        .x = 0,
        .y = 0,
        .h = 0,
        .v = 0,
        .buttons = 0
    }
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (mouse_report.buttons) {
        // TODO: Change so it actually updates matrix, and stuff other than basic keycodes work
        uint8_t current_layer = get_highest_layer(layer_state);
        tap_code(keymaps[current_layer][key_selector_mode_last_key]);

        return empty_mouse_report();
    }

    // Update the direction
    if (abs(mouse_report.x) > abs(mouse_report.y)) {
        if (mouse_report.x > 0)
            key_selector_direction = DIRECTION_RIGHT;
        else
            key_selector_direction = DIRECTION_LEFT;
    } else {
        if (mouse_report.y > 0)
            key_selector_direction = DIRECTION_UP;
        else
            key_selector_direction = DIRECTION_DOWN;
    }

    return empty_mouse_report();
}
#    endif // POINTING_DEVICE_ENABLE

#    if defined (TOUCH_SCREEN)
void screen_one_hand(touch_report_t touch_report) {
    if (!touch_report.pressed) {
        return;
    }

    int16_t x = touch_report.x - SCREEN_WIDTH/2;
    int16_t y = touch_report.y - SCREEN_HEIGHT/2;

    if (x > 30) {
        key_selector_direction = y > 0 ? DIRECTION_RIGHT : DIRECTION_LEFT;
    } else if (x < -30){
        key_selector_direction = y > 0 ? DIRECTION_UP : DIRECTION_DOWN;
    }
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    // Wait until it is initialized
    if (touch_device == NULL){
        return false;
    }

    // Get touchscreen status
    touch_report_t touch_report = get_spi_touch_report(touch_device);

    // Translate index to matrix coords
    // TODO: Improve this to work with empty spots, etc
    uint8_t row = key_selector_mode_last_key / MATRIX_COLS;
    uint8_t col = key_selector_mode_last_key % MATRIX_COLS;

    // Convert left-based to center-based coord
    int16_t x = touch_report.x - SCREEN_WIDTH/2;

    // Store previous state for comparations
    matrix_row_t previous = current_matrix[row];

    // If screen is not pressed, neither will the key
    if (!touch_report.pressed) {
        current_matrix[row] &= ~(1 << col);
    }
    // If pressed and in zone, press the key
    else if (-30 < x && x < 30) {
        current_matrix[row] |= 1 << col;
    }

    return previous != current_matrix[row];
}
#    endif // TOUCH_SCREEN
#endif // ONE_HAND_MODE
