#ifndef _LCM3_TIMER_H
#define _LCM3_TIMER_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "locm3_bridge.h"

#define TIM1				MDR_TIMER1_BASE //  (0x40070000)
#define TIM2				MDR_TIMER2_BASE //  (0x40078000)
#define TIM3				MDR_TIMER3_BASE //  (0x40080000)

/** @brief TIM_CNT: Основной счетчик таймера */
#define TIM_CNT(tim_base)   MMIO32((tim_base) + 0x00)
#define TIM1_CNT			TIM_CNT(TIM1)
#define TIM2_CNT			TIM_CNT(TIM2)
#define TIM3_CNT			TIM_CNT(TIM3)

/** @brief TIM_PSG: Делитель частоты при счете основного счетчика */
#define TIM_PSG(tim_base)   MMIO32((tim_base) + 0x04)
#define TIM1_PSG			TIM_PSG(TIM1)
#define TIM2_PSG			TIM_PSG(TIM2)
#define TIM3_PSG			TIM_PSG(TIM3)

/** @brief TIM_ARR: Основание счета основного счетчика */
#define TIM_ARR(tim_base)   MMIO32((tim_base) + 0x08)
#define TIM1_ARR			TIM_ARR(TIM1)
#define TIM2_ARR			TIM_ARR(TIM2)
#define TIM3_ARR			TIM_ARR(TIM3)

/** @brief TIM_CNTRL: Регистр управления основного счетчика */
#define TIM_CNTRL(tim_base) MMIO32((tim_base) + 0x0C)
#define TIM1_CNTRL			TIM_CNTRL(TIM1)
#define TIM2_CNTRL			TIM_CNTRL(TIM2)
#define TIM3_CNTRL			TIM_CNTRL(TIM3)


/** TIM_CCRx: Регистр сравнения, захвата для каналов таймера
@{*/
#define TIM_CCR1(tim_base)  MMIO32((tim_base) + 0x10)
#define TIM1_CCR1			TIM_CCR1(TIM1)
#define TIM2_CCR1			TIM_CCR1(TIM2)
#define TIM3_CCR1			TIM_CCR1(TIM3)

#define TIM_CCR2(tim_base)  MMIO32((tim_base) + 0x14)
#define TIM1_CCR2			TIM_CCR2(TIM1)
#define TIM2_CCR2			TIM_CCR2(TIM2)
#define TIM3_CCR2			TIM_CCR2(TIM3)

#define TIM_CCR3(tim_base)  MMIO32((tim_base) + 0x18)
#define TIM1_CCR3			TIM_CCR3(TIM1)
#define TIM2_CCR3			TIM_CCR3(TIM2)
#define TIM3_CCR3			TIM_CCR3(TIM3)

#define TIM_CCR4(tim_base)  MMIO32((tim_base) + 0x1C)
#define TIM1_CCR4			TIM_CCR4(TIM1)
#define TIM2_CCR4			TIM_CCR4(TIM2)
#define TIM3_CCR4			TIM_CCR4(TIM3)
/**@}*/


/** TIM_CHy_CNTRL: Регистр управления для каналов таймера
@{*/
#define TIM_CH1_CNTRL(tim_base) MMIO32((tim_base) + 0x20)
#define TIM1_CH1_CNTRL      TIM_CH1_CNTRL(TIM1)
#define TIM2_CH1_CNTRL      TIM_CH1_CNTRL(TIM2)
#define TIM3_CH1_CNTRL      TIM_CH1_CNTRL(TIM3)

#define TIM_CH2_CNTRL(tim_base) MMIO32((tim_base) + 0x24)
#define TIM1_CH2_CNTRL      TIM_CH2_CNTRL(TIM1)
#define TIM2_CH2_CNTRL      TIM_CH2_CNTRL(TIM2)
#define TIM3_CH2_CNTRL      TIM_CH2_CNTRL(TIM3)

#define TIM_CH3_CNTRL(tim_base) MMIO32((tim_base) + 0x28)
#define TIM1_CH3_CNTRL      TIM_CH3_CNTRL(TIM1)
#define TIM2_CH3_CNTRL      TIM_CH3_CNTRL(TIM2)
#define TIM3_CH3_CNTRL      TIM_CH3_CNTRL(TIM3)

#define TIM_CH4_CNTRL(tim_base) MMIO32((tim_base) + 0x2C)
#define TIM1_CH4_CNTRL      TIM_CH4_CNTRL(TIM1)
#define TIM2_CH4_CNTRL      TIM_CH4_CNTRL(TIM2)
#define TIM3_CH4_CNTRL      TIM_CH4_CNTRL(TIM3)

#define TIM_CHy_CNTRL(tim_base, tim_ch_pos) MMIO32((tim_base) + (0x20 + ((tim_ch_pos) * 4)))

#define TIM_CHy_CNTRL_MODE          (1 << 15)

#define TIM_CHy_CNTRL_CHPSC_MASK    (0x3 << 6)  // [7:6]
#define TIM_CHy_CNTRL_CHPL_MASK     (0x3 << 4)  // [5:4]
#define TIM_CHy_CNTRL_CHF_MASK      (0xF << 0)  // [3:0]


// (1 << 15)

/**@}*/


/** TIM_CHy_CNTRL1: Регистр управления 1 для каналов таймера
@{*/
#define TIM_CH1_CNTRL1(tim_base) MMIO32((tim_base) + 0x30)
#define TIM1_CH1_CNTRL1     TIM_CH1_CNTRL1(TIM1)
#define TIM2_CH1_CNTRL1     TIM_CH1_CNTRL1(TIM2)
#define TIM3_CH1_CNTRL1     TIM_CH1_CNTRL1(TIM3)

#define TIM_CH2_CNTRL1(tim_base) MMIO32((tim_base) + 0x34)
#define TIM1_CH2_CNTRL1     TIM_CH2_CNTRL1(TIM1)
#define TIM2_CH2_CNTRL1     TIM_CH2_CNTRL1(TIM2)
#define TIM3_CH2_CNTRL1     TIM_CH2_CNTRL1(TIM3)

#define TIM_CH3_CNTRL1(tim_base) MMIO32((tim_base) + 0x38)
#define TIM1_CH3_CNTRL1     TIM_CH3_CNTRL1(TIM1)
#define TIM2_CH3_CNTRL1     TIM_CH3_CNTRL1(TIM2)
#define TIM3_CH3_CNTRL1     TIM_CH3_CNTRL1(TIM3)

#define TIM_CH4_CNTRL1(tim_base) MMIO32((tim_base) + 0x3C)
#define TIM1_CH4_CNTRL1     TIM_CH4_CNTRL1(TIM1)
#define TIM2_CH4_CNTRL1     TIM_CH4_CNTRL1(TIM2)
#define TIM3_CH4_CNTRL1     TIM_CH4_CNTRL1(TIM3)

#define TIM_CHy_CNTRL1(tim_base, tim_ch_pos) MMIO32((tim_base) + (0x30 + ((tim_ch_pos) * 4)))
/**@}*/


/** TIM_CHy_DTG: Регистр управления DTG для каналов таймера
@{*/
#define TIM_CH1_DTG(tim_base) MMIO32((tim_base) + 0x40)
#define TIM1_CH1_DTG        TIM_CH1_DTG(TIM1)
#define TIM2_CH1_DTG        TIM_CH1_DTG(TIM2)
#define TIM3_CH1_DTG        TIM_CH1_DTG(TIM3)

#define TIM_CH2_DTG(tim_base) MMIO32((tim_base) + 0x44)
#define TIM1_CH2_DTG        TIM_CH2_DTG(TIM1)
#define TIM2_CH2_DTG        TIM_CH2_DTG(TIM2)
#define TIM3_CH2_DTG        TIM_CH2_DTG(TIM3)

#define TIM_CH3_DTG(tim_base) MMIO32((tim_base) + 0x48)
#define TIM1_CH3_DTG        TIM_CH3_DTG(TIM1)
#define TIM2_CH3_DTG        TIM_CH3_DTG(TIM2)
#define TIM3_CH3_DTG        TIM_CH3_DTG(TIM3)

#define TIM_CH4_DTG(tim_base) MMIO32((tim_base) + 0x4C)
#define TIM1_CH4_DTG        TIM_CH4_DTG(TIM1)
#define TIM2_CH4_DTG        TIM_CH4_DTG(TIM2)
#define TIM3_CH4_DTG        TIM_CH4_DTG(TIM3)
/**@}*/


/** @brief TIM_BRKETR_CNTRL: Регистр управления входом BRK и ETR */
#define TIM_BRKETR_CNTRL(tim_base)  MMIO32((tim_base) + 0x50)
#define TIM1_BRKETR_CNTRL       TIM_BRKETR_CNTRL(TIM1)
#define TIM2_BRKETR_CNTRL       TIM_BRKETR_CNTRL(TIM2)
#define TIM3_BRKETR_CNTRL       TIM_BRKETR_CNTRL(TIM3)

/** @brief TIM_SR: Регистр статуса таймера (STATUS) */
#define TIM_SR(tim_base)        MMIO32((tim_base) + 0x54)
#define TIM1_SR			        TIM_SR(TIM1)
#define TIM2_SR			        TIM_SR(TIM2)
#define TIM3_SR			        TIM_SR(TIM3)

/** @brief TIM_IER: Регистр разрешения прерывания таймера (IE)*/
#define TIM_IER(tim_base)       MMIO32((tim_base) + 0x58)
#define TIM1_IER                TIM_IER(TIM1)
#define TIM2_IER                TIM_IER(TIM2)
#define TIM3_IER                TIM_IER(TIM3)

/** @brief TIM_DMA_RE: Регистр разрешения запросов DMA от прерываний таймера */
#define TIM_DMA_RE(tim_base)    MMIO32((tim_base) + 0x5C)
#define TIM1_DMA_RE			    TIM_DMA_RE(TIM1)
#define TIM2_DMA_RE			    TIM_DMA_RE(TIM2)
#define TIM3_DMA_RE			    TIM_DMA_RE(TIM3)


/** TIM_CHy_CNTRL2: Регистр управления 2 для каналов таймера
@{*/
#define TIM_CH1_CNTRL2(tim_base)  MMIO32((tim_base) + 0x60)
#define TIM1_CH1_CNTRL2         TIM_CH1_CNTRL2(TIM1)
#define TIM2_CH1_CNTRL2         TIM_CH1_CNTRL2(TIM2)
#define TIM3_CH1_CNTRL2         TIM_CH1_CNTRL2(TIM3)

#define TIM_CH2_CNTRL2(tim_base)    MMIO32((tim_base) + 0x64)
#define TIM1_CH2_CNTRL2         TIM_CH2_CNTRL2(TIM1)
#define TIM2_CH2_CNTRL2         TIM_CH2_CNTRL2(TIM2)
#define TIM3_CH2_CNTRL2         TIM_CH2_CNTRL2(TIM3)

#define TIM_CH3_CNTRL2(tim_base)    MMIO32((tim_base) + 0x68)
#define TIM1_CH3_CNTRL2         TIM_CH3_CNTRL2(TIM1)
#define TIM2_CH3_CNTRL2         TIM_CH3_CNTRL2(TIM2)
#define TIM3_CH3_CNTRL2         TIM_CH3_CNTRL2(TIM3)

#define TIM_CH4_CNTRL2(tim_base)    MMIO32((tim_base) + 0x6C)
#define TIM1_CH4_CNTRL2         TIM_CH4_CNTRL2(TIM1)
#define TIM2_CH4_CNTRL2         TIM_CH4_CNTRL2(TIM2)
#define TIM3_CH4_CNTRL2         TIM_CH4_CNTRL2(TIM3)
/**@}*/


/** TIM_CCRy1: Регистр сравнения 1, захвата для каналов таймера
@{*/
#define TIM_CCR11(tim_base) MMIO32((tim_base) + 0x70)
#define TIM1_CCR11          TIM_CCR11(TIM1)
#define TIM2_CCR11          TIM_CCR11(TIM2)
#define TIM3_CCR11          TIM_CCR11(TIM3)

#define TIM_CCR21(tim_base) MMIO32((tim_base) + 0x74)
#define TIM1_CCR21          TIM_CCR21(TIM1)
#define TIM2_CCR21          TIM_CCR21(TIM2)
#define TIM3_CCR21          TIM_CCR21(TIM3)

#define TIM_CCR31(tim_base) MMIO32((tim_base) + 0x78)
#define TIM1_CCR31          TIM_CCR31(TIM1)
#define TIM2_CCR31          TIM_CCR31(TIM2)
#define TIM3_CCR31          TIM_CCR31(TIM3)

#define TIM_CCR41(tim_base) MMIO32((tim_base) + 0x7C)
#define TIM1_CCR41          TIM_CCR41(TIM1)
#define TIM2_CCR41          TIM_CCR41(TIM2)
#define TIM3_CCR41          TIM_CCR41(TIM3)
/**@}*/


// TIM_CNTRL
// #define TIMER_CNTRL_EVENT_SEL_Msk   (1 << 0)
// #define TIMER_CNTRL_CNT_MODE_Msk    (1 << 0)
// #define TIMER_CNTRL_FDTS_Msk        (1 << 0)
#define TIMER_CNTRL_DIR_DOWN        (1 << 3)
// #define TIMER_CNTRL_WR_CMPL         (1 << 2)
// #define TIMER_CNTRL_ARRB_EN         (1 << 1)
#define TIM_CNTRL_CNT_EN            (1 << 0)


/* --- TIMx_IE values ----------------------------------------------------
@{*/
#define TIM_IER_CCR4_CAP1_EVENT        (1 << 16)
#define TIM_IER_CCR3_CAP1_EVENT        (1 << 15)
#define TIM_IER_CCR2_CAP1_EVENT        (1 << 14)
#define TIM_IER_CCR1_CAP1_EVENT        (1 << 13)
// #define TIM_IE_EVENT_CCR_CAP1         (1 << 13)    /** [16:13] */

#define TIM_IER_CCR4_REF_EVENT         (1 << 12)
#define TIM_IER_CCR3_REF_EVENT         (1 << 11)
#define TIM_IER_CCR2_REF_EVENT         (1 << 10)
#define TIM_IER_CCR1_REF_EVENT         (1 << 9)
// #define TIM_IE_EVENT_CCR_REF          (1 << 9)   /** [12:9] */

#define TIM_IER_CCR4_CAP_EVENT         (1 << 8)
#define TIM_IER_CCR3_CAP_EVENT         (1 << 7)
#define TIM_IER_CCR2_CAP_EVENT         (1 << 6)
#define TIM_IER_CCR1_CAP_EVENT         (1 << 5)
// #define TIM_IE_EVENT_CCR_CAP          (1 << 5)    /** [8:5] */

#define TIM_IER_BRK_EVENT              (1 << 4)
#define TIM_IER_ETR_FE_EVENT           (1 << 3)
#define TIM_IER_ETR_RE_EVENT           (1 << 2)
#define TIM_IER_CNT_ARR_EVENT          (1 << 1)
#define TIM_IER_CNT_ZERO_EVENT         (1 << 0)
/**@}*/


/*-- TIMER_STATUS: Timer Status Register ---------------------------
@{*/
#define TIM_SR_CCR4_CAP1_EVENT        (1 << 16)
#define TIM_SR_CCR3_CAP1_EVENT        (1 << 15)
#define TIM_SR_CCR2_CAP1_EVENT        (1 << 14)
#define TIM_SR_CCR1_CAP1_EVENT        (1 << 13)
// #define TIMER_SR_CCR_CAP1_EVENT         (1 << 13)   /** [16:13] */

#define TIM_SR_CCR4_REF_EVENT         (1 << 12)
#define TIM_SR_CCR3_REF_EVENT         (1 << 11)
#define TIM_SR_CCR2_REF_EVENT         (1 << 10)
#define TIM_SR_CCR1_REF_EVENT         (1 << 9)
// #define TIMER_SR_CCR_REF_EVENT          (1 << 9)   /** [12:9] */

#define TIM_SR_CCR4_CAP_EVENT         (1 << 8)
#define TIM_SR_CCR3_CAP_EVENT         (1 << 7)
#define TIM_SR_CCR2_CAP_EVENT         (1 << 6)
#define TIM_SR_CCR1_CAP_EVENT         (1 << 5)
// #define TIMER_SR_CCR_CAP_EVENT          (1 << 5)    /** [8:5] */

#define TIM_SR_BRK_EVENT              (1 << 4) //TIM_SR_BIF
#define TIM_SR_ETR_FE_EVENT           (1 << 3)
#define TIM_SR_ETR_RE_EVENT           (1 << 2)
#define TIM_SR_CNT_ARR_EVENT          (1 << 1)
#define TIM_SR_CNT_ZERO_EVENT         (1 << 0)
/**@}*/


/** Input Capture channel designators */
enum tim_ic_id {
	TIM_IC1,
	TIM_IC2,
	TIM_IC3,
	TIM_IC4
};

/** Input Capture input filter. The frequency used to sample the
input and the number of events needed to validate an output transition.

TIM_IC_CK_INT_N_x No division from the Deadtime and Sampling Clock frequency
(DTF), filter length x
TIM_IC_DTF_DIV_y_N_x Division by y from the DTF, filter length x
 */
enum tim_ic_filter {
	TIM_IC_OFF,
	TIM_IC_CK_INT_N_2,
	TIM_IC_CK_INT_N_4,
	TIM_IC_CK_INT_N_8,
	TIM_IC_DTF_DIV_2_N_6,
	TIM_IC_DTF_DIV_2_N_8,
	TIM_IC_DTF_DIV_4_N_6,
	TIM_IC_DTF_DIV_4_N_8,
	TIM_IC_DTF_DIV_8_N_6,
	TIM_IC_DTF_DIV_8_N_8,
	TIM_IC_DTF_DIV_16_N_5,
	TIM_IC_DTF_DIV_16_N_6,
	TIM_IC_DTF_DIV_16_N_8,
	TIM_IC_DTF_DIV_32_N_5,
	TIM_IC_DTF_DIV_32_N_6,
	TIM_IC_DTF_DIV_32_N_8
};

/** Input Capture input prescaler.

TIM_IC_PSC_x Input capture is done every x events*/
enum tim_ic_psc {
	TIM_IC_PSC_OFF,
	TIM_IC_PSC_2,
	TIM_IC_PSC_4,
	TIM_IC_PSC_8
};

/** Input Capture input polarity */
enum tim_ic_pol {
	TIM_IC_RISING,
	TIM_IC_FALLING
};

/**
 * @brief Выбор события по входному каналу CHxi для фиксации значения
 *        основного счетчика (регистр MDR_TIMERx->CNT) в регистр CCR
 *        при условии:
 *         - таймер использует режим "Режим 1";
 *         - источник события положительный фронт другого канала.
 * 
 *  Таблица сопоставления каналов-источников и каналов-слушателей:
 *   | in \ out | CH1 | CH2 | CH3 | CH4 |
 *   |----------|-----|-----|-----|-----|
 *   | CH1      |   0 |   1 |   1 |   0 |
 *   | CH2      |   0 |   0 |   1 |   1 |
 *   | CH3      |   1 |   0 |   0 |   1 |
 *   | CH4      |   1 |   1 |   0 |   0 |
 * 
 * @note Текущая реализация библиотеки не предусматривает режимы
 * каналов master-slave. При этом, указанное перечисление определено,
 * так как имеет опции общих битов для других настроек в других режимах.
 */
enum tim_ic_input {
	TIM_IC_IN_TI1 = 1,
	TIM_IC_IN_TI2 = 2,
	TIM_IC_IN_TI3 = 5,
	TIM_IC_IN_TI4 = 6,
};

/**
 * @note MCU не поддерживает регистр предзагрузки регистрорв,
 * поэтому нижеуказанных методов нет в этом МК
 * 
 * void timer_enable_preload(uint32_t timer_peripheral);
 * void timer_disable_preload(uint32_t timer_peripheral);
 */
void timer_enable_irq(uint32_t timer_peripheral, uint32_t irq);
void timer_disable_irq(uint32_t timer_peripheral, uint32_t irq);
bool timer_interrupt_source(uint32_t timer_peripheral, uint32_t flag);
bool timer_get_flag(uint32_t timer_peripheral, uint32_t flag);
void timer_clear_flag(uint32_t timer_peripheral, uint32_t flag);
void timer_direction_up(uint32_t timer_peripheral);
void timer_direction_down(uint32_t timer_peripheral);
void timer_enable_counter(uint32_t timer_peripheral);
void timer_disable_counter(uint32_t timer_peripheral);
void timer_set_prescaler(uint32_t timer_peripheral, uint32_t value); // ??? 
void timer_set_period(uint32_t timer_peripheral, uint32_t period);
uint32_t timer_get_counter(uint32_t timer_peripheral);
void timer_set_counter(uint32_t timer_peripheral, uint32_t count);
void timer_ic_set_filter(uint32_t timer_peripheral, enum tim_ic_id ic, enum tim_ic_filter flt);
void timer_ic_set_prescaler(uint32_t timer_peripheral, enum tim_ic_id ic, enum tim_ic_psc psc);
void timer_ic_set_polarity(uint32_t timer_peripheral, enum tim_ic_id ic, enum tim_ic_pol pol);

/**
 * @note MCU в режиме НЕ-"master-slave" каналов, не требует обязательной
 * необходимости указывать канал захвата на самого себя.
 * Поскольку в текущей реализации библиотеки не предусмотрен режим
 * каналов master-slave, то метод конфигурирования входа такого
 * канала - не предусмотрен.
 * 
 * void timer_ic_set_input(uint32_t timer_peripheral, enum tim_ic_id ic, enum tim_ic_input in);
 */
void timer_ic_enable(uint32_t timer_peripheral, enum tim_ic_id ic);
void timer_ic_disable(uint32_t timer_peripheral, enum tim_ic_id ic);

#ifdef __cplusplus
}
#endif
#endif