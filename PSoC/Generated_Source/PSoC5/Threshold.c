/*******************************************************************************
* File Name: Threshold.c  
* Version 1.90
*
* Description:
*  This file provides the source code to the API for the 8-bit Voltage DAC 
*  (VDAC8) User Module.
*
* Note:
*  Any unusual or non-standard behavior should be noted here. Other-
*  wise, this section should remain blank.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Threshold.h"

#if (CY_PSOC5A)
#include <CyLib.h>
#endif /* CY_PSOC5A */

uint8 Threshold_initVar = 0u;

#if (CY_PSOC5A)
    static uint8 Threshold_restoreVal = 0u;
#endif /* CY_PSOC5A */

#if (CY_PSOC5A)
    static Threshold_backupStruct Threshold_backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: Threshold_Init
********************************************************************************
* Summary:
*  Initialize to the schematic state.
* 
* Parameters:
*  void:
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Threshold_Init(void) 
{
    Threshold_CR0 = (Threshold_MODE_V );

    /* Set default data source */
    #if(Threshold_DEFAULT_DATA_SRC != 0 )
        Threshold_CR1 = (Threshold_DEFAULT_CNTL | Threshold_DACBUS_ENABLE) ;
    #else
        Threshold_CR1 = (Threshold_DEFAULT_CNTL | Threshold_DACBUS_DISABLE) ;
    #endif /* (Threshold_DEFAULT_DATA_SRC != 0 ) */

    /* Set default strobe mode */
    #if(Threshold_DEFAULT_STRB != 0)
        Threshold_Strobe |= Threshold_STRB_EN ;
    #endif/* (Threshold_DEFAULT_STRB != 0) */

    /* Set default range */
    Threshold_SetRange(Threshold_DEFAULT_RANGE); 

    /* Set default speed */
    Threshold_SetSpeed(Threshold_DEFAULT_SPEED);
}


/*******************************************************************************
* Function Name: Threshold_Enable
********************************************************************************
* Summary:
*  Enable the VDAC8
* 
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Threshold_Enable(void) 
{
    Threshold_PWRMGR |= Threshold_ACT_PWR_EN;
    Threshold_STBY_PWRMGR |= Threshold_STBY_PWR_EN;

    /*This is to restore the value of register CR0 ,
    which is modified  in Stop API , this prevents misbehaviour of VDAC */
    #if (CY_PSOC5A)
        if(Threshold_restoreVal == 1u) 
        {
             Threshold_CR0 = Threshold_backup.data_value;
             Threshold_restoreVal = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Threshold_Start
********************************************************************************
*
* Summary:
*  The start function initializes the voltage DAC with the default values, 
*  and sets the power to the given level.  A power level of 0, is the same as
*  executing the stop function.
*
* Parameters:
*  Power: Sets power level between off (0) and (3) high power
*
* Return:
*  void 
*
* Global variables:
*  Threshold_initVar: Is modified when this function is called for the 
*  first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Threshold_Start(void)  
{
    /* Hardware initiazation only needs to occure the first time */
    if(Threshold_initVar == 0u)
    { 
        Threshold_Init();
        Threshold_initVar = 1u;
    }

    /* Enable power to DAC */
    Threshold_Enable();

    /* Set default value */
    Threshold_SetValue(Threshold_DEFAULT_DATA); 
}


/*******************************************************************************
* Function Name: Threshold_Stop
********************************************************************************
*
* Summary:
*  Powers down DAC to lowest power state.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Threshold_Stop(void) 
{
    /* Disble power to DAC */
    Threshold_PWRMGR &= (uint8)(~Threshold_ACT_PWR_EN);
    Threshold_STBY_PWRMGR &= (uint8)(~Threshold_STBY_PWR_EN);

    /* This is a work around for PSoC5A  ,
    this sets VDAC to current mode with output off */
    #if (CY_PSOC5A)
        Threshold_backup.data_value = Threshold_CR0;
        Threshold_CR0 = Threshold_CUR_MODE_OUT_OFF;
        Threshold_restoreVal = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Threshold_SetSpeed
********************************************************************************
*
* Summary:
*  Set DAC speed
*
* Parameters:
*  power: Sets speed value
*
* Return:
*  void
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Threshold_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    Threshold_CR0 &= (uint8)(~Threshold_HS_MASK);
    Threshold_CR0 |=  (speed & Threshold_HS_MASK);
}


/*******************************************************************************
* Function Name: Threshold_SetRange
********************************************************************************
*
* Summary:
*  Set one of three current ranges.
*
* Parameters:
*  Range: Sets one of Three valid ranges.
*
* Return:
*  void 
*
* Theory:
*
* Side Effects:
*
*******************************************************************************/
void Threshold_SetRange(uint8 range) 
{
    Threshold_CR0 &= (uint8)(~Threshold_RANGE_MASK);      /* Clear existing mode */
    Threshold_CR0 |= (range & Threshold_RANGE_MASK);      /*  Set Range  */
    Threshold_DacTrim();
}


/*******************************************************************************
* Function Name: Threshold_SetValue
********************************************************************************
*
* Summary:
*  Set 8-bit DAC value
*
* Parameters:  
*  value:  Sets DAC value between 0 and 255.
*
* Return: 
*  void 
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void Threshold_SetValue(uint8 value) 
{
    #if (CY_PSOC5A)
        uint8 Threshold_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    Threshold_Data = value;                /*  Set Value  */

    /* PSOC5A requires a double write */
    /* Exit Critical Section */
    #if (CY_PSOC5A)
        Threshold_Data = value;
        CyExitCriticalSection(Threshold_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Threshold_DacTrim
********************************************************************************
*
* Summary:
*  Set the trim value for the given range.
*
* Parameters:
*  range:  1V or 4V range.  See constants.
*
* Return:
*  void
*
* Theory: 
*
* Side Effects:
*
*******************************************************************************/
void Threshold_DacTrim(void) 
{
    uint8 mode;

    mode = (uint8)((Threshold_CR0 & Threshold_RANGE_MASK) >> 2) + Threshold_TRIM_M7_1V_RNG_OFFSET;
    Threshold_TR = CY_GET_XTND_REG8((uint8 *)(Threshold_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
