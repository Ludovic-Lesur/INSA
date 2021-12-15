/*
 * gpio.c
 *
 * Author: Jean-Louis NOULLET.
 * Revision for BE Systèmes Communicants: Ludovic LESUR and Benjamin ROQUES.
 *
 */


#include "gpio.h"


/**
 * CONFIGURES LED AND BUTTON PINS.
 *
 * @param	None.
 * @return	None.
 */
void GPIO_InitRadio() {

	// Enables GPIOC clock.
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE) ;

	// GPIO initialisation structure used to configure pins.
	GPIO_InitTypeDef gpio ;
	GPIO_StructInit(&gpio) ;

	// Configure LED pin PC10 as output.
	gpio.GPIO_Pin = N_LED ;
	gpio.GPIO_Mode = GPIO_Mode_OUT ;
	GPIO_Init(P_LED, &gpio) ;

	// Configure button pin PC12 as pulled-up input.
	gpio.GPIO_Pin = N_Button ;
	gpio.GPIO_Mode = GPIO_Mode_IN ;
	gpio.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(P_Button, &gpio) ;
}


/**
 * READ THE BUTTON STATE.
 *
 * @param	None.
 * @return	'1' if the button is pressed.
 * 			'0' otherwiser.
 */
int GPIO_ButtonTX() {
	return (GPIO_ReadInputDataBit(P_Button, N_Button) == 0) ;
}


/**
 * SWITCHES ON AND OFF THE LED.
 *
 * @param state	'0' to switch off the LED.
 * 				'1' to switch on the LED.
 * @return		None.
 */
void GPIO_Led(int state) {
	if (state == 0) {
		GPIO_ResetBits(P_LED, N_LED) ;
	}
	else {
		GPIO_SetBits(P_LED, N_LED) ;
	}
}


/**
 * ENABLES RADIO EMISSION (HARDWARE).
 *
 * @param 	None.
 * @return	None.
 */
void enableTX(void) {
	GPIO_SetBits(P_TX, N_TX) ;
}


/**
 * DISABLES RADIO EMISSION (HARDWARE).
 *
 * @param 	None.
 * @return	None.
 */
void disableTX(void) {
	GPIO_ResetBits(P_TX, N_TX) ;
}


/**
 * ENABLES RADIO RECEPTION (HARDWARE).
 *
 * @param 	None.
 * @return	None.
 */
void enableRX(void) {
	GPIO_SetBits(P_RX, N_RX) ;
}


/**
 * DISABLES RADIO RECEPTION (HARDWARE).
 *
 * @param 	None.
 * @return	None.
 */
void disableRX(void) {
	GPIO_ResetBits(P_RX, N_RX) ;
}
