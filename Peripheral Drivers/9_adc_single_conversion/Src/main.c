/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Abdi Tujuba
 * @brief          : ADC Single Conversion
 * Board 		   :  Discovery Board
 ******************************************************************************
 */

#include "stm32f4xx.h"
#include <stdint.h>
#include <stdio.h>
#include "adc.h"

uint32_t sensor_value;
int main (void)
{

	/* Initialize ADC */
	pal_adc_init();


	while(1)
	{
		start_conversion();
		sensor_value = adc_read();
		printf("Sensor value: %d \n\r", (int)sensor_value);
	}
}

