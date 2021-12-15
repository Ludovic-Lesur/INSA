/*******************************************************************************
* File Name: TX1.h  
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

#if !defined(CY_PINS_TX1_H) /* Pins TX1_H */
#define CY_PINS_TX1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TX1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TX1__PORT == 15 && ((TX1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    TX1_Write(uint8 value);
void    TX1_SetDriveMode(uint8 mode);
uint8   TX1_ReadDataReg(void);
uint8   TX1_Read(void);
void    TX1_SetInterruptMode(uint16 position, uint16 mode);
uint8   TX1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the TX1_SetDriveMode() function.
     *  @{
     */
        #define TX1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define TX1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define TX1_DM_RES_UP          PIN_DM_RES_UP
        #define TX1_DM_RES_DWN         PIN_DM_RES_DWN
        #define TX1_DM_OD_LO           PIN_DM_OD_LO
        #define TX1_DM_OD_HI           PIN_DM_OD_HI
        #define TX1_DM_STRONG          PIN_DM_STRONG
        #define TX1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define TX1_MASK               TX1__MASK
#define TX1_SHIFT              TX1__SHIFT
#define TX1_WIDTH              1u

/* Interrupt constants */
#if defined(TX1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in TX1_SetInterruptMode() function.
     *  @{
     */
        #define TX1_INTR_NONE      (uint16)(0x0000u)
        #define TX1_INTR_RISING    (uint16)(0x0001u)
        #define TX1_INTR_FALLING   (uint16)(0x0002u)
        #define TX1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define TX1_INTR_MASK      (0x01u) 
#endif /* (TX1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TX1_PS                     (* (reg8 *) TX1__PS)
/* Data Register */
#define TX1_DR                     (* (reg8 *) TX1__DR)
/* Port Number */
#define TX1_PRT_NUM                (* (reg8 *) TX1__PRT) 
/* Connect to Analog Globals */                                                  
#define TX1_AG                     (* (reg8 *) TX1__AG)                       
/* Analog MUX bux enable */
#define TX1_AMUX                   (* (reg8 *) TX1__AMUX) 
/* Bidirectional Enable */                                                        
#define TX1_BIE                    (* (reg8 *) TX1__BIE)
/* Bit-mask for Aliased Register Access */
#define TX1_BIT_MASK               (* (reg8 *) TX1__BIT_MASK)
/* Bypass Enable */
#define TX1_BYP                    (* (reg8 *) TX1__BYP)
/* Port wide control signals */                                                   
#define TX1_CTL                    (* (reg8 *) TX1__CTL)
/* Drive Modes */
#define TX1_DM0                    (* (reg8 *) TX1__DM0) 
#define TX1_DM1                    (* (reg8 *) TX1__DM1)
#define TX1_DM2                    (* (reg8 *) TX1__DM2) 
/* Input Buffer Disable Override */
#define TX1_INP_DIS                (* (reg8 *) TX1__INP_DIS)
/* LCD Common or Segment Drive */
#define TX1_LCD_COM_SEG            (* (reg8 *) TX1__LCD_COM_SEG)
/* Enable Segment LCD */
#define TX1_LCD_EN                 (* (reg8 *) TX1__LCD_EN)
/* Slew Rate Control */
#define TX1_SLW                    (* (reg8 *) TX1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TX1_PRTDSI__CAPS_SEL       (* (reg8 *) TX1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TX1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TX1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TX1_PRTDSI__OE_SEL0        (* (reg8 *) TX1__PRTDSI__OE_SEL0) 
#define TX1_PRTDSI__OE_SEL1        (* (reg8 *) TX1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TX1_PRTDSI__OUT_SEL0       (* (reg8 *) TX1__PRTDSI__OUT_SEL0) 
#define TX1_PRTDSI__OUT_SEL1       (* (reg8 *) TX1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TX1_PRTDSI__SYNC_OUT       (* (reg8 *) TX1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(TX1__SIO_CFG)
    #define TX1_SIO_HYST_EN        (* (reg8 *) TX1__SIO_HYST_EN)
    #define TX1_SIO_REG_HIFREQ     (* (reg8 *) TX1__SIO_REG_HIFREQ)
    #define TX1_SIO_CFG            (* (reg8 *) TX1__SIO_CFG)
    #define TX1_SIO_DIFF           (* (reg8 *) TX1__SIO_DIFF)
#endif /* (TX1__SIO_CFG) */

/* Interrupt Registers */
#if defined(TX1__INTSTAT)
    #define TX1_INTSTAT            (* (reg8 *) TX1__INTSTAT)
    #define TX1_SNAP               (* (reg8 *) TX1__SNAP)
    
	#define TX1_0_INTTYPE_REG 		(* (reg8 *) TX1__0__INTTYPE)
#endif /* (TX1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TX1_H */


/* [] END OF FILE */
