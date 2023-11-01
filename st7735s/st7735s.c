#include "st7735s.h"
#include "hardware/spi.h"
#include "pico/time.h"

void st7735s_init(void)
{
    spi_init(spi0, 15000000u);
    gpio_set_function(ST7735S_SDA, GPIO_FUNC_SPI);
    gpio_set_function(ST7735S_SCL, GPIO_FUNC_SPI);
    gpio_init(ST7735S_CS);
    gpio_set_dir(ST7735S_CS, GPIO_OUT);
    gpio_put(ST7735S_CS, 1);
    gpio_init(ST7735S_DC);
    gpio_set_dir(ST7735S_DC, GPIO_OUT);
    gpio_put(ST7735S_DC, 0);
    sleep_ms(120);

    st7735s_command(ST7735S_SLPOUT, 0, NULL);
    sleep_ms(120);
    st7735s_command(ST7735S_SWRESET, 0, NULL);
    st7735s_command(ST7735S_SLPOUT, 0, NULL);
    sleep_ms(120);
    st7735s_command(ST7735S_DISPOFF, 0, NULL);
    st7735s_command(ST7735S_FRMCTR1, 3, (uint8_t [3]){0x05, 0x3C, 0x3C});
    st7735s_command(ST7735S_FRMCTR2, 3, (uint8_t [3]){0x05, 0x3C, 0x3C});
    st7735s_command(ST7735S_FRMCTR3, 6, (uint8_t [6]){0x05, 0x3C, 0x3C, 0x05, 0x3C, 0x3C});
    st7735s_command(ST7735S_INVCTR, 1, (uint8_t [1]){0x07});
    st7735s_command(ST7735S_INVON, 0, NULL);
    
    //st7735s_command(ST7735S_MADCTL, 1, (uint8_t [1]){0xC8});
    st7735s_command(ST7735S_COLMOD, 1, (uint8_t [1]){0x05});
    st7735s_command(ST7735S_NORON, 0, NULL);
    st7735s_command(ST7735S_CASET, 4, (uint8_t [4]){0x00, ST7735S_X_OFFSET, 0x00, ST7735S_WIDTH + ST7735S_X_OFFSET - 1});
    st7735s_command(ST7735S_RASET, 4, (uint8_t [4]){0x00, ST7735S_Y_OFFSET, 0x00, ST7735S_HEIGHT + ST7735S_Y_OFFSET - 1});
    st7735s_command(ST7735S_DISPON, 0, NULL);
    sleep_ms(120);
}

void st7735s_set_memory_address(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
    uint8_t data[4] = {0x00, x1 + ST7735S_X_OFFSET, 0x00, x2 + ST7735S_X_OFFSET};
    st7735s_command(ST7735S_CASET, 4, data);
    data[1] = y1 + ST7735S_Y_OFFSET;
    data[3] = y2 + ST7735S_Y_OFFSET;
    st7735s_command(ST7735S_RASET, 4, data);
}

void st7735s_update(uint8_t *frame)
{
    st7735s_command(ST7735S_RAMWR, ST7735S_FRAME_SIZE, frame);
}