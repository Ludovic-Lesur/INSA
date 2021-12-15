/*******************************************************************************
* File Name: Reset_Counter.h  
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

#if !defined(CY_CONTROL_REG_Reset_Counter_H) /* CY_CONTROL_REG_Reset_Counter_H */
#define CY_CONTROL_REG_Reset_Counter_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} Reset_Counter_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    Reset_Counter_Write(uint8 control) ;
uint8   Reset_Counter_Read(void) ;

void Reset_Counter_SaveConfig(void) ;
void Reset_Counter_RestoreConfig(void) ;
void Reset_Counter_Sleep(void) ; 
void Reset_Counter_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define Reset_Counter_Control        (* (reg8 *) Reset_Counter_Sync_ctrl_reg__CONTROL_REG )
#define Reset_Counter_Control_PTR    (  (reg8 *) Reset_Counter_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_Reset_Counter_H */


/* [] END OF FILE */
