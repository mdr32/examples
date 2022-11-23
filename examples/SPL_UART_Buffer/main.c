#include "main.h"

#include "MDR32FxQI_rst_clk.h"
#include "common/core_clock.h"
#include "common/delay.h"

#define MSLEEP 300 // ms

int main(void)
{
    clk_CoreConfig();
    delay_setup();

    while (1)
    {
        delay_ms(MSLEEP);
    }
    return 0;
}