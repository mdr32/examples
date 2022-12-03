#ifndef _DRIVERS_SERIAL_H
#define _DRIVERS_SERIAL_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "FreeRTOS.h"
#include "queue.h"

typedef void * xComPortHandle; // MDR_UART_TypeDef

xComPortHandle xSerialPortInit (uint32_t eWantedBaud, uint32_t uxTXQueueLength, uint32_t uxRXQueueLength);
signed portBASE_TYPE isSerialSendMessageEmpty (void);
void xSerialAddMessageSend(const uint8_t * const cOutChar, TickType_t xBlockTime );
signed portBASE_TYPE xSerialSendMessage ( TickType_t xBlockTime );
signed portBASE_TYPE xSerialGetChar(signed char *pcRxedChar, TickType_t xBlockTime );

void vSerialInterruptHandler( xComPortHandle xPort );
#ifdef __cplusplus
}
#endif
#endif