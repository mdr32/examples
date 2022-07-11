#ifndef _DELAY_H
#define _DELAY_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "locm3_rcc.h"
#include "locm3_systick.h"

/**
 * @brief Реализация задержки
 * 
 * @example Пример "Hello World" 
 * @code
    #include "MDR32FxQI_port.h"
    #include "MDR32FxQI_rst_clk.h"
    #include "locm3_gpio.h"

    #define LED_PORT GPIOC
    #define LED_PIN GPIO2
    #define MSLEEP 300 // ms

    static void clk_CoreConfig(void);

    int main(void)
    {
        clk_CoreConfig();
        delay_setup();

        PORT_InitTypeDef GPIOInitStruct; // Заводим структуру конфигурации вывода(-ов) порта GPIO
        RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTC, ENABLE);//  Включаем тактирование порта C
        PORT_StructInit(&GPIOInitStruct); //  Инициализируем структуру конфигурации вывода(-ов) порта значениями по умолчанию

        //  Изменяем значения по умолчанию на необходимые нам настройки
        GPIOInitStruct.PORT_Pin = LED_PIN;
        GPIOInitStruct.PORT_OE = PORT_OE_OUT;
        GPIOInitStruct.PORT_SPEED = PORT_SPEED_SLOW;
        GPIOInitStruct.PORT_MODE = PORT_MODE_DIGITAL;
        //  Применяем заполненную нами структуру для PORTC.
        PORT_Init(LED_PORT, &GPIOInitStruct);

        while (1)
        {
            gpio_toggle(LED_PORT, LED_PIN);
            delay_ms(MSLEEP);
        }
        return 0;
    }
 * @endcode
 * 
 */

/** @brief Настройка прерывания для SysTick */
void delay_setup(void);

/** @brief Метод задержки */
void delay_ms(uint16_t delay);

#ifdef __cplusplus
}
#endif
#endif