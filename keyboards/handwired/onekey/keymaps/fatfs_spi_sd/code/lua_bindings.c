// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "code/fatfs_helpers.h"

static lua_State *L;

static void create_files(void) {
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
        "    wait_us(50e3)\n"
        "    _f(args)\n"
        "end\n"
        "\n"
        "return _f",

        0
    );
}

static int exec_impl(lua_State *L) {
    const char *filepath = luaL_checkstring(L, 1);
    if (filepath == NULL) {
        printf("exec_impl: error (filepath arg was bad)\n");
        return 0;
    }

    // load the file
    char *content = read((char *)filepath, 0);
    if (content == NULL) {
        printf("exec_impl: error (couldn't read %s)\n", filepath);
        return 0;
    }

    // convert it into a lua function
    int ret = luaL_loadstring(L, content);
    if (ret != LUA_OK) {
        printf("exec_impl: error (loading file contents - %d)\n", ret);
        return 0;
    }

    // execute string, this creates a function to execute its code
    // f = loadstring(content)
    ret = lua_pcall(L, 0, 1, 0);
    if (ret != LUA_OK) {
        printf("exec_impl: error (executing loadstring - %d)\n", ret);
        return 0;
    }

    // execute it, and get the result from our actual code, a function to be executed
    // g = f()
    ret = lua_pcall(L, 0, 1, 0);
    if (ret != LUA_OK) {
        printf("exec_impl: error (executing custom Lua code, which returns the func to be run - %d)\n", ret);
        return 0;
    }

    // copy arguments (a table object) to the top of the stack, and call our func
    // g(args)
    lua_pushvalue(L, 2);
    ret = lua_pcall(L, 1, 0, 0);
    if (ret != LUA_OK) {
        printf("exec_impl: error (actual logic failed - %d)\n", ret);
        return 0;
    }

    return 0;
}

static int fatfs_read_file_impl(lua_State *L) {
    const char *filepath = luaL_checkstring(L, 1);

    if (filepath == NULL) {
        printf("fatfs_read_file_impl: error (filepath was empty)\n");
        lua_pushnil(L);
        return 1;
    }

    char *content = read((char *)filepath, 0);
    lua_pushstring(L, content);

    return 1;
}

void lua_setup(void) {
    create_files();

    extern lua_State *qmk_lua_newstate(void); // forward declaration
    L = qmk_lua_newstate();

    if (!L) {
        printf("Error creating the state\n");
        return;
    }

    // Add fatfs_read_file binding
    lua_register(L, "fatfs_read_file", fatfs_read_file_impl);

    // add exec binding
    lua_register(L, "exec", exec_impl);
}

void lua_exec(char *filepath) {
    lua_pushstring(L, filepath);
    lua_pushnil(L); // args parameter
    exec_impl(L);
}

void lua_kill(void) {
    lua_close(L);
}
