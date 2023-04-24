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


#ifdef PORTA
static const pin_impl_t pin_A0 = {.type = PIN_MCU, .mcu_pin = PINDEF(A, 0)};
static const pin_impl_t pin_A1 = {.type = PIN_MCU, .mcu_pin = PINDEF(A, 1)};
static const pin_impl_t pin_A2 = {.type = PIN_MCU, .mcu_pin = PINDEF(A, 2)};
static const pin_impl_t pin_A3 = {.type = PIN_MCU, .mcu_pin = PINDEF(A, 3)};
static const pin_impl_t pin_A4 = {.type = PIN_MCU, .mcu_pin = PINDEF(A, 4)};
static const pin_impl_t pin_A5 = {.type = PIN_MCU, .mcu_pin = PINDEF(A, 5)};
static const pin_impl_t pin_A6 = {.type = PIN_MCU, .mcu_pin = PINDEF(A, 6)};
static const pin_impl_t pin_A7 = {.type = PIN_MCU, .mcu_pin = PINDEF(A, 7)};
#define A0 ((pin_t)&pin_A0)
#define A1 ((pin_t)&pin_A1)
#define A2 ((pin_t)&pin_A2)
#define A3 ((pin_t)&pin_A3)
#define A4 ((pin_t)&pin_A4)
#define A5 ((pin_t)&pin_A5)
#define A6 ((pin_t)&pin_A6)
#define A7 ((pin_t)&pin_A7)
#endif


#ifdef PORTB
static const pin_impl_t pin_B0 = {.type = PIN_MCU, .mcu_pin = PINDEF(B, 0)};
static const pin_impl_t pin_B1 = {.type = PIN_MCU, .mcu_pin = PINDEF(B, 1)};
static const pin_impl_t pin_B2 = {.type = PIN_MCU, .mcu_pin = PINDEF(B, 2)};
static const pin_impl_t pin_B3 = {.type = PIN_MCU, .mcu_pin = PINDEF(B, 3)};
static const pin_impl_t pin_B4 = {.type = PIN_MCU, .mcu_pin = PINDEF(B, 4)};
static const pin_impl_t pin_B5 = {.type = PIN_MCU, .mcu_pin = PINDEF(B, 5)};
static const pin_impl_t pin_B6 = {.type = PIN_MCU, .mcu_pin = PINDEF(B, 6)};
static const pin_impl_t pin_B7 = {.type = PIN_MCU, .mcu_pin = PINDEF(B, 7)};
#define B0 ((pin_t)&pin_B0)
#define B1 ((pin_t)&pin_B1)
#define B2 ((pin_t)&pin_B2)
#define B3 ((pin_t)&pin_B3)
#define B4 ((pin_t)&pin_B4)
#define B5 ((pin_t)&pin_B5)
#define B6 ((pin_t)&pin_B6)
#define B7 ((pin_t)&pin_B7)
#endif


#ifdef PORTC
static const pin_impl_t pin_C0 = {.type = PIN_MCU, .mcu_pin = PINDEF(C, 0)};
static const pin_impl_t pin_C1 = {.type = PIN_MCU, .mcu_pin = PINDEF(C, 1)};
static const pin_impl_t pin_C2 = {.type = PIN_MCU, .mcu_pin = PINDEF(C, 2)};
static const pin_impl_t pin_C3 = {.type = PIN_MCU, .mcu_pin = PINDEF(C, 3)};
static const pin_impl_t pin_C4 = {.type = PIN_MCU, .mcu_pin = PINDEF(C, 4)};
static const pin_impl_t pin_C5 = {.type = PIN_MCU, .mcu_pin = PINDEF(C, 5)};
static const pin_impl_t pin_C6 = {.type = PIN_MCU, .mcu_pin = PINDEF(C, 6)};
static const pin_impl_t pin_C7 = {.type = PIN_MCU, .mcu_pin = PINDEF(C, 7)};
#define C0 ((pin_t)&pin_C0)
#define C1 ((pin_t)&pin_C1)
#define C2 ((pin_t)&pin_C2)
#define C3 ((pin_t)&pin_C3)
#define C4 ((pin_t)&pin_C4)
#define C5 ((pin_t)&pin_C5)
#define C6 ((pin_t)&pin_C6)
#define C7 ((pin_t)&pin_C7)
#endif


#ifdef PORTD
static const pin_impl_t pin_D0 = {.type = PIN_MCU, .mcu_pin = PINDEF(D, 0)};
static const pin_impl_t pin_D1 = {.type = PIN_MCU, .mcu_pin = PINDEF(D, 1)};
static const pin_impl_t pin_D2 = {.type = PIN_MCU, .mcu_pin = PINDEF(D, 2)};
static const pin_impl_t pin_D3 = {.type = PIN_MCU, .mcu_pin = PINDEF(D, 3)};
static const pin_impl_t pin_D4 = {.type = PIN_MCU, .mcu_pin = PINDEF(D, 4)};
static const pin_impl_t pin_D5 = {.type = PIN_MCU, .mcu_pin = PINDEF(D, 5)};
static const pin_impl_t pin_D6 = {.type = PIN_MCU, .mcu_pin = PINDEF(D, 6)};
static const pin_impl_t pin_D7 = {.type = PIN_MCU, .mcu_pin = PINDEF(D, 7)};
#define D0 ((pin_t)&pin_D0)
#define D1 ((pin_t)&pin_D1)
#define D2 ((pin_t)&pin_D2)
#define D3 ((pin_t)&pin_D3)
#define D4 ((pin_t)&pin_D4)
#define D5 ((pin_t)&pin_D5)
#define D6 ((pin_t)&pin_D6)
#define D7 ((pin_t)&pin_D7)
#endif


#ifdef PORTE
static const pin_impl_t pin_E0 = {.type = PIN_MCU, .mcu_pin = PINDEF(E, 0)};
static const pin_impl_t pin_E1 = {.type = PIN_MCU, .mcu_pin = PINDEF(E, 1)};
static const pin_impl_t pin_E2 = {.type = PIN_MCU, .mcu_pin = PINDEF(E, 2)};
static const pin_impl_t pin_E3 = {.type = PIN_MCU, .mcu_pin = PINDEF(E, 3)};
static const pin_impl_t pin_E4 = {.type = PIN_MCU, .mcu_pin = PINDEF(E, 4)};
static const pin_impl_t pin_E5 = {.type = PIN_MCU, .mcu_pin = PINDEF(E, 5)};
static const pin_impl_t pin_E6 = {.type = PIN_MCU, .mcu_pin = PINDEF(E, 6)};
static const pin_impl_t pin_E7 = {.type = PIN_MCU, .mcu_pin = PINDEF(E, 7)};
#define E0 ((pin_t)&pin_E0)
#define E1 ((pin_t)&pin_E1)
#define E2 ((pin_t)&pin_E2)
#define E3 ((pin_t)&pin_E3)
#define E4 ((pin_t)&pin_E4)
#define E5 ((pin_t)&pin_E5)
#define E6 ((pin_t)&pin_E6)
#define E7 ((pin_t)&pin_E7)
#endif


#ifdef PORTF
static const pin_impl_t pin_F0 = {.type = PIN_MCU, .mcu_pin = PINDEF(F, 0)};
static const pin_impl_t pin_F1 = {.type = PIN_MCU, .mcu_pin = PINDEF(F, 1)};
static const pin_impl_t pin_F2 = {.type = PIN_MCU, .mcu_pin = PINDEF(F, 2)};
static const pin_impl_t pin_F3 = {.type = PIN_MCU, .mcu_pin = PINDEF(F, 3)};
static const pin_impl_t pin_F4 = {.type = PIN_MCU, .mcu_pin = PINDEF(F, 4)};
static const pin_impl_t pin_F5 = {.type = PIN_MCU, .mcu_pin = PINDEF(F, 5)};
static const pin_impl_t pin_F6 = {.type = PIN_MCU, .mcu_pin = PINDEF(F, 6)};
static const pin_impl_t pin_F7 = {.type = PIN_MCU, .mcu_pin = PINDEF(F, 7)};
#define F0 ((pin_t)&pin_F0)
#define F1 ((pin_t)&pin_F1)
#define F2 ((pin_t)&pin_F2)
#define F3 ((pin_t)&pin_F3)
#define F4 ((pin_t)&pin_F4)
#define F5 ((pin_t)&pin_F5)
#define F6 ((pin_t)&pin_F6)
#define F7 ((pin_t)&pin_F7)
#endif
