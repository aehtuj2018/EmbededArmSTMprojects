/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Abdi Tujuba
 * @brief          : GPIO - using STM include file
 ******************************************************************************
 */

#include "stm32f4xx.h"

#define GPIOGEN  (1U<<6)
#define GPIOAEN  (1U<<0)

#define PINA0    (1U<<0)
#define BTN_PIN  PINA0

#define PIN14    (1U<<14)
#define LED_PIN  PIN14

int main (void)
{

	/* Enable clock register for LED - output and INpuit push button*/

	RCC->AHB1ENR |= GPIOGEN;
	RCC->AHB1ENR |= GPIOAEN;

	/* Set PIN14 as output, LED  */
	GPIOG->MODER |= (1U<<28);
	GPIOG->MODER &= ~ (1U<<29);

	/* Set PIN PA0 as input PIN */

	GPIOA->MODER &= ~(1U<<0);
	GPIOA->MODER &= ~(1U<<1);


	while(1)
	{

		/* Check if button is pressed*/

		if (GPIOA->IDR & BTN_PIN )
		{

			GPIOG->BSRR = LED_PIN; /* Sets the corresponding Bit 14 to high, Turn on LED */

		}


		else
		{
			GPIOG->BSRR = (1U<<30); /* Sets the corresponding Bit 14 to low, Turn OFF LED */
		}

}

}
