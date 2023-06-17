// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef uint16_t fs_fd_t;
typedef int32_t  fs_offset_t;
typedef int32_t  fs_size_t;
#define INVALID_FILESYSTEM_FD ((fs_fd_t)0)

typedef enum fs_whence_t {
    FILESYSTEM_SEEK_SET = 0, // Seek relative to start position
    FILESYSTEM_SEEK_CUR = 1, // Seek relative to the current file position
    FILESYSTEM_SEEK_END = 2  // Seek relative to the end of the file
} fs_whence_t;

bool fs_init(void);
bool fs_mount(void);
void fs_unmount(void);

bool fs_mkdir(const char *path);
bool fs_rmdir(const char *path, bool recursive);

fs_fd_t fs_open(const char *filename, const char *mode);
void    fs_close(fs_fd_t fd);
bool    fs_delete(const char *filename);

fs_offset_t fs_seek(fs_fd_t fd, fs_offset_t offset, fs_whence_t whence);
fs_offset_t fs_tell(fs_fd_t fd);
fs_size_t   fs_read(fs_fd_t fd, void *buffer, fs_size_t length);
fs_size_t   fs_write(fs_fd_t fd, const void *buffer, fs_size_t length);
bool        fs_is_eof(fs_fd_t fd);

#ifdef FILESYSTEM_DEBUG
#    include <debug.h>
#    include <print.h>
#    define fs_dprintf(...) dprintf(__VA_ARGS__)
#else
#    define fs_dprintf(...) \
        do {                \
        } while (0)
#endif
