/*
Copyright 2018 Massdrop Inc.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "arm_atsam_protocol.h"
#include "spi_master.h"
#include "gpio.h"

/* Determine bits to set for mux selection */
#if SPI_DATAOUT_PIN % 2 == 0
#    define SPI_DATAOUT_MUX_SEL PMUXE
#else
#    define SPI_DATAOUT_MUX_SEL PMUXO
#endif

/* Determine bits to set for mux selection */
#if SPI_SCLK_PIN % 2 == 0
#    define SPI_SCLK_MUX_SEL PMUXE
#else
#    define SPI_SCLK_MUX_SEL PMUXO
#endif

static bool spiStarted = false;
static pin_t currentSlavePin;

__attribute__((weak)) void spi_init(void) {
    static bool is_initialised = false;
    if (!is_initialised) {
        mcu_pin_t sck  = 0;
        bool sck_real  = get_mcu_pin(SPI_SCLK_PIN, &sck);
        mcu_pin_t mosi = 0;
        bool mosi_real = get_mcu_pin(SPI_DATAOUT_PIN, &mosi);

        if (!sck_real) {
            dprintln("Can't configure SPI with SCK being a virtual pin");
            return;
        }

        is_initialised = true;

        DBGC(DC_SPI_INIT_BEGIN);

        CLK_set_spi_freq(CHAN_SERCOM_SPI, FREQ_SPI_DEFAULT);

        // Set up MCU SPI pins
        PORT->Group[SAMD_PORT(sck)].PMUX[SAMD_PIN(sck) / 2].bit.SPI_SCLK_MUX_SEL          = SPI_SCLK_MUX;    // MUX select for sercom
        PORT->Group[SAMD_PORT(sck)].PINCFG[SAMD_PIN(sck)].bit.PMUXEN                      = 1;               // MUX Enable

        if (mosi_real) {
            PORT->Group[SAMD_PORT(mosi)].PMUX[SAMD_PIN(mosi) / 2].bit.SPI_DATAOUT_MUX_SEL = SPI_DATAOUT_MUX; // MUX select for sercom
            PORT->Group[SAMD_PORT(mosi)].PINCFG[SAMD_PIN(mosi)].bit.PMUXEN                = 1;               // MUX Enable
        } else {
            dprintln("Configuring SPI with a virtual MOSI pin, leading to the signal being lost");
        }

        DBGC(DC_SPI_INIT_COMPLETE);
        spiStarted = false;
    }
}

bool spi_start(pin_t csPin, bool lsbFirst, uint8_t mode, uint16_t divisor) {
    if (spiStarted) {
        return false;
    }

    if (csPin == NO_PIN) {
        dprintln("Starting SPI without CS pin");
    }

    spiStarted = true;

    currentSlavePin = csPin;
    setPinOutput(csPin);
    writePinLow(csPin);

    SPI_SERCOM->SPI.CTRLA.bit.DORD = lsbFirst; // Data Order - LSB is transferred first
    SPI_SERCOM->SPI.CTRLA.bit.CPOL = 1;        // Clock Polarity - SCK high when idle. Leading edge of cycle is falling. Trailing rising.
    SPI_SERCOM->SPI.CTRLA.bit.CPHA = 1;        // Clock Phase - Leading Edge Falling, change, Trailing Edge - Rising, sample
    SPI_SERCOM->SPI.CTRLA.bit.DIPO = 3;        // Data In Pinout - SERCOM PAD[3] is used as data input (Configure away from DOPO. Not using input.)
    SPI_SERCOM->SPI.CTRLA.bit.DOPO = 0;        // Data Output PAD[0], Serial Clock PAD[1]
    SPI_SERCOM->SPI.CTRLA.bit.MODE = 3;        // Operating Mode - Master operation

    SPI_SERCOM->SPI.CTRLA.bit.ENABLE = 1; // Enable - Peripheral is enabled or being enabled
    while (SPI_SERCOM->SPI.SYNCBUSY.bit.ENABLE) {
        DBGC(DC_SPI_SYNC_ENABLING);
    }
    return true;
}

spi_status_t spi_transmit(const uint8_t *data, uint16_t length) {
    while (!(SPI_SERCOM->SPI.INTFLAG.bit.DRE)) {
        DBGC(DC_SPI_WRITE_DRE);
    }

    for (uint16_t i = 0; i < length; i++) {
        SPI_SERCOM->SPI.DATA.bit.DATA = data[i];
        while (!(SPI_SERCOM->SPI.INTFLAG.bit.TXC)) {
            DBGC(DC_SPI_WRITE_TXC_1);
        }
    }

    return SPI_STATUS_SUCCESS;
}

void spi_stop(void) {
    if (spiStarted) {
        setPinOutput(currentSlavePin);
        writePinHigh(currentSlavePin);
        spiStarted = false;
    }
}

// Not implemented yet....

spi_status_t spi_write(uint8_t data);

spi_status_t spi_read(void);

spi_status_t spi_receive(uint8_t *data, uint16_t length);
