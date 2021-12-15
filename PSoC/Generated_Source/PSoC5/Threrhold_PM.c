/*******************************************************************************
* File Name: Threrhold_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Threrhold.h"

static Threrhold_backupStruct Threrhold_backup;


/*******************************************************************************
* Function Name: Threrhold_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void Threrhold_SaveConfig(void) 
{
    if (!((Threrhold_CR1 & Threrhold_SRC_MASK) == Threrhold_SRC_UDB))
    {
        Threrhold_backup.data_value = Threrhold_Data;
    }
}


/*******************************************************************************
* Function Name: Threrhold_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void Threrhold_RestoreConfig(void) 
{
    if (!((Threrhold_CR1 & Threrhold_SRC_MASK) == Threrhold_SRC_UDB))
    {
        if((Threrhold_Strobe & Threrhold_STRB_MASK) == Threrhold_STRB_EN)
        {
            Threrhold_Strobe &= (uint8)(~Threrhold_STRB_MASK);
            Threrhold_Data = Threrhold_backup.data_value;
            Threrhold_Strobe |= Threrhold_STRB_EN;
        }
        else
        {
            Threrhold_Data = Threrhold_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: Threrhold_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  Threrhold_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void Threrhold_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(Threrhold_ACT_PWR_EN == (Threrhold_PWRMGR & Threrhold_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        Threrhold_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        Threrhold_backup.enableState = 0u;
    }
    
    Threrhold_Stop();
    Threrhold_SaveConfig();
}


/*******************************************************************************
* Function Name: Threrhold_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Threrhold_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Threrhold_Wakeup(void) 
{
    Threrhold_RestoreConfig();
    
    if(Threrhold_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        Threrhold_Enable();

        /* Restore the data register */
        Threrhold_SetValue(Threrhold_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
