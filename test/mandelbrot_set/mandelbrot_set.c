#include <stdio.h>
#include "pico/stdlib.h"
#include "st7735s.h"

int main(void)
{
    st7735s_init();
    uint8_t frame[25600];

    uint max_iteration = 127;
    uint i = 0;
    float x, y, x0, y0;
    float x_min = -2.0f;
    float x_max = 1.0f;
    float y_min = -3.0f;
    float y_max = 3.0f;
    float x_step = (x_max - x_min) / (float)ST7735S_WIDTH;
    float y_step = (y_max - y_min) / (float)ST7735S_HEIGHT;

    uint16_t color_table[16] = {0xFFFF, 0xF45D, 0xE8BB, 0xDD19, 0xD177, 0xC5D5, 0xBA33, 0xAE91,
    0xA2EF, 0x974D, 0x45DF, 0x3A3D, 0x2E9B, 0x22F9, 0x1757, 0x0BB5};
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
                uint16_t color = i == max_iteration ? 0 : color_table[i % 16];
                frame[address] = color >> 8;
                frame[++address] = color >> 0;
            }
        }
        x_min += 0.01;
        x_max -= 0.01;
        y_min += 0.02;
        y_max -= 0.02;
        x_step = (x_max - x_min) / (float)ST7735S_WIDTH;
        y_step = (y_max - y_min) / (float)ST7735S_HEIGHT;
        st7735s_update(frame);
    }
    return 0;
}