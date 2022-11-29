#include "MDR32FxQI_rst_clk.h"
#include "MDR32FxQI_uart.h"
#include "MDR32FxQI_port.h"
#include "MDR32F9Q2I_IT.h"

#include "FreeRTOS.h"
#include "queue.h"

#include "serial.h"

#define serINVALID_QUEUE    ( ( QueueHandle_t ) 0 )

static QueueHandle_t xRxedChars;
static QueueHandle_t xCharsForTx;

xComPortHandle xSerialPortInit (uint32_t eWantedBaud, uint32_t uxTXQueueLength, uint32_t uxRXQueueLength)
{
    xComPortHandle xReturn = MDR_UART2;

    PORT_InitTypeDef PORT_InitStructure;
    UART_InitTypeDef UART_InitStructure;

    xRxedChars = xQueueCreate( uxRXQueueLength, ( unsigned portBASE_TYPE ) sizeof( uint8_t ) );
    xCharsForTx = xQueueCreate( uxTXQueueLength + 1, ( unsigned portBASE_TYPE ) sizeof( uint8_t ));

    if( ( xRxedChars != serINVALID_QUEUE ) && ( xCharsForTx != serINVALID_QUEUE ) )
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

        // UART_DMAConfig (MDR_UART2, UART_IT_FIFO_LVL_12words, UART_IT_FIFO_LVL_12words);
        // UART_DMACmd(MDR_UART2, UART_DMA_RXE | UART_DMA_ONERR, ENABLE);

        UART_BRGInit(MDR_UART2, UART_HCLKdiv1);
        UART_ITConfig (MDR_UART2, UART_IT_RX, ENABLE);
        UART_Init(MDR_UART2, &UART_InitStructure);
        UART_Cmd(MDR_UART2, ENABLE);
    } else {
        xReturn = ( xComPortHandle ) 0;
    }

    return xReturn;
}

/** Соводен ли UART порт для отправки сообщения */
signed portBASE_TYPE isSerialSendMessageEmpty (void)
{
    signed portBASE_TYPE xReturn = pdFALSE;
    if( UART_GetFlagStatus (MDR_UART2, UART_FLAG_TXFE) == SET && !uxQueueMessagesWaiting(xCharsForTx) )
    {
        xReturn = pdTRUE;
    }
    return xReturn;
}

/** циклом добавляем структуру в буффер */
void xSerialAddMessageSend(const uint8_t * const cOutChar, TickType_t xBlockTime )
{
    for(uint8_t i = 0; i < sizeof(cOutChar); i++)
    {
        xQueueSendToBack( xCharsForTx, &cOutChar[i], xBlockTime );
    }
}

/** Отправить накопленные данные из очереди */
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

signed portBASE_TYPE xSerialGetChar(signed char *pcRxedChar, TickType_t xBlockTime )
{
	/* Get the next character from the buffer.  Return false if no characters
	are available, or arrive before xBlockTime expires. */
	if( xQueueReceive( xRxedChars, pcRxedChar, xBlockTime ) )
	{
		return pdTRUE;
	}
	else
	{
		return pdFALSE;
	}
}

void UART2_IRQHandler( void )
{
    portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    char cChar;
    if( UART_GetITStatus( MDR_UART2, UART_IT_TX ) == SET )
    {
        /** если есть еще сообщения, то продолжаем отправку*/
        if( xQueueReceiveFromISR( xCharsForTx, &cChar, 0 ) == pdTRUE )
        {
            UART_ITConfig (MDR_UART2, UART_IT_TX, ENABLE);
            UART_SendData(MDR_UART2, cChar);
        } else {
            UART_ITConfig (MDR_UART2, UART_IT_TX, DISABLE);
        }
        UART_ClearITPendingBit(MDR_UART2, UART_IT_TX);
    }

    if( UART_GetITStatus( MDR_UART2, UART_IT_RX ) == SET )
	{
		cChar = UART_ReceiveData( MDR_UART2 );
		xQueueSendFromISR( xRxedChars, &cChar, &xHigherPriorityTaskWoken );
        UART_ClearITPendingBit(MDR_UART2, UART_IT_RX);
	}

    portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
}