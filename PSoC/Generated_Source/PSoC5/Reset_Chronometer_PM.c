/*******************************************************************************
* File Name: Reset_Chronometer_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Reset_Chronometer.h"

/* Check for removal by optimization */
#if !defined(Reset_Chronometer_Sync_ctrl_reg__REMOVED)

static Reset_Chronometer_BACKUP_STRUCT  Reset_Chronometer_backup = {0u};

    
/*******************************************************************************
* Function Name: Reset_Chronometer_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Reset_Chronometer_SaveConfig(void) 
{
    Reset_Chronometer_backup.controlState = Reset_Chronometer_Control;
}


/*******************************************************************************
* Function Name: Reset_Chronometer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void Reset_Chronometer_RestoreConfig(void) 
{
     Reset_Chronometer_Control = Reset_Chronometer_backup.controlState;
}


/*******************************************************************************
* Function Name: Reset_Chronometer_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Reset_Chronometer_Sleep(void) 
{
    Reset_Chronometer_SaveConfig();
}


/*******************************************************************************
* Function Name: Reset_Chronometer_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Reset_Chronometer_Wakeup(void)  
{
    Reset_Chronometer_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
