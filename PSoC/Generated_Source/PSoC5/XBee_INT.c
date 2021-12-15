/*******************************************************************************
* File Name: XBeeINT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "XBee.h"
#include "cyapicallbacks.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (XBee_RX_INTERRUPT_ENABLED && (XBee_RX_ENABLED || XBee_HD_ENABLED))
    /*******************************************************************************
    * Function Name: XBee_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  XBee_rxBuffer - RAM buffer pointer for save received data.
    *  XBee_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  XBee_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  XBee_rxBufferOverflow - software overflow flag. Set to one
    *     when XBee_rxBufferWrite index overtakes
    *     XBee_rxBufferRead index.
    *  XBee_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when XBee_rxBufferWrite is equal to
    *    XBee_rxBufferRead
    *  XBee_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  XBee_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(XBee_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef XBee_RXISR_ENTRY_CALLBACK
        XBee_RXISR_EntryCallback();
    #endif /* XBee_RXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START XBee_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = XBee_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in XBee_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (XBee_RX_STS_BREAK | 
                            XBee_RX_STS_PAR_ERROR |
                            XBee_RX_STS_STOP_ERROR | 
                            XBee_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                XBee_errorStatus |= readStatus & ( XBee_RX_STS_BREAK | 
                                                            XBee_RX_STS_PAR_ERROR | 
                                                            XBee_RX_STS_STOP_ERROR | 
                                                            XBee_RX_STS_OVERRUN);
                /* `#START XBee_RXISR_ERROR` */

                /* `#END` */
                
            #ifdef XBee_RXISR_ERROR_CALLBACK
                XBee_RXISR_ERROR_Callback();
            #endif /* XBee_RXISR_ERROR_CALLBACK */
            }
            
            if((readStatus & XBee_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = XBee_RXDATA_REG;
            #if (XBee_RXHW_ADDRESS_ENABLED)
                if(XBee_rxAddressMode == (uint8)XBee__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & XBee_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & XBee_RX_STS_ADDR_MATCH) != 0u)
                        {
                            XBee_rxAddressDetected = 1u;
                        }
                        else
                        {
                            XBee_rxAddressDetected = 0u;
                        }
                    }
                    if(XBee_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        XBee_rxBuffer[XBee_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    XBee_rxBuffer[XBee_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                XBee_rxBuffer[XBee_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (XBee_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(XBee_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        XBee_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    XBee_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(XBee_rxBufferWrite >= XBee_RX_BUFFER_SIZE)
                    {
                        XBee_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(XBee_rxBufferWrite == XBee_rxBufferRead)
                    {
                        XBee_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (XBee_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            XBee_RXSTATUS_MASK_REG  &= (uint8)~XBee_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(XBee_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (XBee_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & XBee_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START XBee_RXISR_END` */

        /* `#END` */

    #ifdef XBee_RXISR_EXIT_CALLBACK
        XBee_RXISR_ExitCallback();
    #endif /* XBee_RXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }
    
#endif /* (XBee_RX_INTERRUPT_ENABLED && (XBee_RX_ENABLED || XBee_HD_ENABLED)) */


#if (XBee_TX_INTERRUPT_ENABLED && XBee_TX_ENABLED)
    /*******************************************************************************
    * Function Name: XBee_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  XBee_txBuffer - RAM buffer pointer for transmit data from.
    *  XBee_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  XBee_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(XBee_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

    #ifdef XBee_TXISR_ENTRY_CALLBACK
        XBee_TXISR_EntryCallback();
    #endif /* XBee_TXISR_ENTRY_CALLBACK */

        /* User code required at start of ISR */
        /* `#START XBee_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((XBee_txBufferRead != XBee_txBufferWrite) &&
             ((XBee_TXSTATUS_REG & XBee_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(XBee_txBufferRead >= XBee_TX_BUFFER_SIZE)
            {
                XBee_txBufferRead = 0u;
            }

            XBee_TXDATA_REG = XBee_txBuffer[XBee_txBufferRead];

            /* Set next pointer */
            XBee_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START XBee_TXISR_END` */

        /* `#END` */

    #ifdef XBee_TXISR_EXIT_CALLBACK
        XBee_TXISR_ExitCallback();
    #endif /* XBee_TXISR_EXIT_CALLBACK */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
   }
#endif /* (XBee_TX_INTERRUPT_ENABLED && XBee_TX_ENABLED) */


/* [] END OF FILE */
