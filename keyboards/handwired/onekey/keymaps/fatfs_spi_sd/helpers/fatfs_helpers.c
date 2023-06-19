#include "helpers.h"

void close(FIL *Fil) {
    FRESULT fr;
    fr = f_close(Fil);
    if (fr != FR_OK) {
        printf("ERROR: Couldnt close a file, weird...\n");
    }
}

void _write(FIL *Fil, char *path, BYTE *buff, UINT btw) {
    FRESULT fr = f_open(Fil, path, FA_WRITE | FA_CREATE_ALWAYS);

    if (fr != FR_OK) {
        printf("ERROR: couldnt open '%s' in write mode, fr=%d\n", path, fr);
        return;
    }

    UINT bw;

    f_write(Fil, buff, btw, &bw);

    if (bw != btw) {
        printf("WARN: bytes written != bytes to write\n");
    }

    close(Fil);
}

static BYTE read_buff[READ_BUFFER_SIZE] = {0};
BYTE *_read(FIL *Fil, char *path, UINT btr) {
    FRESULT fr = f_open(Fil, path, FA_READ);

    if (fr != FR_OK) {
        printf("ERROR: couldnt open '%s' in read mode, fr=%d\n", path, fr);
        return NULL;
    }

    // If size not provided, find out the file size
    if (btr == 0) {
        btr = f_size(Fil);
    }

    if (btr > READ_BUFFER_SIZE) {
        printf("ERROR: read buffer is not big enough for '%s'\n", path);
        return NULL;
    }

    UINT br;

    // clean the buffer
    memset(read_buff, 0, READ_BUFFER_SIZE);
    f_read(Fil, read_buff, btr, &br);

    if (br != btr) {
        printf("WARN: bytes read != bytes to read\n");
    }

    close(Fil);

    return read_buff;
}
