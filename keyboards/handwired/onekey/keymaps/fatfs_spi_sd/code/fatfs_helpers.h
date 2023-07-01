// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// FatFS
#include "ff.h"

void fatfs_mount(void);

char *fatfs_read(char *path, UINT btr);
void fatfs_read_into(char *path, UINT btr, char *buffer); // WARNING: buffer has to be big enough

void fatfs_write(char *path, char *buff, UINT btw);

void fatfs_close(void);
