#include "main.h"

#include "MDR32FxQI_rst_clk.h"

int main(void)
{
    clk_CoreConfig();
    delay_setup();
    while (1)
    {

    }
    return 0;
}


/**
 * @brief Инициализация тактирования микроконтроллера
 * 		  Crystal=16MHz
 * 		  Speed=80MHz
 */
static void clk_CoreConfig(void)
{
	//Реинициализация настроек тактирования
	RST_CLK_DeInit();

	//Включение тактирования от внешнего источника HSE (High Speed External)
	RST_CLK_HSEconfig(RST_CLK_HSE_ON);

	//Проверка статуса HSE
	if (RST_CLK_HSEstatus() == ERROR) while (1);  	
		
	//Настройка делителя/умножителя частоты CPU_PLL(фазовая подстройка частоты
	RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul5);

	//Включение CPU_PLL
	RST_CLK_CPU_PLLcmd(ENABLE);
	
	//Проверка статуса CPU_PLL
	if (RST_CLK_CPU_PLLstatus() == ERROR) while (1);  

	//Коммутация выхода CPU_PLL на вход CPU_C3
	RST_CLK_CPU_PLLuse(ENABLE);

	//Выбор источника тактирования ядра процессора
	RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
}