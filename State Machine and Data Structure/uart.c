/*
		Name: Abdi Tujuba
		File: uart.c
		Development - Board: STM32F446RE
		Description: UART Driver 
*/
#include "stm32f4xx.h"                  // Device header

void USART2_Init(void);

#define APB1EN			(1U<<17)
#define AHB1EN			(1U<<0)


// configure uart

void USART2_Init(void)
{
// 1. Enable clock Access to uart2
	
	RCC->APB1ENR |= APB1EN;
// 2. Enable clock access to portA
	
	RCC->AHB1ENR |= AHB1EN; 
	
// 3. Enable pins for alternet function PA2, PA3 

		GPIOA->MODER
	
	
// 4. Configure type of alternet function => AF7

// configure uart
}