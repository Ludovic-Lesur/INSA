/*
 * radioFM_TX.c
 *
 * Authors: Ludovic LESUR and Benjamin ROQUES.
 *
 */


#include "radioFM_TX.h"


// TX state machine
enum state_tx current_state_TX ;
enum state_tx next_state_TX ;

// Emission
char data_out[NUMBER_OF_DATA_BYTES] ;
int button_pressed ;
char dest_adress ;
char computedChecksumTX ;


/**
 * INITIALISES EXTERN VARIABLES.
 *
 * @param		None.
 * @return	None.
 */
void initVariablesTX(void) {
	current_state_TX = init_TX ;
	next_state_TX = init_TX ;
	button_pressed = 0 ;
	data_out[0] = 0x05 ;
	data_out[1] = 0x05 ;
	data_out[2] = 0x05 ;
	data_out[3] = 0x05 ;
}


/**
 * SETS THE DESTINATION ADDRESS.
 *
 * @param	newAddr		New recipient address of type 'int' (between 0x01 and 0x3F).
 * @return					None.
 */
void setDestAddress(int newAddr) {
	dest_adress = newAddr ;
}


/**
 * UPDATES THE CURRENT STATE OF THE TX STATE MACHINE.
 *
 * @param		None.
 * @return	None.
 */
void evolution_TX() {

	next_state_TX = current_state_TX ; // Remaining in the same state by default.

	switch (current_state_TX) {

		case init_TX :
			if (GPIO_ButtonTX()) {
				disableRX() ;
				enableTX() ;
				next_state_TX = t1 ;
				button_pressed = 1 ;
			}
			else {
				disableTX() ;
				enableRX() ;
				button_pressed = 0 ;
			}
			break ;

		case t1 :
			next_state_TX = t2 ;
			break ;

		case t2 :
			next_state_TX = t3 ;
			break ;

		case t3 :
			next_state_TX = t4 ;
			break ;

		case t4 :
			next_state_TX = t5 ;
			break ;

		case t5 :
			next_state_TX = t6 ;
			break ;

		case t6 :
			next_state_TX = t7 ;
			break ;

		case t7 :
			next_state_TX = t8 ;
			break ;

		case t8 :
			next_state_TX = t9 ;
			break ;

		case t9 :
			next_state_TX = t10 ;
			break ;

		case t10 :
			next_state_TX = t11 ;
			break ;

		case t11 :
			next_state_TX = t12 ;
			break ;

		case t12 :
			next_state_TX = init_TX ;
			break ;

		default :
			next_state_TX = init_TX ;
			break ;
	}

	// Updating state.
	current_state_TX = next_state_TX ;
}


/**
 * MAKES THE ACCURATE ACTIONS DEPENDING ON THE TX CURRENT STATE.
 *
 * @param		None.
 * @return	None.
 */
void actions_TX() {

	switch (current_state_TX) {

		case init_TX :
			break ;

		// TX actions.
		case t1 :
			USART_SendData(USART2, 0xFF) ;
			break ;

		case t2 :
			USART_SendData(USART2, 0xFF) ;
			break ;

		case t3 :
			USART_SendData(USART2, 0xFF) ;
			break ;

		case t4 :
			USART_SendData(USART2, MAGIC_NUMBER) ;
			break ;

		case t5 :
			USART_SendData(USART2, dest_adress) ;
			break ;

		case t6 :
			USART_SendData(USART2, MY_ADDRESS) ;
			break ;

		case t7 :
			USART_SendData(USART2, data_out[0]) ;
			break ;

		case t8 :
			USART_SendData(USART2, data_out[1]) ;
			break ;

		case t9 :
			USART_SendData(USART2, data_out[2]) ;
			break ;

		case t10 :
			USART_SendData(USART2, data_out[3]) ;
			break ;

		case t11 :
			computeChecksumTX() ;
			break ;

		case t12 :
			USART_SendData(USART2, computedChecksumTX) ;
			break ;

		default :
			break ;
	}
}


/**
 * COMPUTES THE CHECKSUM OF THE DATAS TO SEND.
 *
 * @param 	None.
 * @return	None.
 */
void computeChecksumTX(void) {
	int i = 0 ;
	for (i=0 ; i<NUMBER_OF_DATA_BYTES ; i++) {
		computedChecksumTX += data_out[i] ;
	}
	computedChecksumTX = (char) (computedChecksumTX % 255) ;
}
