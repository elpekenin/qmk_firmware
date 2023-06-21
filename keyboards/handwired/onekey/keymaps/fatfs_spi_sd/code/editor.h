// Copyright 2023 Pablo Martinez (@elpekenin) <elpekenin@elpekenin.dev>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "qp.h"

#include "code/input.h"

void editor_open(char *_filepath);

void editor_move(uint16_t keycode);

void editor_write_char(char c);

void editor_needs_redraw(void);
void editor_flush(painter_device_t device, painter_font_handle_t font);

void editor_menu_selection(void);

