/*
 * adc.h
 *
 *  Created on: Dec. 13, 2021
 *      Author: abdit
 */


#ifndef ADC_H_
#define ADC_H_
#include <stdint.h>

void pal_adc_interrupt_init(void);
void pal_adc_init(void);
uint32_t adc_read(void);
void start_conversion(void);

#define SR_EOC         	(1U<<1)

#endif /* ADC_H_ */
