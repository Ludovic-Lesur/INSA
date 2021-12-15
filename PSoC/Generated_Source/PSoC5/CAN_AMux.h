/*******************************************************************************
* File Name: CAN_AMux.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_CAN_AMux_H)
#define CY_AMUX_CAN_AMux_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyfitter_cfg.h"


/***************************************
*        Function Prototypes
***************************************/

void CAN_AMux_Start(void) ;
#define CAN_AMux_Init() CAN_AMux_Start()
void CAN_AMux_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void CAN_AMux_Stop(void); */
/* void CAN_AMux_Select(uint8 channel); */
/* void CAN_AMux_Connect(uint8 channel); */
/* void CAN_AMux_Disconnect(uint8 channel); */
/* void CAN_AMux_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define CAN_AMux_CHANNELS  2u
#define CAN_AMux_MUXTYPE   1
#define CAN_AMux_ATMOSTONE 0

/***************************************
*             API Constants
***************************************/

#define CAN_AMux_NULL_CHANNEL 0xFFu
#define CAN_AMux_MUX_SINGLE   1
#define CAN_AMux_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if CAN_AMux_MUXTYPE == CAN_AMux_MUX_SINGLE
# if !CAN_AMux_ATMOSTONE
#  define CAN_AMux_Connect(channel) CAN_AMux_Set(channel)
# endif
# define CAN_AMux_Disconnect(channel) CAN_AMux_Unset(channel)
#else
# if !CAN_AMux_ATMOSTONE
void CAN_AMux_Connect(uint8 channel) ;
# endif
void CAN_AMux_Disconnect(uint8 channel) ;
#endif

#if CAN_AMux_ATMOSTONE
# define CAN_AMux_Stop() CAN_AMux_DisconnectAll()
# define CAN_AMux_Select(channel) CAN_AMux_FastSelect(channel)
void CAN_AMux_DisconnectAll(void) ;
#else
# define CAN_AMux_Stop() CAN_AMux_Start()
void CAN_AMux_Select(uint8 channel) ;
# define CAN_AMux_DisconnectAll() CAN_AMux_Start()
#endif

#endif /* CY_AMUX_CAN_AMux_H */


/* [] END OF FILE */
