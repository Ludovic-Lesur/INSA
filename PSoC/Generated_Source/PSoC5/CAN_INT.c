/*******************************************************************************
* File Name: CAN_INT.c
* Version 3.20
*
* Description:
*  This file contains the code that operates during the ADC_DelSig interrupt
*  service routine.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CAN.h"
#include "cyapicallbacks.h"


/*******************************************************************************
* Custom Declarations and Variables
* - add user include files, prototypes and variables between the following
*   #START and #END tags
*******************************************************************************/
/* `#START ADC_SYS_VAR`  */

/* `#END`  */

#if(CAN_IRQ_REMOVE == 0u)


    /*****************************************************************************
    * Function Name: CAN_ISR1
    ******************************************************************************
    *
    * Summary:
    *  Handle Interrupt Service Routine.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *
    *****************************************************************************/
    CY_ISR( CAN_ISR1)
    {
        #ifdef CAN_ISR1_ENTRY_CALLBACK
            CAN_ISR1_EntryCallback();
        #endif /* CAN_ISR1_ENTRY_CALLBACK */
        

        /**************************************************************************
        *  Custom Code
        *  - add user ISR code between the following #START and #END tags
        **************************************************************************/
        /* `#START MAIN_ADC_ISR1`  */

        /* `#END`  */
        
        /* Stop the conversion if conversion mode is single sample and resolution
        *  is above 16 bits.
        */
        #if(CAN_CFG1_RESOLUTION > 16 && \
            CAN_CFG1_CONV_MODE == CAN_MODE_SINGLE_SAMPLE)
            CAN_StopConvert();
            /* Software flag for checking conversion complete or not. Will be used when
            *  resolution is above 16 bits and conversion mode is single sample 
			*/
            CAN_convDone = CAN_DEC_CONV_DONE;
        #endif /* Single sample conversion mode with resolution above 16 bits */

        #ifdef CAN_ISR1_EXIT_CALLBACK
            CAN_ISR1_ExitCallback();
        #endif /* CAN_ISR1_EXIT_CALLBACK */
    }


    /*****************************************************************************
    * Function Name: CAN_ISR2
    ******************************************************************************
    *
    * Summary:
    *  Handle Interrupt Service Routine.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *
    *****************************************************************************/
    CY_ISR( CAN_ISR2)
    {
        #ifdef CAN_ISR2_ENTRY_CALLBACK
            CAN_ISR2_EntryCallback();
        #endif /* CAN_ISR2_ENTRY_CALLBACK */
        
        
        /***************************************************************************
        *  Custom Code
        *  - add user ISR code between the following #START and #END tags
        **************************************************************************/
        /* `#START MAIN_ADC_ISR2`  */

        /* `#END`  */

        /* Stop the conversion conversion mode is single sample and resolution
        *  is above 16 bits.
        */
        #if(CAN_CFG2_RESOLUTION > 16 && \
            CAN_CFG2_CONVMODE == CAN_MODE_SINGLE_SAMPLE)
            CAN_StopConvert();
            /* Software flag for checking conversion complete or not. Will be used when
            *   resolution is above 16 bits and conversion mode is single sample 
			*/
            CAN_convDone = CAN_DEC_CONV_DONE;
        #endif /* Single sample conversion mode with resolution above 16 bits */

        #ifdef CAN_ISR2_EXIT_CALLBACK
            CAN_ISR2_ExitCallback();
        #endif /* CAN_ISR2_EXIT_CALLBACK */
    }


    /*****************************************************************************
    * Function Name: CAN_ISR3
    ******************************************************************************
    *
    * Summary:
    *  Handle Interrupt Service Routine.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *
    *****************************************************************************/
    CY_ISR( CAN_ISR3)
    {
        #ifdef CAN_ISR3_ENTRY_CALLBACK
            CAN_ISR3_EntryCallback();
        #endif /* CAN_ISR3_ENTRY_CALLBACK */        

        
        /***************************************************************************
        *  Custom Code
        *  - add user ISR code between the following #START and #END tags
        **************************************************************************/
        /* `#START MAIN_ADC_ISR3`  */

        /* `#END`  */
        
        /* Stop the conversion if conversion mode is set to single sample and
        *  resolution is above 16 bits.
        */
        #if(CAN_CFG3_RESOLUTION > 16 && \
            CAN_CFG3_CONVMODE == CAN_MODE_SINGLE_SAMPLE)
            CAN_StopConvert();
            /* Software flag for checking conversion complete or not. Will be used when
            *  resolution is above 16 bits and conversion mode is single sample 
			*/
            CAN_convDone = CAN_DEC_CONV_DONE;
        #endif /* Single sample conversion mode with resolution above 16 bits */

        #ifdef CAN_ISR3_EXIT_CALLBACK
            CAN_ISR3_ExitCallback();
        #endif /* CAN_ISR3_EXIT_CALLBACK */        
    }


    /*****************************************************************************
    * Function Name: CAN_ISR4
    ******************************************************************************
    *
    * Summary:
    *  Handle Interrupt Service Routine.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Reentrant:
    *  No
    *
    *****************************************************************************/
    CY_ISR( CAN_ISR4)
    {
        #ifdef CAN_ISR4_ENTRY_CALLBACK
            CAN_ISR4_EntryCallback();
        #endif /* CAN_ISR4_ENTRY_CALLBACK */            

        
        /***************************************************************************
        *  Custom Code
        *  - add user ISR code between the following #START and #END tags
        **************************************************************************/
        /* `#START MAIN_ADC_ISR4`  */

        /* `#END`  */

        /* Stop the conversion if conversion mode is set to single sample and
        *  resolution is above 16 bits.
        */
        #if(CAN_CFG4_RESOLUTION > 16 && \
            CAN_CFG4_CONVMODE == CAN_MODE_SINGLE_SAMPLE)
            CAN_StopConvert();
            /* Software flag for checking conversion complete or not. Will be used when
            *  resolution is above 16 bits and conversion mode is single sample 
			*/
            CAN_convDone = CAN_DEC_CONV_DONE;
        #endif /* Single sample conversion mode with resolution above 16 bits */
        
        #ifdef CAN_ISR4_EXIT_CALLBACK
            CAN_ISR4_ExitCallback();
        #endif /* CAN_ISR4_EXIT_CALLBACK */            
    }

#endif   /* End CAN_IRQ_REMOVE */


/* [] END OF FILE */
