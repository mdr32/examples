#ifndef _LCM3_GPIOS_H
#define _LCM3_GPIOS_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "locm3_bridge.h"

/** @brief Описание портов */
#define GPIOA				MDR_PORTA_BASE
#define GPIOB				MDR_PORTB_BASE
#define GPIOC				MDR_PORTC_BASE
#define GPIOD				MDR_PORTD_BASE
#define GPIOE				MDR_PORTE_BASE
#define GPIOF				MDR_PORTF_BASE

/** @brief GPIO_RXTX: Регистр чтения/записи данных порта */
#define GPIO_RXTX(MDR_PORT) MMIO32((MDR_PORT) + 0x00)
#define GPIOA_RXTX			GPIO_RXTX(GPIOA)
#define GPIOB_RXTX			GPIO_RXTX(GPIOB)
#define GPIOC_RXTX			GPIO_RXTX(GPIOC)
#define GPIOD_RXTX			GPIO_RXTX(GPIOD)
#define GPIOE_RXTX			GPIO_RXTX(GPIOE)
#define GPIOF_RXTX			GPIO_RXTX(GPIOF)

/** @brief GPIO_OE: Регистр направления порта */
#define GPIO_OE(MDR_PORT)   MMIO32((MDR_PORT) + 0x04)
#define GPIOA_OE			GPIO_OE(GPIOA)
#define GPIOB_OE			GPIO_OE(GPIOB)
#define GPIOC_OE			GPIO_OE(GPIOC)
#define GPIOD_OE			GPIO_OE(GPIOD)
#define GPIOE_OE			GPIO_OE(GPIOE)
#define GPIOF_OE			GPIO_OE(GPIOF)

/** @brief GPIO_FUNC: Регистр режима работы порта */
#define GPIO_FUNC(MDR_PORT) MMIO32((MDR_PORT) + 0x08)
#define GPIOA_FUNC			GPIO_FUNC(GPIOA)
#define GPIOB_FUNC			GPIO_FUNC(GPIOB)
#define GPIOC_FUNC			GPIO_FUNC(GPIOC)
#define GPIOD_FUNC			GPIO_FUNC(GPIOD)
#define GPIOE_FUNC			GPIO_FUNC(GPIOE)
#define GPIOF_FUNC			GPIO_FUNC(GPIOF)

/** @brief GPIO_ANALOG: Регистр аналогового режима работы порта */
#define GPIO_ANALOG(MDR_PORT) MMIO32((MDR_PORT) + 0x0C)
#define GPIOA_ANALOG        GPIO_ANALOG(GPIOA)
#define GPIOB_ANALOG        GPIO_ANALOG(GPIOB)
#define GPIOC_ANALOG        GPIO_ANALOG(GPIOC)
#define GPIOD_ANALOG        GPIO_ANALOG(GPIOD)
#define GPIOE_ANALOG        GPIO_ANALOG(GPIOE)
#define GPIOF_ANALOG        GPIO_ANALOG(GPIOF)

/** @brief GPIO_PULL: Регистр подтяжки порта */
#define GPIO_PULL(MDR_PORT) MMIO32((MDR_PORT) + 0x10)
#define GPIOA_PULL			GPIO_PULL(GPIOA)
#define GPIOB_PULL			GPIO_PULL(GPIOB)
#define GPIOC_PULL			GPIO_PULL(GPIOC)
#define GPIOD_PULL			GPIO_PULL(GPIOD)
#define GPIOE_PULL			GPIO_PULL(GPIOE)
#define GPIOF_PULL			GPIO_PULL(GPIOF)

/** @brief GPIO_PD: Регистр режима работы выходного драйвера */
#define GPIO_PD(MDR_PORT)   MMIO32((MDR_PORT) + 0x14)
#define GPIOA_PD			GPIO_PD(GPIOA)
#define GPIOB_PD			GPIO_PD(GPIOB)
#define GPIOC_PD			GPIO_PD(GPIOC)
#define GPIOD_PD			GPIO_PD(GPIOD)
#define GPIOE_PD			GPIO_PD(GPIOE)
#define GPIOF_PD			GPIO_PD(GPIOF)

/** @brief GPIO_PWR: Регистр режима мощности (корости) передатчика */
#define GPIO_PWR(MDR_PORT) MMIO32((MDR_PORT) + 0x18)
#define GPIOA_PWR			GPIO_PWR(GPIOA)
#define GPIOB_PWR			GPIO_PWR(GPIOB)
#define GPIOC_PWR			GPIO_PWR(GPIOC)
#define GPIOD_PWR			GPIO_PWR(GPIOD)
#define GPIOE_PWR			GPIO_PWR(GPIOE)
#define GPIOF_PWR			GPIO_PWR(GPIOF)

/** @brief GPIO_GFEN: Регистр режима работы входного фильтра */
#define GPIO_GFEN(MDR_PORT) MMIO32((MDR_PORT) + 0x1C)
#define GPIOA_GFEN			GPIO_GFEN(GPIOA)
#define GPIOB_GFEN			GPIO_GFEN(GPIOB)
#define GPIOC_GFEN			GPIO_GFEN(GPIOC)
#define GPIOD_GFEN			GPIO_GFEN(GPIOD)
#define GPIOE_GFEN			GPIO_GFEN(GPIOE)
#define GPIOF_GFEN			GPIO_GFEN(GPIOF)

/** @brief Описание пинов */
#define GPIO0				(1 << 0)
#define GPIO1				(1 << 1)
#define GPIO2				(1 << 2)
#define GPIO3				(1 << 3)
#define GPIO4				(1 << 4)
#define GPIO5				(1 << 5)
#define GPIO6				(1 << 6)
#define GPIO7				(1 << 7)
#define GPIO8				(1 << 8)
#define GPIO9				(1 << 9)
#define GPIO10				(1 << 10)
#define GPIO11				(1 << 11)
#define GPIO12				(1 << 12)
#define GPIO13				(1 << 13)
#define GPIO14				(1 << 14)
#define GPIO15				(1 << 15)
#define GPIO_ALL			0xffff

/**
 * @brief GPIO_MODE: абстрактный тип настройки, не имеющая собственного регистра.
 *        Позволяет настраивать порт в зависимости от бизнес-цели.
 */
#define GPIO_MODE(n, mode)		((mode) << (2 * (n))) // Это не нужно, так как есть FUNC, сам список можно вынести в тип
#define GPIO_MODE_MASK(n)		(0x3 << (2 * (n)))

typedef enum
{
    GPIO_MODE_INPUT		= 0x0,
    GPIO_MODE_OUTPUT	= 0x1,
    GPIO_MODE_AF		= 0x2,
    GPIO_MODE_ANALOG    = 0x3
} GPIO_MODE_TypeDef;


#define GPIO_AF_NUM(n, af)      ((af) << (2 * (n))) // Это не нужно, так как есть FUNC, сам список можно вынести в тип
#define GPIO_AF_NUM_MASK(n)		(0x3 << (2 * (n)))

typedef enum
{
    GPIO_FUN_PORT       = 0x0,
    GPIO_FUN_MAIN       = 0x1,
    GPIO_FUN_ALT        = 0x2,
    GPIO_FUN_OVERRID    = 0x3,
    /** @note Cинонимы по аналогии, приведены для наглядности.
     *       Использование - не желательно! */
    GPIO_AF0            = 0x0,
    GPIO_AF1            = 0x1,
    GPIO_AF2            = 0x2,
    GPIO_AF3            = 0x3
} GPIO_AFNUM_TypeDef;

// #define GPIOA_OFUNC()
/**@}*/

/* --- GPIOx_PD values ------------------------------------------------- */
#define GPIO_OTYPE_PP			0x0 /** Push Pull */
#define GPIO_OTYPE_OD			0x1 /** Open Drain */

/* --- GPIOx_PWR values ------------------------------------------------ */
#define GPIO_OSPEED(n, speed)   ((speed) << (2 * (n)))
#define GPIO_OSPEED_MASK(n)     (0x3 << (2 * (n)))

#define GPIO_OSPEED_OFF      0x0
#define GPIO_OSPEED_SLOW     0x1
#define GPIO_OSPEED_FAST     0x2
#define GPIO_OSPEED_MAXFAST  0x3

/**@}*/

/* --- GPIOx_PULL values -------------------------------------------------- */
/** Одновременная установка в младшем и старшем разраяде */
#define GPIO_PUPD(n, pupd)      (((1 & (pupd >> 1)) << (n + 16)) | ((1 & pupd) <<  n));
#define GPIO_PUPD_MASK(n)       (0x00010001 << (n));

#define GPIO_PUPD_NONE			0x0
#define GPIO_PUPD_PULLDOWN		0x1
#define GPIO_PUPD_PULLUP		0x2


#if defined (USE_JTAG_A)
    #define PORT_JTAG                   GPIOB   // Порт, содержащий интерфейс JTAG
    #define PORT_JTAG_Msk               0x001FU // JTAG pins
#elif defined (USE_JTAG_B)
    #define PORT_JTAG                   GPIOD   // Порт, содержащий интерфейс JTAG
    #define PORT_JTAG_Msk               0x001FU // JTAG pins
#endif

#if defined (PORT_JTAG)
    #define JTAG_PINS(MDR_PORT)         (((MDR_PORT) == PORT_JTAG) ? PORT_JTAG_Msk : 0)
#else
    #define JTAG_PINS(MDR_PORT)         0
#endif


void gpio_set(uint32_t gpioport, uint16_t gpios);
void gpio_clear(uint32_t gpioport, uint16_t gpios);
uint16_t gpio_get(uint32_t gpioport, uint16_t gpios);
void gpio_toggle(uint32_t gpioport, uint16_t gpios);
uint16_t gpio_port_read(uint32_t gpioport);
void gpio_port_write(uint32_t gpioport, uint16_t data);


void gpio_mode_setup(uint32_t gpioport, GPIO_MODE_TypeDef mode, uint8_t pull_up_down, uint16_t gpios);
void gpio_set_output_options(uint32_t gpioport, uint8_t otype, uint8_t speed, uint16_t gpios);
void gpio_set_af(uint32_t gpioport, GPIO_AFNUM_TypeDef alt_func_num, uint16_t gpios);

#ifdef __cplusplus
}
#endif
#endif