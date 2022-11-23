#include "main.h"

#include "common/core_clock.h"
#include "common/delay.h"
#include "DHT.h"

#define MSLEEP 500 // ms

DHT_t Sensor;

void Timer1_IRQHandler(void)
{
    DHT_CaptureIRQCallback(&Sensor);
}

int main(void)
{
    clk_CoreConfig();
    delay_setup();
    while (1)
    {
        DHT_data_read(&Sensor);
        delay_ms(300);
        DHT_data_calc(&Sensor);
        delay_ms(100);
    }
    return 0;
}