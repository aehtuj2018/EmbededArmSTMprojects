

/**
 *	Keil project for UART_TX 
 *
 *  Before you start, select your target, on the right of the "Load" button
 *
 *	@author		Abdi TUJUBA
 *	@email		abdi.tujuba.86@gmail.com
 *	@ide			Keil uVision 5
 *	@packs		STM32F4xx Keil packs version 2.2.0 or greater required
 *	@project  USART/UART Transmit and Recive Driver + Control LED with UART TX
 */
 
#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "uart.h"
#include "gpio.h"

void USART2_IRQHandler(void);
static void uart_callback(void);
 
static char key; 
int main (void)
{

	gpio_init(); 
	uart2_rxtx_init();
	
	//uart2_rx_interrupt_init(); 

	while(1)
	{
	}
}

static void uart_callback()
{
	key = (char) USART2->DR;
		
	
	printf("You have enetered ... %c \n\r",key); 
	
	// printf("LED ON ... %c \n\r",key); 
	
		if(key=='o' || key =='O')
		{
			printf("LED ON ... \n\r"); 
			TURN_LED_ON();
						
		}
		if (key =='f' || key =='F')
		{
			printf("LED OFF ... \n\r");
			TURN_LED_OFF();
			
		}
}

void USART2_IRQHandler()
{
	
	/* check if RXNE is set */
	
	if(USART2->SR & SR_RXNE)
	{
		// Do something 
		
		uart_callback();
		
	}
	
}


