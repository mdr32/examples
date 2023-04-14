#include "MDR32F9Q2I_IT.h"
#include "main.h"
#include "common/core_clock.h"

#include "MDR32FxQI_rst_clk.h"
#include "MDR32FxQI_port.h"
#include "MDR32FxQI_timer.h"

/** Таймер определяется только на одном порту таймера */
#define PORT_ECODER     MDR_PORTA
#define PIN_ECODER_A    PORT_Pin_1  // Альтернативный с функциями таймер
#define PIN_ECODER_B    PORT_Pin_2  // Обычный пин, только для чтения

int main(void)
{
    uint32_t  timeout = 0xfffff; 
    while( timeout-- );

    clk_CoreConfig();


    while (1)
    {

    }
    return 0;
}

void init_port_encoder(void)
{
    PORT_InitTypeDef PORT_InitStructure;
    RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA, ENABLE);
    PORT_StructInit(&PORT_InitStructure);
    // PIN_ECODER_A
    PORT_InitStructure.PORT_Pin   = PIN_ECODER_A;
    PORT_InitStructure.PORT_OE    = PORT_OE_IN;
    PORT_InitStructure.PORT_PULL_UP = PORT_PULL_UP_OFF;
    PORT_InitStructure.PORT_PULL_DOWN = PORT_PULL_DOWN_ON;
    PORT_InitStructure.PORT_PD_SHM = PORT_PD_SHM_OFF;
    PORT_InitStructure.PORT_GFEN = PORT_GFEN_OFF; // ?
    PORT_InitStructure.PORT_FUNC = PORT_FUNC_ALTER;
    PORT_InitStructure.PORT_SPEED = PORT_OUTPUT_OFF;
    PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
    PORT_Init(PORT_ECODER, &PORT_InitStructure);
    // PIN_ECODER_B
    PORT_InitStructure.PORT_Pin     = PIN_ECODER_B;
    PORT_InitStructure.PORT_FUNC    = PORT_FUNC_PORT;
    PORT_Init(PORT_ECODER, &PORT_InitStructure);
}

void init_timer_encoder(void)
{
    
}

void CaptureIRQCallback (void)
{

}

void TIM2_IRQHandler(void)
{
    // static int t1, t2, a;
    // if (TIM2->SR & TIM_SR_CC3IF)
    // {
    //     if (GPIOB->IDR & GPIO_Pin_11)
    //         conor--;
    //     else
    //         conor++;

    //     t2 = TIM2->CNT;

    //     if (t2 > t1)
    //         speed = t2 - t1;
    //     else
    //         speed = t2 - t1 + 65535;

    //     t1 = t2;
    //     speed = 140625 / speed;
    //     speed = (speed * (100 - 90) + a * 90) / 100;
    //     a = speed;
        
    //     TIM2->SR &= ~TIM_SR_CC3IF;
    //     if ((conor >= 3150336) | (conor <= -3150336) | (conor == 0))
    //     {
    //         OSTANOV;
    //     }
    // }
}