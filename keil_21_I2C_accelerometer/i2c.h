
/**
 *	Keil project for I2C 
 *
 *  Before you start, select your target, on the right of the "Load" button
 *
 *	@author		Abdi TUJUBA
 *	@email		abdi.tujuba.86@gmail.com
 *	@ide			Keil uVision 5
 *	@packs		STM32F4xx Keil packs version 2.2.0 or greater required
 */
 
#include "stm32f4xx.h"                  // Device header
 
void I2C1_init(void);
void I2C1_byteRead (char sadd, char maddr, char* data);
void I2C1_burstRead (char saddr, char maddr, int n, char* data); 
void I2C1_burstWrite (char saddr, char maddr, int n, char* data);
