/*******************************************************************************
* File Name: Chronometer_PM.c  
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

#include "Chronometer.h"

static Chronometer_backupStruct Chronometer_backup;


/*******************************************************************************
* Function Name: Chronometer_SaveConfig
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
*  Chronometer_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void Chronometer_SaveConfig(void) 
{
    #if (!Chronometer_UsingFixedFunction)

        Chronometer_backup.CounterUdb = Chronometer_ReadCounter();

        #if(!Chronometer_ControlRegRemoved)
            Chronometer_backup.CounterControlRegister = Chronometer_ReadControlRegister();
        #endif /* (!Chronometer_ControlRegRemoved) */

    #endif /* (!Chronometer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Chronometer_RestoreConfig
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
*  Chronometer_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Chronometer_RestoreConfig(void) 
{      
    #if (!Chronometer_UsingFixedFunction)

       Chronometer_WriteCounter(Chronometer_backup.CounterUdb);

        #if(!Chronometer_ControlRegRemoved)
            Chronometer_WriteControlRegister(Chronometer_backup.CounterControlRegister);
        #endif /* (!Chronometer_ControlRegRemoved) */

    #endif /* (!Chronometer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Chronometer_Sleep
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
*  Chronometer_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Chronometer_Sleep(void) 
{
    #if(!Chronometer_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Chronometer_CTRL_ENABLE == (Chronometer_CONTROL & Chronometer_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Chronometer_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Chronometer_backup.CounterEnableState = 0u;
        }
    #else
        Chronometer_backup.CounterEnableState = 1u;
        if(Chronometer_backup.CounterEnableState != 0u)
        {
            Chronometer_backup.CounterEnableState = 0u;
        }
    #endif /* (!Chronometer_ControlRegRemoved) */
    
    Chronometer_Stop();
    Chronometer_SaveConfig();
}


/*******************************************************************************
* Function Name: Chronometer_Wakeup
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
*  Chronometer_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Chronometer_Wakeup(void) 
{
    Chronometer_RestoreConfig();
    #if(!Chronometer_ControlRegRemoved)
        if(Chronometer_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Chronometer_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!Chronometer_ControlRegRemoved) */
    
}


/* [] END OF FILE */
