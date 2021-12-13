/*
 * systick.c
 *
 *  Created on: Dec. 13, 2021
 *      Author: abdit
 */

#include "stm32f4xx.h"

#define SYSTICK_LOAD_VAL    16000  // 1ms delay => Delay = ()/ SYS_FREQ , where SYS_FREQ = (16000000)
#define CTRL_ENABLE  		(1U<<0)
#define CRTL_CLKSRC			(1U<<2)
#define CTRL_COUNTFLAG		(1U<<16)



void systickDelayMs(int delay)
{
	/************* Configure systick *****************/
	/* Reload with number of clocks per milisecond */
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	/* Clear systick current value*/

	SysTick ->VAL = 0;

	/* Enable systick and select internal clk src*/

	SysTick->CTRL = CTRL_ENABLE | CRTL_CLKSRC;

	for (int i=0; i < delay; i++)
	{
		/* wait until the count flag is set */

		while ((SysTick->CTRL & CTRL_COUNTFLAG) == 0) {}

	}

	SysTick->CTRL = 0;
}
