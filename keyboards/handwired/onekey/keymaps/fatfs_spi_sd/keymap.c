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

    // Test content to be read
    write(
        "content.txt",
    
        "this file was read from lua"
    );

    // lua code to define a test function
    write(
        "test.lua",

        "function lua_test_fn(path)\n"
        "    dprint('Printing from lua')\n"
        "    dprint('-----------------')\n"
        "    dprint(\"'\" .. path .. \"' contains: '\" .. fatfs_read_file(path) .. \"'\")\n"
        "end\n"
    );

    // Read file content and convert it into a function
    char *lua_code = read("test.lua");

    extern lua_State *qmk_lua_newstate(void); // forward declaration
    lua_State *L = qmk_lua_newstate();

    if (!L) {
        printf("Error creating the state\n");
        return 0;
    }

    if (luaL_loadstring(L, lua_code) != LUA_OK) {
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

    // Call it
    lua_getglobal(L, "lua_test_fn");
    lua_pushstring(L, "content.txt"); // path parameter
    lua_pcall(L, 1, 0, 0);

    // Cleanup
    lua_close(L);

    return 0;
}

void keyboard_post_init_user(void) {
    defer_exec(5000, deferred_init, NULL);
}
