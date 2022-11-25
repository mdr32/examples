#include "MDR32FxQI_rst_clk.h"
#include "MDR32FxQI_uart.h"
#include "MDR32FxQI_port.h"
#include "MDR32F9Q2I_IT.h"

#include "serial.h"

/**
 * 
 * @todo    Проверить ошибки в момент отправки
 * 
 * @todo    Установить NVIC
 * 
 * @todo    Попробовать прерывание при использовании DMA в момент отправки,
 *          в ситуации без ошибки и с включенным буфером
 * 
 * @todo    Если все не прокатит для РТОС, то всегда можно использовать вариант
 *          с одним байтом.
 *          В таком случае. Очередь с пакетом данных 8байт отравбатывает в отправке сообщени с блокировкой на критическуюзону
 *          при этом запрос получает с атрибутами ссылкой на сообщение и длину.
 * 
 *          Само сообщение формируется выше без блокировки, когда временная переменная сформирована,
 *          только тогда осуществляется отправка на хост через send-метод
 */

volatile static uint8_t ppp = 0;

volatile static uint8_t ppp_OE  = 0;
volatile static uint8_t ppp_BE  = 0;
volatile static uint8_t ppp_PE  = 0;
volatile static uint8_t ppp_FE  = 0;
volatile static uint8_t ppp_RT  = 0;
volatile static uint8_t ppp_RX  = 0;
volatile static uint8_t ppp_DSR = 0;
volatile static uint8_t ppp_DCD = 0;
volatile static uint8_t ppp_CTS = 0;
volatile static uint8_t ppp_RI  = 0;

volatile static uint8_t yyy_RI      = 0;
volatile static uint8_t yyy_TXFE    = 0;
volatile static uint8_t yyy_RXFF    = 0;
volatile static uint8_t yyy_TXFF    = 0;
volatile static uint8_t yyy_RXFE    = 0;
volatile static uint8_t yyy_BUSY    = 0;
volatile static uint8_t yyy_DCD     = 0;
volatile static uint8_t yyy_DSR     = 0;
volatile static uint8_t yyy_CTS     = 0;

volatile static uint8_t ccc_bool    = 0;
volatile static uint8_t ccc_mess    = 0;

volatile static uint8_t ttt = 0;
volatile static uint8_t buff = 0;

xComPortHandle xSerialPortInit (uint32_t eWantedBaud)
{
    xComPortHandle xReturn = MDR_UART2;

    PORT_InitTypeDef PORT_InitStructure;
    UART_InitTypeDef UART_InitStructure;

    /* Enables the CPU_CLK clock on PORT and UART2 */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTF, ENABLE);

    /* Fill PortInit structure*/
    PORT_InitStructure.PORT_PULL_UP = PORT_PULL_UP_OFF;
    PORT_InitStructure.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
    PORT_InitStructure.PORT_PD_SHM = PORT_PD_SHM_OFF;
    PORT_InitStructure.PORT_PD = PORT_PD_DRIVER;
    PORT_InitStructure.PORT_GFEN = PORT_GFEN_OFF;
    PORT_InitStructure.PORT_FUNC = PORT_FUNC_OVERRID;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
    PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;

    // UART_PIN_RX
    PORT_InitStructure.PORT_OE = PORT_OE_IN;
    PORT_InitStructure.PORT_Pin = PORT_Pin_0;
    PORT_Init(MDR_PORTF, &PORT_InitStructure); 

    // UART_PIN_TX
    PORT_InitStructure.PORT_OE = PORT_OE_OUT;
    PORT_InitStructure.PORT_Pin = PORT_Pin_1; 
    PORT_Init(MDR_PORTF, &PORT_InitStructure);

    RST_CLK_PCLKcmd(RST_CLK_PCLK_UART2, ENABLE);

    /* Set the HCLK division factor = 1 for UART2*/
    UART_BRGInit(MDR_UART2, UART_HCLKdiv1);

    // NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQChannel;
    // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = configLIBRARY_KERNEL_INTERRUPT_PRIORITY;
    // NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    
    /** 
     * Initialize UART_InitStructure
     * 
     * почему умножает на 2, здесь 115200???
     * http://we.easyelectronics.ru/STM32/nastroyka-uart-v-stm32-i-problemy-dvoichno-desyatichnoy-arifmetiki.html
     * http://libopencm3.org/docs/latest/stm32f1/html/usart__common__all_8c_source.html#l00053
     */
    UART_InitStructure.UART_BaudRate = eWantedBaud; 
    UART_InitStructure.UART_WordLength = UART_WordLength8b;
    UART_InitStructure.UART_StopBits = UART_StopBits1;
    UART_InitStructure.UART_Parity = UART_Parity_Even;
    UART_InitStructure.UART_FIFOMode = UART_FIFO_ON;
    // UART_InitStructure.UART_FIFOMode = UART_FIFO_OFF;
    UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_RXE | UART_HardwareFlowControl_TXE;
    
    /* Configure buhher length RX/TX */
    // NVIC_EnableIRQ(DMA_IRQn);
    // UART_DMAConfig (MDR_UART2, UART_IT_FIFO_LVL_4words, UART_IT_FIFO_LVL_4words);
    UART_DMAConfig (MDR_UART2, UART_IT_FIFO_LVL_14words, UART_IT_FIFO_LVL_14words);
    UART_DMACmd(MDR_UART2, UART_DMA_TXE | UART_DMA_ONERR, ENABLE);

    /* Enable Receiver interrupt */
    NVIC_EnableIRQ(UART2_IRQn);
    UART_ITConfig (MDR_UART2, UART_IT_RX, ENABLE);

    UART_Init(MDR_UART2, &UART_InitStructure);
    UART_Cmd(MDR_UART2, ENABLE);

    return xReturn;
}

void xSerialPutChar( xComPortHandle pxPort, volatile uint8_t cOutChar)
{
    (void) pxPort;

    // while (UART_GetFlagStatus (MDR_UART2, UART_FLAG_TXFE)!= SET);
    buff = cOutChar;
    if (ccc_mess < buff)
    {
        ccc_mess = buff;
    }
    
    UART_ClearITPendingBit(MDR_UART2, UART_IT_DSR | UART_IT_DCD | UART_IT_CTS | UART_IT_RI); // ????

    // UART_ITConfig (MDR_UART2, UART_IT_TX | UART_IT_OE, ENABLE);
    // UART_ITConfig (MDR_UART2, UART_IT_TX | UART_IT_OE, ENABLE);

    UART_ITConfig(MDR_UART2, UART_IT_OE | UART_IT_BE | UART_IT_PE | UART_IT_FE | UART_IT_RT | UART_IT_TX | UART_IT_RX | UART_IT_DSR | UART_IT_DCD | UART_IT_CTS | UART_IT_RI, ENABLE);
    UART_SendData(MDR_UART2, ((uint8_t) cOutChar));
}


void UART2_IRQHandler( void )
{
    ttt += 1;
    // if( UART_GetITStatus( MDR_UART2, UART_IT_OE ) == SET )
    // {
    //     ppp += 1;
    //     UART_ClearITPendingBit(MDR_UART2, UART_IT_OE);
    //     UART_ITConfig (MDR_UART2, UART_IT_OE, DISABLE);
    // }

    if(ccc_mess < 10){
       ccc_bool += 1; 
    }

    if( UART_GetITStatus( MDR_UART2, UART_IT_OE ) == SET )  ppp_OE += 1;
    if( UART_GetITStatus( MDR_UART2, UART_IT_BE ) == SET )  ppp_BE += 1;
    if( UART_GetITStatus( MDR_UART2, UART_IT_PE ) == SET )  ppp_PE += 1;
    if( UART_GetITStatus( MDR_UART2, UART_IT_FE ) == SET )  ppp_FE += 1;
    if( UART_GetITStatus( MDR_UART2, UART_IT_RT ) == SET )  ppp_RT += 1;
    if( UART_GetITStatus( MDR_UART2, UART_IT_RX ) == SET )  ppp_RX += 1;
    if( UART_GetITStatus( MDR_UART2, UART_IT_DSR ) == SET ) ppp_DSR += 1;
    if( UART_GetITStatus( MDR_UART2, UART_IT_DCD ) == SET ) ppp_DCD += 1;
    if( UART_GetITStatus( MDR_UART2, UART_IT_CTS ) == SET ) ppp_CTS += 1;
    if( UART_GetITStatus( MDR_UART2, UART_IT_RI ) == SET )  ppp_RI += 1;

    if( UART_GetITStatus( MDR_UART2, UART_IT_TX ) == SET )
    {
        // отрабатывает в одном пакете (message = ttt) это не точный показатель
        ppp += 1;
        if(UART_GetFlagStatus (MDR_UART2, UART_FLAG_RI)  ) yyy_RI      += 1;
        if(UART_GetFlagStatus (MDR_UART2, UART_FLAG_TXFE)) yyy_TXFE    += 1; // Буфер всегда полон, в счетчике 0, равный кол-во вызовов ppp
        if(UART_GetFlagStatus (MDR_UART2, UART_FLAG_RXFF)) yyy_RXFF    += 1;
        if(UART_GetFlagStatus (MDR_UART2, UART_FLAG_TXFF)) yyy_TXFF    += 1;    
        if(UART_GetFlagStatus (MDR_UART2, UART_FLAG_RXFE)) yyy_RXFE    += 1;    
        if(UART_GetFlagStatus (MDR_UART2, UART_FLAG_BUSY)) yyy_BUSY    += 1; // Буфер не пуст и идет отправка, равный кол-во вызовов ppp
        if(UART_GetFlagStatus (MDR_UART2, UART_FLAG_DCD) ) yyy_DCD     += 1;
        if(UART_GetFlagStatus (MDR_UART2, UART_FLAG_DSR) ) yyy_DSR     += 1;
        if(UART_GetFlagStatus (MDR_UART2, UART_FLAG_CTS) ) yyy_CTS     += 1;
        
        // UART_ClearITPendingBit(MDR_UART2, UART_IT_DSR | UART_IT_DCD | UART_IT_CTS | UART_IT_RI); // ????
        UART_ClearITPendingBit(MDR_UART2, UART_IT_TX);
        // UART_ITConfig (MDR_UART2, UART_IT_TX, DISABLE);
        // UART_GetFlagStatus (MDR_UART2, UART_FLAG_TXFF);
    }
}