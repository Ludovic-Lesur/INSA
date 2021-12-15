/*******************************************************************************
* File Name: Timer_TX_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timer_TX.h"

static Timer_TX_backupStruct Timer_TX_backup;


/*******************************************************************************
* Function Name: Timer_TX_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_TX_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_TX_SaveConfig(void) 
{
    #if (!Timer_TX_UsingFixedFunction)
        Timer_TX_backup.TimerUdb = Timer_TX_ReadCounter();
        Timer_TX_backup.InterruptMaskValue = Timer_TX_STATUS_MASK;
        #if (Timer_TX_UsingHWCaptureCounter)
            Timer_TX_backup.TimerCaptureCounter = Timer_TX_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_TX_UDB_CONTROL_REG_REMOVED)
            Timer_TX_backup.TimerControlRegister = Timer_TX_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_TX_RestoreConfig
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
* Global variables:
*  Timer_TX_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_TX_RestoreConfig(void) 
{   
    #if (!Timer_TX_UsingFixedFunction)

        Timer_TX_WriteCounter(Timer_TX_backup.TimerUdb);
        Timer_TX_STATUS_MASK =Timer_TX_backup.InterruptMaskValue;
        #if (Timer_TX_UsingHWCaptureCounter)
            Timer_TX_SetCaptureCount(Timer_TX_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_TX_UDB_CONTROL_REG_REMOVED)
            Timer_TX_WriteControlRegister(Timer_TX_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_TX_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_TX_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_TX_Sleep(void) 
{
    #if(!Timer_TX_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_TX_CTRL_ENABLE == (Timer_TX_CONTROL & Timer_TX_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_TX_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_TX_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_TX_Stop();
    Timer_TX_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_TX_Wakeup
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
*  Timer_TX_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_TX_Wakeup(void) 
{
    Timer_TX_RestoreConfig();
    #if(!Timer_TX_UDB_CONTROL_REG_REMOVED)
        if(Timer_TX_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_TX_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
