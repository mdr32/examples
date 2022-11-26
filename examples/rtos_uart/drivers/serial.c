#include "MDR32FxQI_rst_clk.h"
#include "MDR32FxQI_uart.h"
#include "MDR32FxQI_port.h"
#include "MDR32F9Q2I_IT.h"

#include "FreeRTOS.h"
#include "queue.h"

#include "serial.h"

#define serINVALID_QUEUE    ( ( QueueHandle_t ) 0 )

static QueueHandle_t xCharsForTx;

xComPortHandle xSerialPortInit (uint32_t eWantedBaud, unsigned portBASE_TYPE uxQueueLength)
{
    xComPortHandle xReturn = MDR_UART2;

    PORT_InitTypeDef PORT_InitStructure;
    UART_InitTypeDef UART_InitStructure;

    xCharsForTx = xQueueCreate( uxQueueLength + 1, ucSERIAL_MESSAGE_SIZE);

    if( xCharsForTx != serINVALID_QUEUE )
	{
        RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTF, ENABLE);

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

        UART_InitStructure.UART_BaudRate = eWantedBaud; 
        UART_InitStructure.UART_WordLength = UART_WordLength8b;
        UART_InitStructure.UART_StopBits = UART_StopBits1;
        UART_InitStructure.UART_Parity = UART_Parity_Even;
        UART_InitStructure.UART_FIFOMode = UART_FIFO_OFF;
        UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_RXE | UART_HardwareFlowControl_TXE;

        NVIC_SetPriority(UART2_IRQn, 7);
        NVIC_EnableIRQ(UART2_IRQn);

        UART_BRGInit(MDR_UART2, UART_HCLKdiv1);
        UART_ITConfig (MDR_UART2, UART_IT_RX, ENABLE);
        UART_Init(MDR_UART2, &UART_InitStructure);
        UART_Cmd(MDR_UART2, ENABLE);
    } else {
        xReturn = ( xComPortHandle ) 0;
    }

    return xReturn;
}

// Add to SEND BUFFER
signed portBASE_TYPE xSerialAddMessageSend(signed char cOutChar, TickType_t xBlockTime )
{
    signed portBASE_TYPE xReturn;
    if( xQueueSend( xCharsForTx, &cOutChar, xBlockTime ) == pdPASS )
	{
		xReturn = pdPASS;
	}
	else
	{
		xReturn = pdFAIL;
	}
	return xReturn;
}

// Отправить накопленные данные из ояереди
signed portBASE_TYPE xSerialSendMessage (void)
{
    signed portBASE_TYPE xReturn;
    uint8_t cChar;
    if( xQueueReceive( xCharsForTx, &cChar, 0) == pdTRUE )
    {
        /**
         * Поскольку прерывание при отправке будет выполнено
         * только в случае отправки хотябы одного байта, то отправим
         * первый байт из очереде. Остальное будет доотправлено в
         * самом прерывании.
         */
        UART_ITConfig (MDR_UART2, UART_IT_TX, ENABLE);
        UART_SendData(MDR_UART2, cChar);
        xReturn = pdPASS;
    } else {
        xReturn = pdFAIL;
    }
    return xReturn;
}

void UART2_IRQHandler( void )
{
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    char cChar;
    if( UART_GetITStatus( MDR_UART2, UART_IT_TX ) == SET )
    {
        UART_ClearITPendingBit(MDR_UART2, UART_IT_TX);
        /** если есть еще сообщения, то продолжаем отправку*/
        if( xQueueReceiveFromISR( xCharsForTx, &cChar, 0 ) == pdTRUE )
        {
            UART_ITConfig (MDR_UART2, UART_IT_TX, ENABLE);
            UART_SendData(MDR_UART2, cChar);
        } else {
            UART_ITConfig (MDR_UART2, UART_IT_TX, DISABLE);
        }
    }

    portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
}