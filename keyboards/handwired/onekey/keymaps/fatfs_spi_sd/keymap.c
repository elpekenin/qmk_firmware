// Copyright 2020 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

#include "ff.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(KC_A)
};

FATFS FatFs;
FIL Fil;

void write(char *path, BYTE *buff, UINT btw) {
    UINT bw;
    FRESULT fr;

    printf("Writing '%s' to '%s'\n", buff, path);

    fr = f_open(&Fil, path, FA_WRITE | FA_CREATE_ALWAYS);
    if (fr == FR_OK) {
        f_write(&Fil, buff, btw, &bw);

        fr = f_close(&Fil);
        if (fr == FR_OK && bw == btw) {
            printf("File closed\n");
        }
    }
}

void read(char *path, UINT btr) {
    UINT br;
    BYTE buff[100];
    FRESULT fr;

    printf("Reading from '%s'\n", path);

    fr = f_open(&Fil, path, FA_READ);
    if (fr == FR_OK) {
        f_read(&Fil, buff, btr, &br);

        printf("Found %d bytes: ", br);
        for (UINT i=0; i < br; ++i) {
            printf("%c", buff[i]);
        }
        printf("\n");

        fr = f_close(&Fil);
        if (fr == FR_OK && br == btr) {
            printf("File closed\n");
        }
    }
}

uint32_t deferred_init(uint32_t t, void* cb_arg) {
    printf("Mounting\n");
    f_mount(&FatFs, "", 0);

    char path[] = "foo.txt";

    BYTE buff[] = "hello, world!";
    write(path, buff, sizeof(buff));

    read(path, sizeof(buff));

    return 0;
}

void keyboard_post_init_user(void) {
    defer_exec(5000, deferred_init, NULL);
}
