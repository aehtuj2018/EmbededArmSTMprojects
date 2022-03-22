/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Abdi Tujuba
 * @brief          : ADC Single Conversion
 * Board 		   		 : STM NucleoBoard F446RE
 ******************************************************************************
 */

#include "stm32f4xx.h"
#include <stdint.h>
#include <stdio.h>
#include "adc.h"
#include "uart.h"

void ADC_IRQHandler(void);
static void ADC_callback (void); 

uint32_t sensor_value;
int main (void)
{

	/* Initialize ADC */
	//pal_adc_init();
	uart2_tx_init();
	pal_adc_interrupt_init();
	start_conversion();
	
	
	while(1)
	{
	
		
	}
}

static void ADC_callback (void)
{
	// printf("Sensor value: %d \n\r", (int)sensor_value);
	sensor_value = ADC1->DR; 
	printf("Sensor value: %d \n\r", (int)sensor_value);	
	
}
void ADC_IRQHandler(void)
{
	//********  Check for End of Conversion in SR ****************/
	if((ADC1->SR & SR_EOC)!= 0)
	{
		//***** Clear EOC ***********//
		ADC1->SR &= ~SR_EOC; 
		ADC_callback();
			
	}
	
}
