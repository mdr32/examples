#ifndef _COMMON_DELAY_H
#define _COMMON_DELAY_H

#ifdef __cplusplus
 extern "C" {
#endif

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