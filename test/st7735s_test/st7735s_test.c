#include <stdio.h>
#include "pico/stdlib.h"
#include "st7735s.h"

int main(void)
{
    st7735s_init();
    uint8_t frame[25600];
    uint16_t color = 0;
    while (true)
    {
        for (unsigned int i = 0; i < 25600; i++)
        {
            frame[i] = color;
            if (i % 160 == 0)
                color ++;
        }
        st7735s_update(frame);
        sleep_ms(3);
    }
    return 0;
}