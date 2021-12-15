/*******************************************************************************
* File Name: Threshold_PM.c  
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

#include "Threshold.h"

static Threshold_backupStruct Threshold_backup;


/*******************************************************************************
* Function Name: Threshold_SaveConfig
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
void Threshold_SaveConfig(void) 
{
    if (!((Threshold_CR1 & Threshold_SRC_MASK) == Threshold_SRC_UDB))
    {
        Threshold_backup.data_value = Threshold_Data;
    }
}


/*******************************************************************************
* Function Name: Threshold_RestoreConfig
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
void Threshold_RestoreConfig(void) 
{
    if (!((Threshold_CR1 & Threshold_SRC_MASK) == Threshold_SRC_UDB))
    {
        if((Threshold_Strobe & Threshold_STRB_MASK) == Threshold_STRB_EN)
        {
            Threshold_Strobe &= (uint8)(~Threshold_STRB_MASK);
            Threshold_Data = Threshold_backup.data_value;
            Threshold_Strobe |= Threshold_STRB_EN;
        }
        else
        {
            Threshold_Data = Threshold_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: Threshold_Sleep
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
*  Threshold_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void Threshold_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(Threshold_ACT_PWR_EN == (Threshold_PWRMGR & Threshold_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        Threshold_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        Threshold_backup.enableState = 0u;
    }
    
    Threshold_Stop();
    Threshold_SaveConfig();
}


/*******************************************************************************
* Function Name: Threshold_Wakeup
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
*  Threshold_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Threshold_Wakeup(void) 
{
    Threshold_RestoreConfig();
    
    if(Threshold_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        Threshold_Enable();

        /* Restore the data register */
        Threshold_SetValue(Threshold_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
