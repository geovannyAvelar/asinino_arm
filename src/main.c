#include <string.h>
#include "bsp/board_api.h"
#include "console.h"

int main(void)
{
    board_init();

    console_init();

    return 0;
}
