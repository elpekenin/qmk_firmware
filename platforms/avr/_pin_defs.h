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

#include <avr/io.h>

#define PORT_SHIFTER 4 // this may be 4 for all AVR chips

// If you want to add more to this list, reference the PINx definitions in these header
// files: https://github.com/vancegroup-mirrors/avr-libc/tree/master/avr-libc/include/avr

#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega16U4__)
#    define ADDRESS_BASE 0x00
#    define PINB_ADDRESS 0x3
#    define PINC_ADDRESS 0x6
#    define PIND_ADDRESS 0x9
#    define PINE_ADDRESS 0xC
#    define PINF_ADDRESS 0xF
#elif defined(__AVR_AT90USB162__) || defined(__AVR_ATmega32U2__) || defined(__AVR_ATmega16U2__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
#    define ADDRESS_BASE 0x00
#    define PINB_ADDRESS 0x3
#    define PINC_ADDRESS 0x6
#    define PIND_ADDRESS 0x9
#elif defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__) || defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__)
#    define ADDRESS_BASE 0x00
#    define PINA_ADDRESS 0x0
#    define PINB_ADDRESS 0x3
#    define PINC_ADDRESS 0x6
#    define PIND_ADDRESS 0x9
#    define PINE_ADDRESS 0xC
#    define PINF_ADDRESS 0xF
#elif defined(__AVR_ATmega32A__)
#    define ADDRESS_BASE 0x10
#    define PIND_ADDRESS 0x0
#    define PINC_ADDRESS 0x3
#    define PINB_ADDRESS 0x6
#    define PINA_ADDRESS 0x9
#elif defined(__AVR_ATtiny85__)
#    define ADDRESS_BASE 0x10
#    define PINB_ADDRESS 0x6
#else
#    error "Pins are not defined"
#endif

#define PINDEF(port, pin) ((PIN##port##_ADDRESS << PORT_SHIFTER) | pin)

#define _PIN_ADDRESS(p, offset) _SFR_IO8(ADDRESS_BASE + ((p) >> PORT_SHIFTER) + (offset))
// Port X Input Pins Address
#define PINx_ADDRESS(p) _PIN_ADDRESS(p, 0)
// Port X Data Direction Register,  0:input 1:output
#define DDRx_ADDRESS(p) _PIN_ADDRESS(p, 1)
// Port X Data Register
#define PORTx_ADDRESS(p) _PIN_ADDRESS(p, 2)

/* I/O pins */
#ifdef PORTA
#    define PIN_A0 PINDEF(A, 0)
#    define PIN_A1 PINDEF(A, 1)
#    define PIN_A2 PINDEF(A, 2)
#    define PIN_A3 PINDEF(A, 3)
#    define PIN_A4 PINDEF(A, 4)
#    define PIN_A5 PINDEF(A, 5)
#    define PIN_A6 PINDEF(A, 6)
#    define PIN_A7 PINDEF(A, 7)
static const pin_impl_t pin_A0 = {.type = PIN_MCU, .mcu_pin = PIN_A0};
static const pin_impl_t pin_A1 = {.type = PIN_MCU, .mcu_pin = PIN_A1};
static const pin_impl_t pin_A2 = {.type = PIN_MCU, .mcu_pin = PIN_A2};
static const pin_impl_t pin_A3 = {.type = PIN_MCU, .mcu_pin = PIN_A3};
static const pin_impl_t pin_A4 = {.type = PIN_MCU, .mcu_pin = PIN_A4};
static const pin_impl_t pin_A5 = {.type = PIN_MCU, .mcu_pin = PIN_A5};
static const pin_impl_t pin_A6 = {.type = PIN_MCU, .mcu_pin = PIN_A6};
static const pin_impl_t pin_A7 = {.type = PIN_MCU, .mcu_pin = PIN_A7};
#    define A0 ((pin_t)&pin_A0)
#    define A1 ((pin_t)&pin_A1)
#    define A2 ((pin_t)&pin_A2)
#    define A3 ((pin_t)&pin_A3)
#    define A4 ((pin_t)&pin_A4)
#    define A5 ((pin_t)&pin_A5)
#    define A6 ((pin_t)&pin_A6)
#    define A7 ((pin_t)&pin_A7)
#endif
#ifdef PORTB
#    define PIN_B0 PINDEF(B, 0)
#    define PIN_B1 PINDEF(B, 1)
#    define PIN_B2 PINDEF(B, 2)
#    define PIN_B3 PINDEF(B, 3)
#    define PIN_B4 PINDEF(B, 4)
#    define PIN_B5 PINDEF(B, 5)
#    define PIN_B6 PINDEF(B, 6)
#    define PIN_B7 PINDEF(B, 7)
static const pin_impl_t pin_B0 = {.type = PIN_MCU, .mcu_pin = PIN_B0};
static const pin_impl_t pin_B1 = {.type = PIN_MCU, .mcu_pin = PIN_B1};
static const pin_impl_t pin_B2 = {.type = PIN_MCU, .mcu_pin = PIN_B2};
static const pin_impl_t pin_B3 = {.type = PIN_MCU, .mcu_pin = PIN_B3};
static const pin_impl_t pin_B4 = {.type = PIN_MCU, .mcu_pin = PIN_B4};
static const pin_impl_t pin_B5 = {.type = PIN_MCU, .mcu_pin = PIN_B5};
static const pin_impl_t pin_B6 = {.type = PIN_MCU, .mcu_pin = PIN_B6};
static const pin_impl_t pin_B7 = {.type = PIN_MCU, .mcu_pin = PIN_B7};
#    define B0 ((pin_t)&pin_B0)
#    define B1 ((pin_t)&pin_B1)
#    define B2 ((pin_t)&pin_B2)
#    define B3 ((pin_t)&pin_B3)
#    define B4 ((pin_t)&pin_B4)
#    define B5 ((pin_t)&pin_B5)
#    define B6 ((pin_t)&pin_B6)
#    define B7 ((pin_t)&pin_B7)
#endif
#ifdef PORTC
#    define PIN_C0 PINDEF(C, 0)
#    define PIN_C1 PINDEF(C, 1)
#    define PIN_C2 PINDEF(C, 2)
#    define PIN_C3 PINDEF(C, 3)
#    define PIN_C4 PINDEF(C, 4)
#    define PIN_C5 PINDEF(C, 5)
#    define PIN_C6 PINDEF(C, 6)
#    define PIN_C7 PINDEF(C, 7)
static const pin_impl_t pin_C0 = {.type = PIN_MCU, .mcu_pin = PIN_C0};
static const pin_impl_t pin_C1 = {.type = PIN_MCU, .mcu_pin = PIN_C1};
static const pin_impl_t pin_C2 = {.type = PIN_MCU, .mcu_pin = PIN_C2};
static const pin_impl_t pin_C3 = {.type = PIN_MCU, .mcu_pin = PIN_C3};
static const pin_impl_t pin_C4 = {.type = PIN_MCU, .mcu_pin = PIN_C4};
static const pin_impl_t pin_C5 = {.type = PIN_MCU, .mcu_pin = PIN_C5};
static const pin_impl_t pin_C6 = {.type = PIN_MCU, .mcu_pin = PIN_C6};
static const pin_impl_t pin_C7 = {.type = PIN_MCU, .mcu_pin = PIN_C7};
#    define C0 ((pin_t)&pin_C0)
#    define C1 ((pin_t)&pin_C1)
#    define C2 ((pin_t)&pin_C2)
#    define C3 ((pin_t)&pin_C3)
#    define C4 ((pin_t)&pin_C4)
#    define C5 ((pin_t)&pin_C5)
#    define C6 ((pin_t)&pin_C6)
#    define C7 ((pin_t)&pin_C7)
#endif
#ifdef PORTD
#    define PIN_D0 PINDEF(D, 0)
#    define PIN_D1 PINDEF(D, 1)
#    define PIN_D2 PINDEF(D, 2)
#    define PIN_D3 PINDEF(D, 3)
#    define PIN_D4 PINDEF(D, 4)
#    define PIN_D5 PINDEF(D, 5)
#    define PIN_D6 PINDEF(D, 6)
#    define PIN_D7 PINDEF(D, 7)
static const pin_impl_t pin_D0 = {.type = PIN_MCU, .mcu_pin = PIN_D0};
static const pin_impl_t pin_D1 = {.type = PIN_MCU, .mcu_pin = PIN_D1};
static const pin_impl_t pin_D2 = {.type = PIN_MCU, .mcu_pin = PIN_D2};
static const pin_impl_t pin_D3 = {.type = PIN_MCU, .mcu_pin = PIN_D3};
static const pin_impl_t pin_D4 = {.type = PIN_MCU, .mcu_pin = PIN_D4};
static const pin_impl_t pin_D5 = {.type = PIN_MCU, .mcu_pin = PIN_D5};
static const pin_impl_t pin_D6 = {.type = PIN_MCU, .mcu_pin = PIN_D6};
static const pin_impl_t pin_D7 = {.type = PIN_MCU, .mcu_pin = PIN_D7};
#    define D0 ((pin_t)&pin_D0)
#    define D1 ((pin_t)&pin_D1)
#    define D2 ((pin_t)&pin_D2)
#    define D3 ((pin_t)&pin_D3)
#    define D4 ((pin_t)&pin_D4)
#    define D5 ((pin_t)&pin_D5)
#    define D6 ((pin_t)&pin_D6)
#    define D7 ((pin_t)&pin_D7)
#endif
#ifdef PORTE
#    define PIN_E0 PINDEF(E, 0)
#    define PIN_E1 PINDEF(E, 1)
#    define PIN_E2 PINDEF(E, 2)
#    define PIN_E3 PINDEF(E, 3)
#    define PIN_E4 PINDEF(E, 4)
#    define PIN_E5 PINDEF(E, 5)
#    define PIN_E6 PINDEF(E, 6)
#    define PIN_E7 PINDEF(E, 7)
static const pin_impl_t pin_E0 = {.type = PIN_MCU, .mcu_pin = PIN_E0};
static const pin_impl_t pin_E1 = {.type = PIN_MCU, .mcu_pin = PIN_E1};
static const pin_impl_t pin_E2 = {.type = PIN_MCU, .mcu_pin = PIN_E2};
static const pin_impl_t pin_E3 = {.type = PIN_MCU, .mcu_pin = PIN_E3};
static const pin_impl_t pin_E4 = {.type = PIN_MCU, .mcu_pin = PIN_E4};
static const pin_impl_t pin_E5 = {.type = PIN_MCU, .mcu_pin = PIN_E5};
static const pin_impl_t pin_E6 = {.type = PIN_MCU, .mcu_pin = PIN_E6};
static const pin_impl_t pin_E7 = {.type = PIN_MCU, .mcu_pin = PIN_E7};
#    define E0 ((pin_t)&pin_E0)
#    define E1 ((pin_t)&pin_E1)
#    define E2 ((pin_t)&pin_E2)
#    define E3 ((pin_t)&pin_E3)
#    define E4 ((pin_t)&pin_E4)
#    define E5 ((pin_t)&pin_E5)
#    define E6 ((pin_t)&pin_E6)
#    define E7 ((pin_t)&pin_E7)
#endif
#ifdef PORTF
#    define PIN_F0 PINDEF(F, 0)
#    define PIN_F1 PINDEF(F, 1)
#    define PIN_F2 PINDEF(F, 2)
#    define PIN_F3 PINDEF(F, 3)
#    define PIN_F4 PINDEF(F, 4)
#    define PIN_F5 PINDEF(F, 5)
#    define PIN_F6 PINDEF(F, 6)
#    define PIN_F7 PINDEF(F, 7)
static const pin_impl_t pin_F0 = {.type = PIN_MCU, .mcu_pin = PIN_F0};
static const pin_impl_t pin_F1 = {.type = PIN_MCU, .mcu_pin = PIN_F1};
static const pin_impl_t pin_F2 = {.type = PIN_MCU, .mcu_pin = PIN_F2};
static const pin_impl_t pin_F3 = {.type = PIN_MCU, .mcu_pin = PIN_F3};
static const pin_impl_t pin_F4 = {.type = PIN_MCU, .mcu_pin = PIN_F4};
static const pin_impl_t pin_F5 = {.type = PIN_MCU, .mcu_pin = PIN_F5};
static const pin_impl_t pin_F6 = {.type = PIN_MCU, .mcu_pin = PIN_F6};
static const pin_impl_t pin_F7 = {.type = PIN_MCU, .mcu_pin = PIN_F7};
#    define F0 ((pin_t)&pin_F0)
#    define F1 ((pin_t)&pin_F1)
#    define F2 ((pin_t)&pin_F2)
#    define F3 ((pin_t)&pin_F3)
#    define F4 ((pin_t)&pin_F4)
#    define F5 ((pin_t)&pin_F5)
#    define F6 ((pin_t)&pin_F6)
#    define F7 ((pin_t)&pin_F7)
#endif
