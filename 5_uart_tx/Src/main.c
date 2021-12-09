/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Abdi Tujuba
 * @brief          : GPIO - Driver
 ******************************************************************************
 */

#include "stm32f4xx.h"
#include <stdint.h>

#define UART2EN 			(1U<<17)
#define GPIOAEN  			(1U<<0)
#define GPIOGEN  			(1U<<6)

#define SYS_FREQ    		16000000
#define APB1_CLK			SYS_FREQ
#define UART_BAUD_RATE		115200

#define PIN14    (1U<<14)
#define LED_PIN  PIN14

#define CR1_UE  			(1U<<13) // enable USART2
#define CR1_TE   			(1U<<3) // Transmitter Enable

#define SR_TXE  			(1U<<7) // TRansmit register empty

void uart2_tx_init();
static void uart_set_baudrate(USART_TypeDef *USARTTx, uint32_t  periphClk, uint32_t BaudRate );
static uint16_t compute_uart_bd(uint32_t  periphClk, uint32_t BaudRate);
void uart2_write(int ch);

int main (void)
{
	RCC->AHB1ENR |= GPIOGEN;
	GPIOG->MODER |= (1U<<28);
	GPIOG->MODER &= ~ (1U<<29);

	//RCC->AHB1ENR |= GPIOGEN ;

	//GPIOG->ODR |= LED_PIN;

	uart2_tx_init();

	while(1)
	{
		GPIOG->ODR |= LED_PIN;
		uart2_write('Y');
	}
}

void uart2_tx_init()
{
	/********************* Configure UART GPIO PINs ****************/

	/* Enable clock Access to GPIOA*/

	RCC->AHB1ENR |= GPIOAEN ;


	/* Set PA2 mode to Alternate Function Mode*/

	GPIOA->MODER |=(1U<<5);
	GPIOA->MODER &= ~(1U<<4);


	/*Set PA2 Alternate function type to UART_TX (AF07) */
	// AFRL - index 0 , AFRH - index 1, USART2_TX function is AF07

	GPIOA->AFR[0] |= (1U<<8);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] &= ~(1U<<11);

	/************ Configure UART  module *********************/

	/* Enable clock access to UART2*/

	RCC->APB1ENR |= UART2EN;

	/* Configure baudrate */

	uart_set_baudrate(USART2,APB1_CLK,UART_BAUD_RATE);

	/* Configure the transfer direction */

	USART2 ->CR1 = CR1_TE;


	/*Enable uart module */

	USART2->CR1 |= CR1_UE;
}


void uart2_write(int ch)

{
	/* Make sure the transmit data is empty */
	GPIOG->BSRR = LED_PIN;

	while (!(USART2->SR &  SR_TXE))
	{
		//GPIOG->BSRR = LED_PIN;

		GPIOG->BSRR = (1U<<30); /* Sets the corresponding Bit 14 to low, Turn OFF LED */

	};
	/* Write to transmit data register */

	USART2->DR = (ch & 0xFF);
}
static void uart_set_baudrate(USART_TypeDef *USARTTx, uint32_t  periphClk, uint32_t BaudRate )
{
	USARTTx->BRR = compute_uart_bd(periphClk,BaudRate);
}

static uint16_t compute_uart_bd(uint32_t  periphClk, uint32_t BaudRate)
{

	return ((periphClk + (BaudRate/2U))/BaudRate);
}
