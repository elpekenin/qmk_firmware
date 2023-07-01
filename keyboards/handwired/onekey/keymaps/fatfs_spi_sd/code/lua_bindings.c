// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp.h"
#include "color.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "code/input.h"
#include "code/lua_bindings.h"
#include "code/fatfs_helpers.h"

static lua_State *L;

// Helping macros
#define LUA_REGISTER(func) lua_register(L, #func, lua_##func)
#define REGISTER_COLOR(name) _register_color((HSV){name}, #name)

static void _register_color(HSV color, char *name) {
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
    lua_setglobal(L, name);
}


static void create_files(void) {
    fatfs_write(
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


// ==================================================================
// Misc funcs
static int exec_impl(lua_State *L) {
    const char *filepath = luaL_checkstring(L, 1);
    if (filepath == NULL) {
        printf("exec_impl: error (filepath arg was bad)\n");
        return 0;
    }

    // load the file
    char *content = fatfs_read((char *)filepath, 0);
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

static int lua_fatfs_read_file(lua_State *L) {
    const char *filepath = luaL_checkstring(L, 1);

    if (filepath == NULL) {
        printf("lua_fatfs_read_file: error (filepath was empty)\n");
        lua_pushnil(L);
        return 1;
    }

    char *content = fatfs_read((char *)filepath, 0);
    lua_pushstring(L, content);

    return 1;
}

void lua_game_tick(char *filepath, char *direction) {
    lua_pushstring(L, filepath);

    // args is on position -2 (now -3)
    // args["direction"] = c
    lua_pushstring(L, direction);
    lua_setfield(L, -3, "direction");

    exec_impl(L);
}

// ==================================================================
// Constants
static void register_colors(void) {
    REGISTER_COLOR(HSV_AZURE);
    REGISTER_COLOR(HSV_BLACK);
    REGISTER_COLOR(HSV_BLUE);
    REGISTER_COLOR(HSV_CHARTREUSE);
    REGISTER_COLOR(HSV_CORAL);
    REGISTER_COLOR(HSV_CYAN);
    REGISTER_COLOR(HSV_GOLD);
    REGISTER_COLOR(HSV_GOLDENROD);
    REGISTER_COLOR(HSV_GREEN);
    REGISTER_COLOR(HSV_MAGENTA);
    REGISTER_COLOR(HSV_ORANGE);
    REGISTER_COLOR(HSV_PINK);
    REGISTER_COLOR(HSV_PURPLE);
    REGISTER_COLOR(HSV_RED);
    REGISTER_COLOR(HSV_SPRINGGREEN);
    REGISTER_COLOR(HSV_TEAL);
    REGISTER_COLOR(HSV_TURQUOISE);
    REGISTER_COLOR(HSV_WHITE);
    REGISTER_COLOR(HSV_YELLOW);
    REGISTER_COLOR(HSV_OFF);
}

// ==================================================================
// QP-Lua bindings
static int lua_qp_clear(lua_State *L) {
    const int device_id = luaL_checkinteger(L, 1);

    painter_device_t device = qp_get_device(device_id);

    qp_clear(device);

    return 0;
}

static int lua_qp_flush(lua_State *L) {
    const int device_id = luaL_checkinteger(L, 1);

    painter_device_t device = qp_get_device(device_id);

    qp_flush(device);

    return 0;
}

static int lua_qp_get_geometry(lua_State *L) {
    const int device_id = luaL_checkinteger(L, 1);

    painter_device_t device = qp_get_device(device_id);

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

static int lua_qp_setpixel(lua_State *L) {
    const uint8_t  device_id = luaL_checkinteger(L, 1);
    const uint16_t x         = luaL_checkinteger(L, 2);
    const uint16_t y         = luaL_checkinteger(L, 3);

    // unpack color table
    lua_geti(L, 4, 1);
    lua_geti(L, 4, 2);
    lua_geti(L, 4, 3);
    const uint8_t hue = lua_tointeger(L, -3);
    const uint8_t sat = lua_tointeger(L, -2);
    const uint8_t val = lua_tointeger(L, -1);
    lua_pop(L, 3);

    painter_device_t device = qp_get_device(device_id);

    qp_setpixel(device, x, y, hue, sat, val);

    return 0;
}

static int lua_qp_line(lua_State *L) {
    const uint8_t  device_id = luaL_checkinteger(L, 1);
    const uint16_t x0        = luaL_checkinteger(L, 2);
    const uint16_t y0        = luaL_checkinteger(L, 3);
    const uint16_t x1        = luaL_checkinteger(L, 4);
    const uint16_t y1        = luaL_checkinteger(L, 5);

    // unpack color table
    lua_geti(L, 6, 1);
    lua_geti(L, 6, 2);
    lua_geti(L, 6, 3);
    const uint8_t hue = lua_tointeger(L, -3);
    const uint8_t sat = lua_tointeger(L, -2);
    const uint8_t val = lua_tointeger(L, -1);
    lua_pop(L, 3);

    painter_device_t device = qp_get_device(device_id);

    qp_line(device, x0, y0, x1, y1, hue, sat, val);

    return 0;
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
    lua_pop(L, 3);

    painter_device_t device = qp_get_device(device_id);

    qp_rect(device, left, top, right, bottom, hue, sat, val, filled);

    return 0;
}

static int lua_qp_circle(lua_State *L) {
    const uint8_t  device_id = luaL_checkinteger(L, 1);
    const uint16_t x         = luaL_checkinteger(L, 2);
    const uint16_t y         = luaL_checkinteger(L, 3);
    const uint16_t radius    = luaL_checkinteger(L, 4);
    const bool     filled    = lua_toboolean(L, 6);

    // unpack color table
    lua_geti(L, 5, 1);
    lua_geti(L, 5, 2);
    lua_geti(L, 5, 3);
    const uint8_t hue = lua_tointeger(L, -3);
    const uint8_t sat = lua_tointeger(L, -2);
    const uint8_t val = lua_tointeger(L, -1);
    lua_pop(L, 3);

    painter_device_t device = qp_get_device(device_id);

    qp_circle(device, x, y, radius, hue, sat, val, filled);

    return 0;
}

static int lua_qp_ellipse(lua_State *L) {
    const uint8_t  device_id = luaL_checkinteger(L, 1);
    const uint16_t x         = luaL_checkinteger(L, 2);
    const uint16_t y         = luaL_checkinteger(L, 3);
    const uint16_t sizex     = luaL_checkinteger(L, 4);
    const uint16_t sizey     = luaL_checkinteger(L, 5);
    const bool     filled    = lua_toboolean(L, 7);

    // unpack color table
    lua_geti(L, 6, 1);
    lua_geti(L, 6, 2);
    lua_geti(L, 6, 3);
    const uint8_t hue = lua_tointeger(L, -3);
    const uint8_t sat = lua_tointeger(L, -2);
    const uint8_t val = lua_tointeger(L, -1);
    lua_pop(L, 3);

    painter_device_t device = qp_get_device(device_id);

    qp_ellipse(device, x, y, sizex, sizey, hue, sat, val, filled);

    return 0;
}

static int lua_qp_drawimage_recolor(lua_State *L) {
    const uint8_t  device_id = luaL_checkinteger(L, 1);
    const uint16_t x         = luaL_checkinteger(L, 2);
    const uint16_t y         = luaL_checkinteger(L, 3);
    const uint8_t  image_id  = luaL_checkinteger(L, 4);

    // unpack color tables
    lua_geti(L, 5, 1);
    lua_geti(L, 5, 2);
    lua_geti(L, 5, 3);
    const uint8_t hue_fg = lua_tointeger(L, -3);
    const uint8_t sat_fg = lua_tointeger(L, -2);
    const uint8_t val_fg = lua_tointeger(L, -1);
    lua_pop(L, 3);

    lua_geti(L, 6, 1);
    lua_geti(L, 6, 2);
    lua_geti(L, 6, 3);
    const uint8_t hue_bg = lua_tointeger(L, -3);
    const uint8_t sat_bg = lua_tointeger(L, -2);
    const uint8_t val_bg = lua_tointeger(L, -1);
    lua_pop(L, 3);

    painter_device_t       device = qp_get_device(device_id);
    painter_image_handle_t image  = qp_get_image(image_id);

    qp_drawimage_recolor(device, x, y, image, hue_fg, sat_fg, val_fg, hue_bg, sat_bg, val_bg);

    return 0;
}

// just a wrapper injecting black and white
static int lua_qp_drawimage(lua_State *L) {
    // getglobal pushes the variable to the top of the stack
    // as if they were 2 extra args, perfect!!
    lua_getglobal(L, "HSV_WHITE");
    lua_getglobal(L, "HSV_BLACK");

    return lua_qp_drawimage_recolor(L);
}

static int lua_qp_animate_recolor(lua_State *L) {
    const uint8_t  device_id = luaL_checkinteger(L, 1);
    const uint16_t x         = luaL_checkinteger(L, 2);
    const uint16_t y         = luaL_checkinteger(L, 3);
    const uint8_t  image_id  = luaL_checkinteger(L, 4);

    // unpack color tables
    lua_geti(L, 5, 1);
    lua_geti(L, 5, 2);
    lua_geti(L, 5, 3);
    const uint8_t hue_fg = lua_tointeger(L, -3);
    const uint8_t sat_fg = lua_tointeger(L, -2);
    const uint8_t val_fg = lua_tointeger(L, -1);
    lua_pop(L, 3);

    lua_geti(L, 6, 1);
    lua_geti(L, 6, 2);
    lua_geti(L, 6, 3);
    const uint8_t hue_bg = lua_tointeger(L, -3);
    const uint8_t sat_bg = lua_tointeger(L, -2);
    const uint8_t val_bg = lua_tointeger(L, -1);
    lua_pop(L, 3);

    painter_device_t       device = qp_get_device(device_id);
    painter_image_handle_t image  = qp_get_image(image_id);

    deferred_token token = qp_animate_recolor(device, x, y, image, hue_fg, sat_fg, val_fg, hue_bg, sat_bg, val_bg);
    lua_pushinteger(L, token);

    return 1;
}

// just a wrapper injecting black and white
static int lua_qp_animate(lua_State *L) {
    // getglobal pushes the variable to the top of the stack
    // as if they were 2 extra args, perfect!!
    lua_getglobal(L, "HSV_WHITE");
    lua_getglobal(L, "HSV_BLACK");

    return lua_qp_animate_recolor(L);
}

static int lua_qp_stop_animation(lua_State *L) {
    const deferred_token token = luaL_checkinteger(L, 1);

    qp_stop_animation(token);

    return 0;
}

static int lua_qp_textwidth(lua_State *L) {
    const uint8_t font_id = luaL_checkinteger(L, 1);
    const char *  text    = luaL_checkstring(L, 2);

    painter_font_handle_t font = qp_get_font(font_id);

    int16_t width = qp_textwidth(font, text);
    lua_pushinteger(L, width);

    return 1;
}

static int lua_qp_drawtext_recolor(lua_State *L) {
    const uint8_t  device_id = luaL_checkinteger(L, 1);
    const uint16_t x         = luaL_checkinteger(L, 2);
    const uint16_t y         = luaL_checkinteger(L, 3);
    const uint8_t  font_id   = luaL_checkinteger(L, 4);
    const char *   text      = luaL_checkstring(L, 5);

    // unpack color tables
    lua_geti(L, 6, 1);
    lua_geti(L, 6, 2);
    lua_geti(L, 6, 3);
    const uint8_t hue_fg = lua_tointeger(L, -3);
    const uint8_t sat_fg = lua_tointeger(L, -2);
    const uint8_t val_fg = lua_tointeger(L, -1);
    lua_pop(L, 3);

    lua_geti(L, 7, 1);
    lua_geti(L, 7, 2);
    lua_geti(L, 7, 3);
    const uint8_t hue_bg = lua_tointeger(L, -3);
    const uint8_t sat_bg = lua_tointeger(L, -2);
    const uint8_t val_bg = lua_tointeger(L, -1);
    lua_pop(L, 3);

    painter_device_t       device = qp_get_device(device_id);
    painter_font_handle_t  font   = qp_get_font(font_id);

    int16_t width = qp_drawtext_recolor(device, x, y, font, text, hue_fg, sat_fg, val_fg, hue_bg, sat_bg, val_bg);
    lua_pushinteger(L, width);

    return 1;
}

// just a wrapper injecting black and white
static int lua_qp_drawtext(lua_State *L) {
    // getglobal pushes the variable to the top of the stack
    // as if they were 2 extra args, perfect!!
    lua_getglobal(L, "HSV_WHITE");
    lua_getglobal(L, "HSV_BLACK");

    return lua_qp_drawtext_recolor(L);
}

// ==================================================================
// C-API of this file
void lua_setup(void) {
    create_files();

    extern lua_State *qmk_lua_newstate(void); // forward declaration
    L = qmk_lua_newstate();

    if (!L) {
        printf("Error creating the state\n");
        return;
    }

    // Add fatfs_read_file binding
    LUA_REGISTER(fatfs_read_file);

    // add exec binding
    lua_register(L, "exec", exec_impl);

    // colors
    register_colors();


    // ===== QP bindings
    // primitives
    LUA_REGISTER(qp_clear);
    LUA_REGISTER(qp_flush);
    LUA_REGISTER(qp_get_geometry);
    LUA_REGISTER(qp_setpixel);
    LUA_REGISTER(qp_line);
    LUA_REGISTER(qp_rect);
    LUA_REGISTER(qp_circle);
    LUA_REGISTER(qp_ellipse);
    // images
    LUA_REGISTER(qp_drawimage);
    LUA_REGISTER(qp_drawimage_recolor);
    LUA_REGISTER(qp_animate);
    LUA_REGISTER(qp_animate_recolor);
    LUA_REGISTER(qp_stop_animation);
    // text
    LUA_REGISTER(qp_textwidth);
    LUA_REGISTER(qp_drawtext);
    LUA_REGISTER(qp_drawtext_recolor);
}

void lua_exec(char *filepath) {
    lua_pushstring(L, filepath);
    lua_pushnil(L); // args parameter
    exec_impl(L);
}

void lua_kill(void) {
    lua_close(L);
}
