/*
 * adc.c
 *
 *  Created on: Dec. 13, 2021
 *      Author: Abdi Tujuba
 *      Project: ADC EOC with Intterupt
 *      Board: STM32F446RE - Nucleoboard
 *
 */
#include "stm32f446xx.h"

#include "adc.h"

#define GPIOAEN 		(1U<<0)
#define ADC1EN 			(1U<<8)
#define ADC_CH1			(1U<<0)
#define ADC_SEQ_LEN_1    0x00
#define CR2_ADON 		(1U<<0)
#define CR2_SWSTART		(1U<<30)

#define CR2_CONT        (1U<<1)
#define CR1_EOCIE		(1U<<5)


void pal_adc_interrupt_init(void)
{
	/**************** Configure the ADC GPIO pin ***********/


	RCC->AHB1ENR |= GPIOAEN;


	/************** Set the mode PA1 to analog *****************/

	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);


	/**************** Configure the ADC module ********************/
	/************* Enable clock access to ADC ********************/

	RCC->APB2ENR |= ADC1EN;

	/* Enable  ADC end-of-conversion Interrupt */

	ADC1->CR1 |= CR1_EOCIE;

	/* Enable ADC interrupt in NVIC */

	NVIC_EnableIRQ(ADC_IRQn);


	/**************** Configure ADC parameters  ***********/

	/********** conversion sequence start ****************/

	ADC1->SQR3 = ADC_CH1;

	/********** conversion sequence length ****************/
	ADC1->SQR1 = ADC_SEQ_LEN_1;



	/********** Enable ADC *********************/
	ADC1->CR2 |= CR2_ADON;
}



void pal_adc_init(void)
{
	/**************** Configure the ADC GPIO pin ***********/

	RCC->AHB1ENR |= GPIOAEN;


	/************** Set the mode PA1 to analog *****************/

	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);


	/**************** Configure the ADC module ********************/
	/************* Enable clock access to ADC ********************/

	RCC->APB2ENR |= ADC1EN;


	/**************** Configure ADC parameters  ***********/

	/********** conversion sequence start ****************/

	ADC1->SQR3 = ADC_CH1;

	/********** conversion sequence length ****************/
	ADC1->SQR1 = ADC_SEQ_LEN_1;

	/********** Enable ADC *********************/
	ADC1->CR2 |= CR2_ADON;
}


void start_conversion(void)
{
	/*Enable Continous conversion */
	ADC1->CR2 |= CR2_CONT;
	/* start the ADC conversion */
	ADC1->CR2 |= CR2_SWSTART;
}


uint32_t adc_read(void)
{
	/* wait for conversion to be complete */

	while (!(ADC1->SR & SR_EOC)) {}

	/* read converted result */

	return ADC1->DR;
}
