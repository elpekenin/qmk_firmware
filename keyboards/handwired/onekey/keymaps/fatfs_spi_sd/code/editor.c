// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp.h"
#include "color.h"

#include "code/editor.h"
#include "code/lua_bindings.h"
#include "code/fatfs_helpers.h"

enum file_actions {
    FILE_WRITE = (1 << 0),
    FILE_CLOSE = (1 << 1),
    FILE_EXEC  = (1 << 2),
};

static bool     redraw_area = true;
static bool     redraw_menu = true;
static bool     redraw_text = true;
static char     text_buffer[TEXT_BUFFER_LEN]; // file contents
static char     temp_buff[TEMP_BUFF_LEN]; // make substrings (lines) for drawtext
static uint16_t text_buffer_index; // user location
static char     filepath[INPUT_BUF_LEN] = {0};

// ===== Redraw API
void editor_area_needs_redraw(void) {
    redraw_area = true;
}

void editor_menu_needs_redraw(void) {
    redraw_menu = true;
}

void editor_text_needs_redraw(void) {
    redraw_text = true;
}

// ===== Helper funcs for localization
static bool find_next_newline(uint16_t start_pos, uint16_t *index) {
    *index = start_pos;

    while (text_buffer[*index] != '\n') {
        *index += 1;

        // stop if we find a string terminator, or run out of buffer
        if (*index >= ARRAY_SIZE(text_buffer) || text_buffer[*index] == '\0') {
            return false;
        }
    }

    return true;
}

static bool find_prev_newline(uint16_t start_pos, uint16_t *index) {
    *index = start_pos - 1;

    while (text_buffer[*index] != '\n') {
        *index -= 1;

        // dont go backwards further than the start of the buffer
        if (*index == 0) {
            return false;
        }
    }

    return true;
}

static uint16_t get_current_col(void) {
    uint16_t i;
    find_prev_newline(text_buffer_index, &i);

    uint16_t col = text_buffer_index - i;

    if (col > text_buffer_index) {
        return text_buffer_index;
    }

    return col;
}

// ===== Event handling
static void move_left(void) {
    text_buffer_index--;
}

static void move_right(void) {
    text_buffer_index++;

    // TODO: move word rigth/left
    // if (__mods & MOD_MASK_CTRL) {
}

static void move_up(void) {
    uint16_t col = get_current_col();

    if (text_buffer_index == col) {
        // on first line, can't move upwards
        return;
    }

    uint16_t start_of_prev;
    uint16_t end_of_prev = text_buffer_index - col;
    find_prev_newline(end_of_prev, &start_of_prev);

    // eg: can't move to 10th col if prev row has 8 chars, clip it
    uint16_t prev_cols = end_of_prev - start_of_prev;
    col = MIN(col, prev_cols);

    text_buffer_index = start_of_prev + col - 1;
}

static void move_down(void) {
    uint16_t col = get_current_col() - 1;

    uint16_t end_of_curr;
    if (!find_next_newline(text_buffer_index, &end_of_curr)) {
        // on last line, can't move down
        return;
    }
    end_of_curr += 1;

    uint16_t end_of_next;
    uint16_t start_of_next = end_of_curr;
    find_next_newline(start_of_next, &end_of_next);

    // eg: can't move to 10th col if next row has 8 chars, clip it
    uint16_t next_cols = end_of_next - start_of_next;
    col = MIN(col, next_cols);

    text_buffer_index = start_of_next + col;
}

static void editor_backspace(void) {
    if (text_buffer_index == 0) {
        return;
    }

    uint16_t len = strlen(text_buffer);

    // also moves the \0 backwards
    for (uint16_t i = text_buffer_index - 1; i < len; ++i) {
        text_buffer[i] = text_buffer[i + 1];
    }

    move_left();
}

static void editor_delete(void) {
    move_right();
    editor_backspace();
}

static void editor_tab(void) {
    for (uint8_t i = 0; i < TAB_SIZE; ++i) {
        move_right();
    }
}

static bool editor_write(uint16_t keycode) {
    char c = keycode_to_char(keycode);

    // unknown keycode, let QMK handle it
    if (c == 0) {
        return true;
    }

    uint16_t len = strlen(text_buffer);

    // shift to the rigth to make space
    memmove(&text_buffer[text_buffer_index] + 1, &text_buffer[text_buffer_index], len - text_buffer_index);
    text_buffer[text_buffer_index++] = c;

    editor_text_needs_redraw();

    return false;
}

// ===== Wrapper logic for all small funcs
typedef void (*process_func_t)(void);
typedef struct keycode_func_map_t {
    uint16_t       keycode;
    process_func_t func;
} keycode_func_map_t;

static keycode_func_map_t handlers[] = {
    {KC_LEFT,  &move_left},
    {KC_RIGHT, &move_right},
    {KC_UP,    &move_up},
    {KC_DOWN,  &move_down},
    {KC_BSPC,  &editor_backspace},
    {KC_DEL,   &editor_delete},
    {KC_TAB,   &editor_tab},
};

bool editor_handle(uint16_t keycode) {
    // try and find "special" handlert func
    for (uint8_t i = 0; i < ARRAY_SIZE(handlers); ++i) {
        keycode_func_map_t handler = handlers[i];

        // these are moving the cursor and deleting
        // always need redraw
        if (keycode == handler.keycode) {
            handler.func();
            editor_text_needs_redraw();
            return false;
        }
    }

    // if not found, use default one (write char)
    return editor_write(keycode);
}

// ===== Open a new file
void editor_open(char *_filepath) {
    memset(filepath, 0, ARRAY_SIZE(filepath));
    strcpy(filepath, _filepath);

    memset(text_buffer, 0, ARRAY_SIZE(text_buffer));
    fatfs_read_into(filepath, 0, text_buffer);

    text_buffer_index = 0;

    editor_area_needs_redraw();
    editor_menu_needs_redraw();
    editor_text_needs_redraw();
}

// ===== Deferred exec'ing the file allows to clear screen
static uint32_t deferred_file_exec(uint32_t trigger_time, void *cb_arg) {
    lua_exec(filepath);
    return 0;
}

// ===== Drawing
static void draw_line(painter_device_t device, painter_font_handle_t font, uint16_t *y, uint16_t sw, char *text) {
    uint16_t fh = font->line_height;

    int16_t lw = qp_drawtext(device, 0, *y, font, text);

    qp_rect(device, lw, *y, sw, *y + fh, HSV_BLACK, true); // make sure rest of the line is clean

    *y += fh;
}

static void draw_text(painter_device_t device, painter_font_handle_t font, uint16_t *y, uint16_t sw) {
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
            // terminate the string
            temp_buff[temp_buff_index] = 0;
            draw_line(device, font, y, sw, temp_buff);
            temp_buff_index = 0;
            continue;
        }

        // append char
        temp_buff[temp_buff_index++] = c;
    }

    // leftover text
    if (temp_buff_index) {
        temp_buff[temp_buff_index++] = 0; // terminate it
        draw_line(device, font, y, sw, temp_buff);
        temp_buff_index = 0;
    }
}

static void draw_status(painter_device_t device, painter_font_handle_t font, uint16_t sh, uint16_t sw) {
    uint16_t fh = font->line_height;

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

    uint16_t mode_start_x = sw - mw;
    uint16_t mode_start_y = sh - 2 * fh;

    if (last_mw > mw) {
        qp_rect(device, sw - last_mw, mode_start_y, mode_start_x, mode_start_y + fh, HSV_WHITE, true);
    }
    last_mw = mw;

    qp_drawtext_recolor(device, mode_start_x, mode_start_y, font, mode_str, HSV_BLACK, HSV_WHITE);

    // -----

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

    uint16_t file_start_x = sw - fw;
    uint16_t file_start_y = sh - fh;

    if (last_fw > fw) {
        qp_rect(device, sw - last_fw, file_start_y, file_start_x, file_start_y + fh, HSV_WHITE, true);
    }
    last_fw = fw;

    qp_drawtext_recolor(device, file_start_x, file_start_y, font, file, HSV_BLACK, HSV_WHITE);
}

// ==================================================================
void editor_flush(painter_device_t device, painter_font_handle_t font) {
    if (!redraw_text && !redraw_menu && !redraw_area) {
        return;
    }

    uint16_t fh = font->line_height;

    uint16_t sw;
    uint16_t sh;
    qp_get_geometry(device, &sw, &sh, NULL, NULL, NULL);

    uint16_t separator_y = sh - (2 * fh + 10);

    // background areas
    if (redraw_area) {
        redraw_area = false;

        qp_rect(device, 0, 0, sw, separator_y, HSV_BLACK, true);
        qp_rect(device, 0, separator_y, sw, sh, HSV_WHITE, true);
    }

    // editor text
    if (redraw_text) {
        redraw_text = false;

        uint16_t y = 0;
        draw_text(device, font, &y, sw);

        // bottom part of text area without text
        if (y < separator_y) {
            qp_rect(device, 0, y, sw, separator_y, HSV_BLACK, true);
        }
    }

    // editor status
    if (redraw_menu) {
        redraw_menu = false;

        // small gap between text and border
        sw -= 10;
        sh -= 5;

        draw_status(device, font, sh, sw);
    }
}

void editor_menu_selection(void) {
    char *s = get_input_buffer();

    uint8_t action_flags = 0;

    // collect all actions in the input
    while (*s++) {
        switch (*s) {
            case 'q':
            case 'Q':
                action_flags |= FILE_CLOSE;
                break;

            case 'w':
            case 'W':
                action_flags |= FILE_WRITE;
                break;

            case 'e':
            case 'E':
                action_flags |= FILE_EXEC;
                break;

            default:
                printf("ERROR: %c is not a valid action, closing without saving\n", *s);
        }
    }

    if (action_flags & FILE_EXEC) {
        defer_exec(200, deferred_file_exec, NULL);
    }

    if (action_flags & FILE_WRITE) {
        fatfs_write(filepath, text_buffer, 0);
    }

    if (action_flags & FILE_CLOSE) {
        memset(text_buffer, 0, ARRAY_SIZE(text_buffer));
        fatfs_close();

        redraw_text = true;
        editor_text_needs_redraw();
    }
}
