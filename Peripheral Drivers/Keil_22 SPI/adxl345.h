

#include "stm32f4xx.h"                  // Device header
#include "spi.h"
#include <stdint.h>

#define DEVID_R    						(0x00)
#define POWER_CTL_R						(0x2D)
#define DATA_FORMAT_R					(0x31)
#define FOUR_G								(0x01)

#define DATA_START_ADDR				(0x32)
#define RESET								 	(0x00)
#define SET_MEASURE_B					(0x08)


void adxl_init(void);
void adxl_write(uint8_t address, uint8_t value);
void adxl_read_address(uint8_t address, uint8_t *rxdata);

