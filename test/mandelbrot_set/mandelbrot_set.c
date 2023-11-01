#include <stdio.h>
#include "pico/stdlib.h"
#include "st7735s.h"

int main(void)
{
    st7735s_init();
    uint8_t frame[25600];

    uint max_iteration = 63;
    uint i = 0;
    float x, y, x0, y0;
    float x_min = -2.0f;
    float x_max = 1.0f;
    float y_min = -3.0f;
    float y_max = 3.0f;
    float x_step = (x_max - x_min) / (float)ST7735S_WIDTH;
    float y_step = (y_max - y_min) / (float)ST7735S_HEIGHT;

    uint16_t color_table[8] = {0xFFFF, 0xE000, 0xC001, 0xA002, 0x8003, 0x6004, 0x4005, 0x2006};
    while (true)
    {
        for (uint r = 0; r < ST7735S_HEIGHT; r++)
        {
            y0 = y_min + (float)r * y_step;
            for (uint c = 0; c < ST7735S_WIDTH; c++)
            {
                i = 0;
                x = y = 0.0f;
                x0 = x_min + (float)c * x_step;
                while (x * x + y * y <= 4.0f && i < max_iteration)
                {
                    float x1 = x * x - y * y + x0;
                    y = 2 * x * y + y0;
                    x = x1;
                    i++;
                }
                uint address = (r * ST7735S_WIDTH + c) << 1;
                uint16_t color = i == max_iteration ? 0 : color_table[i % 8];
                frame[address] = color >> 8;
                frame[++address] = color >> 0;
            }
        }
        st7735s_update(frame);
        for (unsigned int i = 0; i < 8; i++)
        {
            color_table[i] += 1;
        }
        sleep_ms(20);
    }
    return 0;
}