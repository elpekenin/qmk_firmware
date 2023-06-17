// Copyright 2020 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

#include "ff.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(KC_A)
};

FATFS FatFs;
FIL Fil;

uint32_t deferred_init(uint32_t t, void* cb_arg) {
    UINT bw;
    FRESULT fr;

    printf("Mounting\n");
    f_mount(&FatFs, "", 0);

    printf("Creating file\n");
    fr = f_open(&Fil, "newfile.txt", FA_WRITE | FA_CREATE_ALWAYS);
    if (fr == FR_OK) {
        printf("Created, writing to it\n");
        f_write(&Fil, "It works!\r\n", 11, &bw);

        printf("Closing file\n");
        fr = f_close(&Fil);

        if (fr == FR_OK && bw == 11) {
            printf("Wrote the file!\n");
        }
    } else {
        // open is crashing, doesnt even get here
        printf("Could not create\n");
    }

    return 0;
}

void keyboard_post_init_user(void) {
    defer_exec(5000, deferred_init, NULL);
}
