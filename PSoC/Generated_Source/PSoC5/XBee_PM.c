/*******************************************************************************
* File Name: XBee_PM.c
* Version 2.50
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "XBee.h"


/***************************************
* Local data allocation
***************************************/

static XBee_BACKUP_STRUCT  XBee_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: XBee_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the XBee_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  XBee_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void XBee_SaveConfig(void)
{
    #if(XBee_CONTROL_REG_REMOVED == 0u)
        XBee_backup.cr = XBee_CONTROL_REG;
    #endif /* End XBee_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: XBee_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the nonretention control register except FIFO.
*  Does not restore the FIFO which is a set of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  XBee_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling XBee_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void XBee_RestoreConfig(void)
{
    #if(XBee_CONTROL_REG_REMOVED == 0u)
        XBee_CONTROL_REG = XBee_backup.cr;
    #endif /* End XBee_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: XBee_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The XBee_Sleep() API saves the current component state. Then it
*  calls the XBee_Stop() function and calls 
*  XBee_SaveConfig() to save the hardware configuration.
*  Call the XBee_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  XBee_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void XBee_Sleep(void)
{
    #if(XBee_RX_ENABLED || XBee_HD_ENABLED)
        if((XBee_RXSTATUS_ACTL_REG  & XBee_INT_ENABLE) != 0u)
        {
            XBee_backup.enableState = 1u;
        }
        else
        {
            XBee_backup.enableState = 0u;
        }
    #else
        if((XBee_TXSTATUS_ACTL_REG  & XBee_INT_ENABLE) !=0u)
        {
            XBee_backup.enableState = 1u;
        }
        else
        {
            XBee_backup.enableState = 0u;
        }
    #endif /* End XBee_RX_ENABLED || XBee_HD_ENABLED*/

    XBee_Stop();
    XBee_SaveConfig();
}


/*******************************************************************************
* Function Name: XBee_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  XBee_Sleep() was called. The XBee_Wakeup() function
*  calls the XBee_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  XBee_Sleep() function was called, the XBee_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  XBee_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void XBee_Wakeup(void)
{
    XBee_RestoreConfig();
    #if( (XBee_RX_ENABLED) || (XBee_HD_ENABLED) )
        XBee_ClearRxBuffer();
    #endif /* End (XBee_RX_ENABLED) || (XBee_HD_ENABLED) */
    #if(XBee_TX_ENABLED || XBee_HD_ENABLED)
        XBee_ClearTxBuffer();
    #endif /* End XBee_TX_ENABLED || XBee_HD_ENABLED */

    if(XBee_backup.enableState != 0u)
    {
        XBee_Enable();
    }
}


/* [] END OF FILE */
