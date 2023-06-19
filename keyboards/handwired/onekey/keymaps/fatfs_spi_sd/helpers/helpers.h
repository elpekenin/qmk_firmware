#pragma once

#include <string.h>

// FatFS
#include "ff.h"
void close(FIL *Fil);
void _write(FIL *Fil, char *path, BYTE *buff, UINT btw);
BYTE *_read(FIL *Fil, char *path, UINT btr);

#define write(fil, path, string) _write((fil), (path), (BYTE *)(string), strlen((string)))
#define read(fil, path) (char *)_read((fil), (path), 0)

// QP
#include "qp.h"
void draw_text_buffer(painter_device_t device, painter_font_handle_t font, char *text_buffer, uint16_t text_buffer_index);

// Lua
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
int fatfs_read_file_impl(lua_State *L);
