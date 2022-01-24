/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Abdi Tujuba
 * @brief          : GPIO - Driver
 ******************************************************************************
 */

#include "stm32f446xx.h"
#include <stdint.h>
#include <stdio.h>
#include "adc.h"

uint32_t sensor_value;
static void adc_callback(void);


int main (void)
{

	/* Initialize ADC */
	//pal_adc_init();
	pal_adc_interrupt_init();

	start_conversion();

	while(1)
	{

	}
}

static void adc_callback(void)

{

	sensor_value = ADC1->DR;
	//printf("Sensor value: %d \n\r", (int)sensor_value);


}


void ADC_IRQHandler (void)
{
	/* check for end of conversion in SR */


	if((ADC1->SR & SR_EOC)!=0)
	{
		/* clear EOC flag */
		ADC1->SR &= ~ SR_EOC;

		// Do something
		adc_callback();
	}
}
