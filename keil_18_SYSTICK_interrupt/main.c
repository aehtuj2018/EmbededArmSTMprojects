/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Abdi Tujuba
 * @brief          : ADC Single Conversion
 * Board 		   		 : STM NucleoBoard F446RE
 ******************************************************************************
 */

#include "stm32f4xx.h"
#include <stdint.h>
#include <stdio.h>
#include "adc.h"
#include "uart.h"
#include "systick.h"

#define GPIOGEN  		(1U<<6)
#define PIN14			(1U<<14)
#define LED_PIN			PIN14

void SysTick_Handler(void);
void ADC_IRQHandler(void);
static void systick_callback(void);

int main (void)
{

	/* Enable clock access to GPIOG */

	RCC->AHB1ENR |= GPIOGEN;

	/* Set PG14 as output pin */


	GPIOG->MODER |= (1U<<28);
	GPIOG->MODER &= ~(1u<<29);

	uart2_tx_init();
	systick_1hz_interrupt();
		
	while(1)
	{

	}
}


static void systick_callback()
{
	printf("A second just passed !!\n\r");

		//GPIOG->ODR ^= LED_PIN;
}

void SysTick_Handler(void)
{
	
	//Do something 
	systick_callback();
}
