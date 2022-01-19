
/**
 *	Keil project for General Purpose Timer 
 *
 *  Before you start, select your target, on the right of the "Load" button
 *
 *	@author		Abdi TUJUBA
 *	@email		abdi.tujuba.86@gmail.com
 *	@ide			Keil uVision 5
 *	@packs		STM32F4xx Keil packs version 2.2.0 or greater required
 *  @Project 	General Purpose Timer Driver 
 */

#ifndef TIMER_H_
#define TIMER_H_
#include <stdint.h>
void tim2_1hz_init(void);
void tim2_PA5_output_compare(void);
void tim3_PA6_input_capture(void);
extern uint32_t time_stamp;

#define SR_UIF  			(1U<<0)
#define SR_CC1IF 			(1U<<0)

#endif /* TIM_H_*/
