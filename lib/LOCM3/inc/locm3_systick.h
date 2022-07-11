#ifndef _LOCM3_SYSTICK_H
#define _LOCM3_SYSTICK_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "locm3_bridge.h"

/** SysTick Control and Status Register (CSR).
 * Controls the system timer and provides status data.
 * Usage constraints: There are no usage constraints.
 * Configurations Always implemented.
 */
#define STK_CSR				SysTick->CTRL

/** SysTick Reload Value Register (RVR).
 * Reads or clears the value that will be loaded to the counter.
 * Usage constraints:
 * - Any write to the register clears the register to zero.
 * - The counter does not provide read-modify-write protection.
 * - Unsupported bits are read as zero
 * Configurations Always implemented.
 */
#define STK_RVR				SysTick->LOAD

/** SysTick Current Value Register (CVR).
 * Holds the current value of the counter.
 * Usage constraints: There are no usage constraints.
 * Configurations Always implemented.
 */
#define STK_CVR				SysTick->VAL

/** SysTick Calibration Value Register(Read Only) (CALIB)
 * Reads the calibration value and parameters for SysTick.
 * Usage constraints: There are no usage constraints.
 * Configurations Always implemented.
 */
#define STK_CALIB			SysTick->CALIB

/** @defgroup STK_CSR_VALUES STK_CSR Values
 * @{
 */
/** COUNTFLAG
 * Indicates whether the counter has counted to 0 since the last read of this
 * register:
 *  0 = Timer has not counted to 0
 *  1 = Timer has counted to 0.
 */
#define STK_CSR_COUNTFLAG		(1 << 16)

#define STK_CSR_CLKSOURCE_LSB		2
/** CLKSOURCE: Clock source selection
 * for 0, SysTick uses the IMPLEMENTATION DEFINED external reference clock.
 * for 1, SysTick uses the processor clock.
 * If no external clock is provided, this bit reads as 1 and ignores writes.
 */
#define STK_CSR_CLKSOURCE		(1 << STK_CSR_CLKSOURCE_LSB)

/** @defgroup systick_clksource Clock source selection
@ingroup CM3_systick_defines

@{*/
#if defined(__ARM_ARCH_6M__)
#define STK_CSR_CLKSOURCE_EXT		(0 << STK_CSR_CLKSOURCE_LSB)
#define STK_CSR_CLKSOURCE_AHB		(1 << STK_CSR_CLKSOURCE_LSB)
#else
#define STK_CSR_CLKSOURCE_AHB_DIV8	(0 << STK_CSR_CLKSOURCE_LSB)
#define STK_CSR_CLKSOURCE_AHB		(1 << STK_CSR_CLKSOURCE_LSB)
#endif
/**@}*/

/** TICKINT: SysTick exception request enable */
#define STK_CSR_TICKINT			(1 << 1)
/** ENABLE: Counter enable */
#define STK_CSR_ENABLE			(1 << 0)
/**@}*/

/** @defgroup STK_RVR_VALUES STK_RVR Values
 * @{
 */
/** RELOAD[23:0]: RELOAD value */
#define STK_RVR_RELOAD			0x00FFFFFF

/**@}*/


/** @defgroup STK_RVR_VALUES STK_RVR Values
 * @{
 */
/** CURRENT[23:0]: Current counter value */
#define STK_CVR_CURRENT			0x00FFFFFF
/**@}*/


/** @defgroup STK_CALIB_VALUES STK_CALIB Values
 * @{
 */
/** NOREF: NOREF flag
 * Bit31 => NOREF Indicates whether the IMPLEMENTATION DEFINED reference clock
 * is implemented:
 * 0 = The reference clock is implemented.
 * 1 = The reference clock is not implemented.
 * When this bit is 1, the CLKSOURCE bit of the SYST_CSR register is forced to
 * 1 and cannot be cleared to 0.
 */
#define STK_CALIB_NOREF			(1 << 31)

/** SKEW: SKEW flag
 * Bit30 => SKEW Indicates whether the 10ms calibration value is exact:
 * 0 = 10ms calibration value is exact.
 * 1 = 10ms calibration value is inexact, because of the clock frequency
 */
#define STK_CALIB_SKEW			(1 << 30)

/* Bits [29:24] Reserved, must be kept cleared. */
/** TENMS Calibration value for 10ms.
 * Bit0 to 23 => TENMS Optionally, holds a reload value to be used for 10ms
 * (100Hz) timing, subject to system clock skew errors. If this field is zero,
 * the calibration value is not known.
 */
#define STK_CALIB_TENMS			0x00FFFFFF

void systick_set_reload(uint32_t value);
bool systick_set_frequency(uint32_t freq, uint32_t ahb);
uint32_t systick_get_reload(void);
uint32_t systick_get_value(void);
void systick_set_clocksource(uint8_t clocksource);
void systick_interrupt_enable(void);
void systick_interrupt_disable(void);
void systick_counter_enable(void);
void systick_counter_disable(void);
uint8_t systick_get_countflag(void);
void systick_clear(void);

uint32_t systick_get_calib(void);

#ifdef __cplusplus
}
#endif
#endif
