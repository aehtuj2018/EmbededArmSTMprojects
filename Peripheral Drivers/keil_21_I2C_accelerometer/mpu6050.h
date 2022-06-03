
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
#include "i2c.h"

#define PWR_MGMT_1 											0x6B 		// Power Management 1 

#define CONFIG           								0x1A
#define GYRO_CONFIG      								0x1B
#define ACCEL_CONFIG     								0x1C

#define GYRO_XOUT_H      								0x43
#define GYRO_XOUT_L      								0x44
#define GYRO_YOUT_H      								0x45
#define GYRO_YOUT_L      								0x46
#define GYRO_ZOUT_H      								0x47
#define GYRO_ZOUT_L      								0x48

#define ACCEL_XOUT_H     								0x3B
#define ACCEL_XOUT_L     								0x3C
#define ACCEL_YOUT_H     								0x3D
#define ACCEL_YOUT_L     								0x3E
#define ACCEL_ZOUT_H     								0x3F
#define ACCEL_ZOUT_L     								0x40
#define WHO_AM_I_MPU6050 								0x75 		// Should return 0x68

#define MPU_SLAVE_ADDR									0x68

#define AFS_SEL_FOUR_G 									(1U<<3)
#define PWR_MGMT_1_RESET						    (1U<<7)								
#define PWR_MGMT_1_CYCLE						    (1U<<5)

void mpu6050_init(void);
void mpu6050_read_values(uint8_t reg);
void check_device(uint16_t sadd);