/*******************************************************************************
* File Name: Clk.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Clk_H)
#define CY_CLOCK_Clk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void Clk_Start(void) ;
void Clk_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Clk_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Clk_StandbyPower(uint8 state) ;
void Clk_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Clk_GetDividerRegister(void) ;
void Clk_SetModeRegister(uint8 modeBitMask) ;
void Clk_ClearModeRegister(uint8 modeBitMask) ;
uint8 Clk_GetModeRegister(void) ;
void Clk_SetSourceRegister(uint8 clkSource) ;
uint8 Clk_GetSourceRegister(void) ;
#if defined(Clk__CFG3)
void Clk_SetPhaseRegister(uint8 clkPhase) ;
uint8 Clk_GetPhaseRegister(void) ;
#endif /* defined(Clk__CFG3) */

#define Clk_Enable()                       Clk_Start()
#define Clk_Disable()                      Clk_Stop()
#define Clk_SetDivider(clkDivider)         Clk_SetDividerRegister(clkDivider, 1u)
#define Clk_SetDividerValue(clkDivider)    Clk_SetDividerRegister((clkDivider) - 1u, 1u)
#define Clk_SetMode(clkMode)               Clk_SetModeRegister(clkMode)
#define Clk_SetSource(clkSource)           Clk_SetSourceRegister(clkSource)
#if defined(Clk__CFG3)
#define Clk_SetPhase(clkPhase)             Clk_SetPhaseRegister(clkPhase)
#define Clk_SetPhaseValue(clkPhase)        Clk_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(Clk__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Clk_CLKEN              (* (reg8 *) Clk__PM_ACT_CFG)
#define Clk_CLKEN_PTR          ((reg8 *) Clk__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Clk_CLKSTBY            (* (reg8 *) Clk__PM_STBY_CFG)
#define Clk_CLKSTBY_PTR        ((reg8 *) Clk__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Clk_DIV_LSB            (* (reg8 *) Clk__CFG0)
#define Clk_DIV_LSB_PTR        ((reg8 *) Clk__CFG0)
#define Clk_DIV_PTR            ((reg16 *) Clk__CFG0)

/* Clock MSB divider configuration register. */
#define Clk_DIV_MSB            (* (reg8 *) Clk__CFG1)
#define Clk_DIV_MSB_PTR        ((reg8 *) Clk__CFG1)

/* Mode and source configuration register */
#define Clk_MOD_SRC            (* (reg8 *) Clk__CFG2)
#define Clk_MOD_SRC_PTR        ((reg8 *) Clk__CFG2)

#if defined(Clk__CFG3)
/* Analog clock phase configuration register */
#define Clk_PHASE              (* (reg8 *) Clk__CFG3)
#define Clk_PHASE_PTR          ((reg8 *) Clk__CFG3)
#endif /* defined(Clk__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Clk_CLKEN_MASK         Clk__PM_ACT_MSK
#define Clk_CLKSTBY_MASK       Clk__PM_STBY_MSK

/* CFG2 field masks */
#define Clk_SRC_SEL_MSK        Clk__CFG2_SRC_SEL_MASK
#define Clk_MODE_MASK          (~(Clk_SRC_SEL_MSK))

#if defined(Clk__CFG3)
/* CFG3 phase mask */
#define Clk_PHASE_MASK         Clk__CFG3_PHASE_DLY_MASK
#endif /* defined(Clk__CFG3) */

#endif /* CY_CLOCK_Clk_H */


/* [] END OF FILE */
