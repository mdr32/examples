#ifndef _LOCM3_RCC_H
#define _LOCM3_RCC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "locm3_bridge.h"

/** @brief Reset and Clock Control (RCC) @{*/
#define RCC_BASE    MDR_RST_CLK_BASE
/**@}*/

/* --- RCC registers ------------------------------------------------------- */
#define RCC_CLOCK_STATUS    MMIO32(RCC_BASE + 0x00)
#define RCC_PLL_CONTROL     MMIO32(RCC_BASE + 0x04)
#define RCC_HS_CONTROL      MMIO32(RCC_BASE + 0x08)
#define RCC_CPU_CLOCK       MMIO32(RCC_BASE + 0x0C)
#define RCC_USB_CLOCK       MMIO32(RCC_BASE + 0x10)
#define RCC_ADC_MCO_CLOCK   MMIO32(RCC_BASE + 0x14)
#define RCC_RTC_CLOCK       MMIO32(RCC_BASE + 0x18)
#define RCC_PER_CLOCK       MMIO32(RCC_BASE + 0x1C)
#define RCC_CAN_CLOCK       MMIO32(RCC_BASE + 0x20)
#define RCC_TIM_CLOCK       MMIO32(RCC_BASE + 0x24)
#define RCC_UART_CLOCK      MMIO32(RCC_BASE + 0x28)
#define RCC_SSP_CLOCK       MMIO32(RCC_BASE + 0x2C)

/** @brief Глобальная переменная со значение тактовой частоты */
extern uint32_t rcc_ahb_frequency;

#ifdef __cplusplus
}
#endif
#endif
