/*  Set up UART on PIN on 
				PA2 - USART2_TX
				PA3 - USART2_RX
					
*/

#include "stdio.h"
#include "uart.h"

#define GPIOAEN       		(1U<<0)  //GPIOA enable 
#define UART2EN						(1U<<17) // USART 2 Enable Clock Access 
#define USART2EN 					(1U<<13) // USART Enable
#define USART2_M					(1U<<12) // 1 start bit, 8 Databits n stop bit
#define USART2_PEIE   		(1U<<8) // Interrupt is generated when PE = 1 in Status Register
#define USART2_TXEIE   		(1U<<7) // Interrupt is generated when TXE =1 in Status Reg
#define USART2_TCIE				(1U<<6) // Interrupt is generated when TC=1 in Status Reg/USART_SR
#define USART2_RXNEIE     (1U<<5) // Interrupt is generated whenever ORE=1 or RXNE=1 status Reg
#define USART2_TE					(1U<<3) // Trasmitter Enable 
#define USART2_RE					(1U<<2) // Receiver Enable 
#define UART_BAUD_RATE     115200 // Baud Rate 
#define APB2_CLK           16000000 // clock frequency 

#define USART2_TXE         (1U<<7)
#define USART2_RXNE        (1U<<5)

static uint16_t compute_uart_bd(uint32_t  periphClk, uint32_t BaudRate);
static void uart_set_baudrate(USART_TypeDef *USARTTx, uint32_t  periphClk, uint32_t BaudRate );

FILE __stdout;
FILE __stdin;

int fputc(int ch , FILE * stream)
{
	//uart2_write(ch);
	USART2_write ((char)ch);
	return ch;  //return the character written to denote a successfull write
}


void usart2_init(void)		
{
	/* Enable Clock to GPIOA */ 
	
	RCC->AHB1ENR  |= GPIOAEN; 
	
	/* Set PA2, PA3 as for Alternet function */
	
	/* PA2 */
	GPIOA->MODER |=  (1U<<5);
	GPIOA->MODER &= ~(1U<<4);
	
	/* PA3 */
	GPIOA->MODER |=  (1U<<7);
	GPIOA->MODER &= ~(1U<<6);

	
	/* Alternet function PA2 - USART2 - AF7 */
	/* 0111: AF7 -> PA2 */
	GPIOA->AFR[0] &= ~(1U<<11);
	GPIOA->AFR[0] |=  (1U<<10);
	GPIOA->AFR[0] |=  (1U<<9);
	GPIOA->AFR[0] |=  (1U<<8);
	
	
	/* 0111: AF7 -> PA3 */
	GPIOA->AFR[0] &= ~(1U<<15);
	GPIOA->AFR[0] |=  (1U<<14);
	GPIOA->AFR[0] |=  (1U<<13);
	GPIOA->AFR[0] |=  (1U<<12);
	
	/* configure UART Module */
	
	/* USART 2 Enable Clock Access */
	
	RCC->APB1ENR |= UART2EN; 
		
	/* Dsable before starting configuration */
	USART2->CR1 &= ~USART2EN;
	
	/* configure bits - for operation */
	
	USART2->CR1 &= ~USART2_M;
	USART2->CR1 |= USART2_PEIE;
	USART2->CR1 |= USART2_TXEIE;
	USART2->CR1 |= USART2_TCIE;
	USART2->CR1 |= USART2_RXNEIE;
	USART2->CR1 |= USART2_TE;
	USART2->CR1 |= USART2_RE;
	
	/* Stop bits */
	
	USART2->CR2 &= ~(1U<<13);
	USART2->CR2 &= ~(1U<<12); 
	
	//USART2->BRR = (int16_t) 17.375; // baud rate 
	 uart_set_baudrate(USART2,APB2_CLK,UART_BAUD_RATE);
	
	/* USART2 Enable */
	USART2->CR1 |= USART2EN;
}


static void uart_set_baudrate(USART_TypeDef *USARTTx, uint32_t  periphClk, uint32_t BaudRate )
{
	//UARTx->BRR = compute_uart_bd(periphClk,BaudRate);
 USARTTx->BRR = compute_uart_bd(periphClk,BaudRate); 


}

static uint16_t compute_uart_bd(uint32_t  periphClk, uint32_t BaudRate)
{

	return (uint16_t) ((periphClk + (BaudRate/2U))/BaudRate);
}

void USART2_write (uint32_t  ch)
{
	while(!(USART2->SR & USART2_TXE)) {} // wait till data transmit is empty
		
	USART2->DR = ch; 	
		
}

char USART2_read(void)
{
	while (!(USART1->SR & USART2_RXNE)) {} // whait till data is received 
	
		return (char)USART2->DR; 
}
