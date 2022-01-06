
/**
 *	Keil project for UART_TX 
 *
 *  Before you start, select your target, on the right of the "Load" button
 *
 *	@author		Abdi TUJUBA
 *	@email		abdi.tujuba.86@gmail.com
 *	@ide			Keil uVision 5
 *	@packs		STM32F4xx Keil packs version 2.2.0 or greater required
 *  @Project 	Output Compare  
 */


#include "stm32f4xx.h"                  // Device header
#include "timer.h"


int main(void)
	
{
	
	
	tim2_PA5_output_compare();
	
	while(1)
	{
		
			
	}
}
