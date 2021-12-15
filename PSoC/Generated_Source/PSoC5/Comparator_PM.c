/*******************************************************************************
* File Name: Comparator.c
* Version 2.0
*
* Description:
*  This file provides the power management source code APIs for the
*  Comparator.
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

#include "Comparator.h"

static Comparator_backupStruct Comparator_backup;


/*******************************************************************************
* Function Name: Comparator_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current user configuration
*
* Parameters:
*  void:
*
* Return:
*  void
*
*******************************************************************************/
void Comparator_SaveConfig(void) 
{
    /* Empty since all are system reset for retention flops */
}


/*******************************************************************************
* Function Name: Comparator_RestoreConfig
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
********************************************************************************/
void Comparator_RestoreConfig(void) 
{
    /* Empty since all are system reset for retention flops */    
}


/*******************************************************************************
* Function Name: Comparator_Sleep
********************************************************************************
*
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
*  Comparator_backup.enableState:  Is modified depending on the enable 
*   state of the block before entering sleep mode.
*
*******************************************************************************/
void Comparator_Sleep(void) 
{
    /* Save Comp's enable state */    
    if(Comparator_ACT_PWR_EN == (Comparator_PWRMGR & Comparator_ACT_PWR_EN))
    {
        /* Comp is enabled */
        Comparator_backup.enableState = 1u;
    }
    else
    {
        /* Comp is disabled */
        Comparator_backup.enableState = 0u;
    }    
    
    Comparator_Stop();
    Comparator_SaveConfig();
}


/*******************************************************************************
* Function Name: Comparator_Wakeup
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
*  Comparator_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Comparator_Wakeup(void) 
{
    Comparator_RestoreConfig();
    
    if(Comparator_backup.enableState == 1u)
    {
        /* Enable Comp's operation */
        Comparator_Enable();

    } /* Do nothing if Comp was disabled before */ 
}


/* [] END OF FILE */
