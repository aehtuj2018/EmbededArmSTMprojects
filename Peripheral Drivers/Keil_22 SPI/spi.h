#include "stm32f4xx.h"                  // Device header

#include <stdint.h>


void cs_enable(void);
void cs_disable(void);

void spi_gpio_init(void);
void spi1_config(void); 

void spi1_transmit(uint8_t *data, uint32_t size);
void spi1_receive (uint8_t *data, uint8_t size);
