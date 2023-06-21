// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <lua.h>

void lua_setup(void);

void lua_exec(char *filepath);

void lua_kill(void);
