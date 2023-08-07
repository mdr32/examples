#include "main.h"
#include "common/core_clock.h"

#include "MDR32FxQI_rst_clk.h"
#include "MDR32FxQI_port.h"

#include "FreeRTOS.h"
#include "task.h"

#define LED_CLKPORT     RST_CLK_PCLK_PORTC
#define LED_PORT        MDR_PORTC
#define LED_PIN         PORT_Pin_2
#define CLK_PERIOD      500

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );
void vApplicationIdleHook(void);

void vBlinkTick_Task(void *pvParameters);
void vLedPortInit (void);


int main(void)
{
    /** предохранитель, на случай если во время
     * разработки залочится камень */
    uint32_t  timeout = 0xfffff; 
    while( timeout-- );

    clk_CoreConfig();
    vLedPortInit();

    xTaskCreate(vBlinkTick_Task, "blink_tick", 50, NULL, tskIDLE_PRIORITY, NULL);

    vTaskStartScheduler();
    while (1){}
    return 0;
}

void vBlinkTick_Task(void *pvParameters)
{
    ( void ) pvParameters;
    for( ; ; )
    {
        if(PORT_ReadInputDataBit(LED_PORT, LED_PIN) != SET){
            PORT_WriteBit(LED_PORT, LED_PIN, SET);
        } else {
            PORT_WriteBit(LED_PORT, LED_PIN, RESET);
        }
        
        vTaskDelay(CLK_PERIOD);
    }
}

void vLedPortInit (void)
{
    PORT_InitTypeDef PORT_InitStructure;
    RST_CLK_PCLKcmd(LED_CLKPORT, ENABLE);
    PORT_StructInit(&PORT_InitStructure);

    PORT_InitStructure.PORT_Pin   = LED_PIN;
    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_PULL_UP = PORT_PULL_UP_OFF;
    PORT_InitStructure.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
    PORT_InitStructure.PORT_PD_SHM = PORT_PD_SHM_OFF;
    PORT_InitStructure.PORT_GFEN = PORT_GFEN_OFF;
    PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
    PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
    PORT_Init(LED_PORT, &PORT_InitStructure);
    PORT_WriteBit(LED_PORT, LED_PIN, SET);
}