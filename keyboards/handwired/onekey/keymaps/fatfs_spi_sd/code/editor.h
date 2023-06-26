// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "qp.h"

#include "code/input.h"

#ifndef TAB_SIZE
#    define TAB_SIZE 4
#endif // TABSIZE

void editor_open(char *_filepath);

bool editor_handle(uint16_t keycode);

void editor_text_needs_redraw(void);
void editor_menu_needs_redraw(void);
void editor_flush(painter_device_t device, painter_font_handle_t font);

void editor_menu_selection(void);

