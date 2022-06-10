#include "adxl345.h"
#include <stdint.h>
#include "spi.h"

#define MULTI_BYTE_EN 						0x40
#define READ_OPERATION						0x80

//static char data;
//static uint8_t data_rec[6];


void adxl_read_address(uint8_t address, uint8_t * rxdata)
{
	//uint8_t data[2]; 
	
	/* Set read operation */
	address |= READ_OPERATION; 
	/* Enable multi-byte*/
	address|= MULTI_BYTE_EN;

	
		/*pull cs line low to enable slave*/
	cs_enable(); 
	
	/* send address */
	
	spi1_transmit(&address,1); 
	
	/* read 6 bytes */ 
	
	spi1_receive(rxdata,6); 
	
	/* pull cs line high to disable slave */
	cs_disable();
	
}

void adxl_write(uint8_t address, uint8_t value)
{
	uint8_t data[2]; 
	
	/* Enable multi-byte, place address into buffer */
	data[0] = address| MULTI_BYTE_EN; 
	
	/* place data into buffer */
	data[1]= value; 
	
	/*pull cs line low to enable slave*/
	cs_enable(); 
	
	/* Transmit data and address */ 
	
	spi1_transmit(data,2); 
	
	/* pull cs line high to disable slave */
	cs_disable(); 
}



void adxl_init(void)
{
	/* Enable SPI GPIO*/
	
	spi_gpio_init();
 
	/* Config SPI*/
	
	spi1_config(); 
	
		
	//printf("Devide Slve Address: %x",adxl_read_address(DEVID_R)); 
	
	/* Read Device ID , this should read 0xE5 */
	
		//adxl_read_address(DEVID_R); 
	
	/* Set data format range to +/- 4g*/
	
	adxl_write (DATA_FORMAT_R, FOUR_G);
	
	/* Reset all bits  */
	adxl_write(POWER_CTL_R, RESET); 
	
	/* Control power control measure bit */
	
	adxl_write(POWER_CTL_R, SET_MEASURE_B); 
	
}
