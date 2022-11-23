#include "locm3_rcc.h"
#include "locm3_systick.h"

#include "delay.h"

/**
 * @brief Процессор имеет 24-х разрядный системный таймер, SysTick
 */
volatile uint16_t _millis;

static uint16_t millis(void) {
    return _millis;
}

/**
 * @brief Обработчик прерывания из таблицы прерываний
 */
void SysTick_Handler(void)
{
    _millis++;
}

void delay_setup(void)
{
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
    systick_clear();
	systick_set_reload(rcc_ahb_frequency / 1000 - 1);
    systick_counter_enable();
	systick_interrupt_enable();
}

void delay_ms(uint16_t delay){
    const uint16_t until = millis() + delay;
    while (millis() < until);
}