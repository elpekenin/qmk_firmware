// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "action.h"

typedef enum {
    NONE,
    PATH,
    EDIT,
    MENU,
    __N_MODES
} input_mode_t;

char keycode_to_char(uint16_t keycode);

bool process_input_mode(uint16_t k, keyrecord_t *kr);

char *get_input_buffer(void);
input_mode_t get_input_mode(void);
