#include "locm3_uart.h"


void uart_set_baudrate(uint32_t uart, uint32_t baud)
{
    // USART_BRR
}
////////////////////////////

void uart_set_databits(uint32_t usart, uint32_t bits);

void uart_set_stopbits(uint32_t usart, uint32_t stopbits);

void uart_set_parity(uint32_t usart, uint32_t parity);

void uart_set_mode(uint32_t usart, uint32_t mode);

void uart_set_flow_control(uint32_t usart, uint32_t flowcontrol);

void uart_enable(uint32_t usart);

void uart_disable(uint32_t usart);

void uart_send(uint32_t usart, uint16_t data);


// locm3_uart