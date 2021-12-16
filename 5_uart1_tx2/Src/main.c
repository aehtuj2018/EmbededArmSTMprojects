/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Abdi Tujuba
 * @brief          : GPIO - Driver
 ******************************************************************************
 */

#include "stm32f4xx.h"
#include <stdint.h>

#define UART1EN 			(1U<<4) //RCC_APB2EN - USART1 Enable
#define GPIOBEN 			(1U<<1)

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
int uart_char;

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

	/* Enable clock Access to GPIOA*/

	RCC->AHB1ENR |= GPIOBEN ; /* USART1 is on PB6, so enable clock to port B*/


	/* Set PA9 mode to Alternate Function Mode*/

	GPIOB->MODER |=(1U<<13); /* USART1 on PA6*/
	GPIOB->MODER &= ~(1U<<12);

	//GPIOB->MODER |= (2U<<GPIO_MODER_MODER6_Pos);

	/*Set PA9 Alternate function type to UART_TX (AF07) */
	// AFRL - index 0 , AFRH - index 1, USART1_TX function is AF07

	GPIOB->AFR[0] |= (1U<<24);
	GPIOB->AFR[0] |= (1U<<25);
	GPIOB->AFR[0] |= (1U<<26);
	GPIOB->AFR[0] &= ~(1U<<27);

	/************ Configure UART  module *********************/

	/* Enable clock access to UART2*/

	RCC->APB2ENR |= UART1EN;

	/* Configure baudrate */

	uart_set_baudrate(USART1,APB2_CLK,UART_BAUD_RATE);

	/* Configure the transfer direction */

	USART1 ->CR1 = CR1_TE;

	/*Stop bit */

	USART1->CR2 &= ~ (1U<<12);
	USART1->CR2 &= ~ (1U<<13);

	/*Enable uart module */

	USART1->CR1 |= CR1_UE;
}


void uart1_write(int ch)

{
	/* Make sure the transmit data is empty */

	while (!(USART1->SR & SR_TXE))
	{};

	/* Write to transmit data register */

	uart_char = ( USART1->DR = (ch & 0xFF));

//	USART1->DR = 120;

}
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t  periphClk, uint32_t BaudRate )
{
	USARTx->BRR = compute_uart_bd(periphClk,BaudRate);


}

static uint16_t compute_uart_bd(uint32_t  periphClk, uint32_t BaudRate)
{

	return ((periphClk + (BaudRate/2U))/BaudRate);
}


