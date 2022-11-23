#include "main.h"

#include "MDR32FxQI_rst_clk.h"
#include "locm3_gpio.h"
#include "common/core_clock.h"
#include "common/delay.h"

#define LED_PORT GPIOC
#define LED_PIN GPIO2
#define MSLEEP 300 // ms

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