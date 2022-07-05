#include "stm32f4xx.h"                  // Device header
#include "uart.h"
#include "spi.h"
#include <stdint.h>
#include "adxl345.h"

static int16_t x,y,z;
static double xg,yg,zg;
static uint8_t datarec[6]; 



int main(void)
{
	adxl_init();
	usart2_init();
	
	printf(" Value to read address\n\r"); 
	
	while(1)
	{
	adxl_read_address(DATA_START_ADDR,datarec);
	
	x = (int16_t) ((datarec[1]<<8)| datarec[0]);
	y = (int16_t) ((datarec[3]<<8)| datarec[2]);
	z = (int16_t) ((datarec[5]<<8)| datarec[4]);
	
	
	yg = (y * 0.0078);
	zg = (z * 0.0078);
	xg = (x * 0.0078);
		
	printf("xg %f\n\r",xg);
	printf("yg %f\n\r",yg);
	printf("zg %f\n\r",zg);
	}
	return 0; 
}
