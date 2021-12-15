/*******************************************************************************
* File Name: Interrupt_Receiver.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_Interrupt_Receiver_H)
#define CY_ISR_Interrupt_Receiver_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Interrupt_Receiver_Start(void);
void Interrupt_Receiver_StartEx(cyisraddress address);
void Interrupt_Receiver_Stop(void);

CY_ISR_PROTO(Interrupt_Receiver_Interrupt);

void Interrupt_Receiver_SetVector(cyisraddress address);
cyisraddress Interrupt_Receiver_GetVector(void);

void Interrupt_Receiver_SetPriority(uint8 priority);
uint8 Interrupt_Receiver_GetPriority(void);

void Interrupt_Receiver_Enable(void);
uint8 Interrupt_Receiver_GetState(void);
void Interrupt_Receiver_Disable(void);

void Interrupt_Receiver_SetPending(void);
void Interrupt_Receiver_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Interrupt_Receiver ISR. */
#define Interrupt_Receiver_INTC_VECTOR            ((reg32 *) Interrupt_Receiver__INTC_VECT)

/* Address of the Interrupt_Receiver ISR priority. */
#define Interrupt_Receiver_INTC_PRIOR             ((reg8 *) Interrupt_Receiver__INTC_PRIOR_REG)

/* Priority of the Interrupt_Receiver interrupt. */
#define Interrupt_Receiver_INTC_PRIOR_NUMBER      Interrupt_Receiver__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Interrupt_Receiver interrupt. */
#define Interrupt_Receiver_INTC_SET_EN            ((reg32 *) Interrupt_Receiver__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Interrupt_Receiver interrupt. */
#define Interrupt_Receiver_INTC_CLR_EN            ((reg32 *) Interrupt_Receiver__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Interrupt_Receiver interrupt state to pending. */
#define Interrupt_Receiver_INTC_SET_PD            ((reg32 *) Interrupt_Receiver__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Interrupt_Receiver interrupt. */
#define Interrupt_Receiver_INTC_CLR_PD            ((reg32 *) Interrupt_Receiver__INTC_CLR_PD_REG)


#endif /* CY_ISR_Interrupt_Receiver_H */


/* [] END OF FILE */
