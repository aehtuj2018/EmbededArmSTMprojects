/*
 * tim.h
 *
 *  Created on: Dec. 15, 2021
 *      Author: abdit
 */

#ifndef TIM_H_
#define TIM_H_
#define SR_UIF    (1U<<0)
void tim2_1hz_init(void);
void tim2_pa5__Output_compare(void);
void tim3_pa6_input__capture(void);
#endif /* TIM_H_ */