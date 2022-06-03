#include "stm32f4xx.h"                  // Device header

void adxl_read_address(uint8_t reg);
void adxl_write_address(uint8_t reg, char value); 
void adxl_init(void);
void adxl_read_values(uint8_t reg); 


#define DEVID_R    						0x00
#define POWER_CTL 						0x2D
#define DATA_FORMAT 					0x31
#define DATA									0x32
