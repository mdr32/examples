#include "main.h"
#include "common/core_clock.h"

#include "FreeRTOS.h"
#include "task.h"

#include "drivers/serial.h"

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );
void vApplicationIdleHook(void);

void vSend_Task(void *pvParameters);
void vRead_Task(void *pvParameters);
void vCMD_Task(void *pvParameters);
void vPrint_Task(void *pvParameters);

int main(void)
{
    clk_CoreConfig();

    // Baud определен с учетом ошибки, реально используется 115200
    // Вторым аргументом передаем длину эл-тов
    xSerialPortInit(57600, 3);

    xTaskCreate(vSend_Task, "Send", 50, NULL, tskIDLE_PRIORITY + 3, NULL);
    xTaskCreate(vRead_Task, "Read", 50, NULL, tskIDLE_PRIORITY + 2, NULL);
    // xTaskCreate(vCMD_Task, "CMD", 50, NULL, tskIDLE_PRIORITY + 1, NULL);
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
    
    // Эта очередь получаем из общего пула именно очередей
    xSerialSendMessage_t msg;
    msg.byte_A = 0xfa;
    msg.byte_C = 0xfc;
    msg.byte_B = 0xfb;
    msg.byte_D = 0xfd;

    for( ; ; )
    {
        if(isSerialSendMessageEmpty() == pdTRUE)
        {
            xSerialAddMessageSend(&msg, 0);
            xSerialSendMessage();
        }
        vTaskDelay(600);
    }
}

/** Чтение отввета на запрос */
void vRead_Task(void *pvParameters)
{
    signed char cByteRxed;
    ( void ) pvParameters;
    for( ; ; )
    {
        xSerialGetChar(&cByteRxed, ( TickType_t ) 0xFFFF);
    }
}


/** Формирование запроса */
void vCMD_Task(void *pvParameters)
{
    ( void ) pvParameters;
    for( ; ; )
    {
        taskYIELD();
    }
}

/** Логирование сообщения */
void vPrint_Task(void *pvParameters)
{
    ( void ) pvParameters;
    for( ; ; )
    {
        taskYIELD();
    }
}