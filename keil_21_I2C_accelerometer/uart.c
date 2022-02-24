
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
#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "uart.h"

#define GPIOAEN								(1U<<0)
#define UART2EN 							(1U<<17)

#define SYS_FREQ 							16000000
#define APB2_CLK							SYS_FREQ
#define UART_BAUD_RATE 				115200

#define CR1_UE								(1U<<13)
#define CR1_TE								(1U<<3)
#define CR1_RE								(1U<<2)

#define SR_TXE								(1U<<7)
#define CR1_RXNEIE 						(1U<<5)

#define DMA1EN 												(1U<<21) 					
#define CHSEL4 												(1U<<27)
#define DMA_MEM_INC  									(1U<<10)
#define DMA_DIR_MEM_TO_PERIPH 				(1U<<6)		
#define DMA_CR_TCIE										(1U<<4)
#define DMA_CR_EN											(1U<<0)
#define UART_CR3_DMAT									(1U<<7)

static void uart_set_baudrate(USART_TypeDef *, uint32_t  , uint32_t );
static uint16_t compute_uart_bd(uint32_t  , uint32_t ); 
void uart2_write(int ch);
void uart2_rxtx_init(void);
char uart2_read(void);
void uart2_rx_interrupt_init(void);
void dma1_stream6_init(uint32_t , uint32_t , uint32_t );
	
FILE __stdout;
FILE __stdin;


int fputc(int ch , FILE * stream)
{
	uart2_write(ch);
	return ch;  //return the character written to denote a successfull write
}
void uart2_rxtx_init()
{
	/********************* Configure UART GPIO PINs ****************/

	/* Enable clock Access to GPIOA - PA2*/

	RCC->AHB1ENR |= GPIOAEN;

	/* Set PA2 mode to Alternate Function Mode - TX*/
	GPIOA->MODER	|= (1U<<5);
	GPIOA->MODER 	&= ~(1U<<4);
	
	/* Set PA3 mode to Alternate Function Mode -RX*/
	GPIOA->MODER	|= (1U<<7);
	GPIOA->MODER 	&= ~(1U<<6);
	
	/*Set PA2 Alternate function type to UART_TX (AF07) */
	// AFRL - index 0 , AFRH - index 1, USART1_TX function is AF07
	
	GPIOA->AFR[0] &= ~(1U<<11);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<8); 
	
		/*Set PA3 Alternate function type to UART_TX (AF07) */
	// AFRL - index 0 , AFRH - index 1, USART1_TX function is AF07
	
	GPIOA->AFR[0] &= ~(1U<<15);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<12); 
	
	/************ Configure UART  module *********************/

	/* Enable clock access to UART2*/

	RCC->APB1ENR |= UART2EN; 
	

	/* Configure baudrate */

	uart_set_baudrate(USART2,APB2_CLK,UART_BAUD_RATE);

	/* Configure the transfer direction */

	USART2->CR1 |= ( CR1_TE | CR1_RE) ;
	
	/*Enable uart module */

	USART2->CR1 |= CR1_UE; 
}

char uart2_read(void)
{
	/* Make sure the recive data register is not empty */
	
	
	while (!(USART2->SR & SR_RXNE)) {}
		
	/* Read data*/ 
	return  (char) USART2->DR; 
}


void uart2_write(int ch)

{
	/* Make sure the transmit data is empty */

	while (!(USART2->SR & SR_TXE))
	{}
		
	/* Write to transmit data register */

	USART2->DR = (ch & 0xFF);

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


void uart2_rx_interrupt_init()
{
	/********************* Configure UART GPIO PINs ****************/

	/* Enable clock Access to GPIOA - PA2*/

	RCC->AHB1ENR |= GPIOAEN;

	/* Set PA2 mode to Alternate Function Mode - TX*/
	GPIOA->MODER	|= (1U<<5);
	GPIOA->MODER 	&= ~(1U<<4);
	
	/* Set PA3 mode to Alternate Function Mode -RX*/
	GPIOA->MODER	|= (1U<<7);
	GPIOA->MODER 	&= ~(1U<<6);
	
	/*Set PA2 Alternate function type to UART_TX (AF07) */
	// AFRL - index 0 , AFRH - index 1, USART1_TX function is AF07
	
	GPIOA->AFR[0] &= ~(1U<<11);
	GPIOA->AFR[0] |= (1U<<10);
	GPIOA->AFR[0] |= (1U<<9);
	GPIOA->AFR[0] |= (1U<<8); 
	
		/*Set PA3 Alternate function type to UART_TX (AF07) */
	// AFRL - index 0 , AFRH - index 1, USART1_TX function is AF07
	
	GPIOA->AFR[0] &= ~(1U<<15);
	GPIOA->AFR[0] |= (1U<<14);
	GPIOA->AFR[0] |= (1U<<13);
	GPIOA->AFR[0] |= (1U<<12); 
	
	/************ Configure UART  module *********************/

	/* Enable clock access to UART2*/

	RCC->APB1ENR |= UART2EN; 
	

	/* Configure baudrate */

	uart_set_baudrate(USART2,APB2_CLK,UART_BAUD_RATE);

	/* Configure the transfer direction */

	USART2->CR1 |= ( CR1_TE | CR1_RE) ;
	
	/*Enbable RXNE interrupt */
	USART2->CR1 |= CR1_RXNEIE; 
	
	/* Enable UART2 Interupt in NVIC*/
	
	NVIC_EnableIRQ(USART2_IRQn); 
	
	/*Enable uart module */

	USART2->CR1 |= CR1_UE; 
}

void dma1_stream6_init(uint32_t src, uint32_t dst, uint32_t len)
{
	/*Enable clock access to DMA*/
	RCC->AHB1ENR |= DMA1EN;
	
	/*Disable DMA1 Stream6*/
	
	DMA1_Stream6->CR &=~DMA_CR_EN;
	
	/* Wait until DMA1 Stream 6 is disabled */
	
	while(DMA1_Stream6->CR & DMA_CR_EN ) {}
	
	/*Clear all interrupt flag of stream6*/
	
	DMA1->HIFCR |= (1U<<16);
	DMA1->HIFCR |= (1U<<18);
	DMA1->HIFCR |= (1U<<19);
	DMA1->HIFCR |= (1U<<20);
	DMA1->HIFCR |= (1U<<21);
	
	/*Set the destination buffer */
	
	DMA1_Stream6->PAR = dst; 
	
	/*Set the source buffer */
	
	DMA1_Stream6->M0AR = src;
	
	/*set  length*/
	
	DMA1_Stream6->NDTR = len; 
	
	/* Select stream CH4*/
	
	DMA1_Stream6->CR= CHSEL4; 
	
	/* Enable memory increment */
	
	DMA1_Stream6->CR |= DMA_MEM_INC;
	
	/*configure transfer direction*/
	
	DMA1_Stream6->CR |= DMA_DIR_MEM_TO_PERIPH;
	
	/*Enable DMA transfer complete interrupt*/
	
	DMA1_Stream6->CR |= DMA_CR_TCIE; 
	
	/*Enable direct mode and disable FIFO*/
	
	DMA1_Stream6->FCR = 0;
	
	/*Enable DMA1 Stream6 */
	
	DMA1_Stream6->CR |= DMA_CR_EN; 
	
	/*Enable UART2 transmitter DMA*/
	
	USART2->CR3 |= UART_CR3_DMAT;
	
	/*DMA INterrupt enable in NVIC*/
	
	NVIC_EnableIRQ(DMA1_Stream6_IRQn); 
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

	uart_set_baudrate(USART2,APB2_CLK,UART_BAUD_RATE);

	/* Configure the transfer direction */

	USART2->CR1 |= CR1_TE;

	/*Enable uart module */

	USART2->CR1 |= CR1_UE; 
	
}
