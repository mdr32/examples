/**
  ******************************************************************************
  * @file    MDR32FxQI_dac.c
  * @author  Milandr Application Team
  * @version V2.0.2i
  * @date    17/03/2022
  * @brief   This file contains all the DAC firmware functions.
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2022 Milandr</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32FxQI_dac.h"

/** @addtogroup __MDR32FxQI_StdPeriph_Driver MDR32FxQI Standard Peripherial Driver
  * @{
  */

/** @defgroup DAC DAC
  * @{
  */

/** @defgroup DAC_Private_Functions DAC Private Functions
  * @{
  */

/**
  * @brief  Deinitializes the DAC peripheral registers to their default reset values.
  * @param  None.
  * @retval None.
  */
void DAC_DeInit(void)
{
    MDR_DAC->DAC1_DATA = 0;
    MDR_DAC->DAC2_DATA = 0;
    MDR_DAC->CFG       = 0;
}

/**
  * @brief  Initializes the DAC peripheral.
  * @param  SyncMode - @ref DAC_Sync_Mode - specifies the DAC1, DAC2
  *         operation mode - synchronous or independent.
  * @param  DAC1_Ref - @ref DAC1_Ref_Src - selects the DAC1 Reference Voltage source.
  * @param  DAC2_Ref - @ref DAC2_Ref_Src - selects the DAC2 Reference Voltage source.
  * @retval None
  */
void DAC_Init(DAC_Sync_Mode SyncMode, DAC1_Ref_Src DAC1_Ref, DAC2_Ref_Src DAC2_Ref)
{
    uint32_t tmpreg_CFG;

    /* Check the parameters */
    assert_param(IS_DAC_SYNC_MODE(SyncMode));
    assert_param(IS_DAC1_REF_CONFIG(DAC1_Ref));
    assert_param(IS_DAC2_REF_CONFIG(DAC2_Ref));

    tmpreg_CFG = MDR_DAC->CFG;
    tmpreg_CFG &= ~(DAC_CFG_SYNC_A | DAC_CFG_M_REF0 | DAC_CFG_M_REF1);
    tmpreg_CFG += (uint32_t)SyncMode + (uint32_t)DAC1_Ref + (uint32_t)DAC2_Ref;

    MDR_DAC->CFG = tmpreg_CFG;
}

/**
  * @brief  Initializes the DAC1 peripheral.
  * @param  DAC1_Ref - @ref DAC1_Ref_Src - selects the DAC1 Reference Voltage source.
  * @retval None
  */
void DAC1_Init(DAC1_Ref_Src DAC1_Ref)
{
    uint32_t tmpreg_CFG;

    /* Check the parameters */
    assert_param(IS_DAC1_REF_CONFIG(DAC1_Ref));

    tmpreg_CFG = MDR_DAC->CFG;
    tmpreg_CFG &= ~DAC_CFG_M_REF0;
    tmpreg_CFG += (uint32_t)DAC1_Ref;

    MDR_DAC->CFG = tmpreg_CFG;
}

/**
  * @brief  Initializes the DAC2 peripheral.
  * @param  DAC2_Ref - @ref DAC2_Ref_Src - selects the DAC2 Reference Voltage source.
  * @retval None
  */
void DAC2_Init(DAC2_Ref_Src DAC2_Ref)
{
    uint32_t tmpreg_CFG;

    /* Check the parameters */
    assert_param(IS_DAC2_REF_CONFIG(DAC2_Ref));

    tmpreg_CFG = MDR_DAC->CFG;
    tmpreg_CFG &= ~DAC_CFG_M_REF1;
    tmpreg_CFG += (uint32_t)DAC2_Ref;

    MDR_DAC->CFG = tmpreg_CFG;
}

/**
  * @brief  Enables or disables the DAC1 peripheral.
  * @param  NewState - @ref FunctionalState - new state of the DAC1 peripheral.
  * @retval None
  */
void DAC1_Cmd(FunctionalState NewState)
{
    uint32_t tmpreg_CFG;

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    tmpreg_CFG = MDR_DAC->CFG;

    /* Form new value */
    if (NewState != DISABLE)
    {
        /* Enable DAC1 by setting the Cfg_ON_DAC0 bit in the DAC_CFG register */
        tmpreg_CFG |= DAC_CFG_ON_DAC0;
    }
    else
    {
        /* Disable DAC1 by resetting the Cfg_ON_DAC0 bit in the DAC_CFG register */
        tmpreg_CFG &= ~DAC_CFG_ON_DAC0;
    }

    /* Configure DAC_CFG register with new value */
    MDR_DAC->CFG = tmpreg_CFG;
}

/**
  * @brief  Enables or disables the DAC2 peripheral.
  * @param  NewState - @ref FunctionalState - new state of the DAC2 peripheral.
  * @retval None
  */
void DAC2_Cmd(FunctionalState NewState)
{
    uint32_t tmpreg_CFG;

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    tmpreg_CFG = MDR_DAC->CFG;

    /* Form new value */
    if (NewState != DISABLE)
    {
        /* Enable DAC2 by setting the Cfg_ON_DAC1 bit in the DAC_CFG register */
        tmpreg_CFG |= DAC_CFG_ON_DAC1;
    }
    else
    {
        /* Disable DAC2 by resetting the Cfg_ON_DAC1 bit in the DAC_CFG register */
        tmpreg_CFG &= ~DAC_CFG_ON_DAC1;
    }

    /* Configure DAC_CFG register with new value */
    MDR_DAC->CFG = tmpreg_CFG;
}

/**
  * @brief  Sets the DAC1 (and DAC2 in Synchronous mode) output data.
  * @param  Data: specifies the DAC output data.
  * @retval None
  */
void DAC1_SetData(uint32_t Data)
{
    /* Check the parameters */
    assert_param(IS_DAC_DATA(Data));

    MDR_DAC->DAC1_DATA = Data;
}

/**
  * @brief  Sets the DAC2 (and DAC1 in Synchronous mode) output data.
  * @param  Data: specifies the DAC output data.
  * @retval None
  */
void DAC2_SetData(uint32_t Data)
{
    /* Check the parameters */
    assert_param(IS_DAC_DATA(Data));

    MDR_DAC->DAC2_DATA = Data;
}

/**
  * @brief  Returns the DAC1 output data.
  * @param  None.
  * @retval Counter Register value.
  */
uint32_t DAC1_GetData(void)
{
    return MDR_DAC->DAC1_DATA;
}

/**
  * @brief  Returns the DAC2 output data.
  * @param  None.
  * @retval Counter Register value.
  */
uint32_t DAC2_GetData(void)
{
    return MDR_DAC->DAC2_DATA;
}

/** @} */ /* End of group DAC_Private_Functions */

/** @} */ /* End of group DAC */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Driver */

/*********************** (C) COPYRIGHT 2022 Milandr ****************************
*
* END OF FILE MDR32FxQI_dac.c */


