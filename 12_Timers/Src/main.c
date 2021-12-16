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
#include "tim.h"

#define GPIOAEN         (1U<<0)
#define GPIOGEN  		(1U<<6)
#define PIN14			(1U<<14)

#define LED_PIN			PIN14

int main (void)
{


	/*Enable clock access to GPIOG*/
	RCC->AHB1ENR |= GPIOGEN;


	/* Set PIN14 as output, LED  */
	GPIOG->MODER |= (1U<<28);
	GPIOG->MODER &= ~ (1U<<29);


	tim2_1hz_init();

	while(1)
	{


		/* Wait  for UIF */
		while(!(TIM2->SR & SR_UIF)) {}

		/*Clear UIF*/

		TIM2->SR &= ~ SR_UIF;

		/* Toggle LED */

		GPIOG->ODR ^= LED_PIN;


	}
}

