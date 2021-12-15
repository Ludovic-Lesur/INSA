/*
 * usart.h
 *
 * Author: Jean-Louis NOULLET.
 * Revision for BE Systèmes Communicants: Ludovic LESUR and Benjamin ROQUES.
 *
 */


#ifndef USART_H
#define USART_H


#include "stm32f4xx_usart.h"
#include "stm32f4xx.h"


/* Functions prototypes */

void NVIC_InitRadio(IRQn_Type IRQn, int priority) ;
void USART_InitRadio(unsigned int bauds) ;


#endif
