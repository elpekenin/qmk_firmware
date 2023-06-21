// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keycode.h"

#include "code/input.h"
#include "code/editor.h"
#include "code/fatfs_helpers.h"

enum custom_keycodes { OPEN_EDITOR = QK_USER };

static input_mode_t input_mode = NONE;

static uint8_t user_input_index;
static char user_input[INPUT_BUF_LEN + 1] = {0};
static void clear_user_input(void) {
    user_input_index = 0;
    memset(user_input, 0, INPUT_BUF_LEN);
}

static void user_input_append(char c) {
    user_input[user_input_index++] = c;
    user_input[user_input_index]   = '\0';
}

uint16_t mock_press(void) {
    static uint8_t i = 0;

    uint16_t mock_events[] = {
         // open file
        OPEN_EDITOR,

        // filepath
        KC_R, KC_E, KC_C, KC_U, KC_R, KC_S, KC_E, KC_DOT, KC_L, KC_U, KC_A,

        // confirm
        KC_ENT,

        // move around
        KC_RIGHT, KC_RIGHT, KC_RIGHT, KC_LEFT,

        // open menu
        KC_ESC,

        // write
        KC_E,

        // confirm
        KC_ENT
    };

    if (i >= ARRAY_SIZE(mock_events)) {
        printf("ERROR: Exhausted mock events for the test\n");
        return KC_NO;
    }

    return mock_events[i++];
}


static char keycode_to_char(uint16_t keycode) {
    switch (keycode) {
        case KC_A ... KC_Z:
            return keycode - KC_A + 'a';

        case KC_1 ... KC_0:
            return keycode - KC_1 + '0';

        case KC_DOT:
            return '.';

        case KC_SLSH:
            return '/';

        case KC_MINUS:
            return '-';

        case KC_SPC:
            return ' ';

        default:
            return 0;
    }
}

bool none_hander(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case OPEN_EDITOR:
            input_mode = PATH;
            return false;

        default:
            return true;
    };
}

bool path_handler(uint16_t keycode, keyrecord_t *record) {
    char c;

    switch (keycode) {
        case KC_ESC:
            input_mode = NONE;

            clear_user_input();
            editor_needs_redraw();

            return false;

        case KC_ENT:
            input_mode = EDIT;

            editor_open(user_input);
            clear_user_input();

            return false;

        default:
            c = keycode_to_char(keycode);

            // unknown keycode
            if (c == 0) {
                return false;
            }

            user_input_append(c);

            editor_needs_redraw();

            return false;
    };
}

bool edit_handler(uint16_t keycode, keyrecord_t *record) {
    char c;

    switch (keycode) {
        case KC_ESC:
            input_mode = MENU;
            editor_needs_redraw();
            return false;

        case KC_ENT:
            editor_write_char('\n');
            return false;

        case KC_LEFT:
        case KC_RIGHT:
        case KC_UP:
        case KC_DOWN:
            editor_move(keycode);
            return false;

        default:
            c = keycode_to_char(keycode);

            if (c == 0) {
                return false;
            }

            editor_write_char(c);
            return false;
    }
}

bool menu_handler(uint16_t keycode, keyrecord_t *record) {
    char c;

    switch (keycode) {
        case KC_ESC:
            input_mode = EDIT;
            clear_user_input();
            return false;

        case KC_ENT:
            input_mode = NONE;
            editor_menu_selection();
            clear_user_input();
            return false;

        default:
            c = keycode_to_char(keycode);

            // unknown keycode
            if (c == 0) {
                return false;
            }

            user_input_append(c);
            return false;
    };
}

static const process_func_t handlers[__N_MODES] = {
    [NONE] = &none_hander,
    [PATH] = &path_handler,
    [EDIT] = &edit_handler,
    [MENU] = &menu_handler,
};

bool process_input_mode(uint16_t keycode, keyrecord_t *record) {
    process_func_t handler = handlers[input_mode];
    return handler(keycode, record);
}

char *get_input_buffer(void) {
    return user_input;
}

input_mode_t get_input_mode(void) {
    return input_mode;
}
