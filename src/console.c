#include "console.h"

#include "tusb.h"
#include "../tinyusb/src/class/cdc/cdc_device.h"

#include <stdint.h>

#define BUFFER_SIZE 128

void console_init(void)
{
    char buffer[128];
    int line_size = 0;

    tud_cdc_write_char('>');
    tud_cdc_write_char(' ');

    for (;;)
    {
        tud_task();

        uint32_t read = tud_cdc_read(buffer, BUFFER_SIZE);

        for (uint32_t i = 0; i < read; i++)
        {
            char c = buffer[i];

            switch (c)
            {
            case '\b':
            case 127:
                if (line_size <= 0)
                {
                    continue;
                }

                tud_cdc_write_char('\b');
                tud_cdc_write_char(' ');
                tud_cdc_write_char('\b');

                break;
            case '\r':
            case '\n':
                tud_cdc_write_char('\r');
                tud_cdc_write_char('\n');
                tud_cdc_write_char('>');
                tud_cdc_write_char(' ');
                line_size = 0;
                break;
            default:
                if (c == 0 || line_size >= (BUFFER_SIZE - 1))
                {
                    continue;
                }

                buffer[line_size] = c;
                tud_cdc_write_char(c);
                line_size++;
                break;
            }
        }

        tud_cdc_write_flush();
    }
}