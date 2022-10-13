#ifndef _DELAY_H
#define _DELAY_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "locm3_rcc.h"
#include "locm3_systick.h"

/**
 * Реализация задержки
 */

/** @brief Настройка прерывания для SysTick */
void delay_setup(void);

/** @brief Метод задержки */
void delay_ms(uint16_t delay);

#ifdef __cplusplus
}
#endif
#endif