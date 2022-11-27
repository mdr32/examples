#ifndef _DRIVERS_SERIAL_H
#define _DRIVERS_SERIAL_H

#ifdef __cplusplus
 extern "C" {
#endif

typedef void * xComPortHandle; // MDR_UART_TypeDef

xComPortHandle xSerialPortInit (uint32_t eWantedBaud, uint32_t uxTXQueueLength, uint32_t uxRXQueueLength);
signed portBASE_TYPE isSerialSendMessageEmpty (void);
void xSerialAddMessageSend(const uint8_t * const cOutChar, TickType_t xBlockTime );
signed portBASE_TYPE xSerialSendMessage (void);
signed portBASE_TYPE xSerialGetChar(signed char *pcRxedChar, TickType_t xBlockTime );
#ifdef __cplusplus
}
#endif
#endif