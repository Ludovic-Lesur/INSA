/*******************************************************************************
* File Name: Interrupt_Xbee.h
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
#if !defined(CY_ISR_Interrupt_Xbee_H)
#define CY_ISR_Interrupt_Xbee_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Interrupt_Xbee_Start(void);
void Interrupt_Xbee_StartEx(cyisraddress address);
void Interrupt_Xbee_Stop(void);

CY_ISR_PROTO(Interrupt_Xbee_Interrupt);

void Interrupt_Xbee_SetVector(cyisraddress address);
cyisraddress Interrupt_Xbee_GetVector(void);

void Interrupt_Xbee_SetPriority(uint8 priority);
uint8 Interrupt_Xbee_GetPriority(void);

void Interrupt_Xbee_Enable(void);
uint8 Interrupt_Xbee_GetState(void);
void Interrupt_Xbee_Disable(void);

void Interrupt_Xbee_SetPending(void);
void Interrupt_Xbee_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Interrupt_Xbee ISR. */
#define Interrupt_Xbee_INTC_VECTOR            ((reg32 *) Interrupt_Xbee__INTC_VECT)

/* Address of the Interrupt_Xbee ISR priority. */
#define Interrupt_Xbee_INTC_PRIOR             ((reg8 *) Interrupt_Xbee__INTC_PRIOR_REG)

/* Priority of the Interrupt_Xbee interrupt. */
#define Interrupt_Xbee_INTC_PRIOR_NUMBER      Interrupt_Xbee__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Interrupt_Xbee interrupt. */
#define Interrupt_Xbee_INTC_SET_EN            ((reg32 *) Interrupt_Xbee__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Interrupt_Xbee interrupt. */
#define Interrupt_Xbee_INTC_CLR_EN            ((reg32 *) Interrupt_Xbee__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Interrupt_Xbee interrupt state to pending. */
#define Interrupt_Xbee_INTC_SET_PD            ((reg32 *) Interrupt_Xbee__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Interrupt_Xbee interrupt. */
#define Interrupt_Xbee_INTC_CLR_PD            ((reg32 *) Interrupt_Xbee__INTC_CLR_PD_REG)


#endif /* CY_ISR_Interrupt_Xbee_H */


/* [] END OF FILE */
