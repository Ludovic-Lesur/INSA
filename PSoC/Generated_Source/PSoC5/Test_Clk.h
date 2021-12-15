/*******************************************************************************
* File Name: Test_Clk.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Test_Clk_H) /* Pins Test_Clk_H */
#define CY_PINS_Test_Clk_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Test_Clk_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Test_Clk__PORT == 15 && ((Test_Clk__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Test_Clk_Write(uint8 value);
void    Test_Clk_SetDriveMode(uint8 mode);
uint8   Test_Clk_ReadDataReg(void);
uint8   Test_Clk_Read(void);
void    Test_Clk_SetInterruptMode(uint16 position, uint16 mode);
uint8   Test_Clk_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Test_Clk_SetDriveMode() function.
     *  @{
     */
        #define Test_Clk_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Test_Clk_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Test_Clk_DM_RES_UP          PIN_DM_RES_UP
        #define Test_Clk_DM_RES_DWN         PIN_DM_RES_DWN
        #define Test_Clk_DM_OD_LO           PIN_DM_OD_LO
        #define Test_Clk_DM_OD_HI           PIN_DM_OD_HI
        #define Test_Clk_DM_STRONG          PIN_DM_STRONG
        #define Test_Clk_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Test_Clk_MASK               Test_Clk__MASK
#define Test_Clk_SHIFT              Test_Clk__SHIFT
#define Test_Clk_WIDTH              1u

/* Interrupt constants */
#if defined(Test_Clk__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Test_Clk_SetInterruptMode() function.
     *  @{
     */
        #define Test_Clk_INTR_NONE      (uint16)(0x0000u)
        #define Test_Clk_INTR_RISING    (uint16)(0x0001u)
        #define Test_Clk_INTR_FALLING   (uint16)(0x0002u)
        #define Test_Clk_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Test_Clk_INTR_MASK      (0x01u) 
#endif /* (Test_Clk__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Test_Clk_PS                     (* (reg8 *) Test_Clk__PS)
/* Data Register */
#define Test_Clk_DR                     (* (reg8 *) Test_Clk__DR)
/* Port Number */
#define Test_Clk_PRT_NUM                (* (reg8 *) Test_Clk__PRT) 
/* Connect to Analog Globals */                                                  
#define Test_Clk_AG                     (* (reg8 *) Test_Clk__AG)                       
/* Analog MUX bux enable */
#define Test_Clk_AMUX                   (* (reg8 *) Test_Clk__AMUX) 
/* Bidirectional Enable */                                                        
#define Test_Clk_BIE                    (* (reg8 *) Test_Clk__BIE)
/* Bit-mask for Aliased Register Access */
#define Test_Clk_BIT_MASK               (* (reg8 *) Test_Clk__BIT_MASK)
/* Bypass Enable */
#define Test_Clk_BYP                    (* (reg8 *) Test_Clk__BYP)
/* Port wide control signals */                                                   
#define Test_Clk_CTL                    (* (reg8 *) Test_Clk__CTL)
/* Drive Modes */
#define Test_Clk_DM0                    (* (reg8 *) Test_Clk__DM0) 
#define Test_Clk_DM1                    (* (reg8 *) Test_Clk__DM1)
#define Test_Clk_DM2                    (* (reg8 *) Test_Clk__DM2) 
/* Input Buffer Disable Override */
#define Test_Clk_INP_DIS                (* (reg8 *) Test_Clk__INP_DIS)
/* LCD Common or Segment Drive */
#define Test_Clk_LCD_COM_SEG            (* (reg8 *) Test_Clk__LCD_COM_SEG)
/* Enable Segment LCD */
#define Test_Clk_LCD_EN                 (* (reg8 *) Test_Clk__LCD_EN)
/* Slew Rate Control */
#define Test_Clk_SLW                    (* (reg8 *) Test_Clk__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Test_Clk_PRTDSI__CAPS_SEL       (* (reg8 *) Test_Clk__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Test_Clk_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Test_Clk__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Test_Clk_PRTDSI__OE_SEL0        (* (reg8 *) Test_Clk__PRTDSI__OE_SEL0) 
#define Test_Clk_PRTDSI__OE_SEL1        (* (reg8 *) Test_Clk__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Test_Clk_PRTDSI__OUT_SEL0       (* (reg8 *) Test_Clk__PRTDSI__OUT_SEL0) 
#define Test_Clk_PRTDSI__OUT_SEL1       (* (reg8 *) Test_Clk__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Test_Clk_PRTDSI__SYNC_OUT       (* (reg8 *) Test_Clk__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Test_Clk__SIO_CFG)
    #define Test_Clk_SIO_HYST_EN        (* (reg8 *) Test_Clk__SIO_HYST_EN)
    #define Test_Clk_SIO_REG_HIFREQ     (* (reg8 *) Test_Clk__SIO_REG_HIFREQ)
    #define Test_Clk_SIO_CFG            (* (reg8 *) Test_Clk__SIO_CFG)
    #define Test_Clk_SIO_DIFF           (* (reg8 *) Test_Clk__SIO_DIFF)
#endif /* (Test_Clk__SIO_CFG) */

/* Interrupt Registers */
#if defined(Test_Clk__INTSTAT)
    #define Test_Clk_INTSTAT            (* (reg8 *) Test_Clk__INTSTAT)
    #define Test_Clk_SNAP               (* (reg8 *) Test_Clk__SNAP)
    
	#define Test_Clk_0_INTTYPE_REG 		(* (reg8 *) Test_Clk__0__INTTYPE)
#endif /* (Test_Clk__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Test_Clk_H */


/* [] END OF FILE */
