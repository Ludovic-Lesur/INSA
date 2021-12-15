/*******************************************************************************
* File Name: Reset_Counter_PM.c
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

#include "Reset_Counter.h"

/* Check for removal by optimization */
#if !defined(Reset_Counter_Sync_ctrl_reg__REMOVED)

static Reset_Counter_BACKUP_STRUCT  Reset_Counter_backup = {0u};

    
/*******************************************************************************
* Function Name: Reset_Counter_SaveConfig
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
void Reset_Counter_SaveConfig(void) 
{
    Reset_Counter_backup.controlState = Reset_Counter_Control;
}


/*******************************************************************************
* Function Name: Reset_Counter_RestoreConfig
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
void Reset_Counter_RestoreConfig(void) 
{
     Reset_Counter_Control = Reset_Counter_backup.controlState;
}


/*******************************************************************************
* Function Name: Reset_Counter_Sleep
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
void Reset_Counter_Sleep(void) 
{
    Reset_Counter_SaveConfig();
}


/*******************************************************************************
* Function Name: Reset_Counter_Wakeup
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
void Reset_Counter_Wakeup(void)  
{
    Reset_Counter_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
