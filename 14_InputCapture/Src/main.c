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

int timestamp = 0 ;

/* Setup : Connect a jumper wire from PA5 to PA6 */

int main (void)
{


	tim2_pa5__Output_compare();
	tim3_pa6_input__capture();

	while(1)
	{

		/* wait until edge is captured */

		while (!(TIM3->SR & SR_CC1IF)) {}

		/* Read value */

		timestamp = TIM3->CCR1 ;
	}
}

