/*******************************************************************************
* File Name: CAN_PM.c
* Version 3.20
*
* Description:
*  This file provides the power manager source code to the API for the
*  Delta-Sigma ADC Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CAN.h"

static CAN_BACKUP_STRUCT CAN_backup =
{
    CAN_DISABLED,
    CAN_CFG1_DEC_CR
};


/*******************************************************************************
* Function Name: CAN_SaveConfig
********************************************************************************
*
* Summary:
*  Save the register configuration which are not retention.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  CAN_backup:  This global structure variable is used to store
*  configuration registers which are non retention whenever user wants to go
*  sleep mode by calling Sleep() API.
*
*******************************************************************************/
void CAN_SaveConfig(void) 
{
    CAN_backup.deccr = CAN_DEC_CR_REG;
}


/*******************************************************************************
* Function Name: CAN_RestoreConfig
********************************************************************************
*
* Summary:
*  Restore the register configurations which are not retention.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  CAN_backup:  This global structure variable is used to restore
*  configuration registers which are non retention whenever user wants to switch
*  to active power mode by calling Wakeup() API.
*
*******************************************************************************/
void CAN_RestoreConfig(void) 
{
    CAN_DEC_CR_REG = CAN_backup.deccr;
}


/*******************************************************************************
* Function Name: CAN_Sleep
********************************************************************************
*
* Summary:
*  Stops the operation of the block and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  CAN_backup:  The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void CAN_Sleep(void) 
{
    /* Save ADC enable state */
    if((CAN_ACT_PWR_DEC_EN == (CAN_PWRMGR_DEC_REG & CAN_ACT_PWR_DEC_EN)) &&
       (CAN_ACT_PWR_DSM_EN == (CAN_PWRMGR_DSM_REG & CAN_ACT_PWR_DSM_EN)))
    {
        /* Component is enabled */
        CAN_backup.enableState = CAN_ENABLED;
        if((CAN_DEC_CR_REG & CAN_DEC_START_CONV) != 0u)
        {   
            /* Conversion is started */
            CAN_backup.enableState |= CAN_STARTED;
        }
		
        /* Stop the configuration */
        CAN_Stop();
    }
    else
    {
        /* Component is disabled */
        CAN_backup.enableState = CAN_DISABLED;
    }

    /* Save the user configuration */
    CAN_SaveConfig();
}


/*******************************************************************************
* Function Name: CAN_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and enables the power to the block.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  CAN_backup:  The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void CAN_Wakeup(void) 
{
    /* Restore the configuration */
    CAN_RestoreConfig();

    /* Enables the component operation */
    if(CAN_backup.enableState != CAN_DISABLED)
    {
        CAN_Enable();
        if((CAN_backup.enableState & CAN_STARTED) != 0u)
        {
            CAN_StartConvert();
        }
    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
