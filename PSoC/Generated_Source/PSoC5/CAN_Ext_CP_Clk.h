/*******************************************************************************
* File Name: CAN_Ext_CP_Clk.h
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

#if !defined(CY_CLOCK_CAN_Ext_CP_Clk_H)
#define CY_CLOCK_CAN_Ext_CP_Clk_H

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

void CAN_Ext_CP_Clk_Start(void) ;
void CAN_Ext_CP_Clk_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void CAN_Ext_CP_Clk_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void CAN_Ext_CP_Clk_StandbyPower(uint8 state) ;
void CAN_Ext_CP_Clk_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 CAN_Ext_CP_Clk_GetDividerRegister(void) ;
void CAN_Ext_CP_Clk_SetModeRegister(uint8 modeBitMask) ;
void CAN_Ext_CP_Clk_ClearModeRegister(uint8 modeBitMask) ;
uint8 CAN_Ext_CP_Clk_GetModeRegister(void) ;
void CAN_Ext_CP_Clk_SetSourceRegister(uint8 clkSource) ;
uint8 CAN_Ext_CP_Clk_GetSourceRegister(void) ;
#if defined(CAN_Ext_CP_Clk__CFG3)
void CAN_Ext_CP_Clk_SetPhaseRegister(uint8 clkPhase) ;
uint8 CAN_Ext_CP_Clk_GetPhaseRegister(void) ;
#endif /* defined(CAN_Ext_CP_Clk__CFG3) */

#define CAN_Ext_CP_Clk_Enable()                       CAN_Ext_CP_Clk_Start()
#define CAN_Ext_CP_Clk_Disable()                      CAN_Ext_CP_Clk_Stop()
#define CAN_Ext_CP_Clk_SetDivider(clkDivider)         CAN_Ext_CP_Clk_SetDividerRegister(clkDivider, 1u)
#define CAN_Ext_CP_Clk_SetDividerValue(clkDivider)    CAN_Ext_CP_Clk_SetDividerRegister((clkDivider) - 1u, 1u)
#define CAN_Ext_CP_Clk_SetMode(clkMode)               CAN_Ext_CP_Clk_SetModeRegister(clkMode)
#define CAN_Ext_CP_Clk_SetSource(clkSource)           CAN_Ext_CP_Clk_SetSourceRegister(clkSource)
#if defined(CAN_Ext_CP_Clk__CFG3)
#define CAN_Ext_CP_Clk_SetPhase(clkPhase)             CAN_Ext_CP_Clk_SetPhaseRegister(clkPhase)
#define CAN_Ext_CP_Clk_SetPhaseValue(clkPhase)        CAN_Ext_CP_Clk_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(CAN_Ext_CP_Clk__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define CAN_Ext_CP_Clk_CLKEN              (* (reg8 *) CAN_Ext_CP_Clk__PM_ACT_CFG)
#define CAN_Ext_CP_Clk_CLKEN_PTR          ((reg8 *) CAN_Ext_CP_Clk__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define CAN_Ext_CP_Clk_CLKSTBY            (* (reg8 *) CAN_Ext_CP_Clk__PM_STBY_CFG)
#define CAN_Ext_CP_Clk_CLKSTBY_PTR        ((reg8 *) CAN_Ext_CP_Clk__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define CAN_Ext_CP_Clk_DIV_LSB            (* (reg8 *) CAN_Ext_CP_Clk__CFG0)
#define CAN_Ext_CP_Clk_DIV_LSB_PTR        ((reg8 *) CAN_Ext_CP_Clk__CFG0)
#define CAN_Ext_CP_Clk_DIV_PTR            ((reg16 *) CAN_Ext_CP_Clk__CFG0)

/* Clock MSB divider configuration register. */
#define CAN_Ext_CP_Clk_DIV_MSB            (* (reg8 *) CAN_Ext_CP_Clk__CFG1)
#define CAN_Ext_CP_Clk_DIV_MSB_PTR        ((reg8 *) CAN_Ext_CP_Clk__CFG1)

/* Mode and source configuration register */
#define CAN_Ext_CP_Clk_MOD_SRC            (* (reg8 *) CAN_Ext_CP_Clk__CFG2)
#define CAN_Ext_CP_Clk_MOD_SRC_PTR        ((reg8 *) CAN_Ext_CP_Clk__CFG2)

#if defined(CAN_Ext_CP_Clk__CFG3)
/* Analog clock phase configuration register */
#define CAN_Ext_CP_Clk_PHASE              (* (reg8 *) CAN_Ext_CP_Clk__CFG3)
#define CAN_Ext_CP_Clk_PHASE_PTR          ((reg8 *) CAN_Ext_CP_Clk__CFG3)
#endif /* defined(CAN_Ext_CP_Clk__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define CAN_Ext_CP_Clk_CLKEN_MASK         CAN_Ext_CP_Clk__PM_ACT_MSK
#define CAN_Ext_CP_Clk_CLKSTBY_MASK       CAN_Ext_CP_Clk__PM_STBY_MSK

/* CFG2 field masks */
#define CAN_Ext_CP_Clk_SRC_SEL_MSK        CAN_Ext_CP_Clk__CFG2_SRC_SEL_MASK
#define CAN_Ext_CP_Clk_MODE_MASK          (~(CAN_Ext_CP_Clk_SRC_SEL_MSK))

#if defined(CAN_Ext_CP_Clk__CFG3)
/* CFG3 phase mask */
#define CAN_Ext_CP_Clk_PHASE_MASK         CAN_Ext_CP_Clk__CFG3_PHASE_DLY_MASK
#endif /* defined(CAN_Ext_CP_Clk__CFG3) */

#endif /* CY_CLOCK_CAN_Ext_CP_Clk_H */


/* [] END OF FILE */
