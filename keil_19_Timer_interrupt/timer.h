
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
void tim2_1hz_init(void);
void tim2_1hz_interrupt_init(void);
#define SR_UIF  (1U<<0)

#endif /* TIM_H_*/
