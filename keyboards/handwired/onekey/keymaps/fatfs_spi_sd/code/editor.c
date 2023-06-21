// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp.h"
#include "color.h"

#include "code/input.h"
#include "code/lua_bindings.h"
#include "code/fatfs_helpers.h"

static bool     redraw_area = true;
static bool     redraw      = true;
static char     text_buffer[TEXT_BUFFER_LEN]; // file contents
static char     temp_buff[TEMP_BUFF_LEN]; // make substrings (lines) for drawtext
static uint16_t text_buffer_index = 0; // user location
static char     filepath[INPUT_BUF_LEN + 1] = {0};

void editor_open(char *_filepath) {
    memset(filepath, 0, INPUT_BUF_LEN);
    strcpy(filepath, _filepath);

    memset(text_buffer, 0, TEXT_BUFFER_LEN);
    read_into(filepath, 0, text_buffer);

    redraw = true;
}

void editor_move(uint16_t keycode) {
    switch (keycode) {
        case KC_LEFT:
            text_buffer_index--;
            break;

        case KC_RIGHT:
            text_buffer_index++;
            break;

        case KC_UP:
        case KC_DOWN:
            // TODO:
            break;
    };

    redraw = true;
}

void editor_write_char(char c) {
    uint16_t len = strlen(text_buffer);

    // move rest of text to the right
    for (uint8_t i = len - 1 - text_buffer_index; i > 0; --i) {
        text_buffer[i] = text_buffer[i - 1];
    }

    text_buffer[text_buffer_index++] = c;

    redraw = true;
}

void editor_flush(painter_device_t device, painter_font_handle_t font) {
    if (!redraw) {
        return;
    }

    redraw = false;

    uint16_t y = 0;
    uint8_t  fh = font->line_height;

    uint8_t temp_buff_index = 0;

    uint16_t len = strlen(text_buffer);

    for (uint16_t i = 0; i < len; ++i) {
        // current position marker
        if (i == text_buffer_index) {
            temp_buff[temp_buff_index++] = '|'; // TODO: thinner cursor indicator
        }

        char c = text_buffer[i];

        if (c == '\r')
            continue;

        // end of line, print
        if (c == '\n') {
            temp_buff[temp_buff_index] = 0; // terminate the string before drawing
            qp_drawtext(device, 0, y, font, temp_buff);
            temp_buff_index = 0;
            y += fh;
            continue;
        }

        // append char
        temp_buff[temp_buff_index++] = c;
    }

    // leftover text
    if (temp_buff_index) {
        temp_buff[temp_buff_index++] = 0; // terminate it
        qp_drawtext(device, 0, y, font, temp_buff);
    }

    uint16_t sw;
    uint16_t sh;
    qp_get_geometry(device, &sw, &sh, NULL, NULL, NULL);

    // menu on the bottom is black on white
    if (redraw_area) {
        redraw_area = false;

        // black area for text
        qp_rect(device, 0, 0, sw, sh - (2 * fh + 10), HSV_BLACK, true);

        // white area for info
        qp_rect(device, 0, sh - (2 * fh + 10), sw, sh, HSV_WHITE, true);

    }

    // status
    input_mode_t mode  = get_input_mode();
    char *       input = get_input_buffer();

    // mode
    char mode_str[20] = {0};
    switch (mode) {
        case NONE:
            strcpy(mode_str, "Idle");
            break;

        case PATH:
            strcpy(mode_str, "Selecting file");
            break;

        case EDIT:
            strcpy(mode_str, "Editing");
            break;

        case MENU:
            strcpy(mode_str, "In menu");
            break;

        default:
            printf("ERROR: how the hell are we in mode %d\n", mode);
    }

    static int16_t last_mw = 0;
    int16_t mw = qp_textwidth(font, mode_str);

    if (last_mw > mw) {
        qp_rect(device, sw - last_mw, sh - 2 * fh, sw - mw, sh - fh, HSV_WHITE, true);
    }
    last_mw = mw;

    qp_drawtext_recolor(device, sw - mw, sh - 2 * fh, font, mode_str, HSV_BLACK, HSV_WHITE);

    // file
    char *file;
    switch (mode) {
        case PATH:
        case MENU:
            file = input;
            break;

        default:
            file = filepath;
    };

    static int16_t last_fw = 0;
    int16_t fw = qp_textwidth(font, file);

    if (last_fw > fw) {
        qp_rect(device, sw - last_fw, sh - 2 * fh, sw - fw, sh - fh, HSV_WHITE, true);
    }
    last_fw = fw;

    qp_drawtext_recolor(device, sw - fw, sh - fh, font, file, HSV_BLACK, HSV_WHITE);
}

void editor_menu_selection(void) {
    char *s = get_input_buffer();
    char c = s[0];

    // TODO: Multi-option support

    switch (c) {
        case 'q':
            close();
            break;

        case 'w':
            write(filepath, text_buffer, 0);
            break;

        case 'e':
            write(filepath, text_buffer, 0);
            lua_exec(filepath);
            break;

        default:
            printf("ERROR: %c is not a valid action, closing without saving\n", c);
            close();
    }

    memset(filepath, 0, INPUT_BUF_LEN);
    memset(text_buffer, 0, TEXT_BUFFER_LEN);

    redraw = true;
    redraw_area = true;
}

void editor_needs_redraw(void) {
    redraw = true;
}
