#ifndef _COMMON_CORE_CLOCK_H
#define _COMMON_CORE_CLOCK_H

#ifdef __cplusplus
 extern "C" {
#endif

/**
 * @brief Инициализация тактирования микроконтроллера
 * 		  Crystal=16MHz
 * 		  Speed=80MHz
 * 
 * @todo Пока работа с тактированием не имеет своего модуля
 */

void clk_CoreConfig(void);

#ifdef __cplusplus
}
#endif
#endif