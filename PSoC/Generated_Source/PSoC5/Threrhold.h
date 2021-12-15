/*******************************************************************************
* File Name: Threrhold.h  
* Version 1.90
*
*  Description:
*    This file contains the function prototypes and constants used in
*    the 8-bit Voltage DAC (vDAC8) User Module.
*
*   Note:
*     
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_VDAC8_Threrhold_H) 
#define CY_VDAC8_Threrhold_H

#include "cytypes.h"
#include "cyfitter.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component VDAC8_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/***************************************
*       Type defines
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState; 
    uint8 data_value;
}Threrhold_backupStruct;

/* component init state */
extern uint8 Threrhold_initVar;


/***************************************
*        Function Prototypes 
***************************************/

void Threrhold_Start(void)           ;
void Threrhold_Stop(void)            ;
void Threrhold_SetSpeed(uint8 speed) ;
void Threrhold_SetRange(uint8 range) ;
void Threrhold_SetValue(uint8 value) ;
void Threrhold_DacTrim(void)         ;
void Threrhold_Init(void)            ;
void Threrhold_Enable(void)          ;
void Threrhold_SaveConfig(void)      ;
void Threrhold_RestoreConfig(void)   ;
void Threrhold_Sleep(void)           ;
void Threrhold_Wakeup(void)          ;


/***************************************
*            API Constants
***************************************/

/* SetRange constants */

#define Threrhold_RANGE_1V       0x00u
#define Threrhold_RANGE_4V       0x04u


/* Power setting for Start API  */
#define Threrhold_LOWSPEED       0x00u
#define Threrhold_HIGHSPEED      0x02u


/***************************************
*  Initialization Parameter Constants
***************************************/

 /* Default DAC range */
#define Threrhold_DEFAULT_RANGE    4u
 /* Default DAC speed */
#define Threrhold_DEFAULT_SPEED    0u
 /* Default Control */
#define Threrhold_DEFAULT_CNTL      0x00u
/* Default Strobe mode */
#define Threrhold_DEFAULT_STRB     0u
 /* Initial DAC value */
#define Threrhold_DEFAULT_DATA     168u
 /* Default Data Source */
#define Threrhold_DEFAULT_DATA_SRC 0u


/***************************************
*              Registers        
***************************************/
#define Threrhold_CR0_REG            (* (reg8 *) Threrhold_viDAC8__CR0 )
#define Threrhold_CR0_PTR            (  (reg8 *) Threrhold_viDAC8__CR0 )
#define Threrhold_CR1_REG            (* (reg8 *) Threrhold_viDAC8__CR1 )
#define Threrhold_CR1_PTR            (  (reg8 *) Threrhold_viDAC8__CR1 )
#define Threrhold_Data_REG           (* (reg8 *) Threrhold_viDAC8__D )
#define Threrhold_Data_PTR           (  (reg8 *) Threrhold_viDAC8__D )
#define Threrhold_Strobe_REG         (* (reg8 *) Threrhold_viDAC8__STROBE )
#define Threrhold_Strobe_PTR         (  (reg8 *) Threrhold_viDAC8__STROBE )
#define Threrhold_SW0_REG            (* (reg8 *) Threrhold_viDAC8__SW0 )
#define Threrhold_SW0_PTR            (  (reg8 *) Threrhold_viDAC8__SW0 )
#define Threrhold_SW2_REG            (* (reg8 *) Threrhold_viDAC8__SW2 )
#define Threrhold_SW2_PTR            (  (reg8 *) Threrhold_viDAC8__SW2 )
#define Threrhold_SW3_REG            (* (reg8 *) Threrhold_viDAC8__SW3 )
#define Threrhold_SW3_PTR            (  (reg8 *) Threrhold_viDAC8__SW3 )
#define Threrhold_SW4_REG            (* (reg8 *) Threrhold_viDAC8__SW4 )
#define Threrhold_SW4_PTR            (  (reg8 *) Threrhold_viDAC8__SW4 )
#define Threrhold_TR_REG             (* (reg8 *) Threrhold_viDAC8__TR )
#define Threrhold_TR_PTR             (  (reg8 *) Threrhold_viDAC8__TR )
/* Power manager */
#define Threrhold_PWRMGR_REG         (* (reg8 *) Threrhold_viDAC8__PM_ACT_CFG )
#define Threrhold_PWRMGR_PTR         (  (reg8 *) Threrhold_viDAC8__PM_ACT_CFG )
  /* Standby Power manager */
#define Threrhold_STBY_PWRMGR_REG    (* (reg8 *) Threrhold_viDAC8__PM_STBY_CFG )
#define Threrhold_STBY_PWRMGR_PTR    (  (reg8 *) Threrhold_viDAC8__PM_STBY_CFG )

/***************************************
*  Registers definitions
* for backward capability        
***************************************/
#define Threrhold_CR0         (* (reg8 *) Threrhold_viDAC8__CR0 )
#define Threrhold_CR1         (* (reg8 *) Threrhold_viDAC8__CR1 )
#define Threrhold_Data        (* (reg8 *) Threrhold_viDAC8__D )
#define Threrhold_Data_PTR    (  (reg8 *) Threrhold_viDAC8__D )
#define Threrhold_Strobe      (* (reg8 *) Threrhold_viDAC8__STROBE )
#define Threrhold_SW0         (* (reg8 *) Threrhold_viDAC8__SW0 )
#define Threrhold_SW2         (* (reg8 *) Threrhold_viDAC8__SW2 )
#define Threrhold_SW3         (* (reg8 *) Threrhold_viDAC8__SW3 )
#define Threrhold_SW4         (* (reg8 *) Threrhold_viDAC8__SW4 )
#define Threrhold_TR          (* (reg8 *) Threrhold_viDAC8__TR )
/* Power manager */
#define Threrhold_PWRMGR      (* (reg8 *) Threrhold_viDAC8__PM_ACT_CFG )
  /* Standby Power manager */
#define Threrhold_STBY_PWRMGR (* (reg8 *) Threrhold_viDAC8__PM_STBY_CFG )


/***************************************
*         Register Constants       
***************************************/

/* CR0 vDac Control Register 0 definitions */

/* Bit Field  DAC_HS_MODE                  */
#define Threrhold_HS_MASK        0x02u
#define Threrhold_HS_LOWPOWER    0x00u
#define Threrhold_HS_HIGHSPEED   0x02u

/* Bit Field  DAC_MODE                  */
#define Threrhold_MODE_MASK      0x10u
#define Threrhold_MODE_V         0x00u
#define Threrhold_MODE_I         0x10u

/* Bit Field  DAC_RANGE                  */
#define Threrhold_RANGE_MASK     0x0Cu
#define Threrhold_RANGE_0        0x00u
#define Threrhold_RANGE_1        0x04u

/* CR1 iDac Control Register 1 definitions */

/* Bit Field  DAC_MX_DATA                  */
#define Threrhold_SRC_MASK       0x20u
#define Threrhold_SRC_REG        0x00u
#define Threrhold_SRC_UDB        0x20u

/* This bit enable reset from UDB array      */
#define Threrhold_RESET_MASK     0x10u
#define Threrhold_RESET_ENABLE   0x10u
#define Threrhold_RESET_DISABLE  0x00u

/* This bit enables data from DAC bus      */
#define Threrhold_DACBUS_MASK     0x20u
#define Threrhold_DACBUS_ENABLE   0x20u
#define Threrhold_DACBUS_DISABLE  0x00u

/* DAC STROBE Strobe Control Register definitions */

/* Bit Field  DAC_MX_STROBE                  */
#define Threrhold_STRB_MASK     0x08u
#define Threrhold_STRB_EN       0x08u
#define Threrhold_STRB_DIS      0x00u

/* PM_ACT_CFG (Active Power Mode CFG Register)     */ 
#define Threrhold_ACT_PWR_EN   Threrhold_viDAC8__PM_ACT_MSK
  /* Standby Power enable mask */
#define Threrhold_STBY_PWR_EN  Threrhold_viDAC8__PM_STBY_MSK


/*******************************************************************************
*              Trim    
* Note - VDAC trim values are stored in the "Customer Table" area in * Row 1 of
*the Hidden Flash.  There are 8 bytes of trim data for each VDAC block.
* The values are:
*       I Gain offset, min range, Sourcing
*       I Gain offset, min range, Sinking
*       I Gain offset, med range, Sourcing
*       I Gain offset, med range, Sinking
*       I Gain offset, max range, Sourcing
*       I Gain offset, max range, Sinking
*       V Gain offset, 1V range
*       V Gain offset, 4V range
*
* The data set for the 4 VDACs are arranged using a left side/right side
* approach:
*   Left 0, Left 1, Right 0, Right 1.
* When mapped to the VDAC0 thru VDAC3 as:
*   VDAC 0, VDAC 2, VDAC 1, VDAC 3
*******************************************************************************/
#define Threrhold_TRIM_M7_1V_RNG_OFFSET  0x06u
#define Threrhold_TRIM_M8_4V_RNG_OFFSET  0x07u
/*Constatnt to set DAC in current mode and turnoff output */
#define Threrhold_CUR_MODE_OUT_OFF       0x1Eu 
#define Threrhold_DAC_TRIM_BASE          (Threrhold_viDAC8__TRIM__M1)

#endif /* CY_VDAC8_Threrhold_H  */


/* [] END OF FILE */


