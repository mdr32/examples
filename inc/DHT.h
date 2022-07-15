#ifndef _DHT_H
#define _DHT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "MDR32FxQI_rst_clk.h"
#include "locm3_gpio.h"
#include "locm3_timer.h"

#include "delay.h"

/**
 * @example Пример работы с сенсором DHT-21 (AM2301)
 * 
 * @code
    #include "MDR32FxQI_rst_clk.h"
    #include "DHT.h"

    #define MSLEEP 500 // ms

    static void clk_CoreConfig(void);

    DHT_t Sensor;

    void Timer1_IRQHandler(void)
    {
        DHT_CaptureIRQCallback(&Sensor);
    }

    int main(void)
    {
        clk_CoreConfig();
        delay_setup();
        while (1)
        {
            DHT_data_read(&Sensor);
            delay_ms(300);
            DHT_data_calc(&Sensor);
            delay_ms(100);
        }
        return 0;
    }
 * 
 */

typedef enum
{
    DHT_State_IDLE = 0,
    DHT_State_Query,
    DHT_State_Listen,
    DHT_State_Filled,
    DHT_State_Calc
} DHT_State_t;

typedef enum
{
    DHT_Status_Success = 0,
    DHT_Status_Timeout,     /** Подвисший запрос */
    DHT_Status_DataNotValid /** Контрольная сумма не вераная */
} DHT_Status_t;


typedef struct
{
    uint8_t         data[41];
    uint8_t         cnt;
    DHT_State_t     state;
    DHT_Status_t    status;
    float           temperature;
    float           humidity;
} DHT_t;

void DHT_data_read (DHT_t *dht);
void DHT_data_calc (DHT_t *dht);

void DHT_CaptureIRQCallback(DHT_t *dht);

#ifdef __cplusplus
}
#endif
#endif