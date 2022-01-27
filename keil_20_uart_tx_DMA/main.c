

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
static void dma_uart_callback(void);
void DMA1_Stream6_IRQHandler(void);
  
int main (void)
{

	char message[31] = "Hello from stm32 DMA transfer\n\r";  
	gpio_init(); 
	//uart2_rxtx_init();
	uart2_tx_init();
	dma1_stream6_init((uint32_t) message, (uint32_t) &USART2->DR, 31);
	//uart2_rx_interrupt_init(); 

	while(1)
	{
	}
}

static void dma_uart_callback(void)
{
	GPIOA->ODR |= LED_PIN;
}

/*void USART2_IRQHandler()
{
	
	// check if RXNE is set 
	
	if(USART2->SR & SR_RXNE)
	{
		// Do something 
		
		uart_callback();
		
	}
	
}*/

void DMA1_Stream6_IRQHandler(void)
{
	/* Check for transfer complete interrupt */
	if(DMA1->HISR & HISR_TCIF6)
		/* Clear flag */
	DMA1->HIFCR |= HIFCR_CTCIF6;
	
		/* Do something*/
	
	dma_uart_callback();
}


