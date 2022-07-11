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