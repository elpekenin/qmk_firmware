// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "filesystem.h"
#include "lfs.h"
#include "flash_spi.h"

bool fs_device_init(void) {
    flash_init();
    return true;
}

int fs_device_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size) {
    fs_dprintf("read\n");
    flash_read_block(block * c->block_size + off, buffer, size);
    return 0;
}

int fs_device_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size) {
    fs_dprintf("prog\n");
    flash_write_block(block * c->block_size + off, buffer, size);
    return 0;
}

int fs_device_erase(const struct lfs_config *c, lfs_block_t block) {
    fs_dprintf("erase\n");
    flash_erase_sector(block * c->block_size);
    return 0;
}

int fs_device_sync(const struct lfs_config *c) {
    fs_dprintf("sync\n");
    return 0;
}

uint8_t lfs_read_buf[EXTERNAL_FLASH_PAGE_SIZE];
uint8_t lfs_prog_buf[EXTERNAL_FLASH_PAGE_SIZE];
uint8_t lfs_lookahead_buf[EXTERNAL_FLASH_PAGE_SIZE];

// configuration of the filesystem is provided by this struct
const struct lfs_config lfs_cfg = {
    // block device operations
    .read  = fs_device_read,
    .prog  = fs_device_prog,
    .erase = fs_device_erase,
    .sync  = fs_device_sync,

    // block device configuration
    .read_size      = EXTERNAL_FLASH_PAGE_SIZE,
    .prog_size      = EXTERNAL_FLASH_PAGE_SIZE,
    .block_size     = EXTERNAL_FLASH_BLOCK_SIZE,
    .block_count    = EXTERNAL_FLASH_BLOCK_COUNT,
    .cache_size     = EXTERNAL_FLASH_PAGE_SIZE,
    .lookahead_size = EXTERNAL_FLASH_PAGE_SIZE,

    .read_buffer      = lfs_read_buf,
    .prog_buffer      = lfs_prog_buf,
    .lookahead_buffer = lfs_lookahead_buf};
