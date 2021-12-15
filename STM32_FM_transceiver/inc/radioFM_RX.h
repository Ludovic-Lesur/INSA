/*
 * radioFM_RX.h
 *
 * Authors: Ludovic LESUR and Benjamin ROQUES.
 *
 */


#ifndef RADIOFM_RX_H
#define RADIOFM_RX_H


#include "radioFM.h"
#include "usart.h"
#include "gpio.h"


/* Macro declaration */

// Array indices of input buffer.
#define INDICE_ADRESS_SOURCE 0
#define INDICE_BYTE_1 1
#define INDICE_BYTE_2 2
#define INDICE_BYTE_3 3
#define INDICE_BYTE_4 4

// RX state machine
enum state_rx {init_RX, r1, r2, r3, r4, r5, r6, r7, r8} ;
extern enum state_rx current_state_RX ;
extern enum state_rx next_state_RX ;

// Reception
extern unsigned int received_byte ;
extern char buffer [SIZE_buffer] ;
extern char data_in [SIZE_buffer] ;
extern int nb_received_frames ; // Number of correct received frames.
extern char computedChecksumRX ;
extern char checksum_in ;


/* Functions prototypes */

void initVariablesRX(void) ;
void evolution_RX(void) ;
void actions_RX(void) ;
void computeChecksumRX(void) ;



#endif
