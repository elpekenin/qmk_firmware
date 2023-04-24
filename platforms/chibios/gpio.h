/* Copyright 2021 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include <hal.h>
#include "pin_defs.h"
#include "pin.h"

extern const pin_vtable_t gpio_pin_vtable_mcu;

/* Operation of GPIO by pin. */

#define setPinOutputPushPull(pin) palSetLineMode((pin), PAL_MODE_OUTPUT_PUSHPULL)
#define setPinOutputOpenDrain(pin) palSetLineMode((pin), PAL_MODE_OUTPUT_OPENDRAIN)

#define togglePin(pin) palToggleLine(pin)
