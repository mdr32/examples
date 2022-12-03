#include "MDR32F9Q2I_IT.h"
#include "main.h"
#include "common/core_clock.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "drivers/serial.h"
#include "drivers/button.h"

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );
void vApplicationIdleHook(void);

void vSend_Task(void *pvParameters);
void vBtn_Task(void *pvParameters);
void vRead_Task(void *pvParameters);
void vCMD_Task(void *pvParameters);
void vPrint_Task(void *pvParameters);

/** xSerialSendMessage_t Содержание сообщения */
typedef struct tmpl {
    uint8_t sender_id;
    uint8_t message;
    uint8_t message_l;
    uint8_t message_h;
} xSerialSendMessage_t;

static xSerialSendMessage_t tmpl = {};

static QueueHandle_t xCMDListSend;

int main(void)
{
    /** предохранитель, на случай если во время
     * разработки залочится камень */
    uint32_t  timeout = 0xfffff; 
    while( timeout-- );

    clk_CoreConfig();
    vButtonInit();

    // Baud определен с учетом ошибки, реально используется 115200
    xSerialPortInit(57600, sizeof(xSerialSendMessage_t)* 5, sizeof(xSerialSendMessage_t) * 3);

    xCMDListSend = xQueueCreate( 5, sizeof(xSerialSendMessage_t));

    xTaskCreate(vSend_Task, "Send", 50, NULL, tskIDLE_PRIORITY + 4, NULL);
    xTaskCreate(vBtn_Task, "Click", 50, NULL, tskIDLE_PRIORITY + 3, NULL);
    xTaskCreate(vRead_Task, "Read", 50, NULL, tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate(vCMD_Task, "CMD", 50, NULL, tskIDLE_PRIORITY + 1, NULL);
    // xTaskCreate(vPrint_Task, "Print", 50, NULL, tskIDLE_PRIORITY, NULL);

    vTaskStartScheduler();
    while (1)
    {
    }
    return 0;
}

/** Отправка сообщения на сервер, единственный метод, взаимодействующий с UART-драйвером */
void vSend_Task(void *pvParameters)
{
    ( void ) pvParameters;
    xSerialSendMessage_t cmd;

    for( ; ; )
    {
        if( xQueueReceive( xCMDListSend, &cmd, portMAX_DELAY) == pdTRUE )
        {
            xSerialAddMessageSend((uint8_t *)&cmd, portMAX_DELAY);
            xSerialSendMessage(4);
        }
    }
}

/** Опрос кнопки, в случае нажатия будет отправлено сообщение */
void vBtn_Task(void *pvParameters)
{
    ( void ) pvParameters;

    xSerialSendMessage_t cmd = tmpl;
    cmd.sender_id   = 0xB1;

    #define DENDER_TIME 50

    TimeOut_t   xTimeOut;
    BaseType_t  xWaitDender = pdFALSE;
    BaseType_t  xLastKey = 0;
    BaseType_t  xReportedKey = 0;
    TickType_t  xDenderTime;

    for( ; ; )
    {
        BaseType_t xKeyPressed = xButtonReadPortSwitch();

        if (xWaitDender == pdFALSE && xReportedKey != xKeyPressed)
        {
            // Без ожидания Dender, сообщаем о новом статусе ключа
            xReportedKey = xKeyPressed;
            // Отправляем сообщение
            cmd.message_h   = 0x05;
            xQueueSendToBack( xCMDListSend, &cmd, portMAX_DELAY );
        }
        // Изменилось ли значение ключа?
        if (xLastKey != xKeyPressed)
        {
            xLastKey = xKeyPressed;
            xDenderTime = DENDER_TIME;
            vTaskSetTimeOutState(&xTimeOut);
            xWaitDender = pdTRUE;
        } else if (xWaitDender == pdTRUE) {
            // Посмотреть, не истек ли таймер
            if (xTaskCheckForTimeOut(&xTimeOut, &xDenderTime))
            {
                xWaitDender = pdFALSE;
            }
        }
        vTaskDelay(100);
    }
}

/** Чтение отввета на запрос, модификация и возврат обратно */
void vRead_Task(void *pvParameters)
{
    ( void ) pvParameters;
    signed char cByteRxed;
    xSerialSendMessage_t cmd = tmpl;
    cmd.sender_id   = 0xbb;
    for( ; ; )
    {
        if(xSerialGetChar(&cByteRxed, portMAX_DELAY) == pdTRUE)
        {
            cmd.message_l = cByteRxed + 1;
            xQueueSendToBack( xCMDListSend, &cmd, portMAX_DELAY );
        }
    }
}

/** Преиодический опрос */
void vCMD_Task(void *pvParameters)
{
    ( void ) pvParameters;
    xSerialSendMessage_t cmd = tmpl;
    cmd.sender_id   = 0xaa;
    for( ; ; )
    {
        cmd.message_h   = 0x05;
        if(xQueueSendToBack( xCMDListSend, &cmd, portMAX_DELAY ) == pdTRUE)
        {
            vTaskDelay(1000);
        }
    }
}

/** Логирование сообщения, метод пуст и используется только
 * для демонстрации в контексте понимания приоритетов */
void vPrint_Task(void *pvParameters)
{
    ( void ) pvParameters;
    for( ; ; )
    {
        vTaskDelay(300);
    }
}