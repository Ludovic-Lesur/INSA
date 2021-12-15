/*******************************************************************************
* File Name: Pre_Ampli_PM.c  
* Version 2.0
*
* Description:
*  This file provides the power manager source code to the API for PGA 
*  Component.
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

static Pre_Ampli_BACKUP_STRUCT  Pre_Ampli_backup;


/*******************************************************************************
* Function Name: Pre_Ampli_SaveConfig
********************************************************************************
*
* Summary:
*  Save the current user register configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Pre_Ampli_SaveConfig(void) 
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: Pre_Ampli_RestoreConfig
********************************************************************************
*
* Summary:
*  Restore the register configurations.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void Pre_Ampli_RestoreConfig(void) 
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: Pre_Ampli_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Pre_Ampli_backup: The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void Pre_Ampli_Sleep(void) 
{
    /* Save PGA enable state */
    if((Pre_Ampli_PM_ACT_CFG_REG & Pre_Ampli_ACT_PWR_EN) != 0u)
    {
        /* Component is enabled */
        Pre_Ampli_backup.enableState = 1u;
        /* Stop the configuration */
        Pre_Ampli_Stop();
    }
    else
    {
        /* Component is disabled */
        Pre_Ampli_backup.enableState = 0u;
    }
    /* Save the configuration */
    Pre_Ampli_SaveConfig();
}


/*******************************************************************************
* Function Name: Pre_Ampli_Wakeup
********************************************************************************
*
* Summary:
*  Enables block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  void
*
* Global variables:
*  Pre_Ampli_backup: The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
* 
*******************************************************************************/
void Pre_Ampli_Wakeup(void) 
{
    /* Restore the configurations */
    Pre_Ampli_RestoreConfig();
     /* Enables the component operation */
    if(Pre_Ampli_backup.enableState == 1u)
    {
        Pre_Ampli_Enable();
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
