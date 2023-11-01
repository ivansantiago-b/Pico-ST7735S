#ifndef ST7735S_H_
#define ST7735S_H_

#include "hardware/spi.h"
#include "hardware/gpio.h"

#define ST7735S_CS 5  /** CS pin */
#define ST7735S_DC 6  /** DC pin */
#define ST7735S_SDA 3 /** SDA pin */
#define ST7735S_SCL 2 /** SCL pin */

#define ST7735S_WIDTH 80         /** Display width */
#define ST7735S_HEIGHT 160       /** Display height */
#define ST7735S_X_OFFSET 26      /** X offset */
#define ST7735S_Y_OFFSET 1       /** Y offset */
#define ST7735S_FRAME_SIZE 25600 /** Frame size in bytes */

#define ST7735S_NOP 0x00       /** No operation */
#define ST7735S_SWRESET 0x01   /** Software reset */
#define ST7735S_RDDID 0x04     /** Read display ID: Return 4 parameters */
#define ST7735S_RDDST 0x09     /** Read display status: Return 5 parameters */
#define ST7735S_RDDPM 0x0A     /** Read display power mode: Return 2 parameters */
#define ST7735S_RDDMADCTL 0x0B /** Read display MADCTL: Return 2 parameters */
#define ST7735S_RDDCOLMOD 0x0C /** Read display pixel format: Return 2 parameters */
#define ST7735S_RDDIM 0x0D     /** Read display image mode: Return 2 parameters */
#define ST7735S_RDDSM 0x0E     /** Read display signal mode: Return 2 parameters */
#define ST7735S_SLPIN 0x10     /** Sleep in */
#define ST7735S_SLPOUT 0x11    /** Sleep out */
#define ST7735S_PTLON 0x12     /** Partial display mode on */
#define ST7735S_NORON 0x13     /** Normal display mode on */
#define ST7735S_INVOFF 0x20    /** Display inversion off */
#define ST7735S_INVON 0x21     /** Display inversion on */
#define ST7735S_GAMSET 0x26    /** Gamma set: 1 parameter*/
#define ST7735S_DISPOFF 0x28   /** Display off */
#define ST7735S_DISPON 0x29    /** Display on */
#define ST7735S_CASET 0x2A     /** Column address set: 4 parameters */
#define ST7735S_RASET 0x2B     /** Row address set: 4 parameters */
#define ST7735S_RAMWR 0x2C     /** Memory write: N parameters */
#define ST7735S_RAMHD 0x2E     /** Memory read: Return N + 1 parameters */
#define ST7735S_PTLAR 0x30     /** Partial area: 4 parameters */
#define ST7735S_TEOFF 0x34     /** Tearing effect line off */
#define ST7735S_TEON 0x35      /** Tearing effect line on */
#define ST7735S_MADCTL 0x36    /** Memory data access control: 1 parameter */
#define ST7735S_IDMOFF 0x38    /** Idle mode off */
#define ST7735S_IDMON 0x39     /** Idle mode on */
#define ST7735S_COLMOD 0x3A    /** Interface pixel format: 1 parameter */
#define ST7735S_RDID1 0xDA     /** Read ID1 value: Return 2 parameters */
#define ST7735S_RDID2 0xDB     /** Read ID2 value: Return 2 parameters */
#define ST7735S_RDID3 0xDC     /** Read ID3 value: Return 2 parameters */
#define ST7735S_FRMCTR1 0xB1   /** Frame rate control (in normal mode/ Full colors): 3 parameters */
#define ST7735S_FRMCTR2 0xB2   /** Frame rate control (in idle mode/ 8-colors): 3 parameters */
#define ST7735S_FRMCTR3 0xB3   /** Frame Rate Control (in partial mode/ full colors): 6 parameters */
#define ST7735S_INVCTR 0xB4    /** Display inversion control: 1 parameter */
#define ST7735S_DISSET5 0xB6   /** Display function set 5: 2 parameters */
#define ST7735S_PWCTR1 0xC0    /** Power control 1: 2 parameters */
#define ST7735S_PWCTR2 0xC1    /** Power control 2: 1 parameter */
#define ST7735S_PWCTR3 0xC2    /** Power control 3 (in normal mode/ Full colors): 2 parameters */
#define ST7735S_PWCTR4 0xC3    /** Power control 4 (in idle mode/ 8-colors): 2 parameters */
#define ST7735S_PWCTR5 0xC4    /** Power Control 5 (in partial mode/ full-colors): 2 parameters */
#define ST7735S_VMCTR1 0xC5    /** VCOM control 1: 2 parameters */
#define ST7735S_VMOFCTR 0xC7   /** VCOM offset control: 1 parameter */
#define ST7735S_WRID2 0xD1     /** Write ID2 value: 1 parameter */
#define ST7735S_WRID3 0xD2     /** Write ID3 value: 1 parameter */
#define ST7735S_PWCTR6 0xFC    /** Power control 5 (in partial mode + idle mode): 2 parameters */
#define ST7735S_NVFCTR1 0xD9   /** NV memory function controller 1: 1 parameter */
#define ST7735S_NVFCTR2 0xDE   /** NV memory function controller 2: 1 parameter */
#define ST7735S_NVFCTR3 0xDF   /** NV memory function controller 3 : 3 parameters */
#define ST7735S_GMCTRP1 0xE0   /** Gamma (+) polarity correction characteristics setting: 16 parameters */
#define ST7735S_GMCTRN1 0xE1   /** Gamma (-) polarity correction characteristics setting: 16 parameters */
#define ST7735S_EXTCTRL 0xF0   /** Extension command control: 1 parameter */
#define ST7735S_VCOM4L 0xFF    /** VCOM 4 level control: 3 parameters */

/**
 * Write a command to ST7735S
 * @param cmd command
 * @param length number of parameters
 * @param parameters array containing the parameters
 */
static inline void st7735s_command(uint8_t cmd, uint32_t length, uint8_t *parameters)
{
    gpio_put(ST7735S_CS, 0);
    gpio_put(ST7735S_DC, 0);
    asm volatile("nop \n nop \n nop");
    spi_write_blocking(spi0, &cmd, 1);
    gpio_put(ST7735S_DC, 1);
    asm volatile("nop \n nop \n nop");
    spi_write_blocking(spi0, parameters, length);
    gpio_put(ST7735S_CS, 1);
    asm volatile("nop \n nop \n nop");
}

/**
 * Configures the ST7735S
 */
void st7735s_init(void);

/**
 * Set ST7735S address window
 * @param x1 start column address
 * @param y1 start row address
 * @param x2 end column address
 * @param y2 end row address
 */
void st7735s_set_memory_address(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

/**
 * Update the ST7735S memory
 * @param frame data to be written
 */
void st7735s_update(uint8_t *frame);

#endif