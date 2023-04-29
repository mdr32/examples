#include "MDR32F9Q2I_IT.h"
#include "main.h"
#include "common/core_clock.h"

#include "MDR32FxQI_rst_clk.h"
#include "MDR32FxQI_port.h"
#include "MDR32FxQI_timer.h"

/** Таймер определяется только на одном порту таймера */
#define PORT_ECODER     MDR_PORTA
#define PIN_ECODER_A    PORT_Pin_1  // Альтернативный с функциями таймер
#define PIN_ECODER_B    PORT_Pin_3  // Обычный пин, только для чтения
#define PIN_ECODER_TESTOUT    PORT_Pin_4  // Обычный пин, только для чтения

void init_port_encoder(void);
void init_timer_encoder(void);
void CaptureIRQCallback (void);
void init_port_out_test (void);

uint8_t test_changed;

void Timer1_IRQHandler(void)
{
    CaptureIRQCallback();
}

int main(void)
{
    uint32_t  timeout = 0xfffff; 
    while( timeout-- );

    clk_CoreConfig();
    init_port_encoder();
    init_timer_encoder();
    init_port_out_test ();

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
    RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER1, ENABLE);
    TIMER_DeInit(MDR_TIMER1);
    NVIC_EnableIRQ(Timer1_IRQn); // Включаем прерывание таймера

    MDR_TIMER1->CNTRL = 0x00000000; //Режим инициализации таймера
    /* Настраиваем работу основного счетчика */
    MDR_TIMER1->CNT = 0x00000000; //Начальное значение счетчика
    MDR_TIMER1->PSG = 0x00000000; //Предделитель частоты
    MDR_TIMER1->ARR = 0x000000FF; //Основание счета
    
    /* Режим работы каналов – захват по положительному фронту сигнала на входе CHxi */
    MDR_TIMER1->CH1_CNTRL = 0x00008010;
    /* Режим работы выхода канала – канал на выход не работает */
    // MDR_TIMER1->CH1_CNTRL1= 0x00000000;
    MDR_TIMER1->CH1_CNTRL1= 0x00000000;
    TIMER_ITConfig(MDR_TIMER1, TIMER_STATUS_CCR_CAP_CH1 | TIMER_STATUS_CCR_CAP1_CH1, ENABLE);
    /* Включение тактовой частоты таймера */
    TIMER_BRGInit(MDR_TIMER1, TIMER_HCLKdiv1);
    /* Разрешение работы таймера */
    TIMER_Cmd(MDR_TIMER1, ENABLE); // CNTRL
}

void init_port_out_test (void)
{
    PORT_InitTypeDef PORT_InitStructure;
    RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA, ENABLE);
    PORT_StructInit(&PORT_InitStructure);

    PORT_InitStructure.PORT_Pin   = PIN_ECODER_TESTOUT;
    PORT_InitStructure.PORT_OE    = PORT_OE_OUT;
    PORT_InitStructure.PORT_PULL_UP = PORT_PULL_UP_OFF;
    PORT_InitStructure.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
    PORT_InitStructure.PORT_PD_SHM = PORT_PD_SHM_OFF;
    PORT_InitStructure.PORT_GFEN = PORT_GFEN_OFF; // ?
    PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
    PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
    PORT_Init(PORT_ECODER, &PORT_InitStructure);
    PORT_WriteBit(PORT_ECODER, PIN_ECODER_TESTOUT, SET);
}

void CaptureIRQCallback (void)
{
    //start period
    if(TIMER_GetFlagStatus(MDR_TIMER1, TIMER_STATUS_CCR_CAP_CH1))
    {
        test_changed = PORT_ReadInputDataBit(PORT_ECODER, PIN_ECODER_B);
        //// test port
        PORT_WriteBit(PORT_ECODER, PIN_ECODER_TESTOUT, RESET);
    }

    // end period
    if(TIMER_GetFlagStatus(MDR_TIMER1, TIMER_STATUS_CCR_CAP1_CH1))
    {
        //Здесь происходит калькуляция
        if(test_changed != PORT_ReadInputDataBit(PORT_ECODER, PIN_ECODER_B)){
            //// test port
            PORT_WriteBit(PORT_ECODER, PIN_ECODER_TESTOUT, SET);
        }
    }
    TIMER_ClearFlag(MDR_TIMER1, TIMER_STATUS_CCR_CAP_CH1 | TIMER_STATUS_CCR_CAP1_CH1);
}
