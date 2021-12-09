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

#define PIN13    (1U<<0)
#define BTN_PIN  PIN13

#define PIN14    (1U<<14)
#define LED_PIN  PIN14

int main (void)
{

	/* Enable clock register for LED - output and INpuit push button*/

	RCC->AHB1ENR |= GPIOGEN;
	RCC->AHB1ENR |= GPIOAEN;

	/* Set PIN14 as output  */
	GPIOG->MODER |= (1U<<28);
	GPIOG->MODER &= ~ (1U<<29);

	/* Set PC13 as input PIN */
	GPIOA->MODER &= ~(1U<<0);
	GPIOA->MODER &= ~(1U<<0);

	while(1)
	{
		//GPIOG->ODR ^= LED_PIN;
		GPIOG->BSRR |=  LED_PIN;

		for(int i=0;i<150000;i++)
		{}

		GPIOG->BSRR |=(1U<<30);

		for(int i=0;i<150000;i++)
		{}
}

