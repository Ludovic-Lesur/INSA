/*
 * usart.c
 *
 * Author: Jean-Louis NOULLET.
 * Revision for BE Systèmes Communicants: Ludovic LESUR and Benjamin ROQUES.
 *
 */


#include "usart.h"


/**
 * INITIALISES RADIO INTERRUPT.
 *
 * @param IRQn		Interrupt source.
 * @param priority	Priority of the interrupt.
 * @return			None.
 */
void NVIC_InitRadio(IRQn_Type IRQn, int priority) {
	NVIC_InitTypeDef NVIC_InitStructure ;
	// PriorityGroup_4 => 15 niveaux de preemption, 0 niveau de subgrouping */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4) ;
	NVIC_InitStructure.NVIC_IRQChannel = IRQn ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = priority ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0 ;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE ;
	NVIC_Init(&NVIC_InitStructure) ;
}


/**
 * INITIALISES USART2 LINKED TO THE FM TRANSCEIVER.
 *
 * @param bauds		Baud rate in baud.second.
 * @return			None.
 */
void USART_InitRadio(unsigned int bauds) {

	NVIC_InitRadio(USART2_IRQn, 10) ;

	// Enables USART2 clock.
	RCC_AHB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE) ;

	// USART initialisation structure used to configure USART2.
	USART_InitTypeDef usart ;
	USART_StructInit(&usart) ;

	usart.USART_WordLength = USART_WordLength_8b ;
	usart.USART_StopBits = USART_StopBits_1 ;
	usart.USART_Parity = USART_Parity_No ;
	usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None ;
	usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx ;
	usart.USART_BaudRate = bauds ;
	USART_Init(USART2, &usart) ;
	USART_Cmd(USART2, ENABLE) ;

	NVIC_ClearPendingIRQ(USART2_IRQn) ;
	// Enable USART2 Receive interrupts --> USART2_IRQHandler
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE ) ;
}
