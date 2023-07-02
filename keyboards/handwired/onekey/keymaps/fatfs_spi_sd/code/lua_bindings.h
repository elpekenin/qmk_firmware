// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <lua.h>

void lua_setup(void);

void lua_exec(char *filepath, int nresults);
const char *lua_get_type_str(int idx);

void lua_kill(void);

void lua_game_start(char *filepath);
void lua_game_tick(char *filepath, char *direction);
