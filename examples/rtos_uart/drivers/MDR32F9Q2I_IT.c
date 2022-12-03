#include "MDR32F9Q2I_IT.h"
#include "serial.h"

void UART2_IRQHandler( void )
{
    vSerialInterruptHandler(MDR_UART2);
}