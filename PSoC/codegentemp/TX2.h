/*******************************************************************************
* File Name: TX2.h  
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

#if !defined(CY_PINS_TX2_H) /* Pins TX2_H */
#define CY_PINS_TX2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TX2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 TX2__PORT == 15 && ((TX2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    TX2_Write(uint8 value);
void    TX2_SetDriveMode(uint8 mode);
uint8   TX2_ReadDataReg(void);
uint8   TX2_Read(void);
void    TX2_SetInterruptMode(uint16 position, uint16 mode);
uint8   TX2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the TX2_SetDriveMode() function.
     *  @{
     */
        #define TX2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define TX2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define TX2_DM_RES_UP          PIN_DM_RES_UP
        #define TX2_DM_RES_DWN         PIN_DM_RES_DWN
        #define TX2_DM_OD_LO           PIN_DM_OD_LO
        #define TX2_DM_OD_HI           PIN_DM_OD_HI
        #define TX2_DM_STRONG          PIN_DM_STRONG
        #define TX2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define TX2_MASK               TX2__MASK
#define TX2_SHIFT              TX2__SHIFT
#define TX2_WIDTH              1u

/* Interrupt constants */
#if defined(TX2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in TX2_SetInterruptMode() function.
     *  @{
     */
        #define TX2_INTR_NONE      (uint16)(0x0000u)
        #define TX2_INTR_RISING    (uint16)(0x0001u)
        #define TX2_INTR_FALLING   (uint16)(0x0002u)
        #define TX2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define TX2_INTR_MASK      (0x01u) 
#endif /* (TX2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TX2_PS                     (* (reg8 *) TX2__PS)
/* Data Register */
#define TX2_DR                     (* (reg8 *) TX2__DR)
/* Port Number */
#define TX2_PRT_NUM                (* (reg8 *) TX2__PRT) 
/* Connect to Analog Globals */                                                  
#define TX2_AG                     (* (reg8 *) TX2__AG)                       
/* Analog MUX bux enable */
#define TX2_AMUX                   (* (reg8 *) TX2__AMUX) 
/* Bidirectional Enable */                                                        
#define TX2_BIE                    (* (reg8 *) TX2__BIE)
/* Bit-mask for Aliased Register Access */
#define TX2_BIT_MASK               (* (reg8 *) TX2__BIT_MASK)
/* Bypass Enable */
#define TX2_BYP                    (* (reg8 *) TX2__BYP)
/* Port wide control signals */                                                   
#define TX2_CTL                    (* (reg8 *) TX2__CTL)
/* Drive Modes */
#define TX2_DM0                    (* (reg8 *) TX2__DM0) 
#define TX2_DM1                    (* (reg8 *) TX2__DM1)
#define TX2_DM2                    (* (reg8 *) TX2__DM2) 
/* Input Buffer Disable Override */
#define TX2_INP_DIS                (* (reg8 *) TX2__INP_DIS)
/* LCD Common or Segment Drive */
#define TX2_LCD_COM_SEG            (* (reg8 *) TX2__LCD_COM_SEG)
/* Enable Segment LCD */
#define TX2_LCD_EN                 (* (reg8 *) TX2__LCD_EN)
/* Slew Rate Control */
#define TX2_SLW                    (* (reg8 *) TX2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TX2_PRTDSI__CAPS_SEL       (* (reg8 *) TX2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TX2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TX2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TX2_PRTDSI__OE_SEL0        (* (reg8 *) TX2__PRTDSI__OE_SEL0) 
#define TX2_PRTDSI__OE_SEL1        (* (reg8 *) TX2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TX2_PRTDSI__OUT_SEL0       (* (reg8 *) TX2__PRTDSI__OUT_SEL0) 
#define TX2_PRTDSI__OUT_SEL1       (* (reg8 *) TX2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TX2_PRTDSI__SYNC_OUT       (* (reg8 *) TX2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(TX2__SIO_CFG)
    #define TX2_SIO_HYST_EN        (* (reg8 *) TX2__SIO_HYST_EN)
    #define TX2_SIO_REG_HIFREQ     (* (reg8 *) TX2__SIO_REG_HIFREQ)
    #define TX2_SIO_CFG            (* (reg8 *) TX2__SIO_CFG)
    #define TX2_SIO_DIFF           (* (reg8 *) TX2__SIO_DIFF)
#endif /* (TX2__SIO_CFG) */

/* Interrupt Registers */
#if defined(TX2__INTSTAT)
    #define TX2_INTSTAT            (* (reg8 *) TX2__INTSTAT)
    #define TX2_SNAP               (* (reg8 *) TX2__SNAP)
    
	#define TX2_0_INTTYPE_REG 		(* (reg8 *) TX2__0__INTTYPE)
#endif /* (TX2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_TX2_H */


/* [] END OF FILE */
