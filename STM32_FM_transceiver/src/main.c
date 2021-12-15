/*
 * main.c
 *
 * Author: Jean-Louis NOULLET.
 * Revision for BE Systèmes Communicants: Ludovic LESUR and Benjamin ROQUES.
 *
 */


/* Include */

#include "stm32f4xx.h"
#include "gpio.h"
#include "radioFM_rx.h"
#include "radioFM_tx.h"


/*
 * TIMERS CONFIGURATION.
 *
 * @param 	None.
 * @return	None.
 */
static void SysTick_Configuration(void) {
	RCC_ClocksTypeDef zeclocks ;
	RCC_GetClocksFreq(&zeclocks) ;

	// SysTick interrupt each 10 ms with SysTick Clock equal to (HCLK/8).
	if	(SysTick_Config((zeclocks.SYSCLK_Frequency/8)/100)) {
		while (1) ;
	}

	SysTick_CLKSourceConfig( SysTick_CLKSource_HCLK_Div8 ) ;
	NVIC_SetPriority( SysTick_IRQn, 14 ) ;
}


/*
 * USART2 INTERRUPT HANDLER.
 *
 * @param	None.
 * @return	None.
 */
void USART2_IRQHandler(void) {

	USART_ClearFlag(USART2, USART_FLAG_RXNE) ;

	// Run RX state machine.
	evolution_RX() ;
	actions_RX() ;
}


/*
 * TIMER INTERRUPT HANDLER.
 *
 * @param	None.
 * @return	None.
 */
void SysTick_Handler(void) {}


/*
 * MAIN FUNCTION.
 *
 * @param 	None.
 * @return	None.
 */
int main(void) {

	// Initialisations
	SystemInit() ;
	GPIO_InitRadio() ;
	USART_InitRadio(9600) ;
	initVariablesRX() ;
	initVariablesTX() ;

	// Recipient address
	setDestAddress(BROADCAST_ADDRESS) ;

	// Timers initialisation.
	SysTick_Configuration() ;

	// Radio interrupts.
	disableRX() ;
	disableTX() ;
	USART_ITConfig(USART2, USART_IT_TXE, DISABLE) ;

	// Main loop.
	while (1) {

		// Run TX state machine.
		evolution_TX() ;
		actions_TX() ;

		if (button_pressed == 1) {
			USART_ITConfig(USART2, USART_IT_RXNE, DISABLE) ;
		}
		else {
			USART_ITConfig(USART2, USART_IT_RXNE, ENABLE) ;
		}
	}
}
