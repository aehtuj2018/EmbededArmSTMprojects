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
#include "gpio.h"

#define GPIOAEN								(1U<<0)
 


void TURN_LED_ON(void);
void gpio_init(void); 
void TURN_LED_OFF(void);
void gpio_init()
{
	/* Enable clock access to GPIO A*/ 
	
	RCC->AHB1ENR |= GPIOAEN;
	
	/* Configure GPIOA as Output */
	
	GPIOA->MODER &= ~(1U<<11);
	GPIOA->MODER |= (1U<<10);
	
}

void TURN_LED_ON(void)
{
	GPIOA->ODR |= LED_PIN
}

void TURN_LED_OFF(void)
{
	GPIOA->ODR &= ~LED_PIN 
}







