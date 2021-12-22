

/**
 *	Keil project for UART_TX 
 *
 *  Before you start, select your target, on the right of the "Load" button
 *
 *	@author		Abdi TUJUBA
 *	@email		abdi.tujuba.86@gmail.com
 *	@ide			Keil uVision 5
 *	@packs		STM32F4xx Keil packs version 2.2.0 or greater required
 */
 
 
#include "stm32f4xx.h"                  // Device header

#define GPIOAEN								(1U<<0)
#define UART2EN 							(1U<<17)
#define SYS_FREQ 							16000000
#define APB2_CLK							SYS_FREQ
#define UART_BAUD_RATE 				115200

void uart2_tx_init(); 
static void uart_set_baudrate(USART_TypeDef , uint32_t  , uint32_t );

int main (void)
{

	uart2_tx_init();

	while(1)
	{
		//uart1_write('A');

	}
}


void uart2_tx_init()
{
	/********************* Configure UART GPIO PINs ****************/

	/* Enable clock Access to GPIOA - PA2*/

	RCC->AHB1ENR |= GPIOAEN;

	/* Set PA2 mode to Alternate Function Mode*/
	GPIOA->MODER	|= (1U<<5);
	GPIOA->MODER 	&= ~(1U<<4);
	
	/*Set PA2 Alternate function type to UART_TX (AF07) */
	// AFRL - index 0 , AFRH - index 1, USART1_TX function is AF07
	
	GPIOA->AFR[0] &= ~(1U<<11);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<8); 

	
	/************ Configure UART  module *********************/

	/* Enable clock access to UART2*/

	RCC->APB1ENR |= UART2EN; 
	

	/* Configure baudrate */

	uart_set_baudrate(UART2,APB2_CLK,UART_BAUD_RATE);

	/* Configure the transfer direction */

	

	/*Enable uart module */

	
}


void uart1_write(int ch)

{
	/* Make sure the transmit data is empty */

	while ()
	{};

	/* Write to transmit data register */

	


}
static void uart_set_baudrate(USART_TypeDef *UARTx, uint32_t  periphClk, uint32_t BaudRate )
{
	//UARTx->BRR = compute_uart_bd(periphClk,BaudRate);
 


}

static uint16_t compute_uart_bd(uint32_t  periphClk, uint32_t BaudRate)
{

	return ((periphClk + (BaudRate/2U))/BaudRate);
}


