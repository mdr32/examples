#ifndef _DHT_H
#define _DHT_H

#ifdef __cplusplus
extern "C"
{
#endif

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