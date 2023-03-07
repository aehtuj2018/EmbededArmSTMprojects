		/*----------------------------------------------------------------------------
		* Name:    uart.c
		* Purpose: USART usage for STM32
		* Version: V1.00
		*----------------------------------------------------------------------------*/


		/*  Set up UART on PIN on 
					PA2 - USART2_TX
					PA3 - USART2_RX
						
		*/
		#include "stm32f4xx.h"                  // Device header

		#include "stdio.h"
		#include "uart.h"
		#include "timer.h"



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
	
		/* USART 2 Enable Clock Access */

		RCC->APB1ENR |= UART2EN; 
			
		/* Disable before starting configuration */
		USART2->CR1 &= ~USART2EN;

		/* configure bits - for operation */

		USART2->CR1 &= ~USART2_M;
		
		 //enable RXNE and TXE interrupts on USART SIDE
		USART2->CR1 |= USART_CR1_RXNEIE | USART_CR1_TXEIE;
		
		//USART2->CR1 |= USART2_TXEIE; // Transmit Interrupt
		//USART2->CR1 |= USART2_TCIE; // Transmit Complete Intterupt
		//USART2->CR1 |= USART2_RXNEIE;
		USART2->CR1 |= USART2_TE;
		USART2->CR1 |= USART2_RE;

		/* Stop bits */

		USART2->CR2 &= ~(1U<<13);
		USART2->CR2 &= ~(1U<<12); 
 
		uart_set_baudrate(USART2,APB2_CLK,UART_BAUD_RATE);

		NVIC_EnableIRQ(USART2_IRQn);

		/* USART2 Enable */
		USART2->CR1 |= USART2EN;
		__NOP(); 
		__NOP();
		__NOP();
		__NOP();
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


		/* configure UART Module */

		/* USART 2 Enable Clock Access */

		RCC->APB1ENR |= UART2EN; 
			
		/* Dsable before starting configuration */
		USART2->CR1 &= ~USART2EN;

		/* configure bits - for operation */

		USART2->CR1 &= ~USART2_M;
		//USART2->CR1 |= USART2_TXEIE; // Transmit Interrupt
		//USART2->CR1 |= USART2_TCIE; // Transmit Complete Intterupt
		//USART2->CR1 |= USART2_RXNEIE;
		USART2->CR1 |= USART2_TE;
		USART2->CR1 |= USART2_RE;

		/* Stop bits */

		USART2->CR2 &= ~(1U<<13);
		USART2->CR2 &= ~(1U<<12); 

		//USART2->BRR = (int16_t) 17.375; // baud rate 
		 uart_set_baudrate(USART2,APB2_CLK,UART_BAUD_RATE);
		 
		 /* Enable receive interrupt*/
		 USART2->CR1 |= CR1_RXNEIE;
		 

	//	 NVIC_EnableIRQ(USART2_IRQn);

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
