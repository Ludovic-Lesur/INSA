/*******************************************************************************
* File Name: Reset_Chronometer.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_Reset_Chronometer_H) /* CY_CONTROL_REG_Reset_Chronometer_H */
#define CY_CONTROL_REG_Reset_Chronometer_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} Reset_Chronometer_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    Reset_Chronometer_Write(uint8 control) ;
uint8   Reset_Chronometer_Read(void) ;

void Reset_Chronometer_SaveConfig(void) ;
void Reset_Chronometer_RestoreConfig(void) ;
void Reset_Chronometer_Sleep(void) ; 
void Reset_Chronometer_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define Reset_Chronometer_Control        (* (reg8 *) Reset_Chronometer_Sync_ctrl_reg__CONTROL_REG )
#define Reset_Chronometer_Control_PTR    (  (reg8 *) Reset_Chronometer_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_Reset_Chronometer_H */


/* [] END OF FILE */
