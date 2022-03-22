

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

 
static char key; 
int main (void)
{

	gpio_init(); 
	uart2_rxtx_init();

	while(1)
	{

		key = uart2_read();
//  printf(" \n 2%c" , key); // Eco back the character by appending 2 
		// 'o' - Turn ON LED2 , 'f' - Turn OFF LED2 
		if(key=='o' || key =='O')
		{
			TURN_LED_ON(); 
		}
		if (key =='f' || key =='F')
		{
			TURN_LED_OFF();
		}
		

	}
}




