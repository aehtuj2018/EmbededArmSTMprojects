/**
 *	Keil project for UART_TX 
 *
 *  Before you start, select your target, on the right of the "Load" button
 *
 *	@author		Abdi TUJUBA
 *	@email		abdi.tujuba.86@gmail.com
 *	@ide			Keil uVision 5
 *	@packs		STM32F4xx Keil packs version 2.2.0 or greater required
 */

#ifndef GPIO_H_
#define GPIO_H_
#include <stdint.h>

#include "stm32f4xx.h"

void gpio_init(void); 
void TURN_LED_ON(void);
void TURN_LED_OFF(void);

#endif /* GPIO_H_ */


