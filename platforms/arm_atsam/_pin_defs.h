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

#include "pin.h"
#include "samd51j18a.h"

static const pin_impl_t pin_A00 = {.type = PIN_MCU, .mcu_pin = PIN_PA00};
static const pin_impl_t pin_A01 = {.type = PIN_MCU, .mcu_pin = PIN_PA01};
static const pin_impl_t pin_A02 = {.type = PIN_MCU, .mcu_pin = PIN_PA02};
static const pin_impl_t pin_A03 = {.type = PIN_MCU, .mcu_pin = PIN_PA03};
static const pin_impl_t pin_A04 = {.type = PIN_MCU, .mcu_pin = PIN_PA04};
static const pin_impl_t pin_A05 = {.type = PIN_MCU, .mcu_pin = PIN_PA05};
static const pin_impl_t pin_A06 = {.type = PIN_MCU, .mcu_pin = PIN_PA06};
static const pin_impl_t pin_A07 = {.type = PIN_MCU, .mcu_pin = PIN_PA07};
static const pin_impl_t pin_A08 = {.type = PIN_MCU, .mcu_pin = PIN_PA08};
static const pin_impl_t pin_A09 = {.type = PIN_MCU, .mcu_pin = PIN_PA09};
static const pin_impl_t pin_A10 = {.type = PIN_MCU, .mcu_pin = PIN_PA10};
static const pin_impl_t pin_A11 = {.type = PIN_MCU, .mcu_pin = PIN_PA11};
static const pin_impl_t pin_A12 = {.type = PIN_MCU, .mcu_pin = PIN_PA12};
static const pin_impl_t pin_A13 = {.type = PIN_MCU, .mcu_pin = PIN_PA13};
static const pin_impl_t pin_A14 = {.type = PIN_MCU, .mcu_pin = PIN_PA14};
static const pin_impl_t pin_A15 = {.type = PIN_MCU, .mcu_pin = PIN_PA15};
static const pin_impl_t pin_A16 = {.type = PIN_MCU, .mcu_pin = PIN_PA16};
static const pin_impl_t pin_A17 = {.type = PIN_MCU, .mcu_pin = PIN_PA17};
static const pin_impl_t pin_A18 = {.type = PIN_MCU, .mcu_pin = PIN_PA18};
static const pin_impl_t pin_A19 = {.type = PIN_MCU, .mcu_pin = PIN_PA19};
static const pin_impl_t pin_A20 = {.type = PIN_MCU, .mcu_pin = PIN_PA20};
static const pin_impl_t pin_A21 = {.type = PIN_MCU, .mcu_pin = PIN_PA21};
static const pin_impl_t pin_A22 = {.type = PIN_MCU, .mcu_pin = PIN_PA22};
static const pin_impl_t pin_A23 = {.type = PIN_MCU, .mcu_pin = PIN_PA23};
static const pin_impl_t pin_A24 = {.type = PIN_MCU, .mcu_pin = PIN_PA24};
static const pin_impl_t pin_A25 = {.type = PIN_MCU, .mcu_pin = PIN_PA25};
static const pin_impl_t pin_A27 = {.type = PIN_MCU, .mcu_pin = PIN_PA27};
static const pin_impl_t pin_A30 = {.type = PIN_MCU, .mcu_pin = PIN_PA30};
static const pin_impl_t pin_A31 = {.type = PIN_MCU, .mcu_pin = PIN_PA31};

static const pin_impl_t pin_B00 = {.type = PIN_MCU, .mcu_pin = PIN_PB00};
static const pin_impl_t pin_B01 = {.type = PIN_MCU, .mcu_pin = PIN_PB01};
static const pin_impl_t pin_B02 = {.type = PIN_MCU, .mcu_pin = PIN_PB02};
static const pin_impl_t pin_B03 = {.type = PIN_MCU, .mcu_pin = PIN_PB03};
static const pin_impl_t pin_B04 = {.type = PIN_MCU, .mcu_pin = PIN_PB04};
static const pin_impl_t pin_B05 = {.type = PIN_MCU, .mcu_pin = PIN_PB05};
static const pin_impl_t pin_B06 = {.type = PIN_MCU, .mcu_pin = PIN_PB06};
static const pin_impl_t pin_B07 = {.type = PIN_MCU, .mcu_pin = PIN_PB07};
static const pin_impl_t pin_B08 = {.type = PIN_MCU, .mcu_pin = PIN_PB08};
static const pin_impl_t pin_B09 = {.type = PIN_MCU, .mcu_pin = PIN_PB09};
static const pin_impl_t pin_B10 = {.type = PIN_MCU, .mcu_pin = PIN_PB10};
static const pin_impl_t pin_B11 = {.type = PIN_MCU, .mcu_pin = PIN_PB11};
static const pin_impl_t pin_B12 = {.type = PIN_MCU, .mcu_pin = PIN_PB12};
static const pin_impl_t pin_B13 = {.type = PIN_MCU, .mcu_pin = PIN_PB13};
static const pin_impl_t pin_B14 = {.type = PIN_MCU, .mcu_pin = PIN_PB14};
static const pin_impl_t pin_B15 = {.type = PIN_MCU, .mcu_pin = PIN_PB15};
static const pin_impl_t pin_B16 = {.type = PIN_MCU, .mcu_pin = PIN_PB16};
static const pin_impl_t pin_B17 = {.type = PIN_MCU, .mcu_pin = PIN_PB17};
static const pin_impl_t pin_B22 = {.type = PIN_MCU, .mcu_pin = PIN_PB22};
static const pin_impl_t pin_B23 = {.type = PIN_MCU, .mcu_pin = PIN_PB23};
static const pin_impl_t pin_B30 = {.type = PIN_MCU, .mcu_pin = PIN_PB30};
static const pin_impl_t pin_B31 = {.type = PIN_MCU, .mcu_pin = PIN_PB31};


#define A00 ((pin_t)&pin_A00)
#define A01 ((pin_t)&pin_A01)
#define A02 ((pin_t)&pin_A02)
#define A03 ((pin_t)&pin_A03)
#define A04 ((pin_t)&pin_A04)
#define A05 ((pin_t)&pin_A05)
#define A06 ((pin_t)&pin_A06)
#define A07 ((pin_t)&pin_A07)
#define A08 ((pin_t)&pin_A08)
#define A09 ((pin_t)&pin_A09)
#define A10 ((pin_t)&pin_A10)
#define A11 ((pin_t)&pin_A11)
#define A12 ((pin_t)&pin_A12)
#define A13 ((pin_t)&pin_A13)
#define A14 ((pin_t)&pin_A14)
#define A15 ((pin_t)&pin_A15)
#define A16 ((pin_t)&pin_A16)
#define A17 ((pin_t)&pin_A17)
#define A18 ((pin_t)&pin_A18)
#define A19 ((pin_t)&pin_A19)
#define A20 ((pin_t)&pin_A20)
#define A21 ((pin_t)&pin_A21)
#define A22 ((pin_t)&pin_A22)
#define A23 ((pin_t)&pin_A23)
#define A24 ((pin_t)&pin_A24)
#define A25 ((pin_t)&pin_A25)
#define A27 ((pin_t)&pin_A27)
#define A30 ((pin_t)&pin_A30)
#define A31 ((pin_t)&pin_A31)

#define B00 ((pin_t)&pin_B00)
#define B01 ((pin_t)&pin_B01)
#define B02 ((pin_t)&pin_B02)
#define B03 ((pin_t)&pin_B03)
#define B04 ((pin_t)&pin_B04)
#define B05 ((pin_t)&pin_B05)
#define B06 ((pin_t)&pin_B06)
#define B07 ((pin_t)&pin_B07)
#define B08 ((pin_t)&pin_B08)
#define B09 ((pin_t)&pin_B09)
#define B10 ((pin_t)&pin_B10)
#define B11 ((pin_t)&pin_B11)
#define B12 ((pin_t)&pin_B12)
#define B13 ((pin_t)&pin_B13)
#define B14 ((pin_t)&pin_B14)
#define B15 ((pin_t)&pin_B15)
#define B16 ((pin_t)&pin_B16)
#define B17 ((pin_t)&pin_B17)
#define B22 ((pin_t)&pin_B22)
#define B23 ((pin_t)&pin_B23)
#define B30 ((pin_t)&pin_B30)
#define B31 ((pin_t)&pin_B31)


// =====
// These dont exist...
#if 0
static const pin_impl_t pin_A26 = {.type = PIN_MCU, .mcu_pin = PIN_PA26};
static const pin_impl_t pin_A28 = {.type = PIN_MCU, .mcu_pin = PIN_PA28};
static const pin_impl_t pin_A29 = {.type = PIN_MCU, .mcu_pin = PIN_PA29};
static const pin_impl_t pin_B18 = {.type = PIN_MCU, .mcu_pin = PIN_PB18};
static const pin_impl_t pin_B19 = {.type = PIN_MCU, .mcu_pin = PIN_PB19};
static const pin_impl_t pin_B20 = {.type = PIN_MCU, .mcu_pin = PIN_PB20};
static const pin_impl_t pin_B21 = {.type = PIN_MCU, .mcu_pin = PIN_PB21};
static const pin_impl_t pin_B24 = {.type = PIN_MCU, .mcu_pin = PIN_PB24};
static const pin_impl_t pin_B25 = {.type = PIN_MCU, .mcu_pin = PIN_PB25};
static const pin_impl_t pin_B26 = {.type = PIN_MCU, .mcu_pin = PIN_PB26};
static const pin_impl_t pin_B27 = {.type = PIN_MCU, .mcu_pin = PIN_PB27};
static const pin_impl_t pin_B28 = {.type = PIN_MCU, .mcu_pin = PIN_PB28};
static const pin_impl_t pin_B29 = {.type = PIN_MCU, .mcu_pin = PIN_PB29};

#define A26 ((pin_t)&pin_A26)
#define A28 ((pin_t)&pin_A28)
#define A29 ((pin_t)&pin_A29)
#define B18 ((pin_t)&pin_B18)
#define B19 ((pin_t)&pin_B19)
#define B20 ((pin_t)&pin_B20)
#define B21 ((pin_t)&pin_B21)
#define B24 ((pin_t)&pin_B24)
#define B25 ((pin_t)&pin_B25)
#define B26 ((pin_t)&pin_B26)
#define B27 ((pin_t)&pin_B27)
#define B28 ((pin_t)&pin_B28)
#define B29 ((pin_t)&pin_B29)
#endif
