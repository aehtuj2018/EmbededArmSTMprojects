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

uint32_t sensor_value;
int main (void)
{

	/* Initialize ADC */
	pal_adc_init();

	start_conversion();

	while(1)
	{

		sensor_value = adc_read();
		printf("Sensor value: %d \n\r", (int)sensor_value);
	}
}

