// Copyright 2020 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

#include "qp.h"
#include "fira_code.qff.h"

#include "color.h"

#include "helpers.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(KC_A)
};

FATFS FatFs;
FIL Fil;

lua_State *L;

enum custom_keycodes { EDIT_FILE = QK_USER };

typedef enum {
    NONE,
    WRITING_PATH,
    EDITING,
    MENU
} input_mode_t;
input_mode_t input_mode = NONE;

char user_input[20];
uint8_t user_input_index;

char filepath[20];

void clear_input_vars(void) {
    user_input_index = 0;
    user_input[0] = 0;
}

painter_device_t device;
painter_font_handle_t font;

static char text_buffer[TEXT_BUFFER_LEN];
uint16_t text_buffer_index = 0;

bool redraw;

uint16_t mock_press(void) {
    static uint8_t i = 0;

    uint16_t mock_events[] = {
         // open file
        EDIT_FILE,

        // filepath
        KC_T, KC_E, KC_S, KC_T, KC_DOT, KC_T, KC_X, KC_T,

        // confirm
        KC_ENT,

        // write -- B <move left> A <enter>
        KC_MINUS, KC_MINUS,  KC_SPC, KC_B, KC_LEFT, KC_A, KC_ENT,

        // open menu
        KC_ESC,

        // write
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

char keycode_to_char(uint16_t keycode) {
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

void write_char(char c) {
    uint16_t len = strlen(text_buffer);

    // move rest of text to the right
    for (uint8_t i = len - 1 - text_buffer_index; i > 0; --i) {
        text_buffer[i] = text_buffer[i - 1];
    }

    text_buffer[text_buffer_index++] = c;

    for (uint8_t i = 0; i < len + 1; ++i) {
        char c = text_buffer[i];

        if (c == '\n')
            c = ' ';

        printf("%c", c);
    }
    printf("\n");

    redraw = true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return false;
    }

    keycode = mock_press();
    if (keycode == KC_NO) {
        return false;
    }

    char c;
    switch (keycode) {
        case EDIT_FILE:
            switch (input_mode) {
                case NONE:
                    input_mode = WRITING_PATH;
                    break;

                case WRITING_PATH:
                case EDITING:
                case MENU:
                    break;
            }
            return false;

        case KC_ESC:
            switch (input_mode) {
                case NONE:
                    break;

                case WRITING_PATH:
                    input_mode = NONE;
                    break;

                case EDITING:
                    input_mode = MENU;
                    memset(user_input, 0, ARRAY_SIZE(user_input));
                    break;

                case MENU:
                    input_mode = EDITING;
                    break;
            }
            return false;


        case KC_ENT:
            switch (input_mode) {
                case NONE:
                    break;

                // finished writing path
                case WRITING_PATH:
                    input_mode = EDITING;

                    strcpy(filepath, user_input);
                    memset(text_buffer, 0, ARRAY_SIZE(text_buffer));
                    char *read_buff = read(&Fil, filepath);

                    // if file exits, copy its content
                    if (read_buff != NULL) {
                        strcpy(text_buffer, read_buff);
                    }

                    redraw = true;
                    clear_input_vars();

                    break;

                case EDITING:
                    write_char('\n');
                    redraw = true;
                    break;

                // finished selecting op
                case MENU:
                    input_mode = NONE;

                    c = user_input[0];
                    switch (c) {
                        case 'w':
                            write(&Fil, filepath, text_buffer);
                            break;

                        case 'q':
                            close(&Fil);
                            break;

                        // write and run
                        case 'e':
                            write(&Fil, filepath, text_buffer);

                            lua_getglobal(L, "exec");
                            lua_pushstring(L, filepath); // path parameter
                            lua_pushnil(L); // args parameter

                            break;

                        // any weird iactionnput, just close
                        default:
                            printf("ERROR: %c is not a valid action, closing without saving\n", c);
                            close(&Fil);
                            break;
                    }

                    redraw = true;
                    clear_input_vars();

                    break;
            }
            return false;

        case KC_LEFT:
        case KC_RIGHT:
            switch (input_mode) {
                case EDITING:
                    text_buffer_index += (keycode == KC_LEFT) ? -1 : 1;
                    redraw = true;
                    break;

                default:
                    break;
            }
            return false;

        case KC_UP:
        case KC_DOWN:
            // TODO
            break;

        // most keys
        default:
            c = keycode_to_char(keycode);

            if (c == 0) {
                return false;
            }

            switch (input_mode) {
                case NONE:
                    break;

                case WRITING_PATH:
                    if (user_input_index >= ARRAY_SIZE(user_input) - 1) {
                        printf("ERROR: Path too long\n");
                        clear_input_vars();
                        break;
                    }

                    user_input[user_input_index++] = c;
                    strcpy(filepath, user_input);
                    break;

                case MENU:
                    if (user_input_index > 0) {
                        printf("ERROR: Mode is a single letter\n");
                        clear_input_vars();
                        break;
                    }

                    user_input[user_input_index++] = c;
                    break;

                case EDITING:
                    write_char(c);
                    break;
            }
            return false;
    }

    return true;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

bool oled_task_user(void) {
    switch (input_mode) {
        case NONE:
            oled_write_ln("Idle", false);
            break;

        case WRITING_PATH:
            oled_write_ln("Writing path", false);
            break;

        case EDITING:
            oled_write("Editing: ", false); oled_write_ln(filepath, false);
            oled_write_ln(user_input, false);
            break;

        case MENU:
            oled_write("Menu: ", false); oled_write_ln(user_input, true);
            break;
    }

    oled_write("\n\nInput: ", false); oled_write_ln(user_input, false);
    return false;
}

uint32_t deferred_init(uint32_t t, void* cb_arg) {
    // FatFS setup
    f_mount(&FatFs, "", 0);

    // =====
    // Lua

    // function to execute a file
    write(
        &Fil,
        "exec.lua",

        "function exec(path, args)\n"
        "    -- guard clause the path value\n"
        "    if path == nil or path == '' then\n"
        "        dprint('LUA ERROR: Gotta pass a path to exec')\n"
        "        return\n"
        "    end\n"
        "\n"
        "    -- load(code) returns a function which executes the file's contents\n"
        "    -- the file itself returns another function, retrieved with g = f()\n"
        "    code = fatfs_read_file(path)\n"
        "    dprint(\"LUA Executing path: '\" .. path .. \"' with content: '\" .. code .. \"'\")\n"
        "    f = load(code)\n"
        "    g = f()\n"
        "    g(args)\n"
        "end\n"
    );

    // example function to be `exec`
    write(
        &Fil,
        "recurse.lua",

        "function _f(args)\n"
        "    -- 1st iteration, start value\n"
        "    if args == nil then\n"
        "        args = {}\n"
        "        args[0] = 10\n"
        "    end\n"
        "\n"
        "    n = args[0]\n"
        "    dprint('Recursive with value: ' .. n)\n"
        "\n"
        "    -- base case, gotta end somewhere\n"
        "    if n == 0 then\n"
        "        return\n"
        "    end\n"
        "\n"
        "    args[0] = n - 1\n"
        "    -- calls itself again, with n-1 \n"
        "    wait_us(1e6)\n"
        // should work but fails in non-deterministic iterations
        // "    exec('recurse.lua', args)\n"
        "    _f(args)\n"
        "end\n"
        "\n"
        "return _f"
    );

    f_unlink("text.txt");

    write(
        &Fil,
        "test.txt",

        ""
    );

    extern lua_State *qmk_lua_newstate(void); // forward declaration
    L = qmk_lua_newstate();

    if (!L) {
        printf("Error creating the state\n");
        return 0;
    }

    // load exec.lua code
    char *exec_code = read(&Fil, "exec.lua");
    if (luaL_loadstring(L, exec_code) != LUA_OK) {
        printf("luaL_loadstring failed\n");
        return 0;
    }
    if (lua_pcall(L, 0, 1, 0) != LUA_OK) {
        printf("lua_pcall failed\n");
        return 0;
    }
    lua_pop(L, lua_gettop(L));

    // Add fatfs_read_file binding
    lua_register(L, "fatfs_read_file", fatfs_read_file_impl);

    // Quantum Painter
    device = qp_ili9486_make_spi_waveshare_device(320, 480, ILI9486_CS_PIN, DC_PIN, RST_PIN, SPI_DIV, SPI_MODE);
    font = qp_load_font_mem(font_fira_code);
    qp_init(device, QP_ROTATION_180);
    qp_rect(device, 0, 0, 320, 480, HSV_BLACK, true);
    qp_rect(device, 10, 10, 30, 30, HSV_WHITE, false);
    qp_drawtext(device, 0, 50, font, "hello world");

    // Cleanup
    // lua_close(L);

    return 0;
}

void keyboard_post_init_user(void) {
    debug_enable   = true;
    debug_matrix   = false;
    debug_keyboard = false;

    defer_exec(5000, deferred_init, NULL);
}

void housekeeping_task_user(void) {
    if (redraw) {
        redraw = false;
        draw_text_buffer(device, font, text_buffer, text_buffer_index);
    }
}
