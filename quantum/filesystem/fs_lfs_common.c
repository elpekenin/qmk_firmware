// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "filesystem.h"
#include "lfs.h"

#ifndef MAX_NUM_OPEN_FILES
#    define MAX_NUM_OPEN_FILES 4
#endif

// Can't use fd of 0, or 1/2/3 (stdin/stdout/stderr)
#define FIRST_VALID_FD 4

lfs_t lfs;

extern const struct lfs_config lfs_cfg;

static fs_fd_t current_fd = FIRST_VALID_FD;

typedef struct fs_handle_t {
    fs_fd_t    fd;
    lfs_file_t file;
} fs_handle_t;

static fs_handle_t handles[MAX_NUM_OPEN_FILES];

#define FIND_FD_GET_HANDLE(search_fd, block)                                      \
    do {                                                                          \
        for (int __find_idx = 0; __find_idx < MAX_NUM_OPEN_FILES; ++__find_idx) { \
            fs_handle_t *handle = &handles[__find_idx];                           \
            if (handle->fd == search_fd) {                                        \
                { block }                                                         \
            }                                                                     \
        }                                                                         \
    } while (0)

static inline bool fd_can_be_used(fs_fd_t fd) {
    if (fd < FIRST_VALID_FD) {
        return false;
    }
    for (int i = 0; i < MAX_NUM_OPEN_FILES; ++i) {
        if (handles[i].fd == fd) {
            return false;
        }
    }
    return true;
}

static inline fs_fd_t allocate_fd(void) {
    fs_fd_t first = ++current_fd;
    while (!fd_can_be_used(current_fd)) {
        ++current_fd;
        if (current_fd == first) {
            // If we've looped back around to the first, everything is already allocated (yikes!). Need to exit with a failure.
            return INVALID_FILESYSTEM_FD;
        }
    }
    return current_fd;
}

bool fs_init(void) {
    fs_dprintf("init\n");

    extern bool fs_device_init(void);
    return fs_device_init();
}

static int mount_count = 0;

bool fs_mount(void) {
    fs_dprintf("mount\n");
    if (mount_count == 0) {
        int err = lfs_mount(&lfs, &lfs_cfg);

        // reformat if we can't mount the filesystem
        // this should only happen on the first boot
        if (err < 0) {
            err = lfs_format(&lfs, &lfs_cfg);
            if (err < 0) {
                return false;
            }
            err = lfs_mount(&lfs, &lfs_cfg);
            if (err < 0) {
                return false;
            }
        }
    }
    ++mount_count;
    return true;
}

void fs_unmount(void) {
    fs_dprintf("unmount\n");
    --mount_count;
    if (mount_count == 0) {
        lfs_unmount(&lfs);
    }
}

bool fs_mkdir(const char *path) {
    if (!fs_mount()) {
        return false;
    }

    int err = lfs_mkdir(&lfs, path);
    if (err != LFS_ERR_EXIST && err < 0) {
        fs_unmount();
        return false;
    }

    fs_unmount();
    return true;
}

bool fs_rmdir(const char *path, bool recursive) {
    if (!fs_mount()) {
        return false;
    }

    if (recursive) {
        // TBD
    }

    int err = lfs_remove(&lfs, path);
    if (err < 0) {
        fs_unmount();
        return false;
    }

    fs_unmount();
    return true;
}

fs_fd_t fs_open(const char *filename, const char *mode) {
    FIND_FD_GET_HANDLE(INVALID_FILESYSTEM_FD, {
        if (!fs_mount()) {
            return INVALID_FILESYSTEM_FD;
        }

        int flags = LFS_O_CREAT;
        while (*mode) {
            switch (*mode) {
                case 'r':
                    flags |= LFS_O_RDONLY;
                    break;
                case 'w':
                    flags |= LFS_O_WRONLY;
                    break;
                case 't':
                    flags |= LFS_O_TRUNC;
                    break;
            }
            ++mode;
        }

        int err = lfs_file_open(&lfs, &handle->file, filename, flags);
        if (err < 0) {
            fs_unmount();
            return INVALID_FILESYSTEM_FD;
        }

        fs_fd_t fd = allocate_fd();
        handle->fd = fd;
        return fd;
    });
    return INVALID_FILESYSTEM_FD;
}

void fs_close(fs_fd_t fd) {
    FIND_FD_GET_HANDLE(fd, {
        lfs_file_close(&lfs, &handle->file);
        handle->fd = INVALID_FILESYSTEM_FD;
        fs_unmount();
    });
}

bool fs_delete(const char *filename) {
    if (!fs_mount()) {
        return false;
    }

    int err = lfs_remove(&lfs, filename);
    fs_unmount();
    return err >= 0;
}

fs_offset_t fs_seek(fs_fd_t fd, fs_offset_t offset, fs_whence_t whence) {
    FIND_FD_GET_HANDLE(fd, {
        int lfs_whence = 0;
        switch (whence) {
            case FILESYSTEM_SEEK_SET:
                lfs_whence = LFS_SEEK_SET;
                break;
            case FILESYSTEM_SEEK_CUR:
                lfs_whence = LFS_SEEK_CUR;
                break;
            case FILESYSTEM_SEEK_END:
                lfs_whence = LFS_SEEK_END;
                break;
        }

        int err = lfs_file_seek(&lfs, &handle->file, (lfs_soff_t)offset, lfs_whence);
        if (err < 0) {
            return -1;
        }

        fs_offset_t offset = (fs_offset_t)lfs_file_tell(&lfs, &handle->file);
        return (offset < 0) ? -1 : offset;
    });
    return -1;
}

fs_offset_t fs_tell(fs_fd_t fd) {
    FIND_FD_GET_HANDLE(fd, {
        fs_offset_t offset = (fs_offset_t)lfs_file_tell(&lfs, &handle->file);
        return (offset < 0) ? -1 : offset;
    });
    return -1;
}

fs_size_t fs_read(fs_fd_t fd, void *buffer, fs_size_t length) {
    FIND_FD_GET_HANDLE(fd, {
        fs_size_t ret = (fs_size_t)lfs_file_read(&lfs, &handle->file, buffer, (lfs_size_t)length);
        return (ret < 0) ? -1 : ret;
    });
    return -1;
}

fs_size_t fs_write(fs_fd_t fd, const void *buffer, fs_size_t length) {
    FIND_FD_GET_HANDLE(fd, {
        fs_size_t ret = (fs_size_t)lfs_file_write(&lfs, &handle->file, buffer, (lfs_size_t)length);
        return (ret < 0) ? -1 : ret;
    });
    return -1;
}

bool fs_is_eof(fs_fd_t fd) {
    FIND_FD_GET_HANDLE(fd, {
        lfs_soff_t orig_offset = lfs_file_tell(&lfs, &handle->file);
        if (orig_offset < 0) {
            return true;
        }

        lfs_soff_t end_offset = lfs_file_seek(&lfs, &handle->file, 0, LFS_SEEK_END);
        if (end_offset < 0) {
            return true;
        }

        if (orig_offset != end_offset) {
            lfs_file_seek(&lfs, &handle->file, orig_offset, LFS_SEEK_SET);
            return true;
        }

        return false;
    });
    return true;
}
