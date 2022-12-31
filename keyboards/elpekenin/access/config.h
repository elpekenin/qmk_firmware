// Copyright 2022 Pablo Martinez (@elpekenin)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

// =======
// Debugging
#define QUANTUM_PAINTER_DEBUG
// #define DEBUG_MATRIX_SCAN_RATE
#define INIT_DELAY 2000
#define TOUCH_SCREEN_DEBUG

// =======
// Painter
#define QUANTUM_PAINTER_NUM_IMAGES 16
#define SURFACE_NUM_DEVICES 2
#define QUANTUM_PAINTER_NUM_DISPLAYS 4 // <- Used for custom QP over XAP
#define QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE 65536


// =======
// Power indicator
#define POWER_LED_PIN GP25

// =======
// SPI config
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP2
#define SPI_MOSI_PIN GP3
#define SPI_MISO_PIN GP4
#define SPI_DC_PIN GP6
#define SPI_MODE 0
#define SPI_DIV 16

// -- Displays
#define ILI9163_ROTATION 0
#define ILI9163_CS_PIN GP10
#define ILI9163_RST_PIN GP11

#define ILI9341_ROTATION 2
#define ILI9341_CS_PIN GP12
#define ILI9341_RST_PIN GP13
#define ILI9341_TOUCH_CS_PIN GP14
#define ILI9341_TOUCH_IRQ_PIN GP15

#define ILI9486_ROTATION 1
#define ILI9486_CS_PIN GP5
#define ILI9486_RST_PIN GP7
#define ILI9486_TOUCH_CS_PIN GP8
#define ILI9486_TOUCH_IRQ_PIN GP9

#define IL91874_ROTATION 0
#define IL91874_CS_PIN GP18
#define IL91874_RST_PIN GP1

#define SSD1680_ROTATION 0
#define SSD1680_CS_PIN GP18
#define SSD1680_RST_PIN GP1

// =======
// RGB
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define RGB_DI_PIN GP0
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGB_MATRIX_LED_COUNT 16
#define RGB_MATRIX_TIMEOUT 300
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 10
#define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#if defined(ONE_HAND_ENABLE)
#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_onehand_mode
#else
#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT
#endif   // ONE_HAND_ENABLE
#define WS2812_PIO_USE_PIO1

// =======
// Pointing device
#define ANALOG_JOYSTICK_CLICK_PIN  GP15
#define ANALOG_JOYSTICK_X_AXIS_PIN GP28
#define ANALOG_JOYSTICK_Y_AXIS_PIN GP27

// =======
// Audio
#define AUDIO_PIN GP11
#define AUDIO_PWM_DRIVER PWMD5
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_B
#define AUDIO_ENABLE_TONE_MULTIPLEXING
#define AUDIO_TONE_MULTIPLEXING_RATE_DEFAULT 10
#define AUDIO_INIT_DELAY 0
#define STARTUP_SONG SONG(ONE_UP_SOUND)
#define GOODBYE_SONG SONG(COIN_SOUND)

// ==================================================================================================
// SOME MAGIC DOWN HERE
// - Real size, used for init function
#define _ILI9163_WIDTH 129
#define _ILI9163_HEIGHT 128
#define _ILI9341_WIDTH 240
#define _ILI9341_HEIGHT 320
#define _ILI9486_WIDTH 320
#define _ILI9486_HEIGHT 480
#define _IL91874_WIDTH 176
#define _IL91874_HEIGHT 264
#define _SSD1680_WIDTH 250
#define _SSD1680_HEIGHT 122

// - Check rotation
#if !(ILI9163_ROTATION == 0 || ILI9163_ROTATION == 1 || ILI9163_ROTATION == 2 || ILI9163_ROTATION == 3)
#    error ILI9163_ROTATION has to be within 0-3 (both included)
#endif
#if !(ILI9341_ROTATION == 0 || ILI9341_ROTATION == 1 || ILI9341_ROTATION == 2 || ILI9341_ROTATION == 3)
#    error ILI9341_ROTATION has to be within 0-3 (both included)
#endif
#if !(ILI9486_ROTATION == 0 || ILI9486_ROTATION == 1 || ILI9486_ROTATION == 2 || ILI9486_ROTATION == 3)
#    error ILI9486_ROTATION has to be within 0-3 (both included)
#endif
#if !(IL91874_ROTATION == 0 || IL91874_ROTATION == 1 || IL91874_ROTATION == 2 || IL91874_ROTATION == 3)
#    error IL91874_ROTATION has to be within 0-3 (both included)
#endif
#if !(SSD1680_ROTATION == 0 || SSD1680_ROTATION == 1 || SSD1680_ROTATION == 2 || SSD1680_ROTATION == 3)
#    error SSD1680_ROTATION has to be within 0-3 (both included)
#endif

// - Virtual size, used for drawing funcs
#if (ILI9163_ROTATION % 2 == 0)
#    define ILI9163_WIDTH  _ILI9163_WIDTH
#    define ILI9163_HEIGHT _ILI9163_HEIGHT
#else
#    define ILI9163_WIDTH  _ILI9163_HEIGHT
#    define ILI9163_HEIGHT _ILI9163_WIDTH
#endif

#if (ILI9341_ROTATION % 2 == 0)
#    define ILI9341_WIDTH  _ILI9341_WIDTH
#    define ILI9341_HEIGHT _ILI9341_HEIGHT
#else
#    define ILI9341_WIDTH  _ILI9341_HEIGHT
#    define ILI9341_HEIGHT _ILI9341_WIDTH
#endif

#if (ILI9486_ROTATION % 2 == 0)
#    define ILI9486_WIDTH  _ILI9486_WIDTH
#    define ILI9486_HEIGHT _ILI9486_HEIGHT
#else
#    define ILI9486_WIDTH  _ILI9486_HEIGHT
#    define ILI9486_HEIGHT _ILI9486_WIDTH
#endif

#if (IL91874_ROTATION % 2 == 0)
#    define IL91874_WIDTH  _IL91874_WIDTH
#    define IL91874_HEIGHT _IL91874_HEIGHT
#else
#    define IL91874_WIDTH  _IL91874_HEIGHT
#    define IL91874_HEIGHT _IL91874_WIDTH
#endif

#if (SSD1680_ROTATION % 2 == 0)
#    define SSD1680_WIDTH  _SSD1680_WIDTH
#    define SSD1680_HEIGHT _SSD1680_HEIGHT
#else
#    define SSD1680_WIDTH  _SSD1680_HEIGHT
#    define SSD1680_HEIGHT _SSD1680_WIDTH
#endif

// - Default values
#if !defined(INIT_DELAY)
#    define INIT_DELAY 5
#endif // INIT_DELAY
