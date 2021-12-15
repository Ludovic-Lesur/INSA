/*
 * gpio.h
 *
 * Author: Jean-Louis NOULLET.
 * Revision for BE Systèmes Communicants: Ludovic LESUR and Benjamin ROQUES.
 *
 */


#ifndef GPIO_H
#define GPIO_H


#include "stm32f4xx_gpio.h"


// Hardware enable and disable
#define P_RX 0
#define N_RX 0
#define P_TX 0
#define N_TX 0

// Button and LED
#define P_LED GPIOC
#define N_LED GPIO_Pin_10
#define P_Button GPIOC
#define N_Button GPIO_Pin_12


/* Functions prototypes */

void GPIO_InitRadio() ;
int GPIO_ButtonTX() ;
void GPIO_Led(int state) ;
void enableTX(void) ;
void disableTX(void) ;
void enableRX(void) ;
void disableRX(void) ;


#endif
