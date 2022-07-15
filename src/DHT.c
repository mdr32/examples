#include "DHT.h"

#define DHT_INTERVAL_TIMER_US_LIMIT 200 // µs

#define DHT_PORT    GPIOA
#define DHT_PIN     GPIO1
#define DHT_RCC     RST_CLK_PCLK_PORTA

#define DHT_TIM     TIM1

static void DHT_tim_init (void)
{
    // init tim bus clock - Инициализация тактирования для переферии и таймера
    NVIC_EnableIRQ(Timer1_IRQn); // Включаем прерывание таймера
    RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER1, ENABLE);
    MDR_RST_CLK->TIM_CLOCK = 0x01000000; //Включение тактовой частоты таймера 1, TIM1_CLK == HCLK    

    // init tim - Инициализация таймера
    TIM_CNTRL(DHT_TIM) = 0x00000000;  // Сбрасываем настройки таймера
    timer_set_counter(DHT_TIM, 0);
    timer_set_prescaler(DHT_TIM, rcc_ahb_frequency / 1000000 - 1); // 1MHz = 1µs
    timer_set_period(DHT_TIM, DHT_INTERVAL_TIMER_US_LIMIT);
}

static void DHT_tim_delay_us (uint16_t us)
{
    timer_disable_counter(DHT_TIM);
    timer_set_counter(DHT_TIM, 0);
    timer_enable_irq(DHT_TIM, TIM_IER_CNT_ARR_EVENT);
    timer_enable_counter(DHT_TIM);
    while (timer_get_counter(DHT_TIM) < us);
    timer_disable_counter(DHT_TIM);
    timer_disable_irq(DHT_TIM, TIM_IER_CNT_ARR_EVENT);
    TIM_SR(DHT_TIM) = 0x00;
}

static void DHT_tim_irq_start (void)
{
    timer_set_counter(DHT_TIM, 0);
    timer_enable_irq(DHT_TIM, TIM_IER_CCR1_CAP_EVENT | TIM_IER_CNT_ARR_EVENT);
    /**
     * Режим работы каналов
     * Захват по положительному фронту сигнала на входе CHxi,
     * сигнал зафиксирован в 1 триггере на частоте TIM_CLK
     * TIM_CH1_CNTRL(DHT_TIM) = 0x00008000; */
    timer_ic_set_prescaler(DHT_TIM, TIM_IC1, TIM_IC_PSC_OFF);
    timer_ic_set_filter(DHT_TIM, TIM_IC1, TIM_IC_OFF);
    timer_ic_set_polarity(DHT_TIM, TIM_IC1, TIM_IC_FALLING);
    timer_ic_enable(DHT_TIM, TIM_IC1);
    /** Режим работы выхода канала – канал на выход не работает
     * рекомендуется обнулить регистр канала TIM_CH1_CNTRL1 */
    TIM_CH1_CNTRL1(DHT_TIM) = 0x00000000;
    timer_enable_counter(DHT_TIM);
}

static void DHT_tim_irq_stop (void)
{
    timer_disable_counter(DHT_TIM);
    timer_disable_irq(DHT_TIM, TIM_IER_CCR1_CAP_EVENT | TIM_IER_CNT_ARR_EVENT);
}

static void DHT_pin_read (void)
{
    /** @note errata-0032: Подробности смотри в Errata Sheet */
    if((GPIO_OE(DHT_PORT) & DHT_PIN) && gpio_get(DHT_PORT, DHT_PIN))
    {
        gpio_clear(DHT_PORT, DHT_PIN);
        while(!gpio_get(DHT_PORT, DHT_PIN));
    }
    /** @note Поскольку между отправкой контрольного запроса и получением ответа
     * интервал должен отсутствовать, то именно здесь можно переключить
     * порт на чтение, обратившись напрямую к регистру. */
    GPIO_OE(DHT_PORT) &= ~DHT_PIN;
    gpio_set_af(DHT_PORT, GPIO_FUN_ALT, DHT_PIN);
}

static void DHT_pin_low (void)
{
    gpio_clear(DHT_PORT, DHT_PIN);
}

static void DHT_pin_hight (void)
{
    gpio_set(DHT_PORT, DHT_PIN);
}

static void DHT_pin_init (void)
{
    /** Изначально порт настроен на выход */
    RST_CLK_PCLKcmd(DHT_RCC, ENABLE);
    gpio_mode_setup(DHT_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, DHT_PIN);
    gpio_set_output_options(DHT_PORT, GPIO_OTYPE_OD, GPIO_OSPEED_MAXFAST, DHT_PIN);
}

/**
 * @brief Отправка команды на чтение данных от сенсора
 */
void DHT_data_read (DHT_t *dht)
{
    /** Старт инициализации переферии */
    // DHT_tim_irq_stop(); /** @todo - not test */
    dht->state = DHT_State_Query;
    DHT_pin_init();
    DHT_tim_init();

    /** Старт сигнала управления */
    DHT_pin_low();
    delay_ms(5);
    DHT_pin_hight();
    DHT_tim_delay_us(20);
    DHT_pin_low();
    DHT_pin_read();
    DHT_tim_delay_us(5);
    dht->cnt = 0;

    /** Старт записи ответа */
    DHT_tim_irq_start();
    dht->state = DHT_State_Listen;
}

/**
 * @brief Вычисление полученного логи сигналов с декодированиием
 *        в значения температуры и влажности
 */
void DHT_data_calc (DHT_t *dht)
{
    if(dht->state != DHT_State_Filled){
        return;
    }
    dht->state = DHT_State_Calc;

    volatile uint8_t __data[5];
    volatile uint8_t __dti = 0;

    /**
     * @brief  Определение разряд бита данных из ширины периода
     * Направление получаемого бита определяется из ширины положительного импульса.
     * 
     * Соответственно, сохраняя по событию таймера ширину полного периода (t),
     * учитывая постоянную длину отрицательного полупериода (50мкс),
     * можно определить ширину положительного импульса (t-50мкс).
     * После чего, определить направление бита, исходя из границы смещения (45мкс).
     * Например:
     * 1 = (t - 50мкс) > 45мкс;
     * 0 = (t - 50мкс) <= 45мкс;
     * 
     * В данной реализации, для сокращения количества операций, ширина отрицательного
     * импульса суммирована с периодом смещения (50мкс + 45мкс = 95мкс), т.е.
     * 1 = t > (50мкс + 45мкс);
     * 0 = t <= (50мкс + 45мкс);
     */
    for (uint8_t __i = 0; __i < 40; __i++)
    {
        /** bit direction - вставляем на место нулевого бита, после смещаем влево*/
        if(dht->data[__i + 1] > 95)
        {
            __data[__dti] |= (1 << 0);
        }else {
            __data[__dti] &= ~(1 << 0);
        }

        /** bit position */
        if((__i % 8) == 7)
        {
            __dti++;
            __data[__dti] = 0x00;
        } else {
            __data[__dti] <<= 1;
        }
    }

    /** Проверка контрольной суммы */
    if((__data[0] + __data[1] + __data[2] + __data[3]) != __data[4])
    {
        dht->status = DHT_Status_DataNotValid;
        return;
    }

    dht->temperature = (float)(__data[2]*256 + __data[3]) / 10.0f;
    dht->humidity = (float)(__data[0]*256 + __data[1]) / 10.0f;
    dht->status = DHT_Status_Success;
    dht->state = DHT_State_IDLE;
}

/**
 * @brief Обработчик прерывания, когда таймер изменен
 * 
 * @todo Не протестирована отрицательная температура!
 * @todo Можно упростить логгироывние в массив, вместо буффера uint8_t[40] 
 *       использовать uint8_t[5]
 * @todo Можно поставить игнорирование первого сигнала, чтобы сократить массив
 *       до uint8_t[40], сократив тем самым количество операций в методе
 *       калькуляции.
 */
void DHT_CaptureIRQCallback (DHT_t *dht)
{
    /** Если прерывание не связано с текущим процессом, то игнорируем его*/
    if(dht->state != DHT_State_Query && dht->state != DHT_State_Listen)
    {
         return;
    }

    /** Переполнение таймера (например, если долго нет ответа от сенсора) */
    if(timer_get_flag(DHT_TIM, TIM_SR_CNT_ARR_EVENT))
    {
        if(dht->state == DHT_State_Listen){
            dht->state = DHT_Status_Timeout;
            DHT_tim_irq_stop();
        }
        return;
    }

    /** Внешнее событие с изменением фронта сигнала */
    if(timer_get_flag(DHT_TIM, TIM_SR_CCR1_CAP_EVENT))
    {
        if (dht->cnt < 42)
        {
            dht->data[dht->cnt] = TIM_CCR1(DHT_TIM);
            dht->cnt += 1;
        }
        timer_set_counter(DHT_TIM, 0);

        if(dht->cnt == 41)
        {
            dht->state = DHT_State_Filled;
            DHT_tim_irq_stop();
        }
    }
    TIM_SR(DHT_TIM) = 0x00;
}