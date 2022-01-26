/**
 ******************************************************************************
 * @file           : adc.c
 * @author         : Abdi Tujuba
 * @brief          : ADC Continueous Conversion 
 * Board 		   		 : STM NucleoBoard F446RE
 ******************************************************************************
 */
#include "stm32f4xx.h"                  // Device header
#include "adc.h"

#define GPIOAEN 						(1U<<0)
#define ADC1EN							(1U<<8)

#define ADC_CH1       			(1U<<0)
#define ADC_SEQ_LEN_1  			 0x00
#define CR2_ADON         		(1U<<0)

#define CR2_CONT						(1U<<1)
#define CR2_SWSTART					(1U<<30)

#define CR1_EOCIE 					(1U<<5)
 void pal_adc_init(void );
 void start_conversion(void );
 uint32_t adc_read(void );
 void pal_adc_interrupt_init(void );
 
  void pal_adc_interrupt_init()
	{
 /* Initialize ADC */
 
 	 //****************   Configure the ADC GPIO pin  ***********//
		RCC->AHB1ENR |= GPIOAEN; 
	  	 
	 //***************  Set PA1 to Analog *********************//
	  GPIOA->MODER |= (1U<<2);
	  GPIOA->MODER |= (1U<<3); 
	 
	 //************ Configure ADC Module **********************//
	 //************ Enable clock Access to ADC ****************//
	 
	 RCC->APB2ENR |= ADC1EN;
	 
	 //************  Enable ADC End of Conversion Intterupt ***********//
		
		ADC1->CR1 |= CR1_EOCIE; 
		
		//**************  Enable ADC Interrupt in NVIC ******************//
		
		NVIC_EnableIRQ(ADC_IRQn);
		
	 //********** Configure ADC parameters *****************//
	 //********** conversion sequence start ****************//
	 
	 ADC1->SQR3 |= ADC_CH1; 
	 
	 // **************** Conversion Sequence length ********//
	 ADC1->SQR1 = ADC_SEQ_LEN_1;
	 
	 //************* Enable ADC **************************//
	 ADC1->CR2 |= CR2_ADON;
 }
 
 void pal_adc_init()
 {
	 //****************   Configure the ADC GPIO pin  ***********//
		RCC->AHB1ENR |= GPIOAEN; 
	  	 
	 //***************  Set PA1 to Analog *********************//
	  GPIOA->MODER |= (1U<<2);
	  GPIOA->MODER |= (1U<<3); 
	 
	 //************ Configure ADC Module **********************//
	 //************ Enable clock Access to ADC ****************//
	 
	 RCC->APB2ENR |= ADC1EN;
	 
	 
	 //********** Configure ADC parameters *****************//
	 //********** conversion sequence start ****************//
	 
	 ADC1->SQR3 |= ADC_CH1; 
	 
	 // **************** Conversion Sequence length ********//
	 ADC1->SQR1 = ADC_SEQ_LEN_1;
	 
	 //************* Enable ADC **************************//
	 ADC1->CR2 |= CR2_ADON; 
 }
 
 void start_conversion()
 {
	 //********* Enable continuous conversion Mode **********//
	 ADC1->CR2 |=CR2_CONT; 
	 //**********  Start the ADC Conversion *****************//
	 ADC1->CR2 |= CR2_SWSTART; 		 
 }
 
 /*uint32_t adc_read(void)
 {
	 while(!(ADC1->SR & SR_EOC)) {}
		 
	// read converted result  	 
	return ADC1->DR; 
}*/
