#include "adxl345.h"
#include <stdint.h>
#include "spi.h"

static char data;
static uint8_t data_rec[6];

void adxl_read_address(uint8_t reg)
{

}

void adxl_write_address(uint8_t reg, char value)
{

}

void adxl_read_values(uint8_t reg)
{
	
}

void adxl_init(void)
{
	
	spi1_config(); 
	
	/* Read Device ID , this should read 0xE5 */
	
	printf("Devide Slve Address: %x",adxl_read_address(DEVID_R)); 
	
}
