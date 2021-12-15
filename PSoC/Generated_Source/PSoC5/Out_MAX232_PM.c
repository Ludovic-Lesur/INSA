/*******************************************************************************
* File Name: Out_MAX232_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Out_MAX232.h"

static Out_MAX232_backupStruct Out_MAX232_backup;


/*******************************************************************************
* Function Name: Out_MAX232_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Out_MAX232_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Out_MAX232_SaveConfig(void) 
{

    #if(!Out_MAX232_UsingFixedFunction)
        #if(!Out_MAX232_PWMModeIsCenterAligned)
            Out_MAX232_backup.PWMPeriod = Out_MAX232_ReadPeriod();
        #endif /* (!Out_MAX232_PWMModeIsCenterAligned) */
        Out_MAX232_backup.PWMUdb = Out_MAX232_ReadCounter();
        #if (Out_MAX232_UseStatus)
            Out_MAX232_backup.InterruptMaskValue = Out_MAX232_STATUS_MASK;
        #endif /* (Out_MAX232_UseStatus) */

        #if(Out_MAX232_DeadBandMode == Out_MAX232__B_PWM__DBM_256_CLOCKS || \
            Out_MAX232_DeadBandMode == Out_MAX232__B_PWM__DBM_2_4_CLOCKS)
            Out_MAX232_backup.PWMdeadBandValue = Out_MAX232_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Out_MAX232_KillModeMinTime)
             Out_MAX232_backup.PWMKillCounterPeriod = Out_MAX232_ReadKillTime();
        #endif /* (Out_MAX232_KillModeMinTime) */

        #if(Out_MAX232_UseControl)
            Out_MAX232_backup.PWMControlRegister = Out_MAX232_ReadControlRegister();
        #endif /* (Out_MAX232_UseControl) */
    #endif  /* (!Out_MAX232_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Out_MAX232_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Out_MAX232_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Out_MAX232_RestoreConfig(void) 
{
        #if(!Out_MAX232_UsingFixedFunction)
            #if(!Out_MAX232_PWMModeIsCenterAligned)
                Out_MAX232_WritePeriod(Out_MAX232_backup.PWMPeriod);
            #endif /* (!Out_MAX232_PWMModeIsCenterAligned) */

            Out_MAX232_WriteCounter(Out_MAX232_backup.PWMUdb);

            #if (Out_MAX232_UseStatus)
                Out_MAX232_STATUS_MASK = Out_MAX232_backup.InterruptMaskValue;
            #endif /* (Out_MAX232_UseStatus) */

            #if(Out_MAX232_DeadBandMode == Out_MAX232__B_PWM__DBM_256_CLOCKS || \
                Out_MAX232_DeadBandMode == Out_MAX232__B_PWM__DBM_2_4_CLOCKS)
                Out_MAX232_WriteDeadTime(Out_MAX232_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Out_MAX232_KillModeMinTime)
                Out_MAX232_WriteKillTime(Out_MAX232_backup.PWMKillCounterPeriod);
            #endif /* (Out_MAX232_KillModeMinTime) */

            #if(Out_MAX232_UseControl)
                Out_MAX232_WriteControlRegister(Out_MAX232_backup.PWMControlRegister);
            #endif /* (Out_MAX232_UseControl) */
        #endif  /* (!Out_MAX232_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Out_MAX232_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Out_MAX232_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Out_MAX232_Sleep(void) 
{
    #if(Out_MAX232_UseControl)
        if(Out_MAX232_CTRL_ENABLE == (Out_MAX232_CONTROL & Out_MAX232_CTRL_ENABLE))
        {
            /*Component is enabled */
            Out_MAX232_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Out_MAX232_backup.PWMEnableState = 0u;
        }
    #endif /* (Out_MAX232_UseControl) */

    /* Stop component */
    Out_MAX232_Stop();

    /* Save registers configuration */
    Out_MAX232_SaveConfig();
}


/*******************************************************************************
* Function Name: Out_MAX232_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Out_MAX232_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Out_MAX232_Wakeup(void) 
{
     /* Restore registers values */
    Out_MAX232_RestoreConfig();

    if(Out_MAX232_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Out_MAX232_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
