#include "locm3_gpio.h"

void gpio_set(uint32_t gpioport, uint16_t gpios)
{
    GPIO_RXTX(gpioport) = (gpios | GPIO_RXTX(gpioport)) & (~JTAG_PINS(gpioport));
}

void gpio_clear(uint32_t gpioport, uint16_t gpios)
{
    GPIO_RXTX(gpioport) &= ~(gpios | JTAG_PINS(gpioport));
}

uint16_t gpio_get(uint32_t gpioport, uint16_t gpios)
{
    return gpio_port_read(gpioport) & gpios;
}

void gpio_toggle(uint32_t gpioport, uint16_t gpios)
{
    /** @note На текущий момент в MDR32 доступ чтение/запись к портам
     *        осуществляется через один регистра RX/TX (т.е. нет доступа
     *        по отдельностик к RX или TX и нет атомарности), поэтому
     *        переключатель на обычном тернарном операторе.
     */
    gpio_get(gpioport, gpios)
        ? gpio_clear(gpioport, gpios)
        : gpio_set(gpioport, gpios);
}

uint16_t gpio_port_read(uint32_t gpioport)
{
    return (uint16_t) GPIO_RXTX(gpioport);
}

void gpio_port_write(uint32_t gpioport, uint16_t data)
{
    GPIO_RXTX(gpioport) = data & (~JTAG_PINS(gpioport));
}

void gpio_mode_setup(uint32_t gpioport, GPIO_MODE_TypeDef mode, uint8_t pull_up_down, uint16_t gpios)
{
	uint16_t i;
	uint32_t pupd, oafr;

	if (mode == GPIO_MODE_ANALOG) {
		GPIO_ANALOG(gpioport) &= ~(gpios | JTAG_PINS(gpioport));
	} else {
        GPIO_ANALOG(gpioport) = (gpios | GPIO_ANALOG(gpioport)) & (~JTAG_PINS(gpioport));
	}

	if (mode == GPIO_MODE_INPUT) {
		GPIO_OE(gpioport) &= ~(gpios | JTAG_PINS(gpioport));
	} else {
        GPIO_OE(gpioport) = (gpios | GPIO_OE(gpioport)) & (~JTAG_PINS(gpioport));
	}

	pupd = GPIO_PULL(gpioport);
	oafr = GPIO_FUNC(gpioport);

	for (i = 0; i < 16; i++) {
		if (!((1 << i) & gpios)) {
			continue;
		}
		pupd &= ~GPIO_PUPD_MASK(i);
		pupd |= GPIO_PUPD(i, pull_up_down);
		/** @note у MCU только один управляющий регистр альтернативных функций,
		 * 		  лучше сбросить, исключив по умолчанию приоритет функции над портом */
		if(mode != GPIO_MODE_AF) {
			oafr &= ~GPIO_AF_NUM_MASK(i);
			oafr |= GPIO_AF_NUM(i, GPIO_FUN_PORT);
		}
	}
	GPIO_PULL(gpioport) = pupd & (~JTAG_PINS(gpioport));
	GPIO_FUNC(gpioport) = oafr & (~JTAG_PINS(gpioport));
}

void gpio_set_output_options(uint32_t gpioport, uint8_t otype, uint8_t speed, uint16_t gpios)
{
    uint16_t i;
	uint32_t ospeedr;

	if (otype == GPIO_OTYPE_OD) {
        GPIO_PD(gpioport) = (gpios | GPIO_PD(gpioport)) & (~JTAG_PINS(gpioport));
	} else {
        GPIO_PD(gpioport) &= ~(gpios | JTAG_PINS(gpioport));
	}

    ospeedr = GPIO_PWR(gpioport);
	for (i = 0; i < 16; i++) {
		if (!((1 << i) & gpios)) {
			continue;
		}
		ospeedr &= ~GPIO_OSPEED_MASK(i);
		ospeedr |= GPIO_OSPEED(i, speed);
	}
	GPIO_PWR(gpioport) = ospeedr & (~JTAG_PINS(gpioport));
}

void gpio_set_af(uint32_t gpioport, GPIO_AFNUM_TypeDef alt_func_num, uint16_t gpios)
{
	uint16_t i;
	uint32_t oafr;

	oafr = GPIO_FUNC(gpioport);
	for (i = 0; i < 16; i++) {
		if (!((1 << i) & gpios)) {
			continue;
		}
		oafr &= ~GPIO_AF_NUM_MASK(i);
		oafr |= GPIO_AF_NUM(i, alt_func_num);
	}
	GPIO_FUNC(gpioport) = oafr & (~JTAG_PINS(gpioport));
}