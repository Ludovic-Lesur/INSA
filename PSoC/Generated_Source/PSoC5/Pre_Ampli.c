/*******************************************************************************
* File Name: Pre_Ampli.c  
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the PGA 
*  User Module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Pre_Ampli.h"

#if (!CY_PSOC5A)
    #if (CYDEV_VARIABLE_VDDA == 1u)
        #include "CyScBoostClk.h"
    #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
#endif /* (!CY_PSOC5A) */

#if (CY_PSOC5A)
    static Pre_Ampli_BACKUP_STRUCT  Pre_Ampli_P5backup;
#endif /* (CY_ PSOC5A) */

uint8 Pre_Ampli_initVar = 0u;


/*******************************************************************************   
* Function Name: Pre_Ampli_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  Pre_Ampli_Start().
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Pre_Ampli_Init(void) 
{
    /* Set PGA mode */
    Pre_Ampli_CR0_REG = Pre_Ampli_MODE_PGA;      
    /* Set non-inverting PGA mode and reference mode */
    Pre_Ampli_CR1_REG |= Pre_Ampli_PGA_NINV;  
    /* Set default gain and ref mode */
    Pre_Ampli_CR2_REG = Pre_Ampli_VREF_MODE;
    /* Set gain and compensation */
    Pre_Ampli_SetGain(Pre_Ampli_DEFAULT_GAIN);
    /* Set power */
    Pre_Ampli_SetPower(Pre_Ampli_DEFAULT_POWER);
}


/*******************************************************************************   
* Function Name: Pre_Ampli_Enable
********************************************************************************
*
* Summary:
*  Enables the PGA block operation.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Pre_Ampli_Enable(void) 
{
    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modifications in stop() API */
    #if (CY_PSOC5A)
        if(Pre_Ampli_P5backup.enableState == 1u)
        {
            Pre_Ampli_CR1_REG = Pre_Ampli_P5backup.scCR1Reg;
            Pre_Ampli_CR2_REG = Pre_Ampli_P5backup.scCR2Reg;
            Pre_Ampli_P5backup.enableState = 0u;
        }
    #endif /* CY_PSOC5A */   

    /* Enable power to the Amp in Active mode*/
    Pre_Ampli_PM_ACT_CFG_REG |= Pre_Ampli_ACT_PWR_EN;

    /* Enable power to the Amp in Alternative Active mode*/
    Pre_Ampli_PM_STBY_CFG_REG |= Pre_Ampli_STBY_PWR_EN;
    
    Pre_Ampli_PUMP_CR1_REG |= Pre_Ampli_PUMP_CR1_SC_CLKSEL;
    
    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            if(CyScPumpEnabled == 1u)
            {
                Pre_Ampli_BSTCLK_REG &= (uint8)(~Pre_Ampli_BST_CLK_INDEX_MASK);
                Pre_Ampli_BSTCLK_REG |= Pre_Ampli_BST_CLK_EN | CyScBoostClk__INDEX;
                Pre_Ampli_SC_MISC_REG |= Pre_Ampli_PUMP_FORCE;
                CyScBoostClk_Start();
            }
            else
            {
                Pre_Ampli_BSTCLK_REG &= (uint8)(~Pre_Ampli_BST_CLK_EN);
                Pre_Ampli_SC_MISC_REG &= (uint8)(~Pre_Ampli_PUMP_FORCE);
            }
        #endif /* (CYDEV_VARIABLE_VDDA == 1u) */
    #endif /* (!CY_PSOC5A) */
}


/*******************************************************************************
* Function Name: Pre_Ampli_Start
********************************************************************************
*
* Summary:
*  The start function initializes the PGA with the default values and sets
*  the power to the given level. A power level of 0, is same as executing
*  the stop function.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Pre_Ampli_Start(void) 
{

    /* This is to restore the value of register CR1 and CR2 which is saved 
      in prior to the modification in stop() API */

    if(Pre_Ampli_initVar == 0u)
    {
        Pre_Ampli_Init();
        Pre_Ampli_initVar = 1u;
    }

    Pre_Ampli_Enable();
}


/*******************************************************************************
* Function Name: Pre_Ampli_Stop
********************************************************************************
*
* Summary:
*  Powers down amplifier to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Pre_Ampli_Stop(void) 
{ 
    /* Disble power to the Amp in Active mode template */
    Pre_Ampli_PM_ACT_CFG_REG &= (uint8)(~Pre_Ampli_ACT_PWR_EN);

    /* Disble power to the Amp in Alternative Active mode template */
    Pre_Ampli_PM_STBY_CFG_REG &= (uint8)(~Pre_Ampli_STBY_PWR_EN);

    #if (!CY_PSOC5A)
        #if (CYDEV_VARIABLE_VDDA == 1u)
            Pre_Ampli_BSTCLK_REG &= (uint8)(~Pre_Ampli_BST_CLK_EN);
            /* Disable pumps only if there aren't any SC block in use */
            if ((Pre_Ampli_PM_ACT_CFG_REG & Pre_Ampli_PM_ACT_CFG_MASK) == 0u)
            {
                Pre_Ampli_SC_MISC_REG &= (uint8)(~Pre_Ampli_PUMP_FORCE);
                Pre_Ampli_PUMP_CR1_REG &= (uint8)(~Pre_Ampli_PUMP_CR1_SC_CLKSEL);
                CyScBoostClk_Stop();
            }
        #endif /* CYDEV_VARIABLE_VDDA == 1u */
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /* This sets PGA in zero current mode and output routes are valid */
    #if (CY_PSOC5A)
        Pre_Ampli_P5backup.scCR1Reg = Pre_Ampli_CR1_REG;
        Pre_Ampli_P5backup.scCR2Reg = Pre_Ampli_CR2_REG;
        Pre_Ampli_CR1_REG = 0x00u;
        Pre_Ampli_CR2_REG = 0x00u;
        Pre_Ampli_P5backup.enableState = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Pre_Ampli_SetPower
********************************************************************************
*
* Summary:
*  Set the power of the PGA.
*
* Parameters:
*  power: Sets power level between (0) and (3) high power
*
* Return:
*  void
*
*******************************************************************************/
void Pre_Ampli_SetPower(uint8 power) 
{
    uint8 tmpCR;

    tmpCR = Pre_Ampli_CR1_REG & (uint8)(~Pre_Ampli_DRIVE_MASK);
    tmpCR |= (power & Pre_Ampli_DRIVE_MASK);
    Pre_Ampli_CR1_REG = tmpCR;  
}


/*******************************************************************************
* Function Name: Pre_Ampli_SetGain
********************************************************************************
*
* Summary:
*  This function sets values of the input and feedback resistors to set a 
*  specific gain of the amplifier.
*
* Parameters:
*  gain: Gain value of PGA (See header file for gain values.)
*
* Return:
*  void 
*
*******************************************************************************/
void Pre_Ampli_SetGain(uint8 gain) 
{
    /* Constant array for gain settings */
    const uint8 Pre_Ampli_GainArray[9] = { 
        (Pre_Ampli_RVAL_0K   | Pre_Ampli_R20_40B_40K | Pre_Ampli_BIAS_LOW), /* G=1  */
        (Pre_Ampli_RVAL_40K  | Pre_Ampli_R20_40B_40K | Pre_Ampli_BIAS_LOW), /* G=2  */
        (Pre_Ampli_RVAL_120K | Pre_Ampli_R20_40B_40K | Pre_Ampli_BIAS_LOW), /* G=4  */
        (Pre_Ampli_RVAL_280K | Pre_Ampli_R20_40B_40K | Pre_Ampli_BIAS_LOW), /* G=8  */
        (Pre_Ampli_RVAL_600K | Pre_Ampli_R20_40B_40K | Pre_Ampli_BIAS_LOW), /* G=16 */
        (Pre_Ampli_RVAL_460K | Pre_Ampli_R20_40B_40K | Pre_Ampli_BIAS_LOW), /* G=24, Sets Rin as 20k */
        (Pre_Ampli_RVAL_620K | Pre_Ampli_R20_40B_20K | Pre_Ampli_BIAS_LOW), /* G=32 */
        (Pre_Ampli_RVAL_470K | Pre_Ampli_R20_40B_20K | Pre_Ampli_BIAS_LOW), /* G=48, Sets Rin as 10k */
        (Pre_Ampli_RVAL_490K | Pre_Ampli_R20_40B_20K | Pre_Ampli_BIAS_LOW)  /* G=50, Sets Rin as 10k */
    };
    
    /* Constant array for gain compenstion settings */
    const uint8 Pre_Ampli_GainComp[9] = { 
        ( Pre_Ampli_COMP_4P35PF  | (uint8)( Pre_Ampli_REDC_00 >> 2 )), /* G=1  */
        ( Pre_Ampli_COMP_4P35PF  | (uint8)( Pre_Ampli_REDC_01 >> 2 )), /* G=2  */
        ( Pre_Ampli_COMP_3P0PF   | (uint8)( Pre_Ampli_REDC_01 >> 2 )), /* G=4  */
        ( Pre_Ampli_COMP_3P0PF   | (uint8)( Pre_Ampli_REDC_01 >> 2 )), /* G=8  */
        ( Pre_Ampli_COMP_3P6PF   | (uint8)( Pre_Ampli_REDC_01 >> 2 )), /* G=16 */
        ( Pre_Ampli_COMP_3P6PF   | (uint8)( Pre_Ampli_REDC_11 >> 2 )), /* G=24 */
        ( Pre_Ampli_COMP_3P6PF   | (uint8)( Pre_Ampli_REDC_11 >> 2 )), /* G=32 */
        ( Pre_Ampli_COMP_3P6PF   | (uint8)( Pre_Ampli_REDC_00 >> 2 )), /* G=48 */
        ( Pre_Ampli_COMP_3P6PF   | (uint8)( Pre_Ampli_REDC_00 >> 2 ))  /* G=50 */
    };
    
    /* Only set new gain if it is a valid gain */
    if( gain <= Pre_Ampli_GAIN_MAX)
    {
        /* Clear resistors, redc, and bias */
        Pre_Ampli_CR2_REG &= (uint8)(~(Pre_Ampli_RVAL_MASK | Pre_Ampli_R20_40B_MASK | 
                                Pre_Ampli_REDC_MASK | Pre_Ampli_BIAS_MASK ));

        /* Set gain value resistors, redc comp, and bias */
        Pre_Ampli_CR2_REG |= (Pre_Ampli_GainArray[gain] |
                                ((uint8)(Pre_Ampli_GainComp[gain] << 2 ) & Pre_Ampli_REDC_MASK));

        /* Clear sc_comp  */
        Pre_Ampli_CR1_REG &= (uint8)(~Pre_Ampli_COMP_MASK);
        /* Set sc_comp  */
        Pre_Ampli_CR1_REG |= ( Pre_Ampli_GainComp[gain] | Pre_Ampli_COMP_MASK );
    }
}


/* [] END OF FILE */
