// Copyright 2018-2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <lua.h>
#include <lauxlib.h>

#include "debug.h"
#include "keycodes.h"

static int dprint_wrapper(lua_State *L) {
    const char *arg = luaL_checkstring(L, 1); // first arg is what we want to print
    dprintf("%s\n", arg);
    return 0;
}

static const luaL_Reg qmk_lua_funcs[] = {
    {"dprint", dprint_wrapper},
    {NULL, NULL} // Terminator
};

LUAMOD_API int luaopen_qmk(lua_State *L) {
    luaL_newlib(L, qmk_lua_funcs);
    return 1;
}

LUAMOD_API void register_globals(lua_State *L) {
    lua_register(L, "dprint", dprint_wrapper);
}
