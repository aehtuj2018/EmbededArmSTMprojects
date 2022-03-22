/*
 * adc.h
 *
 *  Created on: Dec. 13, 2021
 *      Author: abdit
 */


#ifndef ADC_H_
#define ADC_H_
#include <stdint.h>
void pal_adc_init(void);
uint32_t adc_read(void);
void start_conversion(void);


#endif /* ADC_H_ */
