#include "i2c.h"

#define  DEVID_R  											(0x00)         			// Device Register 
#define  DEVICE_ADDR										(0x53)							// Device Address
#define  DATA_FORMAT_R 									(0x31)              // Data Format 
#define  POWER_CTL_R										(0x2D)              // Power Control 
#define  DATA_START_ADDR								(0x32)							// Data Start Address  

#define  	FOUR_G												(0x01)
#define  	RESET 												(0x00)
#define  	SET_MEASURE_B									(0x08)		

#define   ACCEL_CONFIG									(0x1C)           //Data Format +/- 2g, 4g, 8g, 16g  
#define   FOUR_G_SCALE_FACT 						(65.5)

void adxl_init (void);
void adxl_read_values(uint8_t reg);
void adxl_write(uint8_t reg , char value);
void adxl_read_address(uint8_t reg);


extern  uint8_t data_rec[6]; 
