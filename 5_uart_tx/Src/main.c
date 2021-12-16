/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Abdi Tujuba
 * @brief          : UART_TX Driver
 ******************************************************************************
 */

#include "stm32f4xx.h"
#include <stdint.h>

#define UART5EN 			(1U<<20) //RCC_APB2EN - UART5 Enable
#define GPIOCEN				(1U<<2)  // Enable PORTC

#define SYS_FREQ    		16000000
#define APB2_CLK			SYS_FREQ
#define UART_BAUD_RATE		115200

#define CR1_TE   			(1U<<3) // Transmitter Enable
#define CR1_UE  			(1U<<13) // enable USART1

#define SR_TXE  			(1U<<7) // Transmit register empty

void uart1_tx_init();
static void uart_set_baudrate(USART_TypeDef *USARTTx, uint32_t  periphClk, uint32_t BaudRate );
static uint16_t compute_uart_bd(uint32_t  periphClk, uint32_t BaudRate);
void uart1_write(int ch);


int main (void)
{

	uart1_tx_init();

	while(1)
	{
		uart1_write('A');

	}
}


void uart1_tx_init()
{
	/********************* Configure UART GPIO PINs ****************/

	/* Enable clock Access to GPIOC*/

	RCC->AHB1ENR |= GPIOCEN ; /* UART5_TX is on PC12, enable clock to port C UART5_RX is on PD2 */


	/* Set PC12 mode to Alternate Function Mode*/

	GPIOC->MODER |=(1U<<25); /* UART on PC12*/
	GPIOC->MODER &= ~(1U<<24);

	/*Set PC12 Alternate function type to UART_TX (AF08) */
	// AFRL - index 0 , AFRH - index 1, USART1_TX function is AF07

	GPIOC->AFR[1] &= ~(1U<<16);
	GPIOC->AFR[1] &= ~(1U<<17);
	GPIOC->AFR[1] &= ~(1U<<18);
	GPIOC->AFR[1] |= (1U<<19);

	/************ Configure UART  module *********************/

	/* Enable clock access to UART5*/

	RCC->APB1ENR |= UART5EN;

	/* Configure baudrate */

	uart_set_baudrate(UART5,APB2_CLK,UART_BAUD_RATE);

	/* Configure the transfer direction */

	UART5->CR1 = CR1_TE;

	/*Enable uart module */

	UART5->CR1 |= CR1_UE;
}


void uart1_write(int ch)

{
	/* Make sure the transmit data is empty */

	while (!(UART5->SR & SR_TXE))
	{};

	/* Write to transmit data register */

	UART5->DR = (ch & 0xFF);



}
static void uart_set_baudrate(USART_TypeDef *UARTx, uint32_t  periphClk, uint32_t BaudRate )
{
	//UARTx->BRR = compute_uart_bd(periphClk,BaudRate);
	UART5->BRR = compute_uart_bd(periphClk,BaudRate);


}

static uint16_t compute_uart_bd(uint32_t  periphClk, uint32_t BaudRate)
{

	return ((periphClk + (BaudRate/2U))/BaudRate);
}


