
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

#include "mpu6050.h"
#include "i2c.h"
#include "uart.h"

static uint8_t data_rec[6]; 
static char data; 

void mpu6050_read_address (uint8_t reg); 
void mpu6050_write (uint8_t reg, char value); 
void check_device(uint16_t sadd);
void mpu6050_read_values(uint8_t reg);



void mpu6050_read_address (uint8_t reg)
{
	I2C1_byteRead (MPU_SLAVE_ADDR, reg, &data);
	//printf(" WHO AM I %x",I2C1_byteRead (DEVICE_ADDR, WHO_AM_I_MPU6050, &data); 
}


void mpu6050_write (uint8_t reg, char value)
{
	char datas[1];
	datas[0] = value; 
	
	//I2C1_byteRead (DEVICE_ADDR, reg, &data);
	I2C1_burstWrite(MPU_SLAVE_ADDR,reg,1,datas);
}

void check_device(uint16_t sadd)
{
	mpu6050_read_address (WHO_AM_I_MPU6050);
	if( data == sadd)
		printf("Device Found %x\r\n", data	); 
	
}

void mpu6050_read_values(uint8_t reg)
{
	I2C1_burstRead(MPU_SLAVE_ADDR, reg,6,(char *)data_rec);
}

void mpu6050_init(void)
{
	/* Enable I2C*/
	
	I2C1_init(); 
	
	/* Read the DEVID, this should return 0x6B*/
	  
		mpu6050_read_address (WHO_AM_I_MPU6050);
	
	/*Set gthe data format range to +/- 4g */
	
			mpu6050_write (ACCEL_CONFIG,AFS_SEL_FOUR_G);
	
	/*reset all bits */
	
	mpu6050_write (PWR_MGMT_1,PWR_MGMT_1_RESET);
	
	
	/* configure power control measure bits */
	
	mpu6050_write (PWR_MGMT_1,PWR_MGMT_1_CYCLE);
	
}