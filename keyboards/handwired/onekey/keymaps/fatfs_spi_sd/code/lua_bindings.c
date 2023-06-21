// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "code/fatfs_helpers.h"

static lua_State *L;

static void create_files(void) {
    write(
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
        "    dprint(\"LUA Executing path: '\" .. path .. \"'\")\n"
        "    f = load(code)\n"
        "    g = f()\n"
        "    dprint(' ')\n"
        "    g(args)\n"
        "end\n",

        0
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
        "return _f",

        0
    );
}

int fatfs_read_file_impl(lua_State *L) {
    const char *arg = luaL_checkstring(L, 1); // first arg is the path to read from

    char *content = read((char *)arg, 0);
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

    // load exec.lua code
    char *exec_code = read("exec.lua", 0);
    if (luaL_loadstring(L, exec_code) != LUA_OK) {
        printf("luaL_loadstring failed\n");
        return;
    }
    if (lua_pcall(L, 0, 1, 0) != LUA_OK) {
        printf("lua_pcall failed\n");
        return;
    }
    lua_pop(L, lua_gettop(L));

    // Add fatfs_read_file binding
    lua_register(L, "fatfs_read_file", fatfs_read_file_impl);
}

void lua_exec(char *filepath) {
    lua_getglobal(L, "exec");
    lua_pushstring(L, filepath); // path parameter
    lua_pushnil(L); // args parameter
    lua_pcall(L, 2, 0, 0);
}

void lua_kill(void) {
    lua_close(L);
}
