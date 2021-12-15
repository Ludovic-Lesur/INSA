/*******************************************************************************
* File Name: Vref.h  
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

#if !defined(CY_VDAC8_Vref_H) 
#define CY_VDAC8_Vref_H

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
}Vref_backupStruct;

/* component init state */
extern uint8 Vref_initVar;


/***************************************
*        Function Prototypes 
***************************************/

void Vref_Start(void)           ;
void Vref_Stop(void)            ;
void Vref_SetSpeed(uint8 speed) ;
void Vref_SetRange(uint8 range) ;
void Vref_SetValue(uint8 value) ;
void Vref_DacTrim(void)         ;
void Vref_Init(void)            ;
void Vref_Enable(void)          ;
void Vref_SaveConfig(void)      ;
void Vref_RestoreConfig(void)   ;
void Vref_Sleep(void)           ;
void Vref_Wakeup(void)          ;


/***************************************
*            API Constants
***************************************/

/* SetRange constants */

#define Vref_RANGE_1V       0x00u
#define Vref_RANGE_4V       0x04u


/* Power setting for Start API  */
#define Vref_LOWSPEED       0x00u
#define Vref_HIGHSPEED      0x02u


/***************************************
*  Initialization Parameter Constants
***************************************/

 /* Default DAC range */
#define Vref_DEFAULT_RANGE    4u
 /* Default DAC speed */
#define Vref_DEFAULT_SPEED    2u
 /* Default Control */
#define Vref_DEFAULT_CNTL      0x00u
/* Default Strobe mode */
#define Vref_DEFAULT_STRB     0u
 /* Initial DAC value */
#define Vref_DEFAULT_DATA     200u
 /* Default Data Source */
#define Vref_DEFAULT_DATA_SRC 0u


/***************************************
*              Registers        
***************************************/
#define Vref_CR0_REG            (* (reg8 *) Vref_viDAC8__CR0 )
#define Vref_CR0_PTR            (  (reg8 *) Vref_viDAC8__CR0 )
#define Vref_CR1_REG            (* (reg8 *) Vref_viDAC8__CR1 )
#define Vref_CR1_PTR            (  (reg8 *) Vref_viDAC8__CR1 )
#define Vref_Data_REG           (* (reg8 *) Vref_viDAC8__D )
#define Vref_Data_PTR           (  (reg8 *) Vref_viDAC8__D )
#define Vref_Strobe_REG         (* (reg8 *) Vref_viDAC8__STROBE )
#define Vref_Strobe_PTR         (  (reg8 *) Vref_viDAC8__STROBE )
#define Vref_SW0_REG            (* (reg8 *) Vref_viDAC8__SW0 )
#define Vref_SW0_PTR            (  (reg8 *) Vref_viDAC8__SW0 )
#define Vref_SW2_REG            (* (reg8 *) Vref_viDAC8__SW2 )
#define Vref_SW2_PTR            (  (reg8 *) Vref_viDAC8__SW2 )
#define Vref_SW3_REG            (* (reg8 *) Vref_viDAC8__SW3 )
#define Vref_SW3_PTR            (  (reg8 *) Vref_viDAC8__SW3 )
#define Vref_SW4_REG            (* (reg8 *) Vref_viDAC8__SW4 )
#define Vref_SW4_PTR            (  (reg8 *) Vref_viDAC8__SW4 )
#define Vref_TR_REG             (* (reg8 *) Vref_viDAC8__TR )
#define Vref_TR_PTR             (  (reg8 *) Vref_viDAC8__TR )
/* Power manager */
#define Vref_PWRMGR_REG         (* (reg8 *) Vref_viDAC8__PM_ACT_CFG )
#define Vref_PWRMGR_PTR         (  (reg8 *) Vref_viDAC8__PM_ACT_CFG )
  /* Standby Power manager */
#define Vref_STBY_PWRMGR_REG    (* (reg8 *) Vref_viDAC8__PM_STBY_CFG )
#define Vref_STBY_PWRMGR_PTR    (  (reg8 *) Vref_viDAC8__PM_STBY_CFG )

/***************************************
*  Registers definitions
* for backward capability        
***************************************/
#define Vref_CR0         (* (reg8 *) Vref_viDAC8__CR0 )
#define Vref_CR1         (* (reg8 *) Vref_viDAC8__CR1 )
#define Vref_Data        (* (reg8 *) Vref_viDAC8__D )
#define Vref_Data_PTR    (  (reg8 *) Vref_viDAC8__D )
#define Vref_Strobe      (* (reg8 *) Vref_viDAC8__STROBE )
#define Vref_SW0         (* (reg8 *) Vref_viDAC8__SW0 )
#define Vref_SW2         (* (reg8 *) Vref_viDAC8__SW2 )
#define Vref_SW3         (* (reg8 *) Vref_viDAC8__SW3 )
#define Vref_SW4         (* (reg8 *) Vref_viDAC8__SW4 )
#define Vref_TR          (* (reg8 *) Vref_viDAC8__TR )
/* Power manager */
#define Vref_PWRMGR      (* (reg8 *) Vref_viDAC8__PM_ACT_CFG )
  /* Standby Power manager */
#define Vref_STBY_PWRMGR (* (reg8 *) Vref_viDAC8__PM_STBY_CFG )


/***************************************
*         Register Constants       
***************************************/

/* CR0 vDac Control Register 0 definitions */

/* Bit Field  DAC_HS_MODE                  */
#define Vref_HS_MASK        0x02u
#define Vref_HS_LOWPOWER    0x00u
#define Vref_HS_HIGHSPEED   0x02u

/* Bit Field  DAC_MODE                  */
#define Vref_MODE_MASK      0x10u
#define Vref_MODE_V         0x00u
#define Vref_MODE_I         0x10u

/* Bit Field  DAC_RANGE                  */
#define Vref_RANGE_MASK     0x0Cu
#define Vref_RANGE_0        0x00u
#define Vref_RANGE_1        0x04u

/* CR1 iDac Control Register 1 definitions */

/* Bit Field  DAC_MX_DATA                  */
#define Vref_SRC_MASK       0x20u
#define Vref_SRC_REG        0x00u
#define Vref_SRC_UDB        0x20u

/* This bit enable reset from UDB array      */
#define Vref_RESET_MASK     0x10u
#define Vref_RESET_ENABLE   0x10u
#define Vref_RESET_DISABLE  0x00u

/* This bit enables data from DAC bus      */
#define Vref_DACBUS_MASK     0x20u
#define Vref_DACBUS_ENABLE   0x20u
#define Vref_DACBUS_DISABLE  0x00u

/* DAC STROBE Strobe Control Register definitions */

/* Bit Field  DAC_MX_STROBE                  */
#define Vref_STRB_MASK     0x08u
#define Vref_STRB_EN       0x08u
#define Vref_STRB_DIS      0x00u

/* PM_ACT_CFG (Active Power Mode CFG Register)     */ 
#define Vref_ACT_PWR_EN   Vref_viDAC8__PM_ACT_MSK
  /* Standby Power enable mask */
#define Vref_STBY_PWR_EN  Vref_viDAC8__PM_STBY_MSK


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
#define Vref_TRIM_M7_1V_RNG_OFFSET  0x06u
#define Vref_TRIM_M8_4V_RNG_OFFSET  0x07u
/*Constatnt to set DAC in current mode and turnoff output */
#define Vref_CUR_MODE_OUT_OFF       0x1Eu 
#define Vref_DAC_TRIM_BASE          (Vref_viDAC8__TRIM__M1)

#endif /* CY_VDAC8_Vref_H  */


/* [] END OF FILE */


