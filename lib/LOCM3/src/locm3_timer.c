#include "locm3_timer.h"

/*---------------------------------------------------------------------------*/
/** @brief Enable Interrupts for a Timer

@param[in] timer_peripheral Unsigned int32. Timer register address base @ref
tim_reg_base
@param[in] irq Unsigned int32. @ref tim_irq_enable. Logical OR of all interrupt
enable bits to be set
*/

void timer_enable_irq(uint32_t timer_peripheral, uint32_t irq)
{
	TIM_IER(timer_peripheral) |= irq;
}

/*---------------------------------------------------------------------------*/
/** @brief Disable Interrupts for a Timer.

@param[in] timer_peripheral Unsigned int32. Timer register address base @ref
tim_reg_base
@param[in] irq Unsigned int32. @ref tim_irq_enable. Logical OR of all interrupt
enable bits to be cleared
*/

void timer_disable_irq(uint32_t timer_peripheral, uint32_t irq)
{
	TIM_IER(timer_peripheral) &= ~irq;
}

/*---------------------------------------------------------------------------*/
/** @brief Return Interrupt Source.

Returns true if the specified interrupt flag (UIF, TIF or CCxIF, with BIF or
COMIF for advanced timers) was set and the interrupt was enabled. If the
specified flag is not an interrupt flag, the function returns false.

@todo Timers 6-7, 9-14 have fewer interrupts, but invalid flags are not caught
here.

@param[in] timer_peripheral Unsigned int32. Timer register address base @ref
tim_reg_base
@param[in] flag Unsigned int32. Status register flag  @ref tim_sr_values.
@returns boolean: flag set.
*/

bool timer_interrupt_source(uint32_t timer_peripheral, uint32_t flag)
{
/* flag not set or interrupt disabled or not an interrupt source */
	if (((TIM_SR(timer_peripheral) &
		TIM_IER(timer_peripheral) & flag) == 0) ||
		(flag > TIM_SR_BRK_EVENT)) {
		return false;
	}
	return true;
}

/*---------------------------------------------------------------------------*/
/** @brief Read a Status Flag.

@param[in] timer_peripheral Unsigned int32. Timer register address base @ref
tim_reg_base
@param[in] flag Unsigned int32. Status register flag  @ref tim_sr_values.
@returns boolean: flag set.
*/

bool timer_get_flag(uint32_t timer_peripheral, uint32_t flag)
{
	if ((TIM_SR(timer_peripheral) & flag) != 0) {
		return true;
	}

	return false;
}

/*---------------------------------------------------------------------------*/
/** @brief Clear a Status Flag.

@param[in] timer_peripheral Unsigned int32. Timer register address base @ref
tim_reg_base
@param[in] flag Unsigned int32. @ref tim_sr_values. Status register flag.
*/

void timer_clear_flag(uint32_t timer_peripheral, uint32_t flag)
{
	/* All defined bits are rc_w0 */
	TIM_SR(timer_peripheral) = ~flag;
}

/*---------------------------------------------------------------------------*/
/** @brief Set the Timer to Count Up.

This has no effect if the timer is set to center aligned.

@param[in] timer_peripheral Unsigned int32. Timer register address base @ref
tim_reg_base
*/

void timer_direction_up(uint32_t timer_peripheral)
{
	TIM_CNTRL(timer_peripheral) &= ~TIMER_CNTRL_DIR_DOWN;
}

/*---------------------------------------------------------------------------*/
/** @brief Set the Timer to Count Down.

This has no effect if the timer is set to center aligned.

@param[in] timer_peripheral Unsigned int32. Timer register address base @ref
tim_reg_base
*/

void timer_direction_down(uint32_t timer_peripheral)
{
	TIM_CNTRL(timer_peripheral) |= TIMER_CNTRL_DIR_DOWN;
}

/*---------------------------------------------------------------------------*/
/** @brief Enable the timer to start counting.

This should be called after the timer initial configuration has been completed.

@param[in] timer_peripheral Unsigned int32. Timer register address base @ref
tim_reg_base
*/

void timer_enable_counter(uint32_t timer_peripheral)
{
	TIM_CNTRL(timer_peripheral) |= TIM_CNTRL_CNT_EN;
}

/*---------------------------------------------------------------------------*/
/** @brief Stop the timer from counting.

@param[in] timer_peripheral Unsigned int32. Timer register address base @ref
tim_reg_base
*/

void timer_disable_counter(uint32_t timer_peripheral)
{
	TIM_CNTRL(timer_peripheral) &= ~TIM_CNTRL_CNT_EN;
}

/*---------------------------------------------------------------------------*/
/** @brief Set the Value for the Timer Prescaler.

The timer clock is prescaled by the 16 bit scale value plus 1.

@param[in] timer_peripheral Unsigned int32. Timer register address base @ref
tim_reg_base
@param[in] value Unsigned int32. Prescaler values 0...0xFFFF.
*/

void timer_set_prescaler(uint32_t timer_peripheral, uint32_t value)
{
	TIM_PSG(timer_peripheral) = value;
}

/*---------------------------------------------------------------------------*/
/** @brief Timer Set Period

Specify the timer period in the auto-reload register.

@param[in] timer_peripheral Unsigned int32. Timer register address base @ref
tim_reg_base
@param[in] period Unsigned int32. Period in counter clock ticks.
*/

void timer_set_period(uint32_t timer_peripheral, uint32_t period)
{
	TIM_ARR(timer_peripheral) = period;
}

/*---------------------------------------------------------------------------*/
/** @brief Read Counter

Read back the value of a timer's counter register contents

@param[in] timer_peripheral Unsigned int32. Timer register address base
@returns Unsigned int32. Counter value.
*/

uint32_t timer_get_counter(uint32_t timer_peripheral)
{
	return TIM_CNT(timer_peripheral);
}

/*---------------------------------------------------------------------------*/
/** @brief Set Counter

Set the value of a timer's counter register contents.

@param[in] timer_peripheral Unsigned int32. Timer register address base
@param[in] count Unsigned int32. Counter value.
*/

void timer_set_counter(uint32_t timer_peripheral, uint32_t count)
{
	TIM_CNT(timer_peripheral) = count;
}

/*---------------------------------------------------------------------------*/
/** @brief Set Input Capture Filter Parameters

Set the input filter parameters for an input channel, specifying:
@li the frequency of sampling from the Deadtime and Sampling clock
(@see @ref timer_set_clock_division)
@li the number of events that must occur before a transition is considered
valid.

@param[in] timer_peripheral Unsigned int32. Timer register address base
@param[in] ic ::tim_ic_id. Input Capture channel designator.
@param[in] flt ::tim_ic_filter. Input Capture Filter identifier.
*/

void timer_ic_set_filter(uint32_t timer_peripheral, enum tim_ic_id ic, enum tim_ic_filter flt)
{
	TIM_CHy_CNTRL(timer_peripheral, ic) &= ~TIM_CHy_CNTRL_CHF_MASK;
	TIM_CHy_CNTRL(timer_peripheral, ic) |= flt;
}

/*---------------------------------------------------------------------------*/
/** @brief Set Input Capture Prescaler

Set the number of events between each capture.

@param[in] timer_peripheral Unsigned int32. Timer register address base
@param[in] ic ::tim_ic_id. Input Capture channel designator.
@param[in] psc ::tim_ic_psc. Input Capture sample clock prescaler.
*/

void timer_ic_set_prescaler(uint32_t timer_peripheral, enum tim_ic_id ic, enum tim_ic_psc psc)
{
	TIM_CHy_CNTRL(timer_peripheral, ic) &= ~TIM_CHy_CNTRL_CHPSC_MASK;
	TIM_CHy_CNTRL(timer_peripheral, ic) |= psc << 6;
}

/*---------------------------------------------------------------------------*/
/** @brief Set Input Polarity

@param[in] timer_peripheral Unsigned int32. Timer register address base
@param[in] ic ::tim_ic_id. Input Capture channel designator.
@param[in] pol ::tim_ic_pol. Input Capture polarity.
*/

void timer_ic_set_polarity(uint32_t timer_peripheral, enum tim_ic_id ic, enum tim_ic_pol pol)
{
	TIM_CHy_CNTRL(timer_peripheral, ic) &= ~TIM_CHy_CNTRL_CHPL_MASK;
	TIM_CHy_CNTRL(timer_peripheral, ic) |= pol << 4;
}

/*---------------------------------------------------------------------------*/
/** @brief Enable Timer Input Capture

@param[in] timer_peripheral Unsigned int32. Timer register address base
@param[in] ic ::tim_ic_id. Input Capture channel designator.
*/

void timer_ic_enable(uint32_t timer_peripheral, enum tim_ic_id ic)
{
	TIM_CHy_CNTRL(timer_peripheral, ic) |= TIM_CHy_CNTRL_MODE;
}

/*---------------------------------------------------------------------------*/
/** @brief Disable Timer Input Capture

@param[in] timer_peripheral Unsigned int32. Timer register address base
@param[in] ic ::tim_ic_id. Input Capture channel designator.
*/

void timer_ic_disable(uint32_t timer_peripheral, enum tim_ic_id ic)
{
	TIM_CHy_CNTRL(timer_peripheral, ic) &= ~TIM_CHy_CNTRL_MODE;
}