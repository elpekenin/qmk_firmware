// Copyright 2018-2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

// Adapted from lib/lua/onelua.c

#include <lprefix.h>

#define LUA_CORE
#define LUA_LIB
#include <luaconf.h>

#undef LUAI_FUNC
#undef LUAI_DDEC
#undef LUAI_DDEF
#define LUAI_FUNC static
#define LUAI_DDEC(def) /* empty */
#define LUAI_DDEF static

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

/* core -- used by all */
#include "lzio.c"
#include "lctype.c"
#include "lopcodes.c"
#include "lmem.c"
#include "lundump.c"
#include "ldump.c"
#include "lstate.c"
#include "lgc.c"
#include "llex.c"
#include "lcode.c"
#include "lparser.c"
#include "ldebug.c"
#include "lfunc.c"
#include "lobject.c"
#include "ltm.c"
#include "lstring.c"
#include "ltable.c"
#include "ldo.c"
#include "lvm.c"
#include "lapi.c"

/* auxiliary library -- used by all */
#include "lauxlib.c"

/* standard library  -- not used by luac */
#ifndef MAKE_LUAC
#    include "lbaselib.c"
//#    include "lcorolib.c"
//#    include "ldblib.c"
#    include "lmathlib.c"
#    include "lstrlib.c"
#    include "ltablib.c"
#    include "lutf8lib.c"
#endif

LUAMOD_API void register_globals(lua_State *L);
LUAMOD_API int luaopen_qmk(lua_State *L);

static const luaL_Reg loadedlibs[] = {
    {LUA_GNAME, luaopen_base}, // Base library
    // {LUA_COLIBNAME, luaopen_coroutine}, // Coroutines
    {LUA_TABLIBNAME, luaopen_table},  // Tables
    {LUA_STRLIBNAME, luaopen_string}, // Strings
    {LUA_MATHLIBNAME, luaopen_math},  // Math
    {LUA_UTF8LIBNAME, luaopen_utf8},  // UTF-8
    // {LUA_DBLIBNAME, luaopen_debug},     // Debug
    {"qmk", luaopen_qmk}, // QMK
    {NULL, NULL},
};

lua_State *qmk_lua_newstate(void) {
    lua_State *L = luaL_newstate();

    // Mirror luaL_openlibs():
    for (const luaL_Reg *lib = loadedlibs; lib->func; lib++) {
        luaL_requiref(L, lib->name, lib->func, 1);
        lua_pop(L, 1); /* remove lib */
    }

    register_globals(L);

    // TBD load QMK-specific safety stuff
    return L;
}
