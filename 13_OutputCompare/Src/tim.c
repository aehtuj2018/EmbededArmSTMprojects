/*
 * tim.c
 *
 *  Created on: Dec. 15, 2021
 *      Author: abdit
 */


#include "stm32f4xx.h"

#define TIM2EN					(1U<<0)
#define CR1_CEN 				(1U<<0)
#define OC_TOGGLE				(1U<<4) | (1U<<5)
#define CCER_CC1E     			(1U<<0)

#define GPIOAEN 				(1U<<0)
#define AFR5_TIM				(1U<<20)

/*Timer 2 Initialize */
void tim2_1hz_init(void)
{
	/* Enable clock access to Timer2*/
	RCC->APB1ENR |= TIM2EN;

	/*Set prescaler value*/

	TIM2->PSC = 1600 - 1; //  16 000 000 / 1 600 = 10 000

	/*set auto-reload value */
	TIM2-> ARR = 10000 - 1; // 10 000/ 10 000 = 1;

	/*Clear Counter*/

	TIM2->CNT = 0;

	/*Enable Timer */

	TIM2->CR1 |= CR1_CEN;

}


void tim2_pa5__Output_compare(void)
{
	/* Enable clock access to GPIOA */

	RCC->AHB1ENR |= GPIOAEN;

	/* Set PA5 mode to alternate function */
	GPIOA->MODER &= ~(1U<<10);
	GPIOA->MODER |=  (1U<<11);

	/* SER PA5 alternate function type to TIM2_CH1 (AF01) */
	GPIOA->AFR[0] |= AFR5_TIM;


	/* Enable clock access to Timer2*/
	RCC->APB1ENR |= TIM2EN;

	/*Set prescaler value*/

	TIM2->PSC = 1600 - 1; //  16 000 000 / 1 600 = 10 000

	/*set auto-reload value */
	TIM2-> ARR = 10000 - 1; // 10 000/ 10 000 = 1;


	/* Set output compare toggle mode */


	TIM2->CCMR1 = OC_TOGGLE  ;


	/* Enable timer2 ch1 in compare mode */

	TIM2->CCER |= CCER_CC1E;


	/*Clear Counter*/

	TIM2->CNT = 0;

	/*Enable Timer */

	TIM2->CR1 |= CR1_CEN;

}
