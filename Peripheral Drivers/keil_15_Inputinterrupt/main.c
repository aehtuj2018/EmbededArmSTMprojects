

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
#include "extinterrupt.h"

void EXTI15_10_IRQHandler(void);
static void extinterrupt_callback(void);

int main (void)
{

	//gpio_init(); 
	uart2_rxtx_init();
	pc13_extinterrupt_init();

	while(1)
	{


	}
}

static void extinterrupt_callback()
{
	printf("Button Pressed ..\n\r");  // print on uart terminal 
}

void EXTI15_10_IRQHandler(void) // Start up file under __vector ; External Line[15:10]s
{
if ((EXTI->PR & LINE13)!=0)
{
	/* Clear PR flag */
	
	EXTI->PR |= LINE13; 
	
	//EXTI->PR &= ~LINE13;
	
	/* Do something */ 
	
	extinterrupt_callback();
}
}



