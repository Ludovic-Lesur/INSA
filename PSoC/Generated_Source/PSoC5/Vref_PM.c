/*******************************************************************************
* File Name: Vref_PM.c  
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

#include "Vref.h"

static Vref_backupStruct Vref_backup;


/*******************************************************************************
* Function Name: Vref_SaveConfig
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
void Vref_SaveConfig(void) 
{
    if (!((Vref_CR1 & Vref_SRC_MASK) == Vref_SRC_UDB))
    {
        Vref_backup.data_value = Vref_Data;
    }
}


/*******************************************************************************
* Function Name: Vref_RestoreConfig
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
void Vref_RestoreConfig(void) 
{
    if (!((Vref_CR1 & Vref_SRC_MASK) == Vref_SRC_UDB))
    {
        if((Vref_Strobe & Vref_STRB_MASK) == Vref_STRB_EN)
        {
            Vref_Strobe &= (uint8)(~Vref_STRB_MASK);
            Vref_Data = Vref_backup.data_value;
            Vref_Strobe |= Vref_STRB_EN;
        }
        else
        {
            Vref_Data = Vref_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: Vref_Sleep
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
*  Vref_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void Vref_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(Vref_ACT_PWR_EN == (Vref_PWRMGR & Vref_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        Vref_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        Vref_backup.enableState = 0u;
    }
    
    Vref_Stop();
    Vref_SaveConfig();
}


/*******************************************************************************
* Function Name: Vref_Wakeup
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
*  Vref_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Vref_Wakeup(void) 
{
    Vref_RestoreConfig();
    
    if(Vref_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        Vref_Enable();

        /* Restore the data register */
        Vref_SetValue(Vref_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
