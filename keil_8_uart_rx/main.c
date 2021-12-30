

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
#include "gpio.h"

 
static char key; 
int main (void)
{

	gpio_init(); 
	uart2_rxtx_init();

	while(1)
	{
		//uart2_write('A');
		//printf("Hello from STM32 F4 ..... \n\r"); 
		key = uart2_read();
		//uart2_write(key);
		if(key=='o')
		{
			TURN_LED_ON(); 
		}
		if (key =='f')
		{
			TURN_LED_OFF();
		}
		

	}
}




