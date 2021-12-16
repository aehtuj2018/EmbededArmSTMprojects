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

	tim2_pa5__Output_compare();

	while(1)
	{
	}
}

