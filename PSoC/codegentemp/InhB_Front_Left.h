/*******************************************************************************
* File Name: InhB_Front_Left.h  
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

#if !defined(CY_PINS_InhB_Front_Left_H) /* Pins InhB_Front_Left_H */
#define CY_PINS_InhB_Front_Left_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "InhB_Front_Left_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 InhB_Front_Left__PORT == 15 && ((InhB_Front_Left__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    InhB_Front_Left_Write(uint8 value);
void    InhB_Front_Left_SetDriveMode(uint8 mode);
uint8   InhB_Front_Left_ReadDataReg(void);
uint8   InhB_Front_Left_Read(void);
void    InhB_Front_Left_SetInterruptMode(uint16 position, uint16 mode);
uint8   InhB_Front_Left_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the InhB_Front_Left_SetDriveMode() function.
     *  @{
     */
        #define InhB_Front_Left_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define InhB_Front_Left_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define InhB_Front_Left_DM_RES_UP          PIN_DM_RES_UP
        #define InhB_Front_Left_DM_RES_DWN         PIN_DM_RES_DWN
        #define InhB_Front_Left_DM_OD_LO           PIN_DM_OD_LO
        #define InhB_Front_Left_DM_OD_HI           PIN_DM_OD_HI
        #define InhB_Front_Left_DM_STRONG          PIN_DM_STRONG
        #define InhB_Front_Left_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define InhB_Front_Left_MASK               InhB_Front_Left__MASK
#define InhB_Front_Left_SHIFT              InhB_Front_Left__SHIFT
#define InhB_Front_Left_WIDTH              1u

/* Interrupt constants */
#if defined(InhB_Front_Left__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in InhB_Front_Left_SetInterruptMode() function.
     *  @{
     */
        #define InhB_Front_Left_INTR_NONE      (uint16)(0x0000u)
        #define InhB_Front_Left_INTR_RISING    (uint16)(0x0001u)
        #define InhB_Front_Left_INTR_FALLING   (uint16)(0x0002u)
        #define InhB_Front_Left_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define InhB_Front_Left_INTR_MASK      (0x01u) 
#endif /* (InhB_Front_Left__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define InhB_Front_Left_PS                     (* (reg8 *) InhB_Front_Left__PS)
/* Data Register */
#define InhB_Front_Left_DR                     (* (reg8 *) InhB_Front_Left__DR)
/* Port Number */
#define InhB_Front_Left_PRT_NUM                (* (reg8 *) InhB_Front_Left__PRT) 
/* Connect to Analog Globals */                                                  
#define InhB_Front_Left_AG                     (* (reg8 *) InhB_Front_Left__AG)                       
/* Analog MUX bux enable */
#define InhB_Front_Left_AMUX                   (* (reg8 *) InhB_Front_Left__AMUX) 
/* Bidirectional Enable */                                                        
#define InhB_Front_Left_BIE                    (* (reg8 *) InhB_Front_Left__BIE)
/* Bit-mask for Aliased Register Access */
#define InhB_Front_Left_BIT_MASK               (* (reg8 *) InhB_Front_Left__BIT_MASK)
/* Bypass Enable */
#define InhB_Front_Left_BYP                    (* (reg8 *) InhB_Front_Left__BYP)
/* Port wide control signals */                                                   
#define InhB_Front_Left_CTL                    (* (reg8 *) InhB_Front_Left__CTL)
/* Drive Modes */
#define InhB_Front_Left_DM0                    (* (reg8 *) InhB_Front_Left__DM0) 
#define InhB_Front_Left_DM1                    (* (reg8 *) InhB_Front_Left__DM1)
#define InhB_Front_Left_DM2                    (* (reg8 *) InhB_Front_Left__DM2) 
/* Input Buffer Disable Override */
#define InhB_Front_Left_INP_DIS                (* (reg8 *) InhB_Front_Left__INP_DIS)
/* LCD Common or Segment Drive */
#define InhB_Front_Left_LCD_COM_SEG            (* (reg8 *) InhB_Front_Left__LCD_COM_SEG)
/* Enable Segment LCD */
#define InhB_Front_Left_LCD_EN                 (* (reg8 *) InhB_Front_Left__LCD_EN)
/* Slew Rate Control */
#define InhB_Front_Left_SLW                    (* (reg8 *) InhB_Front_Left__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define InhB_Front_Left_PRTDSI__CAPS_SEL       (* (reg8 *) InhB_Front_Left__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define InhB_Front_Left_PRTDSI__DBL_SYNC_IN    (* (reg8 *) InhB_Front_Left__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define InhB_Front_Left_PRTDSI__OE_SEL0        (* (reg8 *) InhB_Front_Left__PRTDSI__OE_SEL0) 
#define InhB_Front_Left_PRTDSI__OE_SEL1        (* (reg8 *) InhB_Front_Left__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define InhB_Front_Left_PRTDSI__OUT_SEL0       (* (reg8 *) InhB_Front_Left__PRTDSI__OUT_SEL0) 
#define InhB_Front_Left_PRTDSI__OUT_SEL1       (* (reg8 *) InhB_Front_Left__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define InhB_Front_Left_PRTDSI__SYNC_OUT       (* (reg8 *) InhB_Front_Left__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(InhB_Front_Left__SIO_CFG)
    #define InhB_Front_Left_SIO_HYST_EN        (* (reg8 *) InhB_Front_Left__SIO_HYST_EN)
    #define InhB_Front_Left_SIO_REG_HIFREQ     (* (reg8 *) InhB_Front_Left__SIO_REG_HIFREQ)
    #define InhB_Front_Left_SIO_CFG            (* (reg8 *) InhB_Front_Left__SIO_CFG)
    #define InhB_Front_Left_SIO_DIFF           (* (reg8 *) InhB_Front_Left__SIO_DIFF)
#endif /* (InhB_Front_Left__SIO_CFG) */

/* Interrupt Registers */
#if defined(InhB_Front_Left__INTSTAT)
    #define InhB_Front_Left_INTSTAT            (* (reg8 *) InhB_Front_Left__INTSTAT)
    #define InhB_Front_Left_SNAP               (* (reg8 *) InhB_Front_Left__SNAP)
    
	#define InhB_Front_Left_0_INTTYPE_REG 		(* (reg8 *) InhB_Front_Left__0__INTTYPE)
#endif /* (InhB_Front_Left__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_InhB_Front_Left_H */


/* [] END OF FILE */
