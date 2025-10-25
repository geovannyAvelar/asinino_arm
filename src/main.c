#include <string.h>

#include "bsp/board_api.h"
#include "tusb.h"


int main(void)
{
    board_init();

    while (1)
    {
        tud_task();

        static uint32_t last_ms = 0;
        static uint8_t led_on = 0;

        if (tud_cdc_connected()) {

        }
    }

    return 0;
}
