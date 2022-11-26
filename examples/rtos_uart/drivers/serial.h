#ifndef _DRIVERS_SERIAL_H
#define _DRIVERS_SERIAL_H

#ifdef __cplusplus
 extern "C" {
#endif

typedef void * xComPortHandle; // MDR_UART_TypeDef

/** SerialSendMessage_t Содержание сообщения */
typedef struct {
    uint8_t byte_A;
    uint8_t byte_B;
    uint8_t byte_C;
    uint8_t byte_D;
} SerialSendMessage_t;

/**
 * ucSERIAL_MESSAGE_SIZE - размер сообщения в байтах, можно определить
 * методом `sizeof((SerialMessage_t) message_dummy`
 */
#define ucSERIAL_MESSAGE_SIZE      4

xComPortHandle xSerialPortInit (uint32_t eWantedBaud, unsigned portBASE_TYPE uxQueueLength);
signed portBASE_TYPE xSerialAddMessageSend(signed char cOutChar, TickType_t xBlockTime );
signed portBASE_TYPE xSerialSendMessage (void);

#ifdef __cplusplus
}
#endif
#endif