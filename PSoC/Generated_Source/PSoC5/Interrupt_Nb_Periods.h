/*******************************************************************************
* File Name: Interrupt_Nb_Periods.h
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
#if !defined(CY_ISR_Interrupt_Nb_Periods_H)
#define CY_ISR_Interrupt_Nb_Periods_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Interrupt_Nb_Periods_Start(void);
void Interrupt_Nb_Periods_StartEx(cyisraddress address);
void Interrupt_Nb_Periods_Stop(void);

CY_ISR_PROTO(Interrupt_Nb_Periods_Interrupt);

void Interrupt_Nb_Periods_SetVector(cyisraddress address);
cyisraddress Interrupt_Nb_Periods_GetVector(void);

void Interrupt_Nb_Periods_SetPriority(uint8 priority);
uint8 Interrupt_Nb_Periods_GetPriority(void);

void Interrupt_Nb_Periods_Enable(void);
uint8 Interrupt_Nb_Periods_GetState(void);
void Interrupt_Nb_Periods_Disable(void);

void Interrupt_Nb_Periods_SetPending(void);
void Interrupt_Nb_Periods_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Interrupt_Nb_Periods ISR. */
#define Interrupt_Nb_Periods_INTC_VECTOR            ((reg32 *) Interrupt_Nb_Periods__INTC_VECT)

/* Address of the Interrupt_Nb_Periods ISR priority. */
#define Interrupt_Nb_Periods_INTC_PRIOR             ((reg8 *) Interrupt_Nb_Periods__INTC_PRIOR_REG)

/* Priority of the Interrupt_Nb_Periods interrupt. */
#define Interrupt_Nb_Periods_INTC_PRIOR_NUMBER      Interrupt_Nb_Periods__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Interrupt_Nb_Periods interrupt. */
#define Interrupt_Nb_Periods_INTC_SET_EN            ((reg32 *) Interrupt_Nb_Periods__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Interrupt_Nb_Periods interrupt. */
#define Interrupt_Nb_Periods_INTC_CLR_EN            ((reg32 *) Interrupt_Nb_Periods__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Interrupt_Nb_Periods interrupt state to pending. */
#define Interrupt_Nb_Periods_INTC_SET_PD            ((reg32 *) Interrupt_Nb_Periods__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Interrupt_Nb_Periods interrupt. */
#define Interrupt_Nb_Periods_INTC_CLR_PD            ((reg32 *) Interrupt_Nb_Periods__INTC_CLR_PD_REG)


#endif /* CY_ISR_Interrupt_Nb_Periods_H */


/* [] END OF FILE */
