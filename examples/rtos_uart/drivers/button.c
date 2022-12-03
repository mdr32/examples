#include "MDR32FxQI_rst_clk.h"
#include "MDR32FxQI_port.h"

#include "FreeRTOS.h"
#include "button.h"

void vButtonInit (void)
{
    PORT_InitTypeDef PORT_InitStructure;

    RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA, ENABLE);
    PORT_StructInit(&PORT_InitStructure);
    PORT_InitStructure.PORT_Pin   = PORT_Pin_0;
    PORT_InitStructure.PORT_OE    = PORT_OE_IN;
    PORT_InitStructure.PORT_PULL_UP = PORT_PULL_UP_OFF;
    PORT_InitStructure.PORT_PULL_DOWN = PORT_PULL_DOWN_ON;
    PORT_InitStructure.PORT_PD_SHM = PORT_PD_SHM_OFF;
    PORT_InitStructure.PORT_GFEN = PORT_GFEN_OFF;
    PORT_InitStructure.PORT_FUNC = PORT_FUNC_ALTER;
    PORT_InitStructure.PORT_SPEED = PORT_OUTPUT_OFF;
    PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
    PORT_Init(MDR_PORTA, &PORT_InitStructure);
}

BaseType_t xButtonReadPortSwitch (void)
{
    return PORT_ReadInputDataBit(MDR_PORTA, PORT_Pin_0);
}