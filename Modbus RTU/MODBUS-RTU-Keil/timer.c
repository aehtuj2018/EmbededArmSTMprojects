#include "stm32f4xx.h"                  // Device header
#include "timer.h"

void tim_6_7_1hz_init(void); 


void tim_6_7_1hz_init(void)
{
	/* Enable clock access to Timer 6 */
	
	RCC->APB1ENR |= TIMER6EN;
	
	/* Enable clock access to Timer 7 */
	
	RCC->APB1ENR |= TIMER7EN;
	
	/* Set prescaler value */
	TIM6->PSC = 16 - 1 ; // 16 000 000 /1 6 = 1 000 000
	TIM7->PSC = 16 - 1; // 16 000 000 / 1 6 = 1 000 000
	
	/* Set auto-reload value */
	
	TIM6->ARR = 13;
	TIM7->ARR = 31; 
	
	
	//TIM2-> ARR = 10000 - 1 ; // 10 000 / 10 000 
	
	/* Clear counter */
	
	TIM6->CNT = 0;
	TIM7->CNT = 0;
	
	/* Enable Timer */
	 TIM6->CR1 |= CR1_CEN; 
	 TIM7->CR1 |= CR1_CEN; 
	 
	/* Enable TIM Interrupt*/
	
	TIM6->DIER |= DIER_UIE; 
	TIM7->DIER |= DIER_UIE;
	
	/* Enable TIM in NVIC */
	
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
	
	NVIC_EnableIRQ(TIM7_IRQn);

	
}
