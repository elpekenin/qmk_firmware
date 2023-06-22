// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#include <string.h>

#include "print.h"

#include "fatfs_helpers.h"

static FATFS FatFs;
static FIL _Fil;
static FIL* Fil = &_Fil;

static char read_buff[READ_BUFFER_SIZE] = {0};

void mount(void) {
    f_mount(&FatFs, "", 0);
}

char *read(char *path, UINT btr) {
    FRESULT fr = f_open(Fil, path, FA_READ);

    if (fr != FR_OK) {
        printf("ERROR: couldnt open '%s' in read mode, fr=%d\n", path, fr);
        return NULL;
    }

    // If size not provided, find out the file size
    if (btr == 0) {
        btr = f_size(Fil);
    }

    UINT br;
    if (btr > READ_BUFFER_SIZE) {
        printf("ERROR: read buffer is not big enough for '%s'\n", path);
        return NULL;
    }

    // clean the buffer
    memset(read_buff, 0, READ_BUFFER_SIZE);
    f_read(Fil, read_buff, btr, &br);

    if (br != btr) {
        printf("WARN: bytes read != bytes to read\n");
    }

    close();

    return read_buff;
}

void read_into(char *path, UINT btr, char *buffer) {
    char *_buffer = read(path, btr);

    if (!_buffer) {
        return;
    }

    strcpy(buffer, _buffer);
}

void write(char *path, char *buff, UINT btw) {
    FRESULT fr = f_open(Fil, path, FA_WRITE | FA_CREATE_ALWAYS);

    if (fr != FR_OK) {
        printf("ERROR: couldnt open '%s' in write mode, fr=%d\n", path, fr);
        return;
    }

    UINT bw;
    // If size not provided, find out the string size
    if (btw == 0) {
        btw = strlen(buff);
    }

    f_write(Fil, buff, btw, &bw);

    if (bw != btw) {
        printf("WARN: bytes written != bytes to write\n");
    }

    close();
}

void close(void) {
    FRESULT fr;
    fr = f_close(Fil);
    if (fr != FR_OK) {
        printf("ERROR: Couldnt close a file, fr=%d\n", fr);
    }
}
