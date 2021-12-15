/*******************************************************************************
* File Name: Counter_Pulses_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Counter_Pulses.h"

static Counter_Pulses_backupStruct Counter_Pulses_backup;


/*******************************************************************************
* Function Name: Counter_Pulses_SaveConfig
********************************************************************************
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
*  Counter_Pulses_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Counter_Pulses_SaveConfig(void) 
{
    #if (!Counter_Pulses_UsingFixedFunction)

        Counter_Pulses_backup.CounterUdb = Counter_Pulses_ReadCounter();

        #if(!Counter_Pulses_ControlRegRemoved)
            Counter_Pulses_backup.CounterControlRegister = Counter_Pulses_ReadControlRegister();
        #endif /* (!Counter_Pulses_ControlRegRemoved) */

    #endif /* (!Counter_Pulses_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_Pulses_RestoreConfig
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
*  Counter_Pulses_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_Pulses_RestoreConfig(void) 
{      
    #if (!Counter_Pulses_UsingFixedFunction)

       Counter_Pulses_WriteCounter(Counter_Pulses_backup.CounterUdb);

        #if(!Counter_Pulses_ControlRegRemoved)
            Counter_Pulses_WriteControlRegister(Counter_Pulses_backup.CounterControlRegister);
        #endif /* (!Counter_Pulses_ControlRegRemoved) */

    #endif /* (!Counter_Pulses_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Counter_Pulses_Sleep
********************************************************************************
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
*  Counter_Pulses_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Counter_Pulses_Sleep(void) 
{
    #if(!Counter_Pulses_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Counter_Pulses_CTRL_ENABLE == (Counter_Pulses_CONTROL & Counter_Pulses_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Counter_Pulses_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Counter_Pulses_backup.CounterEnableState = 0u;
        }
    #else
        Counter_Pulses_backup.CounterEnableState = 1u;
        if(Counter_Pulses_backup.CounterEnableState != 0u)
        {
            Counter_Pulses_backup.CounterEnableState = 0u;
        }
    #endif /* (!Counter_Pulses_ControlRegRemoved) */
    
    Counter_Pulses_Stop();
    Counter_Pulses_SaveConfig();
}


/*******************************************************************************
* Function Name: Counter_Pulses_Wakeup
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
*  Counter_Pulses_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Counter_Pulses_Wakeup(void) 
{
    Counter_Pulses_RestoreConfig();
    #if(!Counter_Pulses_ControlRegRemoved)
        if(Counter_Pulses_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Counter_Pulses_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Counter_Pulses_ControlRegRemoved) */
    
}


/* [] END OF FILE */
