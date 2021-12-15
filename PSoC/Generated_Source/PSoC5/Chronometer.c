/*******************************************************************************
* File Name: Chronometer.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
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

uint8 Chronometer_initVar = 0u;


/*******************************************************************************
* Function Name: Chronometer_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void Chronometer_Init(void) 
{
        #if (!Chronometer_UsingFixedFunction && !Chronometer_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!Chronometer_UsingFixedFunction && !Chronometer_ControlRegRemoved) */
        
        #if(!Chronometer_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 Chronometer_interruptState;
        #endif /* (!Chronometer_UsingFixedFunction) */
        
        #if (Chronometer_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            Chronometer_CONTROL &= Chronometer_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                Chronometer_CONTROL2 &= ((uint8)(~Chronometer_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                Chronometer_CONTROL3 &= ((uint8)(~Chronometer_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (Chronometer_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                Chronometer_CONTROL |= Chronometer_ONESHOT;
            #endif /* (Chronometer_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            Chronometer_CONTROL2 |= Chronometer_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            Chronometer_RT1 &= ((uint8)(~Chronometer_RT1_MASK));
            Chronometer_RT1 |= Chronometer_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            Chronometer_RT1 &= ((uint8)(~Chronometer_SYNCDSI_MASK));
            Chronometer_RT1 |= Chronometer_SYNCDSI_EN;

        #else
            #if(!Chronometer_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = Chronometer_CONTROL & ((uint8)(~Chronometer_CTRL_CMPMODE_MASK));
            Chronometer_CONTROL = ctrl | Chronometer_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = Chronometer_CONTROL & ((uint8)(~Chronometer_CTRL_CAPMODE_MASK));
            
            #if( 0 != Chronometer_CAPTURE_MODE_CONF)
                Chronometer_CONTROL = ctrl | Chronometer_DEFAULT_CAPTURE_MODE;
            #else
                Chronometer_CONTROL = ctrl;
            #endif /* 0 != Chronometer_CAPTURE_MODE */ 
            
            #endif /* (!Chronometer_ControlRegRemoved) */
        #endif /* (Chronometer_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!Chronometer_UsingFixedFunction)
            Chronometer_ClearFIFO();
        #endif /* (!Chronometer_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        Chronometer_WritePeriod(Chronometer_INIT_PERIOD_VALUE);
        #if (!(Chronometer_UsingFixedFunction && (CY_PSOC5A)))
            Chronometer_WriteCounter(Chronometer_INIT_COUNTER_VALUE);
        #endif /* (!(Chronometer_UsingFixedFunction && (CY_PSOC5A))) */
        Chronometer_SetInterruptMode(Chronometer_INIT_INTERRUPTS_MASK);
        
        #if (!Chronometer_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)Chronometer_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            Chronometer_WriteCompare(Chronometer_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            Chronometer_interruptState = CyEnterCriticalSection();
            
            Chronometer_STATUS_AUX_CTRL |= Chronometer_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(Chronometer_interruptState);
            
        #endif /* (!Chronometer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Chronometer_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void Chronometer_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (Chronometer_UsingFixedFunction)
        Chronometer_GLOBAL_ENABLE |= Chronometer_BLOCK_EN_MASK;
        Chronometer_GLOBAL_STBY_ENABLE |= Chronometer_BLOCK_STBY_EN_MASK;
    #endif /* (Chronometer_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!Chronometer_ControlRegRemoved || Chronometer_UsingFixedFunction)
        Chronometer_CONTROL |= Chronometer_CTRL_ENABLE;                
    #endif /* (!Chronometer_ControlRegRemoved || Chronometer_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: Chronometer_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  Chronometer_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Chronometer_Start(void) 
{
    if(Chronometer_initVar == 0u)
    {
        Chronometer_Init();
        
        Chronometer_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    Chronometer_Enable();        
}


/*******************************************************************************
* Function Name: Chronometer_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void Chronometer_Stop(void) 
{
    /* Disable Counter */
    #if(!Chronometer_ControlRegRemoved || Chronometer_UsingFixedFunction)
        Chronometer_CONTROL &= ((uint8)(~Chronometer_CTRL_ENABLE));        
    #endif /* (!Chronometer_ControlRegRemoved || Chronometer_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (Chronometer_UsingFixedFunction)
        Chronometer_GLOBAL_ENABLE &= ((uint8)(~Chronometer_BLOCK_EN_MASK));
        Chronometer_GLOBAL_STBY_ENABLE &= ((uint8)(~Chronometer_BLOCK_STBY_EN_MASK));
    #endif /* (Chronometer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Chronometer_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void Chronometer_SetInterruptMode(uint8 interruptsMask) 
{
    Chronometer_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: Chronometer_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   Chronometer_ReadStatusRegister(void) 
{
    return Chronometer_STATUS;
}


#if(!Chronometer_ControlRegRemoved)
/*******************************************************************************
* Function Name: Chronometer_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   Chronometer_ReadControlRegister(void) 
{
    return Chronometer_CONTROL;
}


/*******************************************************************************
* Function Name: Chronometer_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    Chronometer_WriteControlRegister(uint8 control) 
{
    Chronometer_CONTROL = control;
}

#endif  /* (!Chronometer_ControlRegRemoved) */


#if (!(Chronometer_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: Chronometer_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void Chronometer_WriteCounter(uint32 counter) \
                                   
{
    #if(Chronometer_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (Chronometer_GLOBAL_ENABLE & Chronometer_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        Chronometer_GLOBAL_ENABLE |= Chronometer_BLOCK_EN_MASK;
        CY_SET_REG16(Chronometer_COUNTER_LSB_PTR, (uint16)counter);
        Chronometer_GLOBAL_ENABLE &= ((uint8)(~Chronometer_BLOCK_EN_MASK));
    #else
        CY_SET_REG32(Chronometer_COUNTER_LSB_PTR, counter);
    #endif /* (Chronometer_UsingFixedFunction) */
}
#endif /* (!(Chronometer_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: Chronometer_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint32) The present value of the counter.
*
*******************************************************************************/
uint32 Chronometer_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(Chronometer_UsingFixedFunction)
		(void)CY_GET_REG16(Chronometer_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(Chronometer_COUNTER_LSB_PTR_8BIT);
	#endif/* (Chronometer_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(Chronometer_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(Chronometer_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG32(Chronometer_STATICCOUNT_LSB_PTR));
    #endif /* (Chronometer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Chronometer_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint32) Present Capture value.
*
*******************************************************************************/
uint32 Chronometer_ReadCapture(void) 
{
    #if(Chronometer_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(Chronometer_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG32(Chronometer_STATICCOUNT_LSB_PTR));
    #endif /* (Chronometer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Chronometer_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint32) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void Chronometer_WritePeriod(uint32 period) 
{
    #if(Chronometer_UsingFixedFunction)
        CY_SET_REG16(Chronometer_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG32(Chronometer_PERIOD_LSB_PTR, period);
    #endif /* (Chronometer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Chronometer_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint32) Present period value.
*
*******************************************************************************/
uint32 Chronometer_ReadPeriod(void) 
{
    #if(Chronometer_UsingFixedFunction)
        return ((uint32)CY_GET_REG16(Chronometer_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG32(Chronometer_PERIOD_LSB_PTR));
    #endif /* (Chronometer_UsingFixedFunction) */
}


#if (!Chronometer_UsingFixedFunction)
/*******************************************************************************
* Function Name: Chronometer_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void Chronometer_WriteCompare(uint32 compare) \
                                   
{
    #if(Chronometer_UsingFixedFunction)
        CY_SET_REG16(Chronometer_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG32(Chronometer_COMPARE_LSB_PTR, compare);
    #endif /* (Chronometer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Chronometer_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint32) Present compare value.
*
*******************************************************************************/
uint32 Chronometer_ReadCompare(void) 
{
    return (CY_GET_REG32(Chronometer_COMPARE_LSB_PTR));
}


#if (Chronometer_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: Chronometer_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void Chronometer_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    Chronometer_CONTROL &= ((uint8)(~Chronometer_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    Chronometer_CONTROL |= compareMode;
}
#endif  /* (Chronometer_COMPARE_MODE_SOFTWARE) */


#if (Chronometer_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: Chronometer_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void Chronometer_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    Chronometer_CONTROL &= ((uint8)(~Chronometer_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    Chronometer_CONTROL |= ((uint8)((uint8)captureMode << Chronometer_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (Chronometer_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: Chronometer_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void Chronometer_ClearFIFO(void) 
{

    while(0u != (Chronometer_ReadStatusRegister() & Chronometer_STATUS_FIFONEMP))
    {
        (void)Chronometer_ReadCapture();
    }

}
#endif  /* (!Chronometer_UsingFixedFunction) */


/* [] END OF FILE */

