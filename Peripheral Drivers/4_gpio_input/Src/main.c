/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Abdi Tujuba
 * @brief          : GPIO - I/O Driver
 ******************************************************************************
 */

#include "stm32f4xx.h"



#define GPIOGEN  (1U<<6)
#define PIN14    (1U<<14)
#define LED_PIN  PIN14

int main (void)
{

	RCC->AHB1ENR |= GPIOGEN;
	GPIOG->MODER |= (1U<<28);
	GPIOG->MODER &= ~ (1U<<29);

	while(1)
	{
		GPIOG->ODR ^= LED_PIN;
		for(int i=0;i<150000;i++)
		{

		}
	}
}

