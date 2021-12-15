/*
 * radioFM_RX.c
 *
 * Authors: Ludovic LESUR and Benjamin ROQUES.
 *
 */


#include "radioFM_RX.h"


// RX state machine
enum state_rx current_state_RX ;
enum state_rx next_state_RX ;

// Reception
unsigned int received_byte ;
char buffer [SIZE_buffer] ;
char data_in [SIZE_buffer] ;
int nb_received_frames ; // Number of correct received frames.
char computedChecksumRX ;
char checksum_in ;


/**
 * INITIALISES EXTERN VARIABLES.
 *
 * @param		None.
 * @return	None.
 */
void initVariablesRX(void) {
	current_state_RX = init_RX ;
	next_state_RX = init_RX ;
	nb_received_frames = 0 ;
}


/**
 * UPDATES THE CURRENT STATE OF THE RX STATE MACHINE.
 *
 * @param		None.
 * @return	None.
 */
void evolution_RX(void) {

	next_state_RX = current_state_RX ; // Remaining in the same state by default.

	switch (current_state_RX) {

		case init_RX :
			if (received_byte == 0xFF) {
				next_state_RX = r1 ;
			}
			else {
				next_state_RX = init_RX ;
			}
			break ;

		case r1 :
			if (received_byte == MAGIC_NUMBER) {
				next_state_RX = r2 ;
			}
			else {
				if (received_byte != 0xFF) {
					next_state_RX = init_RX ;
				}
			}
			break ;

		case r2 :
			if ((received_byte == MY_ADDRESS) || (received_byte == BROADCAST_ADDRESS)) {
				next_state_RX = r3 ;
			}
			else {
				next_state_RX = init_RX ;
			}
			break ;

		case r3 :
			next_state_RX = r4 ;
			break ;

		case r4 :
			next_state_RX = r5 ;
			break ;

		case r5 :
			next_state_RX = r6 ;
			break ;

		case r6 :
			next_state_RX = r7 ;
			break ;

		case r7 :
			next_state_RX = r8 ;
			break ;

		case r8 :
			next_state_RX = init_RX ;
			break ;

		default :
			next_state_RX = init_RX ;
			break ;
	}

	// Updating state.
	current_state_RX = next_state_RX ;
}


/**
 * MAKES THE ACCURATE ACTIONS DEPENDING ON THE RX CURRENT STATE.
 *
 * @param		None.
 * @return	None.
 */
void actions_RX(void) {

	switch (current_state_RX) {

	case init_RX :
		received_byte = USART_ReceiveData(USART2) ; // Waiting for 0xFF.
		break ;

	case r1 :
		received_byte = USART_ReceiveData(USART2) ; // Waiting for MAGIC_NUMBER.
		break ;

	case r2 :
		received_byte = USART_ReceiveData(USART2) ; // Checking @dest
		break ;

	case r3 :
		buffer[INDICE_ADRESS_SOURCE] = USART_ReceiveData(USART2) ; // Temporary saving @source.
		break ;

	case r4 :
		buffer[INDICE_BYTE_1] = USART_ReceiveData(USART2) ; // Temporary saving first byte.
		break ;

	case r5 :
		buffer[INDICE_BYTE_2] = USART_ReceiveData(USART2) ; // Temporary saving second byte.
		break ;

	case r6 :
		buffer[INDICE_BYTE_3] = USART_ReceiveData(USART2) ; // Temporary saving third byte.
		break ;

	case r7 :
		buffer[INDICE_BYTE_4] = USART_ReceiveData(USART2) ; // Temporary saving fourth byte.
		break ;

	case r8 :
		checksum_in = USART_ReceiveData(USART2) ; // Temporary saving the checksum computed by the sender
		computeChecksumRX() ;
		if (checksum_in == computedChecksumRX) { // Checking checksum.
			int i = 0 ;
			GPIO_Led(1) ;
			for (i=0 ; i<5 ; i++){
					data_in[BYTES_PER_FRAME*nb_received_frames+i] = buffer[i] ;
			}
		}
		nb_received_frames++ ;
		break ;

	default :
		break ;
	}
}


/**
 * COMPUTES THE CHECKSUM ACCORDING TO THE RECEIVED DATAS.
 *
 * @param 	None.
 * @return	None.
 */
void computeChecksumRX(void) {
	int i ;
	for (i=1 ; i<=NUMBER_OF_DATA_BYTES ; i++) { // Start=1 because buffer[0]=@src.
		computedChecksumRX += buffer[i] ;
	}
	computedChecksumRX = (char)(computedChecksumRX % 255) ;
}
