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
#include <hal.h>

/* Include the vendor specific pin defs */
#if __has_include_next("_pin_defs.h")
#    include_next "_pin_defs.h"
#endif

#if defined(GPIOA_BASE)
static const pin_impl_t  pin_A0 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA,  0)};
static const pin_impl_t  pin_A1 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA,  1)};
static const pin_impl_t  pin_A2 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA,  2)};
static const pin_impl_t  pin_A3 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA,  3)};
static const pin_impl_t  pin_A4 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA,  4)};
static const pin_impl_t  pin_A5 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA,  5)};
static const pin_impl_t  pin_A6 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA,  6)};
static const pin_impl_t  pin_A7 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA,  7)};
static const pin_impl_t  pin_A8 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA,  8)};
static const pin_impl_t  pin_A9 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA,  9)};
static const pin_impl_t pin_A10 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA, 10)};
static const pin_impl_t pin_A11 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA, 11)};
static const pin_impl_t pin_A12 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA, 12)};
static const pin_impl_t pin_A13 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA, 13)};
static const pin_impl_t pin_A14 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA, 14)};
static const pin_impl_t pin_A15 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA, 15)};
static const pin_impl_t pin_A16 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA, 16)};
static const pin_impl_t pin_A17 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA, 17)};
static const pin_impl_t pin_A18 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA, 18)};
static const pin_impl_t pin_A19 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA, 19)};
static const pin_impl_t pin_A20 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA, 20)};
static const pin_impl_t pin_A21 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA, 21)};
static const pin_impl_t pin_A22 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA, 22)};
static const pin_impl_t pin_A23 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA, 23)};
static const pin_impl_t pin_A24 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA, 24)};
static const pin_impl_t pin_A25 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA, 25)};
static const pin_impl_t pin_A26 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA, 26)};
static const pin_impl_t pin_A27 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA, 27)};
static const pin_impl_t pin_A28 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA, 28)};
static const pin_impl_t pin_A29 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA, 29)};
static const pin_impl_t pin_A30 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA, 30)};
static const pin_impl_t pin_A31 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA, 31)};
static const pin_impl_t pin_A32 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOA, 32)};
#define  A0  ((pin_t)&pin_A0)
#define  A1  ((pin_t)&pin_A1)
#define  A2  ((pin_t)&pin_A2)
#define  A3  ((pin_t)&pin_A3)
#define  A4  ((pin_t)&pin_A4)
#define  A5  ((pin_t)&pin_A5)
#define  A6  ((pin_t)&pin_A6)
#define  A7  ((pin_t)&pin_A7)
#define  A8  ((pin_t)&pin_A8)
#define  A9  ((pin_t)&pin_A9)
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
#define A26 ((pin_t)&pin_A26)
#define A27 ((pin_t)&pin_A27)
#define A28 ((pin_t)&pin_A28)
#define A29 ((pin_t)&pin_A29)
#define A30 ((pin_t)&pin_A30)
#define A31 ((pin_t)&pin_A31)
#define A32 ((pin_t)&pin_A32)
#endif // defined(GPIOA_BASE)


#if defined(GPIOB_BASE)
static const pin_impl_t  pin_B0 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB,  0)};
static const pin_impl_t  pin_B1 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB,  1)};
static const pin_impl_t  pin_B2 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB,  2)};
static const pin_impl_t  pin_B3 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB,  3)};
static const pin_impl_t  pin_B4 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB,  4)};
static const pin_impl_t  pin_B5 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB,  5)};
static const pin_impl_t  pin_B6 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB,  6)};
static const pin_impl_t  pin_B7 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB,  7)};
static const pin_impl_t  pin_B8 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB,  8)};
static const pin_impl_t  pin_B9 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB,  9)};
static const pin_impl_t pin_B10 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB, 10)};
static const pin_impl_t pin_B11 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB, 11)};
static const pin_impl_t pin_B12 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB, 12)};
static const pin_impl_t pin_B13 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB, 13)};
static const pin_impl_t pin_B14 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB, 14)};
static const pin_impl_t pin_B15 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB, 15)};
static const pin_impl_t pin_B16 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB, 16)};
static const pin_impl_t pin_B17 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB, 17)};
static const pin_impl_t pin_B18 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB, 18)};
static const pin_impl_t pin_B19 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB, 19)};
static const pin_impl_t pin_B20 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB, 20)};
static const pin_impl_t pin_B21 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB, 21)};
static const pin_impl_t pin_B22 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB, 22)};
static const pin_impl_t pin_B23 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB, 23)};
static const pin_impl_t pin_B24 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB, 24)};
static const pin_impl_t pin_B25 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB, 25)};
static const pin_impl_t pin_B26 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB, 26)};
static const pin_impl_t pin_B27 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB, 27)};
static const pin_impl_t pin_B28 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB, 28)};
static const pin_impl_t pin_B29 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB, 29)};
static const pin_impl_t pin_B30 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB, 30)};
static const pin_impl_t pin_B31 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB, 31)};
static const pin_impl_t pin_B32 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOB, 32)};
#define  B0  ((pin_t)&pin_B0)
#define  B1  ((pin_t)&pin_B1)
#define  B2  ((pin_t)&pin_B2)
#define  B3  ((pin_t)&pin_B3)
#define  B4  ((pin_t)&pin_B4)
#define  B5  ((pin_t)&pin_B5)
#define  B6  ((pin_t)&pin_B6)
#define  B7  ((pin_t)&pin_B7)
#define  B8  ((pin_t)&pin_B8)
#define  B9  ((pin_t)&pin_B9)
#define B10 ((pin_t)&pin_B10)
#define B11 ((pin_t)&pin_B11)
#define B12 ((pin_t)&pin_B12)
#define B13 ((pin_t)&pin_B13)
#define B14 ((pin_t)&pin_B14)
#define B15 ((pin_t)&pin_B15)
#define B16 ((pin_t)&pin_B16)
#define B17 ((pin_t)&pin_B17)
#define B18 ((pin_t)&pin_B18)
#define B19 ((pin_t)&pin_B19)
#define B20 ((pin_t)&pin_B20)
#define B21 ((pin_t)&pin_B21)
#define B22 ((pin_t)&pin_B22)
#define B23 ((pin_t)&pin_B23)
#define B24 ((pin_t)&pin_B24)
#define B25 ((pin_t)&pin_B25)
#define B26 ((pin_t)&pin_B26)
#define B27 ((pin_t)&pin_B27)
#define B28 ((pin_t)&pin_B28)
#define B29 ((pin_t)&pin_B29)
#define B30 ((pin_t)&pin_B30)
#define B31 ((pin_t)&pin_B31)
#define B32 ((pin_t)&pin_B32)
#endif // defined(GPIOB_BASE)


#if defined(GPIOC_BASE)
static const pin_impl_t  pin_C0 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC,  0)};
static const pin_impl_t  pin_C1 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC,  1)};
static const pin_impl_t  pin_C2 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC,  2)};
static const pin_impl_t  pin_C3 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC,  3)};
static const pin_impl_t  pin_C4 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC,  4)};
static const pin_impl_t  pin_C5 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC,  5)};
static const pin_impl_t  pin_C6 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC,  6)};
static const pin_impl_t  pin_C7 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC,  7)};
static const pin_impl_t  pin_C8 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC,  8)};
static const pin_impl_t  pin_C9 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC,  9)};
static const pin_impl_t pin_C10 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC, 10)};
static const pin_impl_t pin_C11 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC, 11)};
static const pin_impl_t pin_C12 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC, 12)};
static const pin_impl_t pin_C13 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC, 13)};
static const pin_impl_t pin_C14 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC, 14)};
static const pin_impl_t pin_C15 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC, 15)};
static const pin_impl_t pin_C16 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC, 16)};
static const pin_impl_t pin_C17 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC, 17)};
static const pin_impl_t pin_C18 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC, 18)};
static const pin_impl_t pin_C19 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC, 19)};
static const pin_impl_t pin_C20 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC, 20)};
static const pin_impl_t pin_C21 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC, 21)};
static const pin_impl_t pin_C22 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC, 22)};
static const pin_impl_t pin_C23 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC, 23)};
static const pin_impl_t pin_C24 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC, 24)};
static const pin_impl_t pin_C25 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC, 25)};
static const pin_impl_t pin_C26 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC, 26)};
static const pin_impl_t pin_C27 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC, 27)};
static const pin_impl_t pin_C28 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC, 28)};
static const pin_impl_t pin_C29 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC, 29)};
static const pin_impl_t pin_C30 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC, 30)};
static const pin_impl_t pin_C31 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC, 31)};
static const pin_impl_t pin_C32 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOC, 32)};
#define  C0  ((pin_t)&pin_C0)
#define  C1  ((pin_t)&pin_C1)
#define  C2  ((pin_t)&pin_C2)
#define  C3  ((pin_t)&pin_C3)
#define  C4  ((pin_t)&pin_C4)
#define  C5  ((pin_t)&pin_C5)
#define  C6  ((pin_t)&pin_C6)
#define  C7  ((pin_t)&pin_C7)
#define  C8  ((pin_t)&pin_C8)
#define  C9  ((pin_t)&pin_C9)
#define C10 ((pin_t)&pin_C10)
#define C11 ((pin_t)&pin_C11)
#define C12 ((pin_t)&pin_C12)
#define C13 ((pin_t)&pin_C13)
#define C14 ((pin_t)&pin_C14)
#define C15 ((pin_t)&pin_C15)
#define C16 ((pin_t)&pin_C16)
#define C17 ((pin_t)&pin_C17)
#define C18 ((pin_t)&pin_C18)
#define C19 ((pin_t)&pin_C19)
#define C20 ((pin_t)&pin_C20)
#define C21 ((pin_t)&pin_C21)
#define C22 ((pin_t)&pin_C22)
#define C23 ((pin_t)&pin_C23)
#define C24 ((pin_t)&pin_C24)
#define C25 ((pin_t)&pin_C25)
#define C26 ((pin_t)&pin_C26)
#define C27 ((pin_t)&pin_C27)
#define C28 ((pin_t)&pin_C28)
#define C29 ((pin_t)&pin_C29)
#define C30 ((pin_t)&pin_C30)
#define C31 ((pin_t)&pin_C31)
#define C32 ((pin_t)&pin_C32)
#endif // defined(GPIOC_BASE)


#if defined(GPIOD_BASE)
static const pin_impl_t  pin_D0 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD,  0)};
static const pin_impl_t  pin_D1 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD,  1)};
static const pin_impl_t  pin_D2 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD,  2)};
static const pin_impl_t  pin_D3 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD,  3)};
static const pin_impl_t  pin_D4 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD,  4)};
static const pin_impl_t  pin_D5 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD,  5)};
static const pin_impl_t  pin_D6 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD,  6)};
static const pin_impl_t  pin_D7 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD,  7)};
static const pin_impl_t  pin_D8 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD,  8)};
static const pin_impl_t  pin_D9 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD,  9)};
static const pin_impl_t pin_D10 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD, 10)};
static const pin_impl_t pin_D11 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD, 11)};
static const pin_impl_t pin_D12 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD, 12)};
static const pin_impl_t pin_D13 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD, 13)};
static const pin_impl_t pin_D14 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD, 14)};
static const pin_impl_t pin_D15 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD, 15)};
static const pin_impl_t pin_D16 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD, 16)};
static const pin_impl_t pin_D17 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD, 17)};
static const pin_impl_t pin_D18 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD, 18)};
static const pin_impl_t pin_D19 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD, 19)};
static const pin_impl_t pin_D20 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD, 20)};
static const pin_impl_t pin_D21 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD, 21)};
static const pin_impl_t pin_D22 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD, 22)};
static const pin_impl_t pin_D23 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD, 23)};
static const pin_impl_t pin_D24 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD, 24)};
static const pin_impl_t pin_D25 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD, 25)};
static const pin_impl_t pin_D26 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD, 26)};
static const pin_impl_t pin_D27 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD, 27)};
static const pin_impl_t pin_D28 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD, 28)};
static const pin_impl_t pin_D29 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD, 29)};
static const pin_impl_t pin_D30 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD, 30)};
static const pin_impl_t pin_D31 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD, 31)};
static const pin_impl_t pin_D32 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOD, 32)};
#define  D0  ((pin_t)&pin_D0)
#define  D1  ((pin_t)&pin_D1)
#define  D2  ((pin_t)&pin_D2)
#define  D3  ((pin_t)&pin_D3)
#define  D4  ((pin_t)&pin_D4)
#define  D5  ((pin_t)&pin_D5)
#define  D6  ((pin_t)&pin_D6)
#define  D7  ((pin_t)&pin_D7)
#define  D8  ((pin_t)&pin_D8)
#define  D9  ((pin_t)&pin_D9)
#define D10 ((pin_t)&pin_D10)
#define D11 ((pin_t)&pin_D11)
#define D12 ((pin_t)&pin_D12)
#define D13 ((pin_t)&pin_D13)
#define D14 ((pin_t)&pin_D14)
#define D15 ((pin_t)&pin_D15)
#define D16 ((pin_t)&pin_D16)
#define D17 ((pin_t)&pin_D17)
#define D18 ((pin_t)&pin_D18)
#define D19 ((pin_t)&pin_D19)
#define D20 ((pin_t)&pin_D20)
#define D21 ((pin_t)&pin_D21)
#define D22 ((pin_t)&pin_D22)
#define D23 ((pin_t)&pin_D23)
#define D24 ((pin_t)&pin_D24)
#define D25 ((pin_t)&pin_D25)
#define D26 ((pin_t)&pin_D26)
#define D27 ((pin_t)&pin_D27)
#define D28 ((pin_t)&pin_D28)
#define D29 ((pin_t)&pin_D29)
#define D30 ((pin_t)&pin_D30)
#define D31 ((pin_t)&pin_D31)
#define D32 ((pin_t)&pin_D32)
#endif // defined(GPIOD_BASE)


#if defined(GPIOE_BASE)
static const pin_impl_t  pin_E0 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE,  0)};
static const pin_impl_t  pin_E1 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE,  1)};
static const pin_impl_t  pin_E2 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE,  2)};
static const pin_impl_t  pin_E3 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE,  3)};
static const pin_impl_t  pin_E4 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE,  4)};
static const pin_impl_t  pin_E5 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE,  5)};
static const pin_impl_t  pin_E6 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE,  6)};
static const pin_impl_t  pin_E7 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE,  7)};
static const pin_impl_t  pin_E8 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE,  8)};
static const pin_impl_t  pin_E9 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE,  9)};
static const pin_impl_t pin_E10 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE, 10)};
static const pin_impl_t pin_E11 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE, 11)};
static const pin_impl_t pin_E12 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE, 12)};
static const pin_impl_t pin_E13 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE, 13)};
static const pin_impl_t pin_E14 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE, 14)};
static const pin_impl_t pin_E15 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE, 15)};
static const pin_impl_t pin_E16 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE, 16)};
static const pin_impl_t pin_E17 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE, 17)};
static const pin_impl_t pin_E18 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE, 18)};
static const pin_impl_t pin_E19 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE, 19)};
static const pin_impl_t pin_E20 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE, 20)};
static const pin_impl_t pin_E21 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE, 21)};
static const pin_impl_t pin_E22 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE, 22)};
static const pin_impl_t pin_E23 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE, 23)};
static const pin_impl_t pin_E24 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE, 24)};
static const pin_impl_t pin_E25 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE, 25)};
static const pin_impl_t pin_E26 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE, 26)};
static const pin_impl_t pin_E27 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE, 27)};
static const pin_impl_t pin_E28 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE, 28)};
static const pin_impl_t pin_E29 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE, 29)};
static const pin_impl_t pin_E30 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE, 30)};
static const pin_impl_t pin_E31 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE, 31)};
static const pin_impl_t pin_E32 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOE, 32)};
#define  E0  ((pin_t)&pin_E0)
#define  E1  ((pin_t)&pin_E1)
#define  E2  ((pin_t)&pin_E2)
#define  E3  ((pin_t)&pin_E3)
#define  E4  ((pin_t)&pin_E4)
#define  E5  ((pin_t)&pin_E5)
#define  E6  ((pin_t)&pin_E6)
#define  E7  ((pin_t)&pin_E7)
#define  E8  ((pin_t)&pin_E8)
#define  E9  ((pin_t)&pin_E9)
#define E10 ((pin_t)&pin_E10)
#define E11 ((pin_t)&pin_E11)
#define E12 ((pin_t)&pin_E12)
#define E13 ((pin_t)&pin_E13)
#define E14 ((pin_t)&pin_E14)
#define E15 ((pin_t)&pin_E15)
#define E16 ((pin_t)&pin_E16)
#define E17 ((pin_t)&pin_E17)
#define E18 ((pin_t)&pin_E18)
#define E19 ((pin_t)&pin_E19)
#define E20 ((pin_t)&pin_E20)
#define E21 ((pin_t)&pin_E21)
#define E22 ((pin_t)&pin_E22)
#define E23 ((pin_t)&pin_E23)
#define E24 ((pin_t)&pin_E24)
#define E25 ((pin_t)&pin_E25)
#define E26 ((pin_t)&pin_E26)
#define E27 ((pin_t)&pin_E27)
#define E28 ((pin_t)&pin_E28)
#define E29 ((pin_t)&pin_E29)
#define E30 ((pin_t)&pin_E30)
#define E31 ((pin_t)&pin_E31)
#define E32 ((pin_t)&pin_E32)
#endif // defined(GPIOE_BASE)


#if defined(GPIOF_BASE)
static const pin_impl_t  pin_F0 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOF,  0)};
static const pin_impl_t  pin_F1 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOF,  1)};
static const pin_impl_t  pin_F2 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOF,  2)};
static const pin_impl_t  pin_F3 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOF,  3)};
static const pin_impl_t  pin_F4 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOF,  4)};
static const pin_impl_t  pin_F5 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOF,  5)};
static const pin_impl_t  pin_F6 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOF,  6)};
static const pin_impl_t  pin_F7 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOF,  7)};
static const pin_impl_t  pin_F8 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOF,  8)};
static const pin_impl_t  pin_F9 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOF,  9)};
static const pin_impl_t pin_F10 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOF, 10)};
static const pin_impl_t pin_F11 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOF, 11)};
static const pin_impl_t pin_F12 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOF, 12)};
static const pin_impl_t pin_F13 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOF, 13)};
static const pin_impl_t pin_F14 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOF, 14)};
static const pin_impl_t pin_F15 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOF, 15)};
#define  F0  ((pin_t)&pin_F0)
#define  F1  ((pin_t)&pin_F1)
#define  F2  ((pin_t)&pin_F2)
#define  F3  ((pin_t)&pin_F3)
#define  F4  ((pin_t)&pin_F4)
#define  F5  ((pin_t)&pin_F5)
#define  F6  ((pin_t)&pin_F6)
#define  F7  ((pin_t)&pin_F7)
#define  F8  ((pin_t)&pin_F8)
#define  F9  ((pin_t)&pin_F9)
#define F10 ((pin_t)&pin_F10)
#define F11 ((pin_t)&pin_F11)
#define F12 ((pin_t)&pin_F12)
#define F13 ((pin_t)&pin_F13)
#define F14 ((pin_t)&pin_F14)
#define F15 ((pin_t)&pin_F15)
#endif // defined(GPIOF_BASE)


#if defined(GPIOG_BASE)
static const pin_impl_t  pin_G0 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOG,  0)};
static const pin_impl_t  pin_G1 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOG,  1)};
static const pin_impl_t  pin_G2 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOG,  2)};
static const pin_impl_t  pin_G3 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOG,  3)};
static const pin_impl_t  pin_G4 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOG,  4)};
static const pin_impl_t  pin_G5 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOG,  5)};
static const pin_impl_t  pin_G6 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOG,  6)};
static const pin_impl_t  pin_G7 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOG,  7)};
static const pin_impl_t  pin_G8 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOG,  8)};
static const pin_impl_t  pin_G9 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOG,  9)};
static const pin_impl_t pin_G10 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOG, 10)};
static const pin_impl_t pin_G11 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOG, 11)};
static const pin_impl_t pin_G12 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOG, 12)};
static const pin_impl_t pin_G13 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOG, 13)};
static const pin_impl_t pin_G14 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOG, 14)};
static const pin_impl_t pin_G15 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOG, 15)};
#define  G0  ((pin_t)&pin_G0)
#define  G1  ((pin_t)&pin_G1)
#define  G2  ((pin_t)&pin_G2)
#define  G3  ((pin_t)&pin_G3)
#define  G4  ((pin_t)&pin_G4)
#define  G5  ((pin_t)&pin_G5)
#define  G6  ((pin_t)&pin_G6)
#define  G7  ((pin_t)&pin_G7)
#define  G8  ((pin_t)&pin_G8)
#define  G9  ((pin_t)&pin_G9)
#define G10 ((pin_t)&pin_G10)
#define G11 ((pin_t)&pin_G11)
#define G12 ((pin_t)&pin_G12)
#define G13 ((pin_t)&pin_G13)
#define G14 ((pin_t)&pin_G14)
#define G15 ((pin_t)&pin_G15)
#endif // defined(GPIOG_BASE)


#if defined(GPIOH_BASE)
static const pin_impl_t  pin_H0 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOH,  0)};
static const pin_impl_t  pin_H1 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOH,  1)};
static const pin_impl_t  pin_H2 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOH,  2)};
static const pin_impl_t  pin_H3 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOH,  3)};
static const pin_impl_t  pin_H4 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOH,  4)};
static const pin_impl_t  pin_H5 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOH,  5)};
static const pin_impl_t  pin_H6 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOH,  6)};
static const pin_impl_t  pin_H7 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOH,  7)};
static const pin_impl_t  pin_H8 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOH,  8)};
static const pin_impl_t  pin_H9 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOH,  9)};
static const pin_impl_t pin_H10 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOH, 10)};
static const pin_impl_t pin_H11 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOH, 11)};
static const pin_impl_t pin_H12 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOH, 12)};
static const pin_impl_t pin_H13 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOH, 13)};
static const pin_impl_t pin_H14 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOH, 14)};
static const pin_impl_t pin_H15 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOH, 15)};
#define  H0  ((pin_t)&pin_H0)
#define  H1  ((pin_t)&pin_H1)
#define  H2  ((pin_t)&pin_H2)
#define  H3  ((pin_t)&pin_H3)
#define  H4  ((pin_t)&pin_H4)
#define  H5  ((pin_t)&pin_H5)
#define  H6  ((pin_t)&pin_H6)
#define  H7  ((pin_t)&pin_H7)
#define  H8  ((pin_t)&pin_H8)
#define  H9  ((pin_t)&pin_H9)
#define H10 ((pin_t)&pin_H10)
#define H11 ((pin_t)&pin_H11)
#define H12 ((pin_t)&pin_H12)
#define H13 ((pin_t)&pin_H13)
#define H14 ((pin_t)&pin_H14)
#define H15 ((pin_t)&pin_H15)
#endif // defined(GPIOH_BASE)


#if defined(GPIOI_BASE)
static const pin_impl_t  pin_I0 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOI,  0)};
static const pin_impl_t  pin_I1 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOI,  1)};
static const pin_impl_t  pin_I2 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOI,  2)};
static const pin_impl_t  pin_I3 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOI,  3)};
static const pin_impl_t  pin_I4 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOI,  4)};
static const pin_impl_t  pin_I5 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOI,  5)};
static const pin_impl_t  pin_I6 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOI,  6)};
static const pin_impl_t  pin_I7 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOI,  7)};
static const pin_impl_t  pin_I8 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOI,  8)};
static const pin_impl_t  pin_I9 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOI,  9)};
static const pin_impl_t pin_I10 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOI, 10)};
static const pin_impl_t pin_I11 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOI, 11)};
static const pin_impl_t pin_I12 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOI, 12)};
static const pin_impl_t pin_I13 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOI, 13)};
static const pin_impl_t pin_I14 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOI, 14)};
static const pin_impl_t pin_I15 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOI, 15)};
#define  I0  ((pin_t)&pin_I0)
#define  I1  ((pin_t)&pin_I1)
#define  I2  ((pin_t)&pin_I2)
#define  I3  ((pin_t)&pin_I3)
#define  I4  ((pin_t)&pin_I4)
#define  I5  ((pin_t)&pin_I5)
#define  I6  ((pin_t)&pin_I6)
#define  I7  ((pin_t)&pin_I7)
#define  I8  ((pin_t)&pin_I8)
#define  I9  ((pin_t)&pin_I9)
#define I10 ((pin_t)&pin_I10)
#define I11 ((pin_t)&pin_I11)
#define I12 ((pin_t)&pin_I12)
#define I13 ((pin_t)&pin_I13)
#define I14 ((pin_t)&pin_I14)
#define I15 ((pin_t)&pin_I15)
#endif // defined(GPIOI_BASE)


#if defined(GPIOJ_BASE)
static const pin_impl_t  pin_J0 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOJ,  0)};
static const pin_impl_t  pin_J1 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOJ,  1)};
static const pin_impl_t  pin_J2 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOJ,  2)};
static const pin_impl_t  pin_J3 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOJ,  3)};
static const pin_impl_t  pin_J4 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOJ,  4)};
static const pin_impl_t  pin_J5 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOJ,  5)};
static const pin_impl_t  pin_J6 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOJ,  6)};
static const pin_impl_t  pin_J7 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOJ,  7)};
static const pin_impl_t  pin_J8 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOJ,  8)};
static const pin_impl_t  pin_J9 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOJ,  9)};
static const pin_impl_t pin_J10 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOJ, 10)};
static const pin_impl_t pin_J11 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOJ, 11)};
static const pin_impl_t pin_J12 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOJ, 12)};
static const pin_impl_t pin_J13 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOJ, 13)};
static const pin_impl_t pin_J14 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOJ, 14)};
static const pin_impl_t pin_J15 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOJ, 15)};
#define  J0  ((pin_t)&pin_J0)
#define  J1  ((pin_t)&pin_J1)
#define  J2  ((pin_t)&pin_J2)
#define  J3  ((pin_t)&pin_J3)
#define  J4  ((pin_t)&pin_J4)
#define  J5  ((pin_t)&pin_J5)
#define  J6  ((pin_t)&pin_J6)
#define  J7  ((pin_t)&pin_J7)
#define  J8  ((pin_t)&pin_J8)
#define  J9  ((pin_t)&pin_J9)
#define J10 ((pin_t)&pin_J10)
#define J11 ((pin_t)&pin_J11)
#define J12 ((pin_t)&pin_J12)
#define J13 ((pin_t)&pin_J13)
#define J14 ((pin_t)&pin_J14)
#define J15 ((pin_t)&pin_J15)
#endif // defined(GPIOJ_BASE)


// Keyboards can `#define KEYBOARD_REQUIRES_GPIOK` if they need to access GPIO-K pins. These conflict with a whole
// bunch of layout definitions, so it's intentionally left out unless absolutely required -- in that case, the
// keyboard designer should use a different symbol when defining their layout macros.
#ifdef KEYBOARD_REQUIRES_GPIOK
static const pin_impl_t  pin_K0 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOK,  0)};
static const pin_impl_t  pin_K1 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOK,  1)};
static const pin_impl_t  pin_K2 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOK,  2)};
static const pin_impl_t  pin_K3 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOK,  3)};
static const pin_impl_t  pin_K4 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOK,  4)};
static const pin_impl_t  pin_K5 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOK,  5)};
static const pin_impl_t  pin_K6 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOK,  6)};
static const pin_impl_t  pin_K7 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOK,  7)};
static const pin_impl_t  pin_K8 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOK,  8)};
static const pin_impl_t  pin_K9 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOK,  9)};
static const pin_impl_t pin_K10 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOK, 10)};
static const pin_impl_t pin_K11 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOK, 11)};
static const pin_impl_t pin_K12 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOK, 12)};
static const pin_impl_t pin_K13 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOK, 13)};
static const pin_impl_t pin_K14 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOK, 14)};
static const pin_impl_t pin_K15 = {.type = PIN_MCU, .mcu_pin = PAL_LINE(GPIOK, 15)};
#define  K0  ((pin_t)&pin_K0)
#define  K1  ((pin_t)&pin_K1)
#define  K2  ((pin_t)&pin_K2)
#define  K3  ((pin_t)&pin_K3)
#define  K4  ((pin_t)&pin_K4)
#define  K5  ((pin_t)&pin_K5)
#define  K6  ((pin_t)&pin_K6)
#define  K7  ((pin_t)&pin_K7)
#define  K8  ((pin_t)&pin_K8)
#define  K9  ((pin_t)&pin_K9)
#define K10 ((pin_t)&pin_K10)
#define K11 ((pin_t)&pin_K11)
#define K12 ((pin_t)&pin_K12)
#define K13 ((pin_t)&pin_K13)
#define K14 ((pin_t)&pin_K14)
#define K15 ((pin_t)&pin_K15)
#endif
