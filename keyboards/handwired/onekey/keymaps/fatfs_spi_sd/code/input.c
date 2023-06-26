// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "code/input.h"
#include "code/editor.h"
#include "code/fatfs_helpers.h"

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

static char keycode_to_letter(uint16_t keycode) {
    bool caps  = host_keyboard_led_state().caps_lock;
    bool shift = __mods & MOD_MASK_SHIFT;

    if (caps ^ shift) {
        return keycode - KC_A + 'A';
    }

    return keycode - KC_A + 'a';
}

char keycode_to_char(uint16_t keycode) {
    switch (keycode) {
        case KC_A ... KC_Z:
            return keycode_to_letter(keycode);

        case KC_1 ... KC_0:
            return keycode - KC_1 + '0';

        case KC_DOT:
            return '.';

        case KC_SLSH:
            return '/';

        case KC_MINUS:
            return '-';

        case KC_UNDERSCORE:
            return '_';

        case KC_SPC:
            return ' ';

        default:
            return 0;
    }
}

static bool append_to_input(uint16_t keycode) {
    char c = keycode_to_char(keycode);

    // unknown keycode, let QMK handle it
    if (c == 0) {
        return false;
    }

    user_input_append(c);
    editor_menu_needs_redraw();

    return true;
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
    switch (keycode) {
        case KC_ESC:
            input_mode = NONE;

            clear_user_input();
            editor_menu_needs_redraw();

            return false;

        case KC_ENT:
            input_mode = EDIT;

            editor_open(user_input);
            clear_user_input();

            return false;

        default:
            return append_to_input(keycode);
    };
}

bool edit_handler(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_ESC:
            input_mode = MENU;
            editor_menu_needs_redraw();
            return false;

        default:
            return editor_handle(keycode);
    }
}

bool menu_handler(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_ESC:
            input_mode = EDIT;
            clear_user_input();
            editor_menu_needs_redraw();
            return false;

        case KC_ENT:
            input_mode = NONE;
            editor_menu_selection();
            clear_user_input();
            return false;

        default:
            return append_to_input(keycode);
    };
}

typedef bool (*process_func_t)(uint16_t k, keyrecord_t *kr);

static const process_func_t handlers[__N_MODES] = {
    [NONE] = &none_hander,
    [PATH] = &path_handler,
    [EDIT] = &edit_handler,
    [MENU] = &menu_handler,
};

bool process_input_mode(uint16_t keycode, keyrecord_t *record) {
    /* This should be
     *
     * case KC_CAPS:
     *    return true;
     *
     * But can't do that due to mocking keycodes
     */
    if (keycode == KC_CAPS) {
        tap_code(KC_CAPS);
        return false;
    }

    process_func_t handler = handlers[input_mode];
    return handler(keycode, record);
}

char *get_input_buffer(void) {
    return user_input;
}

input_mode_t get_input_mode(void) {
    return input_mode;
}
