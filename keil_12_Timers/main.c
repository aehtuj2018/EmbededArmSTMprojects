
/**
 *	Keil project for UART_TX 
 *
 *  Before you start, select your target, on the right of the "Load" button
 *
 *	@author		Abdi TUJUBA
 *	@email		abdi.tujuba.86@gmail.com
 *	@ide			Keil uVision 5
 *	@packs		STM32F4xx Keil packs version 2.2.0 or greater required
 *  @Project 	General Purpose Timer Driver 
 */


#include "stm32f4xx.h"                  // Device header
#include "timer.h"

#define GPIOAEN 					(1U<<0)
#define PIN5    					(1U<<5)
#define LED      					 PIN5	

int main(void)
	
{
	
	/*1. Enable clock Access to GPIOA */
	RCC->AHB1ENR |= GPIOAEN; 
	
	/*2. Set PA5 as output pin */
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1U<<11); 
	
	tim2_1hz_init();
	
	while(1)
	{
		/* WAIT UIF which is 1Hz or 1s*/

		//GPIOA->ODR |= LED;		
		
		 while(!(TIM2->SR & SR_UIF)) { }
			
			/* Clear UIF*/
			TIM2->SR &=~SR_UIF; 
			
			GPIOA->ODR ^= LED; 
			
	}
}
