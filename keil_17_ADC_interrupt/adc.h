#include "stm32f4xx.h"                  // Device header
#include <stdint.h>

void 				pal_adc_init(void);
void 				start_conversion(void); 
uint32_t 		adc_read(void);	
void 				pal_adc_interrupt_init(void);
void 				pal_adc_interrupt_init(void);
#define 		SR_EOC (1U<<1)
extern uint32_t sensor_value;
