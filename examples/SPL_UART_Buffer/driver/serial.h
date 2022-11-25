#ifndef _DRIVER_SERIAL_H
#define _DRIVER_SERIAL_H

#ifdef __cplusplus
 extern "C" {
#endif

typedef void * xComPortHandle; // MDR_UART_TypeDef

xComPortHandle xSerialPortInit (uint32_t eWantedBaud);
void xSerialPutChar( xComPortHandle pxPort, volatile uint8_t cOutChar);
// ErrorStatus xSerialPutChar( xComPortHandle pxPort, volatile uint8_t cOutChar);
#ifdef __cplusplus
}
#endif
#endif