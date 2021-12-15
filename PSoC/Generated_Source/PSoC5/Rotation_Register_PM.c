/*******************************************************************************
* File Name: Rotation_Register_PM.c
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

#include "Rotation_Register.h"

/* Check for removal by optimization */
#if !defined(Rotation_Register_Sync_ctrl_reg__REMOVED)

static Rotation_Register_BACKUP_STRUCT  Rotation_Register_backup = {0u};

    
/*******************************************************************************
* Function Name: Rotation_Register_SaveConfig
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
void Rotation_Register_SaveConfig(void) 
{
    Rotation_Register_backup.controlState = Rotation_Register_Control;
}


/*******************************************************************************
* Function Name: Rotation_Register_RestoreConfig
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
void Rotation_Register_RestoreConfig(void) 
{
     Rotation_Register_Control = Rotation_Register_backup.controlState;
}


/*******************************************************************************
* Function Name: Rotation_Register_Sleep
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
void Rotation_Register_Sleep(void) 
{
    Rotation_Register_SaveConfig();
}


/*******************************************************************************
* Function Name: Rotation_Register_Wakeup
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
void Rotation_Register_Wakeup(void)  
{
    Rotation_Register_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
