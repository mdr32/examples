#ifndef _LOCM3_UART_H
#define _LOCM3_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "locm3_bridge.h"

/** @brief Описание портов */
#define UART1				MDR_UART1_BASE
#define UART2				MDR_UART2_BASE

/** @brief UART_DR: Регистр данных */
#define UART_DR(usart_base)         MMIO32((usart_base) + 0x00)
#define UART1_DR                    UART_DR(UART1)
#define UART2_DR                    UART_DR(UART2)

/** @brief UART_RSR_ECR: Регистр состояния приемника / Сброс ошибки приемника */
#define UART_RSR_ECR(usart_base)    MMIO32((usart_base) + 0x004)
#define UART1_RSR_ECR               UART_RSR_ECR(UART1)
#define UART2_RSR_ECR               UART_RSR_ECR(UART2)

/** @brief UART_FR: Регистр флагов */
#define UART_FR(usart_base)         MMIO32((usart_base) + 0x018)
#define UART1_FR                    UART_FR(UART1)
#define UART2_FR                    UART_FR(UART2)

/** @brief UART_ILPR: Регистр управления ИК обменом в режиме пониженного энергопотребления */
#define UART_ILPR(usart_base)		MMIO32((usart_base) + 0x020)
#define UART1_ILPR                  UART_ILPR(UART1)
#define UART2_ILPR                  UART_ILPR(UART2)

/** @brief UART_IBRD: Целая часть делителя скорости обмена данными */
#define UART_IBRD(usart_base)		MMIO32((usart_base) + 0x024)
#define UART1_IBRD                  UART_IBRD(UART1)
#define UART2_IBRD                  UART_IBRD(UART2)

/** @brief UART_FBRD: Дробная часть делителя скорости обмена данными */
#define UART_FBRD(usart_base)		MMIO32((usart_base) + 0x028)
#define UART1_FBRD                  UART_FBRD(UART1)
#define UART2_FBRD                  UART_FBRD(UART2)

/** @brief UART_LCR_H: Регистр управления линией */
#define UART_LCR_H(usart_base)		MMIO32((usart_base) + 0x02C)
#define UART1_LCR_H                 UART_LCR_H(UART1)
#define UART2_LCR_H                 UART_LCR_H(UART2)

/** @brief UART_CR: Регистр управления */
#define UART_CR(usart_base)         MMIO32((usart_base) + 0x030)
#define UART1_CR                    UART_CR(UART1)
#define UART2_CR                    UART_CR(UART2)

/** @brief UART_IFLS: Регистр порога прерывания по заполнению буфера FIFO */
#define UART_IFLS(usart_base)		MMIO32((usart_base) + 0x034)
#define UART1_IFLS                  UART_IFLS(UART1)
#define UART2_IFLS                  UART_IFLS(UART2)

/** @brief UART_IMSC: Регистр маски прерывания */
#define UART_IMSC(usart_base)		MMIO32((usart_base) + 0x038)
#define UART1_IMSC                  UART_IMSC(UART1)
#define UART2_IMSC                  UART_IMSC(UART2)

/** @brief UART_RIS: Регистр состояния прерываний */
#define UART_RIS(usart_base)		MMIO32((usart_base) + 0x03C)
#define UART1_RIS                   UART_RIS(UART1)
#define UART2_RIS                   UART_RIS(UART2)

/** @brief UART_MIS: Регистр состояния прерываний с маскированием */
#define UART_MIS(usart_base)		MMIO32((usart_base) + 0x040)
#define UART1_MIS                   UART_MIS(UART1)
#define UART2_MIS                   UART_MIS(UART2)

/** @brief UART_ICR: Регистр сброса прерывания */
#define UART_ICR(usart_base)		MMIO32((usart_base) + 0x044)
#define UART1_ICR                   UART_ICR(UART1)
#define UART2_ICR                   UART_ICR(UART2)

/** @brief UART_DMACR: Регистр управления DMA */
#define UART_DMACR(usart_base)		MMIO32((usart_base) + 0x048)
#define UART1_DMACR                 UART_DMACR(UART1)
#define UART2_DMACR                 UART_DMACR(UART2)


/** @todo UARTx_DR*/

/** @brief UARTx_RSR_ECR values */
#define UART_RSR_ECR_OE     (1 << 3)
#define UART_RSR_ECR_BE     (1 << 2)
#define UART_RSR_ECR_PE     (1 << 1)
#define UART_RSR_ECR_FE     (1 << 0)

/** @brief UARTx_FR values */
#define UART_RI     (1 << 8)
#define UART_TXFE   (1 << 7)
#define UART_RXFF   (1 << 6)
#define UART_TXFF   (1 << 5)
#define UART_RXFE   (1 << 4)
#define UART_BUSY   (1 << 3)
#define UART_DCD    (1 << 2)
#define UART_DSR    (1 << 1)
#define UART_CTS    (1 << 0)

///////////////////

void uart_set_baudrate(uint32_t uart, uint32_t baud);
void uart_set_databits(uint32_t uart, uint32_t bits);
void uart_set_stopbits(uint32_t uart, uint32_t stopbits);
void uart_set_parity(uint32_t uart, uint32_t parity);
void uart_set_mode(uint32_t uart, uint32_t mode);
void uart_set_flow_control(uint32_t uart, uint32_t flowcontrol);
void uart_enable(uint32_t uart);
void uart_disable(uint32_t uart);
void uart_send(uint32_t uart, uint16_t data);

#ifdef __cplusplus
}
#endif
#endif
