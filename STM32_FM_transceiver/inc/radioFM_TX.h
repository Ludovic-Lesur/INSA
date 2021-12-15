/*
 * radioFM_TX.h
 *
 * Authors: Ludovic LESUR and Benjamin ROQUES.
 *
 */


#ifndef RADIOFM_TX_H
#define RADIOFM_TX_H


#include "radioFM.h"
#include "usart.h"
#include "gpio.h"

// Emission
extern char data_out[NUMBER_OF_DATA_BYTES] ;
extern int button_pressed ;

// Commun
extern char dest_adress ;
extern char computedChecksumTX ;

// TX state machine
enum state_tx {init_TX, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12} ;
extern enum state_tx current_state_TX ;
extern enum state_tx next_state_TX ;


/* Functions prototypes */

void initVariablesTX(void) ;
void setDestAddress(int newAddr) ;
void evolution_TX(void) ;
void actions_TX(void) ;
void computeChecksumTX(void) ;


#endif
