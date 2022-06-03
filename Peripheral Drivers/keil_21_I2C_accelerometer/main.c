

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
#include "mpu6050.h"

static int16_t x; //,y,z;
//static float xg;// , yg, zg;
extern uint8_t data_rec[6];
int main (void)
{

	uart2_tx_init(); 
	mpu6050_init(); 

	while(1)
	{
		
		printf("Printf is good\n\r"); 
		
		//check_device(MPU_SLAVE_ADDR);
		
		mpu6050_read_values(GYRO_XOUT_H);
		x = (int16_t) ((data_rec[1]<<8)| data_rec[0]); 
		//y = ((data_rec[3]<<8)| data_rec[2]);
		//z = ((data_rec[5]<<8)| data_rec[4]);
		
		//xg = (float) x * FOUR_G_SCALE_FACT; 
	}
}

