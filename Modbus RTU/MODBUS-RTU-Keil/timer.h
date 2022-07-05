
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
void tim_6_7_1hz_init(void);


#define TIMER6EN					(1U<<4)
#define TIMER7EN					(1U<<5)
#define CR1_CEN						(1U<<0)
#define DIER_UIE    			(1U<<0)

#define SR_UIF  (1U<<0)

#endif /* TIM_H_*/
