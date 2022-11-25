#include "main.h"

#include "MDR32FxQI_rst_clk.h"
#include "common/core_clock.h"
#include "common/delay.h"

#include "driver/serial.h"

#define MSLEEP 300 // ms

xComPortHandle ComPort;
volatile uint8_t message = 0;

int main(void)
{
    clk_CoreConfig();
    delay_setup();
    ComPort = xSerialPortInit(57600);

    while (1)
    {
        xSerialPutChar(ComPort, 1);
        xSerialPutChar(ComPort, 2);
        xSerialPutChar(ComPort, 3);
        xSerialPutChar(ComPort, 4);
        xSerialPutChar(ComPort, 5);

        xSerialPutChar(ComPort, 6);
        xSerialPutChar(ComPort, 7);
        xSerialPutChar(ComPort, 8);
        xSerialPutChar(ComPort, 9);
        // delay_ms(1);
        xSerialPutChar(ComPort, 10);

        xSerialPutChar(ComPort, 11);
        xSerialPutChar(ComPort, 12);
        xSerialPutChar(ComPort, 13);
        xSerialPutChar(ComPort, 14);
        xSerialPutChar(ComPort, 15);
        
        xSerialPutChar(ComPort, 16);
        xSerialPutChar(ComPort, 17);
        xSerialPutChar(ComPort, 18);
        xSerialPutChar(ComPort, 19);
        xSerialPutChar(ComPort, 20);

        message++;
        delay_ms(MSLEEP);
    }
    return 0;
}