#include "i2c.h"

#define  DEVICE_ADDR  									(0x68)         			// Device Address 
#define  DATA_START_ADDR								(0x3B)              // Data Start Address
#define  I2C_SLV0_ADDR									(0x37)              // RW and Address 
#define  I2C_SLV0_REG										(0x38)							// REG - Data transfer starts at this address 
#define  I2C_SLV0_CTRL									(0x39)							// LEN - number of bytes transferred , EN - Enable Slave ),SW - Byte Swapping
#define  EXT_SENS_DATA									(0x49)   						// External Sensor Data Read write 
#define  WHO_AM_I 											(0x75)							// SLAVE ADDRESS
#define  PWR_MGMT_1											(0x6B)

#define  	FOUR_G													(0x01)
#define  	RESET 													(1U<<7)
#define  	SET_MEASURE_B										(0x08)		
#define   ACCEL_CONFIG										(0x1C)           //Data Format +/- 2g, 4g, 8g, 16g  
#define   FOUR_G_SCALE_FACT 							(65.5)
void adxl_init (void);
void adxl_read_values(uint8_t reg);
void adxl_write(uint8_t reg , char value);
void adxl_read_address(uint8_t reg);