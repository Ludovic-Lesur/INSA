/*******************************************************************************
* File Name: Threrhold.c  
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
#include "Threrhold.h"

#if (CY_PSOC5A)
#include <CyLib.h>
#endif /* CY_PSOC5A */

uint8 Threrhold_initVar = 0u;

#if (CY_PSOC5A)
    static uint8 Threrhold_restoreVal = 0u;
#endif /* CY_PSOC5A */

#if (CY_PSOC5A)
    static Threrhold_backupStruct Threrhold_backup;
#endif /* CY_PSOC5A */


/*******************************************************************************
* Function Name: Threrhold_Init
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
void Threrhold_Init(void) 
{
    Threrhold_CR0 = (Threrhold_MODE_V );

    /* Set default data source */
    #if(Threrhold_DEFAULT_DATA_SRC != 0 )
        Threrhold_CR1 = (Threrhold_DEFAULT_CNTL | Threrhold_DACBUS_ENABLE) ;
    #else
        Threrhold_CR1 = (Threrhold_DEFAULT_CNTL | Threrhold_DACBUS_DISABLE) ;
    #endif /* (Threrhold_DEFAULT_DATA_SRC != 0 ) */

    /* Set default strobe mode */
    #if(Threrhold_DEFAULT_STRB != 0)
        Threrhold_Strobe |= Threrhold_STRB_EN ;
    #endif/* (Threrhold_DEFAULT_STRB != 0) */

    /* Set default range */
    Threrhold_SetRange(Threrhold_DEFAULT_RANGE); 

    /* Set default speed */
    Threrhold_SetSpeed(Threrhold_DEFAULT_SPEED);
}


/*******************************************************************************
* Function Name: Threrhold_Enable
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
void Threrhold_Enable(void) 
{
    Threrhold_PWRMGR |= Threrhold_ACT_PWR_EN;
    Threrhold_STBY_PWRMGR |= Threrhold_STBY_PWR_EN;

    /*This is to restore the value of register CR0 ,
    which is modified  in Stop API , this prevents misbehaviour of VDAC */
    #if (CY_PSOC5A)
        if(Threrhold_restoreVal == 1u) 
        {
             Threrhold_CR0 = Threrhold_backup.data_value;
             Threrhold_restoreVal = 0u;
        }
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Threrhold_Start
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
*  Threrhold_initVar: Is modified when this function is called for the 
*  first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Threrhold_Start(void)  
{
    /* Hardware initiazation only needs to occure the first time */
    if(Threrhold_initVar == 0u)
    { 
        Threrhold_Init();
        Threrhold_initVar = 1u;
    }

    /* Enable power to DAC */
    Threrhold_Enable();

    /* Set default value */
    Threrhold_SetValue(Threrhold_DEFAULT_DATA); 
}


/*******************************************************************************
* Function Name: Threrhold_Stop
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
void Threrhold_Stop(void) 
{
    /* Disble power to DAC */
    Threrhold_PWRMGR &= (uint8)(~Threrhold_ACT_PWR_EN);
    Threrhold_STBY_PWRMGR &= (uint8)(~Threrhold_STBY_PWR_EN);

    /* This is a work around for PSoC5A  ,
    this sets VDAC to current mode with output off */
    #if (CY_PSOC5A)
        Threrhold_backup.data_value = Threrhold_CR0;
        Threrhold_CR0 = Threrhold_CUR_MODE_OUT_OFF;
        Threrhold_restoreVal = 1u;
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Threrhold_SetSpeed
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
void Threrhold_SetSpeed(uint8 speed) 
{
    /* Clear power mask then write in new value */
    Threrhold_CR0 &= (uint8)(~Threrhold_HS_MASK);
    Threrhold_CR0 |=  (speed & Threrhold_HS_MASK);
}


/*******************************************************************************
* Function Name: Threrhold_SetRange
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
void Threrhold_SetRange(uint8 range) 
{
    Threrhold_CR0 &= (uint8)(~Threrhold_RANGE_MASK);      /* Clear existing mode */
    Threrhold_CR0 |= (range & Threrhold_RANGE_MASK);      /*  Set Range  */
    Threrhold_DacTrim();
}


/*******************************************************************************
* Function Name: Threrhold_SetValue
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
void Threrhold_SetValue(uint8 value) 
{
    #if (CY_PSOC5A)
        uint8 Threrhold_intrStatus = CyEnterCriticalSection();
    #endif /* CY_PSOC5A */

    Threrhold_Data = value;                /*  Set Value  */

    /* PSOC5A requires a double write */
    /* Exit Critical Section */
    #if (CY_PSOC5A)
        Threrhold_Data = value;
        CyExitCriticalSection(Threrhold_intrStatus);
    #endif /* CY_PSOC5A */
}


/*******************************************************************************
* Function Name: Threrhold_DacTrim
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
void Threrhold_DacTrim(void) 
{
    uint8 mode;

    mode = (uint8)((Threrhold_CR0 & Threrhold_RANGE_MASK) >> 2) + Threrhold_TRIM_M7_1V_RNG_OFFSET;
    Threrhold_TR = CY_GET_XTND_REG8((uint8 *)(Threrhold_DAC_TRIM_BASE + mode));
}


/* [] END OF FILE */
