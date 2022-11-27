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

/** xSerialSendMessage_t Содержание сообщения */
typedef struct {
    uint8_t device_id;
    uint8_t fn_code;
    uint8_t red_addr[2];
    uint8_t value[2];
    uint8_t crc_low;
    uint8_t crc_high;
} xSerialSendMessage_t;

int main(void)
{
    clk_CoreConfig();

    // Baud определен с учетом ошибки, реально используется 115200
    // Вторым аргументом передаем длину эл-тов
    xSerialPortInit(57600, sizeof(xSerialSendMessage_t), sizeof(xSerialSendMessage_t) * 3);

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
    xSerialSendMessage_t cmd = {};
    cmd.device_id   = 0xaa;
    cmd.fn_code     = 0xbb;

    cmd.red_addr[0] = 0xc1;
    cmd.red_addr[1] = 0xc2;

    cmd.value[0]    = 0xd1;
    cmd.value[1]    = 0xd2;

    cmd.crc_low     = 0xee;
    cmd.crc_high    = 0xff;

    for( ; ; )
    {
        if(isSerialSendMessageEmpty() == pdTRUE)
        {
            xSerialAddMessageSend((uint8_t *)&cmd, 0);
            xSerialSendMessage();
        }
        vTaskDelay(600);
    }
}

/** Чтение отввета на запрос */
void vRead_Task(void *pvParameters)
{
    // Сработает, когда в очереди будет пусто
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