/*******************************************************************************
* File Name: XBee.c
* Version 2.50
*
* Description:
*  This file provides all API functionality of the UART component
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
#if (XBee_INTERNAL_CLOCK_USED)
    #include "XBee_IntClock.h"
#endif /* End XBee_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 XBee_initVar = 0u;

#if (XBee_TX_INTERRUPT_ENABLED && XBee_TX_ENABLED)
    volatile uint8 XBee_txBuffer[XBee_TX_BUFFER_SIZE];
    volatile uint8 XBee_txBufferRead = 0u;
    uint8 XBee_txBufferWrite = 0u;
#endif /* (XBee_TX_INTERRUPT_ENABLED && XBee_TX_ENABLED) */

#if (XBee_RX_INTERRUPT_ENABLED && (XBee_RX_ENABLED || XBee_HD_ENABLED))
    uint8 XBee_errorStatus = 0u;
    volatile uint8 XBee_rxBuffer[XBee_RX_BUFFER_SIZE];
    volatile uint8 XBee_rxBufferRead  = 0u;
    volatile uint8 XBee_rxBufferWrite = 0u;
    volatile uint8 XBee_rxBufferLoopDetect = 0u;
    volatile uint8 XBee_rxBufferOverflow   = 0u;
    #if (XBee_RXHW_ADDRESS_ENABLED)
        volatile uint8 XBee_rxAddressMode = XBee_RX_ADDRESS_MODE;
        volatile uint8 XBee_rxAddressDetected = 0u;
    #endif /* (XBee_RXHW_ADDRESS_ENABLED) */
#endif /* (XBee_RX_INTERRUPT_ENABLED && (XBee_RX_ENABLED || XBee_HD_ENABLED)) */


/*******************************************************************************
* Function Name: XBee_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  XBee_Start() sets the initVar variable, calls the
*  XBee_Init() function, and then calls the
*  XBee_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The XBee_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time XBee_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the XBee_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void XBee_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(XBee_initVar == 0u)
    {
        XBee_Init();
        XBee_initVar = 1u;
    }

    XBee_Enable();
}


/*******************************************************************************
* Function Name: XBee_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call XBee_Init() because
*  the XBee_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void XBee_Init(void) 
{
    #if(XBee_RX_ENABLED || XBee_HD_ENABLED)

        #if (XBee_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(XBee_RX_VECT_NUM, &XBee_RXISR);
            CyIntSetPriority(XBee_RX_VECT_NUM, XBee_RX_PRIOR_NUM);
            XBee_errorStatus = 0u;
        #endif /* (XBee_RX_INTERRUPT_ENABLED) */

        #if (XBee_RXHW_ADDRESS_ENABLED)
            XBee_SetRxAddressMode(XBee_RX_ADDRESS_MODE);
            XBee_SetRxAddress1(XBee_RX_HW_ADDRESS1);
            XBee_SetRxAddress2(XBee_RX_HW_ADDRESS2);
        #endif /* End XBee_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        XBee_RXBITCTR_PERIOD_REG = XBee_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        XBee_RXSTATUS_MASK_REG  = XBee_INIT_RX_INTERRUPTS_MASK;
    #endif /* End XBee_RX_ENABLED || XBee_HD_ENABLED*/

    #if(XBee_TX_ENABLED)
        #if (XBee_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(XBee_TX_VECT_NUM, &XBee_TXISR);
            CyIntSetPriority(XBee_TX_VECT_NUM, XBee_TX_PRIOR_NUM);
        #endif /* (XBee_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (XBee_TXCLKGEN_DP)
            XBee_TXBITCLKGEN_CTR_REG = XBee_BIT_CENTER;
            XBee_TXBITCLKTX_COMPLETE_REG = ((XBee_NUMBER_OF_DATA_BITS +
                        XBee_NUMBER_OF_START_BIT) * XBee_OVER_SAMPLE_COUNT) - 1u;
        #else
            XBee_TXBITCTR_PERIOD_REG = ((XBee_NUMBER_OF_DATA_BITS +
                        XBee_NUMBER_OF_START_BIT) * XBee_OVER_SAMPLE_8) - 1u;
        #endif /* End XBee_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (XBee_TX_INTERRUPT_ENABLED)
            XBee_TXSTATUS_MASK_REG = XBee_TX_STS_FIFO_EMPTY;
        #else
            XBee_TXSTATUS_MASK_REG = XBee_INIT_TX_INTERRUPTS_MASK;
        #endif /*End XBee_TX_INTERRUPT_ENABLED*/

    #endif /* End XBee_TX_ENABLED */

    #if(XBee_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        XBee_WriteControlRegister( \
            (XBee_ReadControlRegister() & (uint8)~XBee_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(XBee_PARITY_TYPE << XBee_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End XBee_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: XBee_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call XBee_Enable() because the XBee_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  XBee_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void XBee_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (XBee_RX_ENABLED || XBee_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        XBee_RXBITCTR_CONTROL_REG |= XBee_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        XBee_RXSTATUS_ACTL_REG  |= XBee_INT_ENABLE;

        #if (XBee_RX_INTERRUPT_ENABLED)
            XBee_EnableRxInt();

            #if (XBee_RXHW_ADDRESS_ENABLED)
                XBee_rxAddressDetected = 0u;
            #endif /* (XBee_RXHW_ADDRESS_ENABLED) */
        #endif /* (XBee_RX_INTERRUPT_ENABLED) */
    #endif /* (XBee_RX_ENABLED || XBee_HD_ENABLED) */

    #if(XBee_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!XBee_TXCLKGEN_DP)
            XBee_TXBITCTR_CONTROL_REG |= XBee_CNTR_ENABLE;
        #endif /* End XBee_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        XBee_TXSTATUS_ACTL_REG |= XBee_INT_ENABLE;
        #if (XBee_TX_INTERRUPT_ENABLED)
            XBee_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            XBee_EnableTxInt();
        #endif /* (XBee_TX_INTERRUPT_ENABLED) */
     #endif /* (XBee_TX_INTERRUPT_ENABLED) */

    #if (XBee_INTERNAL_CLOCK_USED)
        XBee_IntClock_Start();  /* Enable the clock */
    #endif /* (XBee_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: XBee_Stop
********************************************************************************
*
* Summary:
*  Disables the UART operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void XBee_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (XBee_RX_ENABLED || XBee_HD_ENABLED)
        XBee_RXBITCTR_CONTROL_REG &= (uint8) ~XBee_CNTR_ENABLE;
    #endif /* (XBee_RX_ENABLED || XBee_HD_ENABLED) */

    #if (XBee_TX_ENABLED)
        #if(!XBee_TXCLKGEN_DP)
            XBee_TXBITCTR_CONTROL_REG &= (uint8) ~XBee_CNTR_ENABLE;
        #endif /* (!XBee_TXCLKGEN_DP) */
    #endif /* (XBee_TX_ENABLED) */

    #if (XBee_INTERNAL_CLOCK_USED)
        XBee_IntClock_Stop();   /* Disable the clock */
    #endif /* (XBee_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (XBee_RX_ENABLED || XBee_HD_ENABLED)
        XBee_RXSTATUS_ACTL_REG  &= (uint8) ~XBee_INT_ENABLE;

        #if (XBee_RX_INTERRUPT_ENABLED)
            XBee_DisableRxInt();
        #endif /* (XBee_RX_INTERRUPT_ENABLED) */
    #endif /* (XBee_RX_ENABLED || XBee_HD_ENABLED) */

    #if (XBee_TX_ENABLED)
        XBee_TXSTATUS_ACTL_REG &= (uint8) ~XBee_INT_ENABLE;

        #if (XBee_TX_INTERRUPT_ENABLED)
            XBee_DisableTxInt();
        #endif /* (XBee_TX_INTERRUPT_ENABLED) */
    #endif /* (XBee_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: XBee_ReadControlRegister
********************************************************************************
*
* Summary:
*  Returns the current value of the control register.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the control register.
*
*******************************************************************************/
uint8 XBee_ReadControlRegister(void) 
{
    #if (XBee_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(XBee_CONTROL_REG);
    #endif /* (XBee_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: XBee_WriteControlRegister
********************************************************************************
*
* Summary:
*  Writes an 8-bit value into the control register
*
* Parameters:
*  control:  control register value
*
* Return:
*  None.
*
*******************************************************************************/
void  XBee_WriteControlRegister(uint8 control) 
{
    #if (XBee_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       XBee_CONTROL_REG = control;
    #endif /* (XBee_CONTROL_REG_REMOVED) */
}


#if(XBee_RX_ENABLED || XBee_HD_ENABLED)
    /*******************************************************************************
    * Function Name: XBee_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      XBee_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      XBee_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      XBee_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      XBee_RX_STS_BREAK            Interrupt on break.
    *      XBee_RX_STS_OVERRUN          Interrupt on overrun error.
    *      XBee_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      XBee_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void XBee_SetRxInterruptMode(uint8 intSrc) 
    {
        XBee_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: XBee_ReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Returns the next byte of received data. This function returns data without
    *  checking the status. You must check the status separately.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received data from RX register
    *
    * Global Variables:
    *  XBee_rxBuffer - RAM buffer pointer for save received data.
    *  XBee_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  XBee_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  XBee_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 XBee_ReadRxData(void) 
    {
        uint8 rxData;

    #if (XBee_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        XBee_DisableRxInt();

        locRxBufferRead  = XBee_rxBufferRead;
        locRxBufferWrite = XBee_rxBufferWrite;

        if( (XBee_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = XBee_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= XBee_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            XBee_rxBufferRead = locRxBufferRead;

            if(XBee_rxBufferLoopDetect != 0u)
            {
                XBee_rxBufferLoopDetect = 0u;
                #if ((XBee_RX_INTERRUPT_ENABLED) && (XBee_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( XBee_HD_ENABLED )
                        if((XBee_CONTROL_REG & XBee_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            XBee_RXSTATUS_MASK_REG  |= XBee_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        XBee_RXSTATUS_MASK_REG  |= XBee_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end XBee_HD_ENABLED */
                #endif /* ((XBee_RX_INTERRUPT_ENABLED) && (XBee_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = XBee_RXDATA_REG;
        }

        XBee_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = XBee_RXDATA_REG;

    #endif /* (XBee_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: XBee_ReadRxStatus
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the receiver status register and the software
    *  buffer overflow status.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Current state of the status register.
    *
    * Side Effect:
    *  All status register bits are clear-on-read except
    *  XBee_RX_STS_FIFO_NOTEMPTY.
    *  XBee_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  XBee_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   XBee_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   XBee_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 XBee_ReadRxStatus(void) 
    {
        uint8 status;

        status = XBee_RXSTATUS_REG & XBee_RX_HW_MASK;

    #if (XBee_RX_INTERRUPT_ENABLED)
        if(XBee_rxBufferOverflow != 0u)
        {
            status |= XBee_RX_STS_SOFT_BUFF_OVER;
            XBee_rxBufferOverflow = 0u;
        }
    #endif /* (XBee_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: XBee_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. XBee_GetChar() is
    *  designed for ASCII characters and returns a uint8 where 1 to 255 are values
    *  for valid characters and 0 indicates an error occurred or no data is present.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Character read from UART RX buffer. ASCII characters from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Global Variables:
    *  XBee_rxBuffer - RAM buffer pointer for save received data.
    *  XBee_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  XBee_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  XBee_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 XBee_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (XBee_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        XBee_DisableRxInt();

        locRxBufferRead  = XBee_rxBufferRead;
        locRxBufferWrite = XBee_rxBufferWrite;

        if( (XBee_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = XBee_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= XBee_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            XBee_rxBufferRead = locRxBufferRead;

            if(XBee_rxBufferLoopDetect != 0u)
            {
                XBee_rxBufferLoopDetect = 0u;
                #if( (XBee_RX_INTERRUPT_ENABLED) && (XBee_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( XBee_HD_ENABLED )
                        if((XBee_CONTROL_REG & XBee_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            XBee_RXSTATUS_MASK_REG |= XBee_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        XBee_RXSTATUS_MASK_REG |= XBee_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end XBee_HD_ENABLED */
                #endif /* XBee_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = XBee_RXSTATUS_REG;
            if((rxStatus & XBee_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = XBee_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (XBee_RX_STS_BREAK | XBee_RX_STS_PAR_ERROR |
                                XBee_RX_STS_STOP_ERROR | XBee_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        XBee_EnableRxInt();

    #else

        rxStatus =XBee_RXSTATUS_REG;
        if((rxStatus & XBee_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = XBee_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (XBee_RX_STS_BREAK | XBee_RX_STS_PAR_ERROR |
                            XBee_RX_STS_STOP_ERROR | XBee_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (XBee_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: XBee_GetByte
    ********************************************************************************
    *
    * Summary:
    *  Reads UART RX buffer immediately, returns received character and error
    *  condition.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  MSB contains status and LSB contains UART RX data. If the MSB is nonzero,
    *  an error has occurred.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 XBee_GetByte(void) 
    {
        
    #if (XBee_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        XBee_DisableRxInt();
        locErrorStatus = (uint16)XBee_errorStatus;
        XBee_errorStatus = 0u;
        XBee_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | XBee_ReadRxData() );
    #else
        return ( ((uint16)XBee_ReadRxStatus() << 8u) | XBee_ReadRxData() );
    #endif /* XBee_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: XBee_GetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received bytes available in the RX buffer.
    *  * RX software buffer is disabled (RX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty RX FIFO or 1 for not empty RX FIFO.
    *  * RX software buffer is enabled: returns the number of bytes available in 
    *    the RX software buffer. Bytes available in the RX FIFO do not take to 
    *    account.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  uint8: Number of bytes in the RX buffer. 
    *    Return value type depends on RX Buffer Size parameter.
    *
    * Global Variables:
    *  XBee_rxBufferWrite - used to calculate left bytes.
    *  XBee_rxBufferRead - used to calculate left bytes.
    *  XBee_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 XBee_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (XBee_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        XBee_DisableRxInt();

        if(XBee_rxBufferRead == XBee_rxBufferWrite)
        {
            if(XBee_rxBufferLoopDetect != 0u)
            {
                size = XBee_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(XBee_rxBufferRead < XBee_rxBufferWrite)
        {
            size = (XBee_rxBufferWrite - XBee_rxBufferRead);
        }
        else
        {
            size = (XBee_RX_BUFFER_SIZE - XBee_rxBufferRead) + XBee_rxBufferWrite;
        }

        XBee_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((XBee_RXSTATUS_REG & XBee_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (XBee_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: XBee_ClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receiver memory buffer and hardware RX FIFO of all received data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  XBee_rxBufferWrite - cleared to zero.
    *  XBee_rxBufferRead - cleared to zero.
    *  XBee_rxBufferLoopDetect - cleared to zero.
    *  XBee_rxBufferOverflow - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may
    *  have remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM or FIFO buffer will be lost.
    *
    *******************************************************************************/
    void XBee_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        XBee_RXDATA_AUX_CTL_REG |= (uint8)  XBee_RX_FIFO_CLR;
        XBee_RXDATA_AUX_CTL_REG &= (uint8) ~XBee_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (XBee_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        XBee_DisableRxInt();

        XBee_rxBufferRead = 0u;
        XBee_rxBufferWrite = 0u;
        XBee_rxBufferLoopDetect = 0u;
        XBee_rxBufferOverflow = 0u;

        XBee_EnableRxInt();

    #endif /* (XBee_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: XBee_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  XBee__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  XBee__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  XBee__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  XBee__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  XBee__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  XBee_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  XBee_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void XBee_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(XBee_RXHW_ADDRESS_ENABLED)
            #if(XBee_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* XBee_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = XBee_CONTROL_REG & (uint8)~XBee_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << XBee_CTRL_RXADDR_MODE0_SHIFT);
                XBee_CONTROL_REG = tmpCtrl;

                #if(XBee_RX_INTERRUPT_ENABLED && \
                   (XBee_RXBUFFERSIZE > XBee_FIFO_LENGTH) )
                    XBee_rxAddressMode = addressMode;
                    XBee_rxAddressDetected = 0u;
                #endif /* End XBee_RXBUFFERSIZE > XBee_FIFO_LENGTH*/
            #endif /* End XBee_CONTROL_REG_REMOVED */
        #else /* XBee_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End XBee_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: XBee_SetRxAddress1
    ********************************************************************************
    *
    * Summary:
    *  Sets the first of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #1 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void XBee_SetRxAddress1(uint8 address) 
    {
        XBee_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: XBee_SetRxAddress2
    ********************************************************************************
    *
    * Summary:
    *  Sets the second of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #2 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void XBee_SetRxAddress2(uint8 address) 
    {
        XBee_RXADDRESS2_REG = address;
    }

#endif  /* XBee_RX_ENABLED || XBee_HD_ENABLED*/


#if( (XBee_TX_ENABLED) || (XBee_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: XBee_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   XBee_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   XBee_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   XBee_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   XBee_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void XBee_SetTxInterruptMode(uint8 intSrc) 
    {
        XBee_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: XBee_WriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data into the transmit buffer to be sent when the bus is
    *  available without checking the TX status register. You must check status
    *  separately.
    *
    * Parameters:
    *  txDataByte: data byte
    *
    * Return:
    * None.
    *
    * Global Variables:
    *  XBee_txBuffer - RAM buffer pointer for save data for transmission
    *  XBee_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  XBee_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  XBee_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void XBee_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(XBee_initVar != 0u)
        {
        #if (XBee_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            XBee_DisableTxInt();

            if( (XBee_txBufferRead == XBee_txBufferWrite) &&
                ((XBee_TXSTATUS_REG & XBee_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                XBee_TXDATA_REG = txDataByte;
            }
            else
            {
                if(XBee_txBufferWrite >= XBee_TX_BUFFER_SIZE)
                {
                    XBee_txBufferWrite = 0u;
                }

                XBee_txBuffer[XBee_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                XBee_txBufferWrite++;
            }

            XBee_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            XBee_TXDATA_REG = txDataByte;

        #endif /*(XBee_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: XBee_ReadTxStatus
    ********************************************************************************
    *
    * Summary:
    *  Reads the status register for the TX portion of the UART.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Contents of the status register
    *
    * Theory:
    *  This function reads the TX status register, which is cleared on read.
    *  It is up to the user to handle all bits in this return value accordingly,
    *  even if the bit was not enabled as an interrupt source the event happened
    *  and must be handled accordingly.
    *
    *******************************************************************************/
    uint8 XBee_ReadTxStatus(void) 
    {
        return(XBee_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: XBee_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Puts a byte of data into the transmit buffer to be sent when the bus is
    *  available. This is a blocking API that waits until the TX buffer has room to
    *  hold the data.
    *
    * Parameters:
    *  txDataByte: Byte containing the data to transmit
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  XBee_txBuffer - RAM buffer pointer for save data for transmission
    *  XBee_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  XBee_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  XBee_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void XBee_PutChar(uint8 txDataByte) 
    {
    #if (XBee_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint8 locTxBufferWrite;
        uint8 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((XBee_TX_BUFFER_SIZE > XBee_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            XBee_DisableTxInt();
        #endif /* (XBee_TX_BUFFER_SIZE > XBee_MAX_BYTE_VALUE) && (CY_PSOC3) */

            locTxBufferWrite = XBee_txBufferWrite;
            locTxBufferRead  = XBee_txBufferRead;

        #if ((XBee_TX_BUFFER_SIZE > XBee_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            XBee_EnableTxInt();
        #endif /* (XBee_TX_BUFFER_SIZE > XBee_MAX_BYTE_VALUE) && (CY_PSOC3) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint8)(XBee_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((XBee_TXSTATUS_REG & XBee_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            XBee_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= XBee_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            XBee_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((XBee_TX_BUFFER_SIZE > XBee_MAX_BYTE_VALUE) && (CY_PSOC3))
            XBee_DisableTxInt();
        #endif /* (XBee_TX_BUFFER_SIZE > XBee_MAX_BYTE_VALUE) && (CY_PSOC3) */

            XBee_txBufferWrite = locTxBufferWrite;

        #if ((XBee_TX_BUFFER_SIZE > XBee_MAX_BYTE_VALUE) && (CY_PSOC3))
            XBee_EnableTxInt();
        #endif /* (XBee_TX_BUFFER_SIZE > XBee_MAX_BYTE_VALUE) && (CY_PSOC3) */

            if(0u != (XBee_TXSTATUS_REG & XBee_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                XBee_SetPendingTxInt();
            }
        }

    #else

        while((XBee_TXSTATUS_REG & XBee_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        XBee_TXDATA_REG = txDataByte;

    #endif /* XBee_TX_INTERRUPT_ENABLED */
    }


    /*******************************************************************************
    * Function Name: XBee_PutString
    ********************************************************************************
    *
    * Summary:
    *  Sends a NULL terminated string to the TX buffer for transmission.
    *
    * Parameters:
    *  string[]: Pointer to the null terminated string array residing in RAM or ROM
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  XBee_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void XBee_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(XBee_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                XBee_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: XBee_PutArray
    ********************************************************************************
    *
    * Summary:
    *  Places N bytes of data from a memory array into the TX buffer for
    *  transmission.
    *
    * Parameters:
    *  string[]: Address of the memory array residing in RAM or ROM.
    *  byteCount: Number of bytes to be transmitted. The type depends on TX Buffer
    *             Size parameter.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  XBee_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void XBee_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(XBee_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                XBee_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: XBee_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Writes a byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) to the transmit buffer.
    *
    * Parameters:
    *  txDataByte: Data byte to transmit before the carriage return and line feed.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  XBee_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void XBee_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(XBee_initVar != 0u)
        {
            XBee_PutChar(txDataByte);
            XBee_PutChar(0x0Du);
            XBee_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: XBee_GetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of bytes in the TX buffer which are waiting to be 
    *  transmitted.
    *  * TX software buffer is disabled (TX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty TX FIFO, 1 for not full TX FIFO or 4 for full TX FIFO.
    *  * TX software buffer is enabled: returns the number of bytes in the TX 
    *    software buffer which are waiting to be transmitted. Bytes available in the
    *    TX FIFO do not count.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Number of bytes used in the TX buffer. Return value type depends on the TX 
    *  Buffer Size parameter.
    *
    * Global Variables:
    *  XBee_txBufferWrite - used to calculate left space.
    *  XBee_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 XBee_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (XBee_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        XBee_DisableTxInt();

        if(XBee_txBufferRead == XBee_txBufferWrite)
        {
            size = 0u;
        }
        else if(XBee_txBufferRead < XBee_txBufferWrite)
        {
            size = (XBee_txBufferWrite - XBee_txBufferRead);
        }
        else
        {
            size = (XBee_TX_BUFFER_SIZE - XBee_txBufferRead) +
                    XBee_txBufferWrite;
        }

        XBee_EnableTxInt();

    #else

        size = XBee_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & XBee_TX_STS_FIFO_FULL) != 0u)
        {
            size = XBee_FIFO_LENGTH;
        }
        else if((size & XBee_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (XBee_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: XBee_ClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears all data from the TX buffer and hardware TX FIFO.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  XBee_txBufferWrite - cleared to zero.
    *  XBee_txBufferRead - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may have
    *  remained in the RAM.
    *
    * Side Effects:
    *  Data waiting in the transmit buffer is not sent; a byte that is currently
    *  transmitting finishes transmitting.
    *
    *******************************************************************************/
    void XBee_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        XBee_TXDATA_AUX_CTL_REG |= (uint8)  XBee_TX_FIFO_CLR;
        XBee_TXDATA_AUX_CTL_REG &= (uint8) ~XBee_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (XBee_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        XBee_DisableTxInt();

        XBee_txBufferRead = 0u;
        XBee_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        XBee_EnableTxInt();

    #endif /* (XBee_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: XBee_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   XBee_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   XBee_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   XBee_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   XBee_SEND_WAIT_REINIT - Performs both options: 
    *      XBee_SEND_BREAK and XBee_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  XBee_initVar - checked to identify that the component has been
    *     initialized.
    *  txPeriod - static variable, used for keeping TX period configuration.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  SendBreak function initializes registers to send 13-bit break signal. It is
    *  important to return the registers configuration to normal for continue 8-bit
    *  operation.
    *  There are 3 variants for this API usage:
    *  1) SendBreak(3) - function will send the Break signal and take care on the
    *     configuration returning. Function will block CPU until transmission
    *     complete.
    *  2) User may want to use blocking time if UART configured to the low speed
    *     operation
    *     Example for this case:
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     SendBreak(1);     - complete Break operation
    *  3) Same to 2) but user may want to initialize and use the interrupt to
    *     complete break operation.
    *     Example for this case:
    *     Initialize TX interrupt with "TX - On TX Complete" parameter
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     When interrupt appear with XBee_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The XBee_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void XBee_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(XBee_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(XBee_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == XBee_SEND_BREAK) ||
                (retMode == XBee_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                XBee_WriteControlRegister(XBee_ReadControlRegister() |
                                                      XBee_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                XBee_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = XBee_TXSTATUS_REG;
                }
                while((tmpStat & XBee_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == XBee_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == XBee_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = XBee_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & XBee_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == XBee_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == XBee_REINIT) ||
                (retMode == XBee_SEND_WAIT_REINIT) )
            {
                XBee_WriteControlRegister(XBee_ReadControlRegister() &
                                              (uint8)~XBee_CTRL_HD_SEND_BREAK);
            }

        #else /* XBee_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == XBee_SEND_BREAK) ||
                (retMode == XBee_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (XBee_PARITY_TYPE != XBee__B_UART__NONE_REVB) || \
                                    (XBee_PARITY_TYPE_SW != 0u) )
                    XBee_WriteControlRegister(XBee_ReadControlRegister() |
                                                          XBee_CTRL_HD_SEND_BREAK);
                #endif /* End XBee_PARITY_TYPE != XBee__B_UART__NONE_REVB  */

                #if(XBee_TXCLKGEN_DP)
                    txPeriod = XBee_TXBITCLKTX_COMPLETE_REG;
                    XBee_TXBITCLKTX_COMPLETE_REG = XBee_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = XBee_TXBITCTR_PERIOD_REG;
                    XBee_TXBITCTR_PERIOD_REG = XBee_TXBITCTR_BREAKBITS8X;
                #endif /* End XBee_TXCLKGEN_DP */

                /* Send zeros */
                XBee_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = XBee_TXSTATUS_REG;
                }
                while((tmpStat & XBee_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == XBee_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == XBee_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = XBee_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & XBee_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == XBee_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == XBee_REINIT) ||
                (retMode == XBee_SEND_WAIT_REINIT) )
            {

            #if(XBee_TXCLKGEN_DP)
                XBee_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                XBee_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End XBee_TXCLKGEN_DP */

            #if( (XBee_PARITY_TYPE != XBee__B_UART__NONE_REVB) || \
                 (XBee_PARITY_TYPE_SW != 0u) )
                XBee_WriteControlRegister(XBee_ReadControlRegister() &
                                                      (uint8) ~XBee_CTRL_HD_SEND_BREAK);
            #endif /* End XBee_PARITY_TYPE != NONE */
            }
        #endif    /* End XBee_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: XBee_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       XBee_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       XBee_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears XBee_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void XBee_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( XBee_CONTROL_REG_REMOVED == 0u )
            XBee_WriteControlRegister(XBee_ReadControlRegister() |
                                                  XBee_CTRL_MARK);
        #endif /* End XBee_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( XBee_CONTROL_REG_REMOVED == 0u )
            XBee_WriteControlRegister(XBee_ReadControlRegister() &
                                                  (uint8) ~XBee_CTRL_MARK);
        #endif /* End XBee_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndXBee_TX_ENABLED */

#if(XBee_HD_ENABLED)


    /*******************************************************************************
    * Function Name: XBee_LoadRxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the receiver configuration in half duplex mode. After calling this
    *  function, the UART is ready to receive data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the transmitter
    *  configuration.
    *
    *******************************************************************************/
    void XBee_LoadRxConfig(void) 
    {
        XBee_WriteControlRegister(XBee_ReadControlRegister() &
                                                (uint8)~XBee_CTRL_HD_SEND);
        XBee_RXBITCTR_PERIOD_REG = XBee_HD_RXBITCTR_INIT;

    #if (XBee_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        XBee_SetRxInterruptMode(XBee_INIT_RX_INTERRUPTS_MASK);
    #endif /* (XBee_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: XBee_LoadTxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the transmitter configuration in half duplex mode. After calling this
    *  function, the UART is ready to transmit data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the receiver configuration.
    *
    *******************************************************************************/
    void XBee_LoadTxConfig(void) 
    {
    #if (XBee_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        XBee_SetRxInterruptMode(0u);
    #endif /* (XBee_RX_INTERRUPT_ENABLED) */

        XBee_WriteControlRegister(XBee_ReadControlRegister() | XBee_CTRL_HD_SEND);
        XBee_RXBITCTR_PERIOD_REG = XBee_HD_TXBITCTR_INIT;
    }

#endif  /* XBee_HD_ENABLED */


/* [] END OF FILE */
