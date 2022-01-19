#include "stm32f4xx.h"                  // Device header

#define AFR5_TIM  				(1U<<20)
#define GPIOAEN 					(1U<<0)
#define TIMER2EN					(1U<<0)
#define TIM13EN						(1U<<1)
#define CR1_CEN						(1U<<0)
#define OC_TOGGLE    			(1U<<4) | (1U<<5)
#define CCER_CC1E					(1U<<0)
#define CCER_CC1S					(1U<<0)
#define CCER_CC1E 				(1U<<0)

void tim2_1hz_init(void);
void tim2_PA5_output_compare(void);
void tim3_PA6_input_capture(void);


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


void tim3_PA6_input_capture(void)
{
	/* Enable clock Access GPIOA */
	
	RCC->AHB1ENR |= GPIOAEN; 
	
	/* Set PA6 mode to alternet function */
	GPIOA->MODER &=~(1U<<12);
	GPIOA->MODER |=(1U <<13); 
	
	/* Set PA6 altenet function type to TIM3_CH1 (AF02)*/
	
	GPIOA->AFR[0] &=~ (1U<<27);
	GPIOA->AFR[0] &=~ (1U<<26); 
	GPIOA->AFR[0] |=  (1U<<25); 
	GPIOA->AFR[0] &=~ (1U<<24); 	
	
	
	/* Enable clock Access to time3 */
	
	RCC->AHB1ENR |= TIM13EN; 
		
	/* Set Prescaler */
	
	TIM3-> PSC = 1600 - 1; // 16 000 000/ 16 000
	
	/* Set CH1 to input capture mode */
	
	TIM3->CCMR1 |= CCER_CC1S; 
	
	/*set CH1 to capture at rising edge */
	
	TIM3->CCER |= CCER_CC1E;
	
	/* Enable timer 3*/
	
	TIM3->CR1 |= CR1_CEN;
	
}
