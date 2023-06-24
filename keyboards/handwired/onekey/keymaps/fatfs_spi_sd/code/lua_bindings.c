// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp.h"
#include "color.h"

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

    write(
        "house.lua",

        "function _f(args)\n"
        "    device_id = 0\n"
        "\n"
        "    geometry = qp_get_geometry(device_id)\n"
        "    w = geometry['width']\n"
        "    h = geometry['height']\n"
        "\n"
        "    qp_rect(\n"
        "        device_id,\n"
        "        w-30, h-80,\n"
        "        w-10, h-50,\n"
        "        HSV_RED,\n"
        "        true\n"
        "    )\n"
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

    // create a function which executes this string
    // f = loadstring(content)
    int ret = luaL_loadstring(L, content);
    if (ret != LUA_OK) {
        printf("exec_impl: error (executing loadstring: %d)\n", ret);
        return 0;
    }

    // execute string, this returns our actual function
    // g = f()
    ret = lua_pcall(L, 0, 1, 0);
    if (ret != LUA_OK) {
        printf("exec_impl: error (getting the custom func: %d)\n", ret);
        return 0;
    }

    // execute it
    // g(args)
    lua_pushvalue(L, 2);
    ret = lua_pcall(L, 1, 0, 0);
    if (ret != LUA_OK) {
        printf("exec_impl: error (running custom func: %d)\n", ret);
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

static void register_colors(void) {
    // TODO: More dynamic (code-gen?)
    HSV  colors[] = {{HSV_RED}, {HSV_BLUE}};
    char *names[] = {"HSV_RED", "HSV_blue"};

    for (uint8_t i = 0; i < ARRAY_SIZE(colors); ++i) {
        HSV color = colors[i];

        // create table for {h, s, v}
        lua_newtable(L);

        // fill it with values
        lua_pushinteger(L, color.h);
        lua_seti(L, -2, 1);

        lua_pushinteger(L, color.s);
        lua_seti(L, -2, 2);

        lua_pushinteger(L, color.v);
        lua_seti(L, -2, 3);

        // set the global name
        lua_setglobal(L, names[i]);
    }
}

static int lua_qp_rect(lua_State *L) {
    const uint8_t  device_id = luaL_checkinteger(L, 1);
    const uint16_t left      = luaL_checkinteger(L, 2);
    const uint16_t top       = luaL_checkinteger(L, 3);
    const uint16_t right     = luaL_checkinteger(L, 4);
    const uint16_t bottom    = luaL_checkinteger(L, 5);
    const bool     filled    = lua_toboolean(L, 7);

    // unpack color table
    lua_geti(L, 6, 1);
    lua_geti(L, 6, 2);
    lua_geti(L, 6, 3);
    const uint8_t hue = lua_tointeger(L, -3);
    const uint8_t sat = lua_tointeger(L, -2);
    const uint8_t val = lua_tointeger(L, -1);

    painter_device_t device = qp_get_device(device_id);
    qp_rect(device, left, top, right, bottom, hue, sat, val, filled);

    return 0;
}

static int lua_qp_get_geometry(lua_State *L) {
    const int        device_id = luaL_checkinteger(L, 1);
    painter_device_t device    = qp_get_device(device_id);

    uint16_t width, height;
    painter_rotation_t rotation;
    uint16_t offset_x, offset_y;
    qp_get_geometry(device, &width, &height, &rotation, &offset_x, &offset_y);

    lua_newtable(L);

    lua_pushinteger(L, width);
    lua_setfield(L, -2, "width");

    lua_pushinteger(L, height);
    lua_setfield(L, -2, "height");

    lua_pushinteger(L, rotation);
    lua_setfield(L, -2, "rotation");

    lua_pushinteger(L, offset_x);
    lua_setfield(L, -2, "offset_x");

    lua_pushinteger(L, offset_y);
    lua_setfield(L, -2, "offset_y");

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

    // colors
    register_colors();

    // QP bindings
    lua_register(L, "qp_rect", lua_qp_rect);
    lua_register(L, "qp_get_geometry", lua_qp_get_geometry);
}

void lua_exec(char *filepath) {
    lua_pushstring(L, filepath);
    lua_pushnil(L); // args parameter
    exec_impl(L);
}

void lua_kill(void) {
    lua_close(L);
}
