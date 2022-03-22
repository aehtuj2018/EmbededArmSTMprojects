#include "stm32f4xx.h"                  // Device header

void 				pal_adc_init(void);
void 				start_conversion(void); 
uint32_t 		adc_read(void);	
#define 		SR_EOC (1U<<1)
