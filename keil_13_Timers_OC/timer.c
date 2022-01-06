#include "stm32f4xx.h"                  // Device header

#define AFR5_TIM  					(1U<<20)
#define GPIOAEN 					(1U<<0)
#define TIMER2EN					(1U<<0)
#define CR1_CEN						(1U<<0)
#define OC_TOGGLE    			(1U<<4) | (1U<<5)
#define CCER_CC1E					(1U<<0)

void tim2_1hz_init(void);
void tim2_PA5_output_compare(void);


void tim2_1hz_init(void)
{
	/* Enable clock access to Timer 2 */
	
	RCC->APB1ENR |= TIMER2EN;
	
	/* Set prescaler value */
	TIM2->PSC = 1600 - 1 ; // 16 000 000 /1 600 = 10 000
	
	/* Set auto-reload value */
	
	TIM2-> ARR = 10000 - 1 ; // 10 000 / 10 000 
	
	/* Clear counter */
	
	TIM2->CNT = 0;
	
	/* Enable Timer */
	 TIM2->CR1 |= CR1_CEN; 
	
}



void tim2_PA5_output_compare(void)
{
	
	/*1. Enable clock Access to GPIOA */
	RCC->AHB1ENR |= GPIOAEN; 
	
	/*2. Set PA5 as Alternate Function*/
	GPIOA->MODER |= (1U<<11);
	GPIOA->MODER &= ~(1U<<10); 
	/*Set PA5 Alternate Function Type  (AF01)*/
	
	GPIOA->AFR[0]|= AFR5_TIM;
	
	
	/* Enable clock access to Timer 2 */
	
	RCC->APB1ENR |= TIMER2EN;
	
	/* Set prescaler value */
	TIM2->PSC = 1600 - 1 ; // 16 000 000 /1 600 = 10 000
	
	/* Set auto-reload value */
	
	TIM2-> ARR = 10000 - 1 ; // 10 000 / 10 000 
	
	/*Set output Compare toggle mode */
	
	TIM2->CCMR1 |= OC_TOGGLE; 
	
	/*Enable timer 2 ch1 in compare mode */
	
	TIM2->CCER |= CCER_CC1E;
	
	/*Clear counter*/ 
	
	TIM2->CNT = 0; 
	
	/* Enable Timer */
	
	 TIM2->CR1 |= CR1_CEN; 
	
}
