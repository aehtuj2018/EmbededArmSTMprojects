

/**
 *	Keil project for UART_TX 
 *
 *  Before you start, select your target, on the right of the "Load" button
 *
 *	@author		Abdi TUJUBA
 *	@email		abdi.tujuba.86@gmail.com
 *	@ide			Keil uVision 5
 *	@packs		STM32F4xx Keil packs version 2.2.0 or greater required
 *	@project 	UART TX - retarget printf in stdio.h library, modularized  
 */
 
#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "uart.h"


int main (void)
{

	uart2_tx_init();

	while(1)
	{
		//uart2_write('A');
		printf("Hello from STM32 F4 ..... \n\r"); 

	}
}




