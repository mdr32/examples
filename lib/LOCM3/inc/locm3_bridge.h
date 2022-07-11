#ifndef _LOCM3_BRIDGE_H
#define _LOCM3_BRIDGE_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "MDR32F9Q2I_IT.h"

/* Generic memory-mapped I/O accessor functions */
#define MMIO8(addr)         (*(volatile uint8_t *)(addr))
#define MMIO16(addr)		(*(volatile uint16_t *)(addr))
#define MMIO32(addr)		(*(volatile uint32_t *)(addr))
#define MMIO64(addr)		(*(volatile uint64_t *)(addr))

/* Generic bit-band I/O accessor functions */
#define BBIO_SRAM(addr, bit) \
	MMIO32((((uint32_t)addr) & 0x0FFFFF) * 32 + 0x22000000 + (bit) * 4)

#define BBIO_PERIPH(addr, bit) \
	MMIO32((((uint32_t)addr) & 0x0FFFFF) * 32 + 0x42000000 + (bit) * 4)

/* Generic bit definition */
#define BIT0  (1<<0)
#define BIT1  (1<<1)
#define BIT2  (1<<2)
#define BIT3  (1<<3)
#define BIT4  (1<<4)
#define BIT5  (1<<5)
#define BIT6  (1<<6)
#define BIT7  (1<<7)
#define BIT8  (1<<8)
#define BIT9  (1<<9)
#define BIT10 (1<<10)
#define BIT11 (1<<11)
#define BIT12 (1<<12)
#define BIT13 (1<<13)
#define BIT14 (1<<14)
#define BIT15 (1<<15)
#define BIT16 (1<<16)
#define BIT17 (1<<17)
#define BIT18 (1<<18)
#define BIT19 (1<<19)
#define BIT20 (1<<20)
#define BIT21 (1<<21)
#define BIT22 (1<<22)
#define BIT23 (1<<23)
#define BIT24 (1<<24)
#define BIT25 (1<<25)
#define BIT26 (1<<26)
#define BIT27 (1<<27)
#define BIT28 (1<<28)
#define BIT29 (1<<29)
#define BIT30 (1<<30)
#define BIT31 (1<<31)


#if (defined(USE_MDR32F9Q2I))
    /**
     * @brief Защита контактов JTAG для MCU MDR32F9Q2I
     * Предотвращает установку битов RTXT и OE для JTAG при выполнении чтения-модификации-записи GPIO.
     * Раскомментируйте определения ниже, чтобы определить используемые порты JTAG.
     * Оставьте все прокомментированными/не отмеченными, если нет контактов GPIO, объединенных с JTAG.
     */
    // #define USE_JTAG_A // JTAG_A pins protection
    #define USE_JTAG_B // JTAG_B pins protection
    
#endif

#ifdef __cplusplus
}
#endif
#endif