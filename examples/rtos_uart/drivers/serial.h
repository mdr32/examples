#ifndef _DRIVERS_SERIAL_H
#define _DRIVERS_SERIAL_H

#ifdef __cplusplus
 extern "C" {
#endif

typedef void * xComPortHandle; // MDR_UART_TypeDef

/** xSerialSendMessage_t Содержание сообщения */
typedef struct {
    uint8_t byte_A;
    uint8_t byte_B;
    uint8_t byte_C;
    uint8_t byte_D;
} xSerialSendMessage_t;

xComPortHandle xSerialPortInit (uint32_t eWantedBaud, unsigned portBASE_TYPE uxQueueLength);
signed portBASE_TYPE isSerialSendMessageEmpty (void);
void xSerialAddMessageSend(const xSerialSendMessage_t * const cOutChar, TickType_t xBlockTime );
signed portBASE_TYPE xSerialSendMessage (void);

#ifdef __cplusplus
}
#endif
#endif