#include "helpers.h"

int fatfs_read_file_impl(lua_State *L) {
    const char *arg = luaL_checkstring(L, 1); // first arg is the path to read from

    extern FIL Fil;
    char *content = read(&Fil, (char *)arg);
    lua_pushstring(L, content);

    return 1;
}
