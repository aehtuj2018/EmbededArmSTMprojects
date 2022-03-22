
/**
 *	Keil project for EXTINTERRUPT_H_
 *
 *  Before you start, select your target, on the right of the "Load" button
 *
 *	@author		Abdi TUJUBA
 *	@email		abdi.tujuba.86@gmail.com
 *	@ide			Keil uVision 5
 *	@packs		STM32F4xx Keil packs version 2.2.0 or greater required
 */

#ifndef EXTINTERRUPT_H_
#define EXTINTERRUPT_H_
#include <stdint.h>
#include "stm32f4xx.h"
void pc13_extinterrupt_init(void);

#define LINE13        (1U<<13)

#endif /* EXTINTERRUPT_H_ */
