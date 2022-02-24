#include "adxl345.h"
#include "i2c.h"
#include "uart.h"

void adxl_read_address(uint8_t reg); 
void adxl_write(uint8_t reg , char value);
void adxl_read_values(uint8_t reg);
void adxl_init (void);

char* data;
//uint8_t data_rec[6]; 
uint8_t data_rec[24]; 

void adxl_read_address(uint8_t reg)
{
	I2C1_byteRead(DEVICE_ADDR,reg,&data);
}

void adxl_write(uint8_t reg , char value)
{
	char datac[1];
	data[0]= value; 
	
	I2C1_burstWrite (DEVICE_ADDR, reg, 1, datac);

}

void adxl_read_values(uint8_t reg)
{
	I2C1_burstRead (DEVICE_ADDR, reg, 24, (char*)data_rec);
}

void adxl_init (void)
{
	/* Enable I2C*/
	
	 I2C1_init();
	
	/* Read the DEVID, this should return 0x68*/
	
	adxl_read_address(WHO_AM_I); 
	
	/* Set the data format rate to +/- 4g*/
	
	adxl_write(ACCEL_CONFIG,FOUR_G); 
	
	/* Reset all bits */
	
	adxl_write(PWR_MGMT_1,RESET); 
	
	/* Configure power control measure bit*/
	
	adxl_write(PWR_MGMT_1,SET_MEASURE_B); 
	
	// 1. check if the sensor is responding by reading the “WHO_AM_I (0x75)” Register (Should retun 0x68)

	// 2. wake the sensor up and in order to do that we will write to the “PWR_MGMT_1 (0x6B)” Register (sensor wakes up and the Clock sets up to 8 MHz)	
	
	// 3. set the Data output Rate or Sample Rate. This can be done by writing into “SMPLRT_DIV (0x19)” Register
	     //(to get the sample rate of 1KHz, we need to use the SMPLRT_DIV as ‘7’)
	
	
	// Writing (0x01) to both of these registers would set the Full scale range of ± 2g in ACCEL_CONFIG
	

	
}
