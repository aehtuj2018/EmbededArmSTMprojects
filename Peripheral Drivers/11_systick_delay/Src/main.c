/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Abdi Tujuba
 * @brief          : GPIO - Driver
 ******************************************************************************
 */

#include "stm32f4xx.h"
#include <stdint.h>
#include <stdio.h>
#include "adc.h"
#include "systick.h"


#define GPIOGEN  		(1U<<6)
#define PIN14			(1U<<14)

#define LED_PIN			PIN14

int main (void)
{

	/* Enable clock access to GPIOG */

	RCC->AHB1ENR |= GPIOGEN;

	/* Set PG14 as output pin */


	GPIOG->MODER |= (1U<<28);
	GPIOG->MODER &= ~(1u<<29);

	start_conversion();

	while(1)
	{


		//printf("A second just passed !!");

		GPIOG->ODR ^= LED_PIN;
		systickDelayMs(1000);


	}
}

