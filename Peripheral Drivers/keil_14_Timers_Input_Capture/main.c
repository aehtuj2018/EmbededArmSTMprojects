
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
#include <stdint.h>
#include "timer.h"
uint32_t time_stamp = 0;

/* HW setup : connect a jumper wire from PA5 to PA6 */

int main(void)
	
{
	
	
	tim2_PA5_output_compare();
	tim3_PA6_input_capture();
	
	while(1)
	{
		/* Wait untile edge is captured */
		while(!(TIM3->SR & SR_CC1IF)) {}
			
		/*Read captured value */
			
			time_stamp = TIM3->CCR1; 
	}
}
