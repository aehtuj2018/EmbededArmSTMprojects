

/**
 *	Keil project for UART_TX 
 *
 *  Before you start, select your target, on the right of the "Load" button
 *
 *	@author		Abdi TUJUBA
 *	@email		abdi.tujuba.86@gmail.com
 *	@ide			Keil uVision 5
 *	@packs		STM32F4xx Keil packs version 2.2.0 or greater required
 *	@project  USART/UART Transmit and Recive Driver + Control LED with UART TX
 */
 
#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "uart.h"
#include "gpio.h"
#include "adxl345.h"

static int16_t x; //,y,z;
static float xg;// , yg, zg;
extern uint8_t data_rec[24];
int main (void)
{

	adxl_init();

	while(1)
	{
		
		adxl_read_values(DATA_START_ADDR);
		x = (int16_t) ((data_rec[1]<<8)| data_rec[0]); 
		//y = ((data_rec[3]<<8)| data_rec[2]);
		//z = ((data_rec[5]<<8)| data_rec[4]);
		
		xg = (float) x * FOUR_G_SCALE_FACT; 
	}
}

