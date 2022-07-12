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
    #include "main.h"

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
        
        RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTC, ENABLE);//  Включаем тактирование порта C

        gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);
        gpio_set_output_options(LED_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_SLOW, LED_PIN);
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