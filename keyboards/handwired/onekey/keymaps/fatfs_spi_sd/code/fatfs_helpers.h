// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// FatFS
#include "ff.h"

void mount(void);

char *read(char *path, UINT btr);
void read_into(char *path, UINT btr, char *buffer); // WARNING: buffer has to be big enough

void write(char *path, char *buff, UINT btw);

void close(void);
