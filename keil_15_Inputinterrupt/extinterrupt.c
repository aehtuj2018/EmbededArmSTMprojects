
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
#include "uart.h"
#include "extinterrupt.h"


#define GPIOCEN 				(1U<<2)
#define SYSCFEN 				(1U<<14)


void pc13_extinterrupt_init(void);

void pc13_extinterrupt_init(void)
{
	/* Disable global interrupts*/
	
	__disable_irq();
	
	/* Enable clock access for GPIOC*/
	
	RCC->AHB1ENR |= GPIOCEN;
	
	/* Set PC13 as input */
	
	GPIOC->MODER &=~ (1u<<26);
	GPIOC->MODER &=~ (1u<<27);
	
	/*Enable clock access to SYSCFG*/
	
	RCC->APB2ENR |= SYSCFEN; 
	
	/* Select PORTC for EXTI13 */
	
	SYSCFG->EXTICR[3] |= (1U<<5); // 0010  connect EXTI13 to port C
	
	/* Unmask EXTI13 */
	
	EXTI->IMR |= (1U<<13); 
	
	/* Select falling edge trigger */
	
	EXTI->FTSR |= (1U<<13); 
	
	/* Enable EXTI line in NVIC */
	
	NVIC_EnableIRQ(EXTI15_10_IRQn); 
	
	/* Enable global interrupt */
	
	__enable_irq();
	
}
