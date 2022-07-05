
/*----------------------------------------------------------------------------
 * Name:    main.c
 * Purpose: Main usage for STM32
 * Version: V1.00
 *----------------------------------------------------------------------------*/

#include "stm32f4xx.h"                  // Device header
#include "uart.h"
#include "stdio.h"

void USART2_IRQHandler(void);
static void uart_callback(void);
volatile char data; 

int main (void)
{
	usart2_init();
	
	while(1)
	{
	}
	return 0;
}

void USART2_IRQHandler()
{	
	/* check if RXNE is set */
	
	if(USART2->SR & SR_RXNE)
	{	
		/* Read data*/ 
		uart_callback();
   
		
	}
	
}

static void uart_callback()
{
	data = (char) USART2->DR;
	
	printf("char is %c",data); 
	
}
