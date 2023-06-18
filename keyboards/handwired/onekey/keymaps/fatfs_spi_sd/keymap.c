// Copyright 2020 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

#include "ff.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(KC_A)
};

FATFS FatFs;
FIL Fil;

void close(void) {
    FRESULT fr;
    fr = f_close(&Fil);
    if (fr != FR_OK) {
        printf("ERROR: Couldnt close a file, weird...\n");
    }
}

void _write(char *path, BYTE *buff, UINT btw) {
    FRESULT fr = f_open(&Fil, path, FA_WRITE | FA_CREATE_ALWAYS);

    if (fr != FR_OK) {
        printf("ERROR: couldnt open '%s' in write mode\n", path);
        return;
    }

    UINT bw;
    f_write(&Fil, buff, btw, &bw);

    if (bw != btw) {
        printf("WARN: bytes written != bytes to write\n");
    }

    close();
}

BYTE *_read(char *path, UINT btr) {
    static BYTE read_buff[READ_BUFFER_SIZE] = {0};

    FRESULT fr = f_open(&Fil, path, FA_READ);

    if (fr != FR_OK) {
        printf("ERROR: couldnt open '%s' in read mode\n", path);
        return NULL;
    }

    // If size not provided, find out the file size
    if (btr == 0) {
        btr = f_size(&Fil);
    }

    if (btr > READ_BUFFER_SIZE) {
        printf("ERROR: read buffer is not big enough for '%s'\n", path);
        return NULL;
    }

    UINT br;
    f_read(&Fil, read_buff, btr, &br);

    if (br != btr) {
        printf("WARN: bytes read != bytes to read\n");
    }

    close();

    return read_buff;
}

#define write(path, string) _write((path), (BYTE *)(string), sizeof((string)))
#define read(path) (char *)_read((path), 0)

// implemntation of fatfs_read_file
static int fatfs_read_file_impl(lua_State *L) {
    const char *arg = luaL_checkstring(L, 1); // first arg is the path to read from

    char *content = read((char *)arg);
    lua_pushstring(L, content);

    return 1;
}

uint32_t deferred_init(uint32_t t, void* cb_arg) {
    f_mount(&FatFs, "", 0);

   // function to execute a file
    write(
        "exec.lua",

        "function exec(path, args)\n"
        "    -- guard clause the path value\n"
        "    if path == nil or path == '' then\n"
        "        dprint('ERROR: Gotta pass a path to exec')\n"
        "        return\n"
        "    end\n"
        "\n"
        "    -- load(code) returns a function which executes the file's contents\n"
        "    -- the file itself returns another function, retrieved with g = f()\n"
        "    code = fatfs_read_file(path)\n"
        "    f = load(code)\n"
        "    g = f()\n"
        "    g(args)\n"
        "end\n"
    );

    // example function to be `exec`
    write(
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

    extern lua_State *qmk_lua_newstate(void); // forward declaration
    lua_State *L = qmk_lua_newstate();

    if (!L) {
        printf("Error creating the state\n");
        return 0;
    }

    // load exec.lua code
    char *exec_code = read("exec.lua");
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

    // Call
    lua_getglobal(L, "exec");
    lua_pushstring(L, "recurse.lua"); // path parameter
    lua_pushnil(L); // args parameter
    lua_pcall(L, 2, 0, 0);

    // Cleanup
    lua_close(L);

    return 0;
}

void keyboard_post_init_user(void) {
    defer_exec(5000, deferred_init, NULL);
}
